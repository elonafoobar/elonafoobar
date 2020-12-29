use crate::types::DataInstanceId;
use elonafoobar_lua::types::{LuaInt, LuaTable};
use std::collections::HashMap;

/// One story quest's progress ane extra parameters.
pub struct StoryQuest {
    /// Quest progress
    pub progress: LuaInt,
    /// Extension data
    pub ext: LuaTable,
}

/// All story quests.
pub struct StoryQuestTable {
    pub quests: HashMap<DataInstanceId, StoryQuest>,
}
