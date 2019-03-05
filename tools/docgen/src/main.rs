use clang::source::SourceRange;
use clang::token::{Token, TokenKind};
use clang::*;
use clap::{crate_name, crate_version, App, Arg};
use regex::Regex;

use std::fs::{self, File};
use std::io::{self, Write};
use std::path::{Path, PathBuf};

const LUADOC: &str = "@luadoc";
const LUA_API: &str = "LuaApi";
const LUA_CLASS: &str = "Lua";
const VARARGS: &str = "sol::variadic_args";

#[derive(Debug, Clone)]
struct ModuleComment {
    is_class: bool,
    text: String,
    module: String,
}

impl ModuleComment {
    pub fn from_entity<'a>(entity: &Entity<'a>, text: String, is_class: bool) -> Self {
        let name = entity.get_name().unwrap();
        let mut trimmed_name = name
            .trim_start_matches(LUA_API)
            .trim_start_matches(LUA_CLASS)
            .into();

        if is_class {
            trimmed_name = format!("Lua{}", trimmed_name);
        }
        ModuleComment {
            is_class: is_class,
            text: text,
            module: trimmed_name,
        }
    }

    pub fn import_comment(&self) -> String {
        if self.is_class {
            format!("--  @classmod {}", self.module)
        } else {
            format!(
                "--  @usage local {0} = Elona.require(\"{0}\")\nmodule \"{0}\"",
                self.module
            )
        }
    }
}

#[derive(Debug, Clone)]
struct FunctionContent {
    name: String,
    args: Vec<String>,
}

impl FunctionContent {
    pub fn signature(&self) -> String {
        format!(
            "--  @function {0}\nfunction {0}({1}) end",
            self.name,
            self.args.join(", ")
        )
    }
}

#[derive(Debug, Clone)]
struct FieldContent {
    name: String,
    type_: String,
}

impl FieldContent {
    pub fn signature(&self) -> String {
        format!("--  @tfield {} {}", self.type_, self.name)
    }
}

#[derive(Debug, Clone)]
struct EnumContent {
    name: String,
    entries: Vec<String>,
}

impl EnumContent {
    pub fn entries(&self) -> String {
        let mut s = String::new();
        s.push_str(&format!("--  @enum {}\n", self.name));
        for e in self.entries.iter() {
            s.push_str(&format!("--  @tfield Enums.{} {}\n", self.name, e));
        }
        s.push_str(&format!("{} = {{}}", self.name));
        s
    }
}

fn get_range<'a>(tu: &'a TranslationUnit<'a>, path: &Path) -> SourceRange<'a> {
    let clang_file = tu.get_file(path).unwrap();
    let size = fs::metadata(path).unwrap().len() as u32;
    let start = clang_file.get_offset_location(0);
    let end = clang_file.get_offset_location(size);
    SourceRange::new(start, end)
}

const ENUM_MAP: &str = "EnumMap";

enum EnumParseState {
    None,
    Comment,
    TypeName,
    Entries,
}

