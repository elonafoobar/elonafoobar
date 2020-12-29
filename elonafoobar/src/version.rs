#[derive(Debug)]
pub struct Version {
    pub major: u32,
    pub minor: u32,
    pub patch: u32,
    pub serial_id: u32,
    pub revision: &'static str,
    pub platform: &'static str,
}

impl Version {
    // Example: "1.2.3"
    pub fn short_string(&self) -> String {
        format!("{}.{}.{}", self.major, self.minor, self.patch)
    }

    // Example: "Elona foobar version 1.2.3 (14db8cb) on x86_64-apple-darwin"
    pub fn long_string(&self) -> String {
        format!(
            "Elona foobar version {} ({}) on {}",
            self.short_string(),
            self.revision,
            self.platform,
        )
    }

    // Example: "Elona_foobar/1.2.3+14db8cb (x86_64-apple-darwin)"
    pub fn user_agent(&self) -> String {
        format!(
            "Elona_foobar/{}+{} ({})",
            self.short_string(),
            self.revision,
            self.platform
        )
    }
}

pub fn latest_version() -> Version {
    // It is not a const variable because std::parse() is not a const fn.
    Version {
        major: env!("CARGO_PKG_VERSION_MAJOR")
            .parse()
            .expect("It is automatically set by Cargo so definitely number"),
        minor: env!("CARGO_PKG_VERSION_MINOR")
            .parse()
            .expect("automatically set by Cargo so definitely number"),
        patch: env!("CARGO_PKG_VERSION_PATCH")
            .parse()
            .expect("automatically set by Cargo so definitely number"),
        serial_id: 24,
        revision: env!("VERGEN_SHA_SHORT"),     // See ../build.rs
        platform: env!("VERGEN_TARGET_TRIPLE"), // See ../build.rs
    }
}
