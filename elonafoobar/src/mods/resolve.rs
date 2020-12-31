use super::iter_mod_dirs;
use super::manifest::Manifest;
use crate::mods::{ModId, Version, VersionReq};
use anyhow::{bail, format_err, Result};
use serde::Deserialize;
use std::collections::HashMap;
use std::io::ErrorKind as IoErrorKind;
use std::path::Path;
use std::str::FromStr;

#[derive(Debug, Default, Deserialize)]
pub struct ModList {
    #[serde(default)]
    mods: HashMap<ModId, VersionReq>,
}

impl ModList {
    pub fn from_file(path: &Path) -> Result<ModList> {
        match std::fs::read_to_string(path) {
            Ok(json5_source) => json5_source.parse().map_err(Into::into),
            Err(err) if err.kind() == IoErrorKind::NotFound => {
                // It is not error, returns default value.
                Ok(ModList::default())
            }
            Err(err) => Err(err.into()),
        }
    }

    pub fn add(&mut self, mod_id: ModId, req: VersionReq) {
        self.mods.entry(mod_id).or_insert(req);
    }
}

impl FromStr for ModList {
    type Err = json5::Error;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let mods: Self = json5::from_str(s)?;
        Ok(mods)
    }
}

#[derive(Debug)]
pub struct ModLock {
    // TODO
}

#[derive(Debug)]
struct ModIndexEntry {
    version: Version,
    dependencies: HashMap<ModId, VersionReq>,
    optional_dependencies: HashMap<ModId, VersionReq>,
}

#[derive(Debug)]
pub struct ModIndex {
    mods: HashMap<ModId, Vec<ModIndexEntry>>,
}

#[derive(Debug, thiserror::Error)]
pub enum ModIndexQueryError {
    #[error("Mod '{0}' not found")]
    NotFound(ModId),
    #[error("No version of mod '{0}' matches '{1}'")]
    NoMatchVersion(ModId, VersionReq),
}

impl ModIndex {
    pub fn traverse(mod_root_dir: &Path) -> Result<ModIndex> {
        let mut mods = HashMap::new();

        for mod_dir in iter_mod_dirs(mod_root_dir) {
            let manifest = Manifest::from_file(&mod_dir.join("mod.json"))?;
            let id = manifest.id;
            let version = manifest.version;
            let dependencies = manifest.dependencies;
            let optional_dependencies = manifest.optional_dependencies;

            mods.entry(id).or_insert_with(Vec::new).push(ModIndexEntry {
                version,
                dependencies,
                optional_dependencies,
            });
        }

        Ok(ModIndex { mods })
    }

    fn query_latest(
        &self,
        id: &ModId,
        requirement: &VersionReq,
    ) -> Result<&ModIndexEntry, ModIndexQueryError> {
        if let Some(entries) = self.mods.get(id) {
            for entry in entries.iter().rev() {
                if requirement.matches(&entry.version) {
                    return Ok(entry);
                }
            }
            Err(ModIndexQueryError::NoMatchVersion(
                id.clone(),
                requirement.clone(),
            ))
        } else {
            Err(ModIndexQueryError::NotFound(id.clone()))
        }
    }

    fn get_dependencies(&self, id: &ModId, version: &Version) -> &HashMap<ModId, VersionReq> {
        &self.get_entry(id, version).dependencies
    }

    fn get_optional_dependencies(
        &self,
        id: &ModId,
        version: &Version,
    ) -> &HashMap<ModId, VersionReq> {
        &self.get_entry(id, version).optional_dependencies
    }

    // If mod `id` of `version` not found, it panics.
    fn get_entry(&self, id: &ModId, version: &Version) -> &ModIndexEntry {
        let entries = self
            .mods
            .get(id)
            .expect("ModIndex.get_entry(): check existence first");
        for entry in entries {
            if entry.version == *version {
                return entry;
            }
        }
        panic!("ModIndex.get_entry(): check existence first");
    }
}

#[derive(Debug)]
pub struct ResolvedModList {
    pub versions: HashMap<ModId, Version>,
    pub sorted_mods: Vec<ModId>,
}

pub fn resolve(list: &ModList, _lock: &ModLock, index: &ModIndex) -> Result<ResolvedModList> {
    let mut pending_dependencies = list.mods.clone();
    let mut resolved_dependencies = HashMap::new();

    while !pending_dependencies.is_empty() {
        let deps = pending_dependencies.clone();
        pending_dependencies.clear();
        for (mod_id, requirement) in deps {
            if let Some(existing_dependency) = resolved_dependencies.get(&mod_id) {
                if !requirement.matches(existing_dependency) {
                    // TODO: backtrack to find the version which satisfies the requirement.
                    bail!(
                        "failed to resolve mod dependencies: {} ({})",
                        mod_id,
                        requirement
                    );
                }
            } else {
                let index_entry = index.query_latest(&mod_id, &requirement)?;
                resolved_dependencies.insert(mod_id.clone(), index_entry.version.clone());
                for (id, req) in &index_entry.dependencies {
                    pending_dependencies.insert(id.clone(), req.clone());
                }
            }
        }
    }

    let sorted_mods = calculate_loading_order(&resolved_dependencies, index)?
        .into_iter()
        .cloned()
        .collect();
    Ok(ResolvedModList {
        versions: resolved_dependencies,
        sorted_mods,
    })
}

fn calculate_loading_order<'a>(
    mod_versions: &'a HashMap<ModId, Version>,
    index: &'a ModIndex,
) -> Result<Vec<&'a ModId>> {
    type DepGraph<'g> = petgraph::graphmap::DiGraphMap<&'g ModId, ()>;

    let mut dep_graph = DepGraph::new();
    for (mod_a, version_a) in mod_versions {
        dep_graph.add_node(mod_a);
        for mod_b in index.get_dependencies(mod_a, version_a).keys() {
            // Mod 'A' depends on mod 'B'. ('A' -> 'B')
            dep_graph.add_edge(mod_a, mod_b, ());
        }
        for (mod_b, version_requirement_b) in index.get_optional_dependencies(mod_a, version_a) {
            if let Some(version_b) = mod_versions.get(mod_b) {
                if version_requirement_b.matches(version_b) {
                    // Mod 'A' depends on mod 'B'. ('A' -> 'B')
                    dep_graph.add_edge(mod_a, mod_b, ());
                }
            }
        }
    }

    petgraph::algo::toposort(&dep_graph, None).map_err(|err| {
        format_err!(
            "cyclic dependencies detected around the mod '{}'",
            err.node_id()
        )
    })
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse_mod_list() {
        let parse = |s: &str| s.parse::<ModList>();

        assert!(parse(r#"{ mods: {} }"#).is_ok());
        assert!(parse(r#"{ mods: { core: "1.2.3" } }"#).is_ok());
        assert!(parse(r#"{ mods: { core: "^1.2.3", foo: "~1.2.3" } }"#).is_ok());
        assert!(parse(r#"{}"#).is_ok());
    }
}
