# Localization functions
These are the functions available for use inside localization string interpolations. See the Localization section for more information.

## name(chara (LuaCharacter))
Returns: `you` if `chara` is the player, `something` if the `chara` is out of sight of the player, else the full name of the character (with `the` prefixed if appropriate).

Examples:

- As player: `"{name($1)}"` -> `"you"`
- As non-player: `"{name($1)}"` -> `"putit"`
- As non-player who is out of sight: `"{name($1)}"` -> `"something"`

## basename(chara (LuaCharacter))
Returns: the unqualified name of the character regardless of player/non-player or in-sight/out-of-sight.

Examples:

- `"{basename($1)}"` -> `"putit"`

## itemname(item (LuaItem), number (num = 0), needs_article (bool = true))
Returns: `something` if the `chara` is out of sight of the player, else the fully descriptive item name with amount/details included.

Examples:

- `"{itemname($1)}"` -> `"a putitoro"`
- `"{itemname($1, 2)}"` -> `"2 putitoros"`
- `"{itemname($1, 1, false)}"` -> `"putitoro"`
- `"{itemname($1, 1, true)}"` -> `"a putitoro"`

## itembasename(item (LuaItem))
Returns: the unqualified name of the item regardless of its status/number.

Examples:

- `"{itembasename($1)}"` -> `"putitoro"`

## you()
Returns: name of the current player.

Examples:

- `"{you()} fall down the stairs." -> "You fall down the stairs."`

## s(is\_player (bool), needs\_e (bool = false))
Returns: blank if `is_player` is true, else `s` if `needs_e` is false or `es` if `needs_e` is true.

Examples:

- `"You fall${_s(true)} down the stairs." -> "You fall down the stairs."`
- `"She fall${_s(false)} down the stairs." -> "She falls down the stairs."`
- `"You glance{_s(true, true)} at her." -> "You glance at her."`
- `"She glance{_s(false, true)} at you." -> "She glances at you."`

## s(chara (LuaCharacter), needs\_e (bool = false)))
Returns: blank if `chara` is the player, else `s` if `needs_e` is false or `es` if `needs_e` is true.

Examples:

- `"You fall${_s(_1)} down the stairs." -> "You fall down the stairs."`
- `"She fall${_s(_1)} down the stairs." -> "She falls down the stairs."`
- `"You glance{_s(_1, true)} at her." -> "You glance at her."`
- `"She glance{_s(_1, true)} at you." -> "She glances at you."`

## is(is_player (bool))
Returns: `are` if `is_player` is `true`, else `is`.

Examples:

- `"You {is(true)} hurt." -> "You are hurt."`
- `"She {is(false)} happy." -> "She is happy."`

## is(chara (LuaCharacter))
Returns: `are` if `chara` is the player, else `is`.

Examples:

- `"You {is($1)} hurt." -> "You are hurt."`
- `"She {is($1)} happy." -> "She is happy."`

## have(chara (LuaCharacter))
Returns: `have` if `chara` is the player, else `has`.

## he(chara (LuaCharacter))
Returns: `you` if `chara` is the player, else gender-specific `he`.

## him(chara (LuaCharacter))
Returns: `you` if `chara` is the player, else gender-specific `him`.

## his(chara (LuaCharacter))
Returns: `your` if `chara` is the player, else gender-specific `his`.

## his\_owned(chara (LuaCharacter))
Returns: `r` if `chara` is the player, else `'s`.

Examples:

- `"you${his_owned(_1)}" -> "your"`
- `"the putit${his_owned(_1)}" -> "the putit's"`

## trim\_job(name (string)
Returns: `name` with everything after the first space trimmed and an extra space added.

Examples:

- Using the string `"Putit the mochi vendor"`, `"{trim_job{$1}}"` -> `"Putit "`

## kare_wa(chara (LuaCharacter))
Returns: blank if `chara` is the player, "{name}は" if the character is in sight, else "それは". For Japanese only.

## himself(chara (LuaCharacter))
Returns: `yourself` if `chara` is the player, else gender-specific `himself`.

## does(chara (LuaCharacter))
Returns: `do` if `chara` is the player, else `does`.

# Other functions
There are various other functions leftover for Japanese-specific sentence fragments. They are listed here for completeness.

- `yoro(LuaCharacter, int)`
- `dozo(LuaCharacter, int)`
- `thanks(LuaCharacter, int)`
- `rob(LuaCharacter, int)`
- `ka(LuaCharacter, int)`
- `da(LuaCharacter, int)`
- `nda(LuaCharacter, int)`
- `noka(LuaCharacter, int)`
- `kana(LuaCharacter, int)`
- `kimi(LuaCharacter, int)`
- `ru(LuaCharacter, int)`
- `tanomu(LuaCharacter, int)`
- `ore(LuaCharacter, int)`
- `ga(LuaCharacter, int)`
- `dana(LuaCharacter, int)`
- `kure(LuaCharacter, int)`
- `daro(LuaCharacter, int)`
- `yo(LuaCharacter, int)`
- `aru(LuaCharacter, int)`
- `u(LuaCharacter, int)`
- `na(LuaCharacter, int)`
- `ta(LuaCharacter, int)`
