use anyhow::{bail, Context, Result};
use elonafoobar_net::browser;

const TRUSTED_URLS: &[&str] = &[
    "http://ylvania.org/jp",
    "http://ylvania.org/en",
    "https://elonafoobar.com",
];

pub fn open_browser(url: &str) -> Result<()> {
    if TRUSTED_URLS.contains(&url) {
        browser::open_browser(url).context("Failed to open URL on a browser")
    } else {
        // TBD: allow any URLs?
        bail!("Untrusted URL: {}", url)
    }
}
