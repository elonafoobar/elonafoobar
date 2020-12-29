use elonafoobar_lua::types::LuaInt;
use std::cmp::Ordering;

/// Dice
/// "XdY+Z" means "to roll a Y-face dice X times, then add Z."
#[derive(Debug, Clone, PartialEq, Eq, Default)]
pub struct Dice {
    /// Number of rolls.
    pub rolls: LuaInt,
    /// Number of faces.
    pub faces: LuaInt,
    /// Bonus to be added to the dice result.
    pub bonus: LuaInt,
}

impl Dice {
    pub fn new() -> Dice {
        Default::default()
    }

    /// Constructs a dice with the given XdY values.
    pub fn with_xdy(rolls: LuaInt, faces: LuaInt) -> Dice {
        Dice {
            rolls,
            faces,
            bonus: 0,
        }
    }

    /// Constructs a dice with the given XdY+Z values.
    pub fn with_xdy_z(rolls: LuaInt, faces: LuaInt, bonus: LuaInt) -> Dice {
        Dice {
            rolls,
            faces,
            bonus,
        }
    }
}

impl std::fmt::Display for Dice {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self.bonus.cmp(&0) {
            Ordering::Equal => write!(f, "{}d{}", self.rolls, self.faces),
            Ordering::Greater => write!(f, "{}d{}+{}", self.rolls, self.faces, self.bonus),
            Ordering::Less => write!(f, "{}d{}{}", self.rolls, self.faces, self.bonus),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_zero() {
        let d1 = Dice::default();
        assert_eq!(d1.rolls, 0);
        assert_eq!(d1.faces, 0);
        assert_eq!(d1.bonus, 0);

        let d2 = Dice::new();
        assert_eq!(d2.rolls, 0);
        assert_eq!(d2.faces, 0);
        assert_eq!(d2.bonus, 0);

        assert_eq!(d1, d2);
    }

    #[test]
    fn test_construct() {
        let d1 = Dice::with_xdy(12, 7);
        assert_eq!(d1.rolls, 12);
        assert_eq!(d1.faces, 7);
        assert_eq!(d1.bonus, 0);

        let d2 = Dice::with_xdy_z(12, 7, -10);
        assert_eq!(d2.rolls, 12);
        assert_eq!(d2.faces, 7);
        assert_eq!(d2.bonus, -10);

        assert_ne!(d1, d2);
    }

    #[test]
    fn test_display() {
        let d1 = Dice::with_xdy(12, 7);
        assert_eq!(d1.to_string(), "12d7");

        let d2 = Dice::with_xdy_z(12, 7, -10);
        assert_eq!(d2.to_string(), "12d7-10");

        let d3 = Dice::with_xdy_z(12, 7, 10);
        assert_eq!(d3.to_string(), "12d7+10");
    }
}
