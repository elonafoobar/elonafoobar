use crate::types::enums::Direction4;
use elonafoobar_lua::types::{LuaFloat, LuaInt};

/// Arbitrary 2-dimensional coordinate in a game field.
#[derive(Debug, Clone, PartialEq, Eq, Default)]
pub struct Position {
    /// X coordinate
    pub x: LuaInt,
    /// Y coordinate
    pub y: LuaInt,
}

impl Position {
    pub fn new() -> Position {
        Default::default()
    }

    pub fn with_xy(x: LuaInt, y: LuaInt) -> Position {
        Position { x, y }
    }

    /// Calculate a distance from `from` in tiles.
    pub fn dist(&self, from: &Position) -> LuaInt {
        self.fdist(from) as LuaInt
    }

    /// Calculate a distance from `from`.
    pub fn fdist(&self, from: &Position) -> LuaFloat {
        // TODO potential overflow
        let dx = self.x - from.x;
        let dy = self.y - from.y;
        ((dx * dx + dy * dy) as LuaFloat).sqrt()
    }

    /// Returns direction from `self` into `into`.
    #[allow(clippy::collapsible_if)]
    pub fn direction(&self, into: &Position) -> Direction4 {
        // TODO potential overflow
        if (self.y - into.y).abs() < (self.x - into.x).abs() {
            if into.x < self.x {
                Direction4::West
            } else {
                Direction4::East
            }
        } else {
            if into.y < self.y {
                Direction4::North
            } else {
                Direction4::South
            }
        }
    }
}

impl std::fmt::Display for Position {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "({}, {})", self.x, self.y)
    }
}

impl From<(LuaInt, LuaInt)> for Position {
    fn from(xy: (LuaInt, LuaInt)) -> Position {
        Position { x: xy.0, y: xy.1 }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_zero() {
        let p1 = Position::default();
        assert_eq!(p1.x, 0);
        assert_eq!(p1.y, 0);

        let p2 = Position::new();
        assert_eq!(p2.x, 0);
        assert_eq!(p2.y, 0);

        assert_eq!(p1, p2);
    }

    #[test]
    fn test_construct() {
        let p1 = Position::with_xy(123, 42);
        assert_eq!(p1.x, 123);
        assert_eq!(p1.y, 42);

        let p2: Position = (123, 42).into();
        assert_eq!(p2.x, 123);
        assert_eq!(p2.y, 42);

        assert_eq!(p1, p2);
    }

    #[test]
    fn test_display() {
        let p1 = Position::with_xy(-321, 123);
        assert_eq!(p1.to_string(), "(-321, 123)");

        let p2 = Position::new();
        assert_eq!(p2.to_string(), "(0, 0)");
    }

    #[test]
    fn test_dist() {
        let p1 = Position::with_xy(0, 0);
        assert_eq!(p1.dist(&Position::with_xy(0, 1)), 1);

        let p2 = Position::with_xy(0, 0);
        assert_eq!(p2.dist(&Position::with_xy(3, 4)), 5);
    }

    #[test]
    fn test_direct() {
        let p0 = Position::with_xy(0, 0);

        assert_eq!(p0.direction(&Position::with_xy(0, 1)), Direction4::South);
        assert_eq!(p0.direction(&Position::with_xy(1, 0)), Direction4::East);
        assert_eq!(p0.direction(&Position::with_xy(0, -1)), Direction4::North);
        assert_eq!(p0.direction(&Position::with_xy(-1, 0)), Direction4::West);
    }
}
