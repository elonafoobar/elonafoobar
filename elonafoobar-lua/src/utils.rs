use bitflags::bitflags;

pub const LUA_KEYWORDS: &[&str] = &[
    "and", "break", "do", "else", "elseif", "end", "false", "for", "function", "goto", "if", "in",
    "local", "nil", "not", "or", "repeat", "return", "then", "true", "until", "while",
];

bitflags! {
    pub struct IdentifierCheck: u8 {
        const ALLOW_KEYWORD  = 1 << 0;
        const ALLOW_RESERVED = 1 << 1;
    }
}

pub fn is_valid_identifier(name: &str, check: IdentifierCheck) -> bool {
    is_lexically_valid_identifier(name)
        && (check.contains(IdentifierCheck::ALLOW_KEYWORD) || !is_lua_keyword(name))
        && (check.contains(IdentifierCheck::ALLOW_RESERVED) || !is_reserved_identifier(name))
}

pub fn is_lexically_valid_identifier(name: &str) -> bool {
    !name.is_empty()
        && !name
            .bytes()
            .next()
            .expect("already checked above")
            .is_ascii_digit()
        && name.bytes().all(|c| c.is_ascii_alphanumeric() || c == b'_')
}

pub fn is_lua_keyword(name: &str) -> bool {
    LUA_KEYWORDS.iter().any(|kw| *kw == name)
}

#[allow(clippy::iter_nth_zero)]
pub fn is_reserved_identifier(name: &str) -> bool {
    // '__'
    if name.contains("__") {
        return true;
    }

    // '_[A-Z]'
    let first = name.bytes().nth(0);
    let second = name.bytes().nth(1);
    if first == Some(b'_') && second.into_iter().any(|c| c.is_ascii_uppercase()) {
        return true;
    }

    false
}