// clang-rs doesn't appear to provide anything below VarDecl to get at
// the initializer lists, so step through the tokenized source
// directly.
fn extract_enums<'a>(tu: &'a TranslationUnit<'a>, path: &Path) -> Vec<Comment> {
    let mut state = EnumParseState::None;
    let mut braces_left = 0;
    let mut entries = Vec::new();
    let mut comment = String::new();
    let mut name = String::new();
    let mut results = Vec::new();

    let strip_quotes = |t: &Token<'a>| t.get_spelling().trim_matches('\"').into();

    for t in get_range(&tu, path).tokenize() {
        match state {
            EnumParseState::TypeName => {
                if t.get_kind() == TokenKind::Identifier {
                    name = strip_quotes(&t);
                    state = EnumParseState::Entries;
                    // Skip the next 3 opening braces.
                    // EnumMap<Type> Map { "Map", {{ "Member", Type::Member }, ...}};
                    //                   ^        ^^ ~~~~~~~~
                    braces_left = 3;
                }
            }
            EnumParseState::Comment => {
                if t.get_kind() == TokenKind::Identifier && t.get_spelling() == ENUM_MAP {
                    // Found "EnumMap", next identifier token should be type.
                    // EnumMap<Type> Map { ... };
                    // ^^^^^^^ ~~~~
                    state = EnumParseState::TypeName;
                }
            }
            EnumParseState::Entries => {
                if braces_left > 0 {
                    if t.get_kind() == TokenKind::Punctuation {
                        let s = t.get_spelling();

                        if s == ";" {
                            // End of definition.
                            state = EnumParseState::None;
                            braces_left = 0;

                            results.push(Comment {
                                text: comment,
                                module: "Enums".into(),
                                content: Content::Enum(EnumContent {
                                    name: name,
                                    entries: entries,
                                }),
                            });

                            comment = String::new();
                            name = String::new();
                            entries = Vec::new();
                        } else if s == "{" {
                            braces_left -= 1
                        }
                    }
                } else {
                    if t.get_kind() == TokenKind::Literal {
                        entries.push(strip_quotes(&t));
                        // Skip the next open brace.
                        // { "First", Type::First }, { "Second", Type::Second }
                        //                           ^ ~~~~~~~~
                        braces_left = 1;
                    }
                }
            }
            EnumParseState::None => {
                if t.get_kind() == TokenKind::Comment {
                    if let Some((comment_, _)) = strip_comment(&t.get_spelling()) {
                        comment = comment_;
                        state = EnumParseState::Comment;
                    }
                }
            }
        }
    }

    results
}

#[derive(Debug, Clone)]
enum Content {
    Function(FunctionContent),
    Field(FieldContent),
    Enum(EnumContent),
}

#[derive(Debug, Clone)]
struct Comment {
    text: String,
    module: String,
    content: Content,
}

#[derive(Debug, Clone, PartialEq, Eq)]
enum CommentKind {
    Function,
    Field,
    Enum,
    Unknown,
}

impl From<EntityKind> for CommentKind {
    fn from(other: EntityKind) -> CommentKind {
        match other {
            EntityKind::FunctionDecl => CommentKind::Function,
            EntityKind::VarDecl => CommentKind::Enum,
            _ => CommentKind::Unknown,
        }
    }
}

#[derive(Debug, Clone)]
struct Metadata {
    name: Option<String>,
    kind: Option<CommentKind>,
    type_: Option<String>,
}

impl Comment {
    pub fn from_entity<'a>(entity: &Entity<'a>, text: String, meta: Metadata) -> Self {
        let module = entity
            .get_semantic_parent()
            .unwrap()
            .get_name()
            .unwrap()
            .trim_start_matches(LUA_API)
            .into();

        let name = meta.name.unwrap_or(entity.get_name().unwrap());
        let kind = meta.kind.unwrap_or(CommentKind::from(entity.get_kind()));

        let content = match kind {
            CommentKind::Function => {
                let arg_entities = entity.get_arguments().unwrap();
                let mut args = arg_entities
                    .iter()
                    .map(|a| a.get_name().unwrap())
                    .collect::<Vec<String>>();

                let remove_self = match args.first() {
                    Some(first) => first == "self",
                    None => false,
                };
                if remove_self {
                    args.drain(0..1);
                }
                if let Some(last) = arg_entities.last() {
                    if last.get_type().unwrap().get_display_name() == VARARGS {
                        *args.last_mut().unwrap() = "...".into();
                    }
                }
                Content::Function(FunctionContent { name, args })
            }
            CommentKind::Field => {
                let type_ = meta.type_.expect("Fields must have a type declared.");
                Content::Field(FieldContent { name, type_ })
            }
            _ => unreachable!(),
        };

        Comment {
            text: text,
            module: module,
            content: content,
        }
    }

    pub fn from_token<'a>(text: String, meta: Metadata, module: &str) -> Self {
        let name = meta.name.unwrap_or(String::new());
        let kind = meta.kind.unwrap_or(CommentKind::Unknown);

        let content = if kind == CommentKind::Function {
            Content::Function(FunctionContent {
                name: name,
                args: Vec::new(),
            })
        } else {
            let type_ = meta.type_.expect("Fields must have a type declared.");
            Content::Field(FieldContent {
                name: name,
                type_: type_,
            })
        };

        Comment {
            text: text,
            module: module.into(),
            content: content,
        }
    }

    pub fn render(&self, writer: &mut Write) -> io::Result<()> {
        writer.write(to_lua_comment(&self.text).as_bytes())?;
        match &self.content {
            Content::Function(f) => writer.write(&f.signature().as_bytes()).map(|_| ())?,
            Content::Field(f) => writer.write(&f.signature().as_bytes()).map(|_| ())?,
            Content::Enum(f) => writer.write(&f.entries().as_bytes()).map(|_| ())?,
        }
        Ok(())
    }
}

