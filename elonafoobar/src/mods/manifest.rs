use crate::mods::{ModId, Version, VersionReq};
use anyhow::Result;
use serde::Deserialize;
use std::collections::HashMap;
use std::path::Path;
use std::str::FromStr;

pub type Dependencies = HashMap<ModId, VersionReq>;

#[derive(Debug, Deserialize)]
#[serde(untagged)]
pub enum LocalizableString {
    DefaultText(String),
    LocalizedTextTable(HashMap<String, String>),
}

impl LocalizableString {
    pub fn localize(&self, locale_id: &str) -> Option<&str> {
        match self {
            LocalizableString::DefaultText(text) => Some(text.as_str()),
            LocalizableString::LocalizedTextTable(table) => table
                .get(locale_id)
                .or_else(|| table.get("en"))
                .map(String::as_str),
        }
    }
}

#[derive(Debug, Deserialize)]
pub struct Manifest {
    /// The ID. It must be unique. (Required)
    pub id: ModId,

    /// The version. (Required)
    pub version: Version,

    /// The dependencies. (Optional)
    #[serde(default)]
    pub dependencies: Dependencies,

    /// The optional dependencies. (Optional)
    #[serde(default)]
    pub optional_dependencies: Dependencies,

    /// The display name. It can be localized. (Optional)
    pub name: Option<LocalizableString>,

    /// The author(s) name. (Optional)
    pub authors: Option<String>,

    /// The description. It can be localized. (Optional)
    pub description: Option<LocalizableString>,

    /// The license. (Optional)
    pub license: Option<String>,

    /// The homepage. (Optional)
    pub homepage: Option<String>,

    /// The tags. (Optional)
    #[serde(default)]
    pub tags: Vec<String>,
}

impl Manifest {
    pub fn from_file(path: &Path) -> Result<Manifest> {
        let json5_source = std::fs::read_to_string(path)?;
        Ok(json5_source.parse()?)
    }
}

impl FromStr for Manifest {
    type Err = json5::Error;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        json5::from_str(s)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_manifest_deserialization() {
        let parse = |s| json5::from_str::<Manifest>(s);

        parse(
            r#"
            {
              id: "lomias",
              version: "1.2.3",
              name: "Lomias",
              license: "MIT",
            }"#,
        )
        .unwrap();

        parse(
            r#"
            {
              id: "lomias",
              version: "1.2.3",
              name: { en: "Lomias", ja: "ロミアス" },
              description: "本当に食べてしまったのか？"
            }"#,
        )
        .unwrap();
    }
}
