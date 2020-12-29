use std::ffi::OsStr;
use std::path::Path;

pub fn is_portable_name(path: impl AsRef<Path>) -> bool {
    let path = path.as_ref();
    is_lexically_portable(path) && is_windows_portable(path)
}

pub fn path_to_str(path: &Path) -> &str {
    path.to_str().expect(
        "Elona foobar assumes that all paths can be converted into UTF-8 string losslessly.",
    )
}

fn is_lexically_portable(path: &Path) -> bool {
    let path = path_to_str(path);
    !path.is_empty()
        && path.len() < 256
        && path.bytes().all(is_portable_char)
        && is_portable_dot(path)
}

// Letter, digit, hyphen, underscore, and dot are portable.
fn is_portable_char(c: u8) -> bool {
    c.is_ascii_alphanumeric() || c == b'-' || c == b'_' || c == b'.'
}

// "\.\."
// "^\."
// "\.$"
fn is_portable_dot(p: &str) -> bool {
    !p.contains("..") && p.as_bytes().first() != Some(&b'.') && p.as_bytes().last() != Some(&b'.')
}

// https://docs.microsoft.com/en-us/windows/win32/fileio/naming-a-file
const RESERVED_NAMES: &[&str] = &[
    "con", "prn", "aux", "nul", "com1", "com2", "com3", "com4", "com5", "com6", "com7", "com8",
    "com9", "lpt1", "lpt2", "lpt3", "lpt4", "lpt5", "lpt6", "lpt7", "lpt8", "lpt9",
];

fn is_windows_portable(path: &Path) -> bool {
    for reserved_name in RESERVED_NAMES {
        if path == OsStr::new(reserved_name) {
            return false; // reserved by Windows
        }
        // Reserved name following extensions is also reserved.
        if path.file_stem() == Some(OsStr::new(reserved_name)) {
            return false; // reserved by Windows
        }
    }
    true // not reserved by Windows
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_is_portable_name() {
        assert!(is_portable_name("foo.lua"));
        assert!(is_portable_name("init.lua"));
        assert!(is_portable_name("data-update.lua"));
        assert!(is_portable_name("README.md"));
        assert!(is_portable_name("12345.txt"));

        assert!(!is_portable_name("foo/bar.txt"));
        assert!(!is_portable_name("."));
        assert!(!is_portable_name(".."));
        assert!(!is_portable_name(""));
        assert!(!is_portable_name("con"));
        assert!(!is_portable_name("nul.txt"));
        assert!(!is_portable_name("<>"));
        assert!(!is_portable_name(";"));
        assert!(!is_portable_name("foo "));
        assert!(!is_portable_name("foo."));
        assert!(!is_portable_name(".vimrc"));
        assert!(!is_portable_name("abc/xyz"));
        assert!(!is_portable_name("/usr"));
        assert!(!is_portable_name("C:\\Program Files"));
        assert!(!is_portable_name("too_looooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong"));
    }
}
