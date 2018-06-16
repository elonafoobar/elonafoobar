# Localization functions
These are the functions available for use inside localization string interpolations. See the Localization section for more information.

## you()
- Returns: name of the current player.
- Examples:
  + `"${you()} fall down the stairs." -> "You fall down the stairs."`

## s(is_player (bool), needs_e (bool = false))
- Returns: blank if `is_player` is true, else `s` if `needs_e` is false or `es` if `needs_e` is true.
- Examples:
  + `"You fall${_s(true)} down the stairs." -> "You fall down the stairs."`
  + `"She fall${_s(false)} down the stairs." -> "She falls down the stairs."`
  + `"You glance{_s(true, true)} at her." -> "You glance at her."`
  + `"She glance{_s(false, true)} at you." -> "She glances at you."`

## s(chara (LuaCharacter), needs_e (bool = false)))
- Returns: blank if `chara` is the player, else `s` if `needs_e` is false or `es` if `needs_e` is true.
- Examples:
  + `"You fall${_s(_1)} down the stairs." -> "You fall down the stairs."`
  + `"She fall${_s(_1)} down the stairs." -> "She falls down the stairs."`
  + `"You glance{_s(_1, true)} at her." -> "You glance at her."`
  + `"She glance{_s(_1, true)} at you." -> "She glances at you."`

## is(is_player (bool))
- Returns: `are` if `is_player` is `true`, else `is`.
- Examples:
  + `"You ${is(true)} hurt." -> "You are hurt."`
  + `"She ${is(false)} happy." -> "She is happy."`

## is(chara (LuaCharacter))
- Returns: `are` if `chara` is the player, else `is`.
- Examples:
  + `"You ${is(_1)} hurt." -> "You are hurt."`
  + `"She ${is(_1)} happy." -> "She is happy."`