#[derive(Debug, Clone)]
struct Document {
    module_comment: ModuleComment,
    comments: Vec<Comment>,
}

fn to_lua_comment(text: &str) -> String {
    let mut s = String::new();
    let mut long = true;

    for i in text.lines() {
        if long {
            s.push_str("--- ");
            long = false;
        } else if i.len() == 0 {
            s.push_str("--");
        } else {
            s.push_str("--  ");
        }
        s.push_str(i);
        s.push('\n');
    }

    s
}

impl Document {
    pub fn render<W: Write>(&self, writer: &mut W) -> io::Result<()> {
        writer.write(to_lua_comment(&self.module_comment.text).as_bytes())?;
        writer.write(self.module_comment.import_comment().as_bytes())?;

        for comment in self.comments.iter() {
            writer.write("\n\n".as_bytes())?;
            comment.render(writer)?;
        }

        Ok(())
    }
}

fn extract_metadata(text: &str) -> Metadata {
    let mut name: Option<String> = None;
    let mut kind: Option<CommentKind> = None;
    let mut type_: Option<String> = None;

    let stripped = text.trim_start_matches(LUADOC).trim();
    if !stripped.is_empty() {
        let mut parts = stripped.split(" ");
        if let Some(f) = parts.next() {
            name = Some(String::from(f));
        }
        if let Some(f) = parts.next() {
            kind = Some(match f {
                "function" => CommentKind::Function,
                "field" => CommentKind::Field,
                "enum" => CommentKind::Enum,
                _ => CommentKind::Unknown,
            });
        }
        if let Some(f) = parts.next() {
            type_ = Some(f.into());
        }
    }

    Metadata { name, kind, type_ }
}

fn strip_comment(text: &str) -> Option<(String, Metadata)> {
    let mut s = String::new();

    let mut parts = text.lines().skip(1).collect::<Vec<_>>();
    parts.pop();

    let re = Regex::new(r"^[ *]*(.*)").unwrap();
    let strip = |i| re.captures(i).and_then(|c| c.get(1)).unwrap().as_str();
    let mut meta: Metadata;

    match parts.first() {
        Some(st) => {
            let stripped = strip(st);
            if !stripped.starts_with(LUADOC) {
                return None;
            }
            meta = extract_metadata(&stripped);
        }
        _ => return None,
    }

    let mut reached = false;

    for i in parts.iter().skip(1) {
        let stripped = strip(i);
        if !reached && stripped.is_empty() {
            continue;
        }
        reached = true;
        s.push_str(stripped);
        s.push('\n');
    }

    s.pop();
    Some((s, meta))
}

