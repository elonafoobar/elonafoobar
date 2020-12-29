/*
use anyhow::{bail, Result};

type Todo = ();

struct Parser<'src> {
    src: &'src [u8],
    idx: usize,
    // lua: LuaState,
}

impl<'src> Parser<'src> {
    pub fn new(src: &[u8]) -> Parser {
        Parser { src, idx: 0 }
    }

    pub fn parse(mut self) -> Result<Todo> {
        let mut plain_string_start = 0;
        let mut segments = self.make_table();
        let mut segments_index = 1;

        loop {
            if self.eof() {
                break;
            }

            let c = self.src[self.idx];
            if c == b'{' {
                if self.src.len() <= self.idx + 1 {
                    bail!("missing '}'");
                }
                if self.src[self.idx + 1] == b'{' {
                    self.idx += 1;
                    if plain_string_start < self.idx {
                        segments[segments_index] = self.src[plain_string_start..self.idx];
                        segments_index += 1;
                    }
                    self.idx += 1;
                    plain_string_start = self.idx;
                    continue;
                }
                if plain_string_start < self.idx {
                    segments[segments_index] = self.src[plain_string_start..self.idx];
                    segments_index += 1;
                }
                self.idx += 1;
                let exp = self.parse_exp()?;
                if self.idx < self.src.len() && self.src[self.idx] == b'}' {
                    self.idx += 1;
                } else {
                    bail!("missing '}'");
                }
                segments[segments_index] = exp;
                segments_index += 1;
                plain_string_start = self.idx;
            } else if c == b'}' {
                if self.idx + 1 < self.src.size() && self.src[self.idx + 1] == b'}' {
                    self.idx += 1;
                    if plain_string_start < self.idx {
                        segments[segments_index] = self.src[plain_string_start..self.idx];
                        segments_index += 1;
                    }
                    self.idx += 1;
                    plain_string_start = self.idx;
                    continue;
                } else {
                    bail!("missing '{'");
                }
            } else {
                self.idx += 1;
            }
        }
        if plain_string_start < self.idx {
            segments[segments_index] = self.src[plain_string_start..self.idx];
            segments_index += 1;
        }

        Ok(segments);
    }

    fn parse_exp() -> Result<Todo> {
        if self.eof() {
            bail!("expect an expression, but got EOS");
        }

        // Skip whitespaces
        while !self.eof() && self.src[self.idx] == b' ' {
            self.idx += 1;
        }

        let c = self.src[self.idx];
        if c == b'$' {
            parse_arg_index()
        } else if c == b'"' {
            bail!("string in string interpolation has not been implemented yet!");
        } else if c == b'\'' {
            bail!("string in string interpolation has not been implemented yet!");
        } else if c.is_ascii_digit() {
            parse_int()
        } else if is_ident_start(c) {
            parse_ident()
        } else {
            bail!("invalid character: {}", self.src[self.idx]);
        }
    }

    // \$[0-9]+
    fn parse_arg_index() -> Result<Todo> {
        self.idx += 1; // '$'
        if self.eof() {
            bail!("expected argument index after '$', but got EOS");
        }
        let start_idx = self.idx;
        uint8_t arg_idx;
        let [ptr, ec] = std::from_chars(
            self.src.data() + start_idx, self.src.data() + self.src.len(), arg_idx);
        let end_idx = ptr - self.src.data();
        if ec == std::errc::invalid_argument {
            bail!(
                "expected argument index after '$', but got '"s +
                self.src[start_idx] + "'");
        }
        if ec == std::errc::result_out_of_range {
            bail!(
                "integer out of range: "s +
                std::string{self.src.substr(start_idx, end_idx - start_idx)});
        }
        self.idx = end_idx;
        // return {"v", arg_idx}
        auto ret = make_table();
        ret[1] = "v";
        ret[2] = arg_idx;
        Ok(ret)
    }

    // [0-9]+
    fn parse_int() -> Result<Todo> {
        let start_idx = self.idx;
        int64_t num;
        let [ptr, ec] = std::from_chars(
            self.src.data() + start_idx, self.src.data() + self.src.len(), num);
        let end_idx = ptr - self.src.data();
        if ec == std::errc::result_out_of_range {
            bail!(
                "integer out of range: "s +
                std::string{self.src.substr(start_idx, end_idx - start_idx)});
        }
        self.idx = end_idx;
        Ok(make_object(num))
    }

    fn parse_ident(&mut self) -> Result<Todo> {
        match self.parse_ident_internal() {
            "nil" => Ok(""),
            "true" => Ok(true),
            "false" => Ok(false),
            ident => {
                if self.eof() {
                    Ok(ident)
                } else {
                    parse_func_call(ident)
                }
            }
        }
    }

    fn parse_func_call(&mut self, ident: &str) -> Result<Todo> {
        // mod.func(args, ...)

        // Parse function name
        let mut mod_name;
        let mut func_name;
        if self.src[self.idx] == b'.' {
            self.idx += 1;
            if self.eof() {
                bail!("expect an identifier after '.', but got EOS");
            }
            mod_name = ident;
            if is_ident_start(self.src[self.idx]) {
                func_name = self.parse_ident_internal();
            } else {
                bail!(
                    "expect an identifier after '.', but got '{}'",
                    self.src[self.idx]
                );
            }
        } else {
            mod_name = "core";
            func_name = ident;
        }

        // Parse arguments.
        if self.eof() {
            bail!("expect '(', but got EOS");
        }
        if self.src[self.idx] != b'(' {
            bail!("expected '(', but got '"s + self.src[self.idx] + "'");
        }

        self.idx += 1; // '('

        // return {"f", mod_name.."."..func_name, args, ...}
        let mut ret = make_table();
        ret[1] = "f";
        ret[2] = std::string { mod_name } + "." + std::string { func_name };
        let mut ret_index = 3;
        while !self.eof() {
            if self.src[self.idx] == b')' {
                self.idx += 1;
                return Ok(ret);
            }
            let exp = parse_exp()?;
            ret[ret_index] = exp;
            ret_index += 1;
            if self.eof() {
                bail!("expect ',' or ')', but got EOS");
            } else if self.src[self.idx] == b',' {
                self.idx += 1;
            } else if self.src[self.idx] != b')' {
                bail!("expected ',' or ')', but got '{}'", self.src[self.idx]);
            }
        }
        bail!("expected ')', but got EOS");
    }

    fn parse_ident_internal(&mut self) -> &str {
        let start_idx = self.idx;
        while !self.eof() && is_ident_continue(self.src[self.idx]) {
            self.idx += 1;
        }
        &self.src[start_idx..self.idx]
    }

    fn eof(&self) -> bool {
        self.src.len() <= self.idx
    }
}

fn is_ident_start(c: u8) -> bool {
    c.is_ascii_alphabetic() || c == b'_'
}

fn is_ident_continue(c: u8) -> bool {
    is_ident_start(c) || c.is_ascii_digit()
}
*/
