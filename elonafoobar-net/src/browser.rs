use std::io::Result as IoResult;

/// Opens URL on a default browser.
pub fn open_browser(url: &str) -> IoResult<()> {
    webbrowser::open(url).map(|_| ())
}