fn get_comments_of_entity<'a>(entity: &Entity<'a>) -> Vec<Comment> {
    let mut result = Vec::new();

    if entity.get_kind() != EntityKind::Namespace {
        let location = entity.get_location().unwrap();
        if let Some(file) = location.get_file_location().file {
            if file.get_path().extension().map_or(false, |e| e == "cpp") {
                if let Some(comment) = entity.get_comment() {
                    if let Some((stripped, meta)) = strip_comment(&comment) {
                        if entity.get_kind() == EntityKind::FunctionDecl {
                            let comment = Comment::from_entity(entity, stripped, meta);
                            result.push(comment);
                        }
                    }
                }
            }
        }
    }

    for child in entity.get_children().iter() {
        let a = get_comments_of_entity(child);
        result.extend_from_slice(&a);
    }

    result
}

fn get_comments<'a>(tu: &'a TranslationUnit<'a>) -> Vec<Comment> {
    let mut result = Vec::new();

    for child in tu.get_entity().get_children().iter() {
        result.extend_from_slice(&get_comments_of_entity(child));
    }

    result
}

fn get_module_comment_of_entity<'a>(entity: &Entity<'a>, is_class: bool) -> Option<ModuleComment> {
    if entity.get_kind() == EntityKind::Namespace {
        let location = entity.get_location().unwrap();
        let file = location.get_file_location().file.unwrap();
        let name = entity.get_name().unwrap();
        if file.get_path().extension().map_or(false, |e| e == "hpp") {
            if let Some(comment) = entity.get_comment() {
                if let Some((stripped, _)) = strip_comment(&comment) {
                    if name.starts_with(LUA_API) || name.starts_with(LUA_CLASS) {
                        let comment = ModuleComment::from_entity(entity, stripped, is_class);
                        return Some(comment);
                    }
                }
            }
        }
    }

    for child in entity.get_children().iter() {
        if let Some(it) = get_module_comment_of_entity(&child, is_class) {
            return Some(it);
        }
    }

    None
}

fn get_module_comment<'a>(tu: &TranslationUnit<'a>, is_class: bool) -> Option<ModuleComment> {
    for child in tu.get_entity().get_children().iter() {
        if let Some(it) = get_module_comment_of_entity(&child, is_class) {
            return Some(it);
        }
    }

    None
}

fn get_standing_comments<'a>(tu: &TranslationUnit<'a>, path: &Path, module: &str) -> Vec<Comment> {
    let mut result = Vec::new();
    let filesize = fs::metadata(path).unwrap().len() as u32;
    let clang_file = tu.get_file(path).unwrap();
    let start = clang_file.get_offset_location(0);
    let end = clang_file.get_offset_location(filesize);
    let range = SourceRange::new(start, end);

    for token in range.tokenize() {
        if token.get_kind() == TokenKind::Comment {
            if let Some((comment, meta)) = strip_comment(&token.get_spelling()) {
                if meta.kind.is_some() {
                    result.push(Comment::from_token(comment, meta, module));
                }
            }
        }
    }

    result
}

fn generate_doc<'a>(path: &Path, index: &Index<'a>, is_class: bool) -> Option<Document> {
    let tu = index.parser(path).parse().unwrap();

    let module_comment = get_module_comment(&tu, is_class);
    if !module_comment.is_some() {
        println!("{:?}: No @luadoc comment found in header, skipping.", path);
        return None;
    }
    let module_comment_ = module_comment.unwrap();

    let mut comments = get_comments(&tu);
    let mut standing_comments = get_standing_comments(&tu, path, &module_comment_.module);
    let mut enums = extract_enums(&tu, &path);
    comments.append(&mut standing_comments);
    comments.append(&mut enums);

    Some(Document {
        module_comment: module_comment_,
        comments: comments,
    })
}

fn uppercase(s: &str) -> String {
    let mut c = s.chars();
    match c.next() {
        None => String::new(),
        Some(f) => f.to_uppercase().collect::<String>() + c.as_str(),
    }
}

