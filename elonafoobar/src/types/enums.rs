#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Direction4 {
    South = 0,
    West = 1,
    East = 2,
    North = 3,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Direction8 {
    South = 0,
    West = 1,
    East = 2,
    North = 3,
    Southwest = 4,
    Southeast = 5,
    Northwest = 6,
    Northeast = 7,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum CurseState {
    Doomed = -2,
    Cursed = -1,
    None = 0,
    Blessed = 1,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum IdentifyState {
    Unidentified = 0,
    Partly = 1,
    Almost = 2,
    Completely = 3,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Quality {
    None = 0,
    Bad = 1,
    Good = 2,
    Great = 3,
    Miracle = 4,
    Godly = 5,
    Special = 6,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum BuffType {
    Buff = 0,
    Hex = 1,
    Food = 2,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum OwnState {
    /// Your lost items on death.
    Lost = -2,
    /// Your lost items on death. When you enter the map where you died, the
    /// lost items's `OwnState` are set to this value. If you do not pick
    /// them up, they will disappear in your second visit.
    LostDisappearing = -1,
    /// Usual state. Items in character inventory or on dungeons.
    None = 0,
    /// Town's property. It cannot be obtained.
    // TODO rename?
    Town = 1,
    /// It cannot be carried (e.g., wandering vendor's trunk)
    // TODO rename?
    Shop = 2,
    /// Built shelter.
    Shelter = 3,
    /// Crops placed in Harvest quests.
    Crop = 4,
    /// Town's property, and not available for use.
    // TODO rename?
    TownSpecial = 5,
    // Harvested crops. Defining it can fix one known bug in vanilla, but for
    // now, I don't.
    // CropHarvested = 6,
}

// TODO rename
/// Relationship between characters.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Relationship {
    /// Your enemy. Mainly dungeon monsters.
    Enemy = -3,
    /// A town citizen who you attacked once.
    Unfriendly = -2,
    /// Not enemy, not your ally. E.g., little girl, cat, Gwen-chan
    Neutral = -1,
    /// Friendly person. Town citizen.
    Friendly = 0,
    /// Your ally.
    Ally = 10,
}
