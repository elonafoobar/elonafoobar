local Enums = {}

Enums.IdentifyState = {
   Unidentified = 0,
   Partly = 1,
   Almost = 2,
   Completely = 3
}

Enums.CurseState = {
   Doomed = 0,
   Cursed = 1,
   None = 2,
   Blessed = 3,
}

Enums.StatusAilment = {
   Blinded = 4,
   Confused = 5,
   Paralyzed = 3,
   Poisoned = 1,
   Sleep = 2,
   Fear = 6,
   Dimmed = 7,
   Bleeding = 9,
   Drunk = 8,
   Insane = 11,
   Sick = 12,
}

Enums.Element = {
   Fire = 50,
   Cold = 51,
   Lightning = 52,
   Darkness = 53,
   Mind = 54,
   Poison = 55,
   Nether = 56,
   Sound = 57,
   Nerve = 58,
   Chaos = 59,
   Magic = 60,
   Cut = 61,
   Ether = 62,
   Acid = 63,
}

Enums.TileKind = {
   Normal = 0,
   Wall = 1,
   Tunnel = 2,
   Room = 3,
   Fog = 4,
}

Enums.DamageSource = {
   Trap = -1,
   Overcasting = -2,
   Starvation = -3,
   Poisoning = -4,
   Curse = -5,
   BackpackWeight = -6,
   FallFromStairs = -7,
   Audience = -8,
   Burn = -9,
   Adventuring = -10,
   UnseenHand = -11,
   FoodPoisoning = -12,
   BloodLoss = -13,
   EtherDisease = -14,
   Acid = -15,
   Shatter = -16,
   AtomicBomb = -17,
   IronMaiden = -18,
   Guillotine = -19,
   Hanging = -20,
   Mochi = -21,
}

Enums.CharaFlag = {
   -- Intrinsic flags (reset on every character refresh)
   IsFloating = 5,
   IsInvisible = 6,
   CanSeeInvisible = 7,
   IsImmuneToConfusion = 8,
   IsImmuneToBlindness = 9,
   IsImmuneToFear = 10,
   IsImmuneToSleep = 11,
   IsImmuneToParalyzation = 12,
   IsImmuneToPoison = 13,
   CanDigestRottenFood = 14,
   IsProtectedFromThieves = 15,
   IsIncognito = 16,
   DropsGold = 17,
   Explodes = 18,
   IsDeathMaster = 19,
   CanCastRapidMagic = 20,
   HasLayHand = 21,
   IsSuitableForMount = 22,
   Splits = 23,
   HasCursedEquipments = 24,
   IsUnsuitableForMount = 25,
   IsImmuneToElementalDamage = 26,
   Splits2 = 27,
   IsMetal = 28,
   CuresBleedingQuickly = 29,
   HasPowerBash = 30,
   IsImmuneToMine = 31,
   IsQuickTempered = 32,

   -- Mutable flags
   IsLivestock = 960,
   IsMarried = 961,
   HasMadeGene = 962,
   IsEscorted = 963,
   IsTemporary = 964,
   IsSilent = 965,
   HasBeenUsedStethoscope = 966,
   HasOwnSprite = 967,
   IsLeashed = 968,
   IsContracting = 969,
   IsQuestTarget = 970,
   IsEscortedInSubQuest = 971,
   WillExplodeSoon = 972,
   IsSentencedDaeth = 973,
   IsLayHandAvailable = 974,
   IsRidden = 975,
   IsLordOfDungeon = 976,
   HasOwnName = 977,
   IsPregnant = 978,
   DoesNotSearchEnemy = 979,
   IsContractingWithReaper = 980,
   NeedsRefreshingStatus = 981,
   VisitedJustNow = 982,
   BreaksIntoDebris = 983,
   IsBestFriend = 984,
   IsHungOnSandBag = 985,
   HasAnorexia = 986,
   WasPassedItemByYouJustNow = 987,
   CuresMpFrequently = 988,
   HasCustomTalk = 989,
   HasLearnedWords = 990,
   OnlyChristmas = 991,
}

Enums.Gender = {
   Random = -1,
   Male = 0,
   Female = 1
}

Enums.Relation = {
   Aggressive = -3,
   Nonaggressive = -2,
   Unconcerned = -1,
   Neutral = 0,
   Friend = 10
}

Enums.Color = {
   None = 0,         -- rgb(255,255,255)
   White = 1,        -- rgb(255,255,255)
   Green = 2,        -- rgb(175,255,175)
   Red = 3,          -- rgb(255,155,155)
   Blue = 4,         -- rgb(175,175,255)
   Orange = 5,       -- rgb(255,215,175)
   Yellow = 6,       -- rgb(255,255,175)
   Grey = 7,         -- rgb(155,154,153)
   Purple = 8,       -- rgb(185,155,215)
   Cyan = 9,         -- rgb(155,205,205)
   LightRed = 10,    -- rgb(255,195,185)
   Gold = 11,        -- rgb(235,215,155)
   White2 = 12,      -- rgb(255,255,255)
   LightBrown = 13,  -- rgb(225,215,185)
   DarkGreen = 14,   -- rgb(105,235,105)
   LightGrey = 15,   -- rgb(205,205,205)
   PaleRed = 16,     -- rgb(255,225,225)
   LightBlue = 17,   -- rgb(225,225,255)
   LightPurple = 18, -- rgb(225,195,255)
   LightGreen = 19,  -- rgb(215,255,215)
   YellowGreen = 20  -- rgb(210,250,160)
}

return Enums