fn get_output_filename(source_path: &Path, is_class: bool) -> String {
    let file_name = source_path.file_name().and_then(|f| f.to_str()).unwrap();
    let mod_name = Regex::new(r"_([^_]*)\..*$") // lua_api_<...>.cpp
        .ok()
        .and_then(|r| r.captures(file_name))
        .and_then(|c| c.get(1))
        .map(|c| c.as_str());

    match mod_name {
        Some(name) => {
            if is_class {
                format!("Lua{}.luadoc", uppercase(name))
            } else {
                format!("{}.luadoc", name)
            }
        }
        None => {
            let name = source_path
                .file_stem()
                .unwrap()
                .to_os_string()
                .into_string()
                .unwrap();
            format!("{}.luadoc", name)
        }
    }
}

fn generate_and_write_doc<'a>(
    path: &PathBuf,
    output_path: &Option<PathBuf>,
    index: &Index<'a>,
    is_class: bool,
    force: bool,
) -> io::Result<()> {
    match output_path {
        Some(p) => {
            let output_filename = get_output_filename(&path, is_class);
            let output_file = p.join(output_filename);
            let modtime_source = fs::metadata(&path).and_then(|r| r.modified())?;
            let newer = force
                || fs::metadata(&output_file)
                    .and_then(|r| r.modified())
                    .map(|m| modtime_source > m)
                    .unwrap_or(true);

            if newer {
                if let Some(doc) = generate_doc(&path, &index, is_class) {
                    let mut writer = File::create(&output_file).unwrap();
                    doc.render(&mut writer)?;
                    println!("Generated {:?}", output_file);
                }
            }
        }
        None => {
            if let Some(doc) = generate_doc(&path, &index, is_class) {
                let mut output = Vec::new();
                doc.render(&mut output)?;
                println!("{}", String::from_utf8(output).unwrap());
            }
        }
    }
    Ok(())
}

fn generate_docs<'a>(
    source_path: &PathBuf,
    output_path: &Option<PathBuf>,
    index: &Index<'a>,
    is_class: bool,
    force: bool,
) -> io::Result<()> {
    if let Some(p) = output_path {
        fs::create_dir_all(p)?;
    }

    for entry in fs::read_dir(source_path)? {
        let entry = entry?;
        let path = entry.path();

        if path.is_file() && path.extension().map_or(false, |e| e == "cpp") {
            generate_and_write_doc(&path, output_path, index, is_class, force)?;
        }
    }

    Ok(())
}

fn app<'a, 'b>() -> App<'a, 'b> {
    App::new(format!("{} {}", crate_name!(), crate_version!()))
        .about("Generates the Lua API documentation.")
        .arg(
            Arg::with_name("version")
                .short("V")
                .long("version")
                .help("Prints version info"),
        )
        .arg(
            Arg::with_name("output_dir")
                .short("o")
                .long("output_dir")
                .takes_value(true)
                .help("Output directory (elona_foobar/bin/)"),
        )
        .arg(
            Arg::with_name("force")
                .short("f")
                .long("force")
                .requires("output_dir")
                .help("Always overwrite output"),
        )
        .arg(
            Arg::with_name("dir")
                .required(true)
                .takes_value(true)
                .index(1)
                .help("Source directory (elona_foobar/src/elona/lua_env/)"),
        )
}

fn main() {
    let matches = app().get_matches();
    if matches.is_present("version") {
        println!("{} {}", crate_name!(), crate_version!());
        return;
    }

    let source_path = matches.value_of("dir").map(Path::new).unwrap();
    let output_path: Option<PathBuf> = matches.value_of("output_dir").map(PathBuf::from);
    let force = matches.is_present("force");

    let clang = Clang::new().unwrap();
    let index = Index::new(&clang, false, false);

    generate_docs(
        &source_path.join("lua_api"),
        &output_path,
        &index,
        false,
        force,
    )
    .unwrap();
    generate_docs(
        &source_path.join("lua_class"),
        &output_path.clone().map(|e| e.join("classes")),
        &index,
        true,
        force,
    )
    .unwrap();
    generate_and_write_doc(
        &source_path.join("enums/enums.cpp"),
        &output_path,
        &index,
        false,
        force,
    )
    .unwrap();
}
