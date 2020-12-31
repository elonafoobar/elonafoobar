use const_format::formatcp;

pub const VARIANT_MAJOR: u32 = parse_int(env!("CARGO_PKG_VERSION_MAJOR"));
pub const VARIANT_MINOR: u32 = parse_int(env!("CARGO_PKG_VERSION_MINOR"));
pub const VARIANT_PATCH: u32 = parse_int(env!("CARGO_PKG_VERSION_PATCH"));
pub const VARIANT_SERIAL_ID: u32 = 24;
pub const VARIANT_REVISION: &str = env!("VERGEN_SHA_SHORT"); // See ../build.rs
pub const VARIANT_PLATFORM: &str = env!("VERGEN_TARGET_TRIPLE"); // See ../build.rs

// Example: "1.2.3"
pub const VARIANT_SHORT_STRING: &str =
    formatcp!("{}.{}.{}", VARIANT_MAJOR, VARIANT_MINOR, VARIANT_PATCH);

// Example: "Elona foobar version 1.2.3 (14db8cb) on x86_64-apple-darwin"
pub const VARIANT_LONG_STRING: &str = formatcp!(
    "Elona foobar version {} ({}) on {}",
    VARIANT_SHORT_STRING,
    VARIANT_REVISION,
    VARIANT_PLATFORM,
);

// Example: "Elona_foobar/1.2.3+14db8cb (x86_64-apple-darwin)"
pub const VARIANT_USER_AGENT: &str = formatcp!(
    "Elona_foobar/{}+{} ({})",
    VARIANT_SHORT_STRING,
    VARIANT_REVISION,
    VARIANT_PLATFORM,
);

pub const MOD_CORE_MAJOR: u32 = parse_int(env!("ELONAFOOBAR_MOD_CORE_MAJOR"));
pub const MOD_CORE_MINOR: u32 = parse_int(env!("ELONAFOOBAR_MOD_CORE_MINOR"));
pub const MOD_CORE_PATCH: u32 = parse_int(env!("ELONAFOOBAR_MOD_CORE_PATCH"));

// const version of `str::parse::<u32>`.
const fn parse_int(s: &str) -> u32 {
    let bytes = s.as_bytes();
    let mut n = 0;
    let mut i = 0;
    while i < bytes.len() {
        let c = bytes[i];
        n *= 10;
        n += (c - b'0') as u32;
        i += 1;
    }
    n
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse_int() {
        assert_eq!(parse_int("0"), 0);
        assert_eq!(parse_int("42"), 42);
    }
}
