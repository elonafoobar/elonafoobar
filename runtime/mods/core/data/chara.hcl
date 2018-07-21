# Temporary documentation so the format isn't cryptic (until spec support is added)

# define data of type "core.chara" with ID "putit"
chara putit {
    # Legacy character ID.
    id = 3

    level = 1
    portrait = -1
    creaturepack = 3
    normal_actions = [-1]
    can_talk = No # TODO
    has_random_name = false

    # Filter tags, gets concatenated into "/slime/" for now
    filter = ["slime"]

    # One of: "enemy", "nonaggressive", "unconcerned", "neutral", "friend"
    relationship = Enemy

    race = "slime"
    class = "tourist"

    resistances {
        _63 = 500
    }

    cspecialeq = 0

    # One of: ??? TODO
    category = "default"

    # Original rarity / 1000, lower is rarer, 0 is non-generatable
    # TODO old formula = rarity / (500 + abs(level - maxlvl) * coeff)
    rarity = 70
    coefficient = 400

    # Flags by Lua enum identifier. Will be replaced dynamically.
    flags = [IsSuitableForMount]

    ai_calm = 1
    ai_move = 100
    ai_dist = 1
    ai_special_action_frequency = 0
}
