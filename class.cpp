#include "class.hpp"
#include "elona.hpp"
#include "variables.hpp"



namespace elona
{


std::vector<std::string> get_available_classes()
{
    return {
        u8"warrior",
        u8"thief",
        u8"wizard",
        u8"farmer",
        u8"archer",
        u8"warmage",
        u8"tourist",
        u8"pianist",
        u8"priest",
        u8"claymore",
    };
}


int access_class_info(int dbmode, const std::string& dbidn)
{
    if (dbidn == ""s)
    {
        classname = u8"なし"s;
        cequipment = 0;
        return 0;
    }

    if (false)
    {
    }
    else if (dbidn == u8"warrior"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 4)
            {
                return 1;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            classname = u8"戦士"s;
        }
        if (dbmode == 11)
        {
            classname = u8"戦士"s;
            buff = lang(
                u8"戦士は己の肉体を武器に、立ちはだかるものを破壊し突き進みます。魔法の扱いには向いていませんが、その高い戦闘能力には目を見張るものがあります。"s,
                u8"The Warrior. With working knowledge of all things stabby, bashy, choppy, and shooty, anything in a Warrior's hands is bad news for their enemies. No mere thug, they have knowledge of tactics to bring even the strongest down, and are trained early on to be comfortable in all kinds of armor and shields. Warriors are personifications of the adage \"If violence isn't working, you are obviously not using enough of it.\""s);
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(3, rc) = u8"warrior"s;
            cequipment = 1;
            skillinit(10, rc, 10);
            skillinit(11, rc, 10);
            skillinit(12, rc, 2);
            skillinit(13, rc, 0);
            skillinit(14, rc, 0);
            skillinit(15, rc, 3);
            skillinit(16, rc, 0);
            skillinit(17, rc, 0);
            skillinit(18, rc, 0);
            skillinit(100, rc, 6);
            skillinit(101, rc, 4);
            skillinit(103, rc, 6);
            skillinit(102, rc, 6);
            skillinit(104, rc, 4);
            skillinit(107, rc, 5);
            skillinit(167, rc, 6);
            skillinit(152, rc, 4);
            skillinit(173, rc, 5);
            skillinit(154, rc, 5);
            skillinit(170, rc, 4);
            skillinit(169, rc, 4);
            skillinit(168, rc, 5);
        }
    }
    else if (dbidn == u8"thief"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 4)
            {
                return 7;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            classname = u8"遺跡荒らし"s;
        }
        if (dbmode == 11)
        {
            classname = u8"遺跡荒らし"s;
            buff = lang(
                u8"遺跡荒らしは、財宝を目当てに墓や遺跡から貴重品を持ち出すことで生計をたてています。彼らにはそこそこの戦闘能力と、商人と駆け引きをするために必要な才能があります。"s,
                u8"The Thief. Good with swords and bows, though not a believer of a fair fight. Prefers to avoid taking hits if possible. Can dual wield if the weapons aren't too heavy. Years of dealing with fences have given the Thief skills with negotiating a better deal. A firm believer in the adage \"What's yours is mine, and what's mine is mine. See that guy over there, his stuff? Mine too.\""s);
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(3, rc) = u8"thief"s;
            cequipment = 7;
            skillinit(10, rc, 4);
            skillinit(11, rc, 4);
            skillinit(12, rc, 8);
            skillinit(13, rc, 5);
            skillinit(14, rc, 4);
            skillinit(15, rc, 0);
            skillinit(16, rc, 0);
            skillinit(17, rc, 0);
            skillinit(18, rc, 0);
            skillinit(101, rc, 4);
            skillinit(100, rc, 3);
            skillinit(108, rc, 3);
            skillinit(173, rc, 4);
            skillinit(166, rc, 4);
            skillinit(152, rc, 3);
            skillinit(156, rc, 4);
            skillinit(300, rc, 4);
            skillinit(174, rc, 3);
            skillinit(170, rc, 4);
        }
    }
    else if (dbidn == u8"wizard"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 4)
            {
                return 2;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            classname = u8"魔法使い"s;
        }
        if (dbmode == 11)
        {
            classname = u8"魔法使い"s;
            buff = lang(
                u8"魔法使いは、その名のとおり魔法の知識に長けています。魔法使いの生死は、魔法書の取得と管理にかかっています。"s,
                u8"The Wizard. Master of the Arcane, the Eldritch, and the Esoteric. A pity all those years have left little time to build muscles or quick reflexes. Still, they do have some small skill with staff and short sword. And while they start out so feeblePurits scare them, with a few books under their belt, and a little practice, a Wizard will soon decimate legions. Their motto: \"If it's not on fire now, it will be soon\"."s);
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(3, rc) = u8"wizard"s;
            cequipment = 2;
            skillinit(10, rc, 0);
            skillinit(11, rc, 0);
            skillinit(12, rc, 0);
            skillinit(13, rc, 4);
            skillinit(14, rc, 3);
            skillinit(15, rc, 8);
            skillinit(16, rc, 10);
            skillinit(17, rc, 0);
            skillinit(18, rc, 0);
            skillinit(105, rc, 3);
            skillinit(101, rc, 2);
            skillinit(150, rc, 6);
            skillinit(165, rc, 3);
            skillinit(164, rc, 6);
            skillinit(174, rc, 5);
            skillinit(171, rc, 4);
            skillinit(178, rc, 4);
            skillinit(172, rc, 5);
        }
    }
    else if (dbidn == u8"farmer"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 4)
            {
                return 1;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            classname = u8"農民"s;
        }
        if (dbmode == 11)
        {
            classname = u8"農民"s;
            buff = lang(
                u8"農民は生産を得意とする職業です。彼らは我慢強く、またある程度の身体能力を持っています。"s,
                u8"The Farmer. While not a steely-thewed Warrior or or well read Mage, the farmer is a Jack-of All-Trades. Good with a polearm from threshing grain, and good bargainers with their deals with merchants, they have working knowledge of just about every trade there is. As such, they never go hungry, as there's always something someone will pay dearly to get done. Their motto: \"Anything worth doing is best done yourself\"."s);
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(3, rc) = u8"farmer"s;
            cequipment = 1;
            skillinit(10, rc, 5);
            skillinit(11, rc, 5);
            skillinit(12, rc, 2);
            skillinit(13, rc, 0);
            skillinit(14, rc, 8);
            skillinit(15, rc, 5);
            skillinit(16, rc, 0);
            skillinit(17, rc, 0);
            skillinit(18, rc, 0);
            skillinit(104, rc, 4);
            skillinit(107, rc, 3);
            skillinit(173, rc, 3);
            skillinit(156, rc, 5);
            skillinit(184, rc, 6);
            skillinit(161, rc, 7);
            skillinit(154, rc, 5);
            skillinit(180, rc, 5);
            skillinit(177, rc, 5);
        }
    }
    else if (dbidn == u8"predator"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 4)
            {
                return 0;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            classname = u8"プレデター"s;
        }
        if (dbmode == 11)
        {
            classname = u8"プレデター"s;
            buff = lang(""s, ""s);
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(3, rc) = u8"predator"s;
            cequipment = 0;
            skillinit(10, rc, 8);
            skillinit(11, rc, 11);
            skillinit(12, rc, 8);
            skillinit(13, rc, 0);
            skillinit(14, rc, 0);
            skillinit(15, rc, 0);
            skillinit(16, rc, 0);
            skillinit(17, rc, 0);
            skillinit(18, rc, 10);
            skillinit(152, rc, 4);
        }
    }
    else if (dbidn == u8"archer"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 4)
            {
                return 3;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            classname = u8"狩人"s;
        }
        if (dbmode == 11)
        {
            classname = u8"狩人"s;
            buff = lang(
                u8"狩人は遠隔攻撃のスペシャリストです。多少の打撃能力もありますが、大抵は敵の接近を許さずに倒すことができるでしょう。"s,
                u8"The Archer. Skilled in the ways of the forest and hunting, they are master marksmen, and don't see why one should hunt monster any different than a deer. Skilled with the Short Sword, the axe, and of course all types of bows, plus a few skills they picked up on their long trips in the woods. Firm believers that \"Anything dead over THERE will not be bothering me HERE\"."s);
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(3, rc) = u8"archer"s;
            cequipment = 3;
            skillinit(10, rc, 6);
            skillinit(11, rc, 4);
            skillinit(12, rc, 8);
            skillinit(13, rc, 5);
            skillinit(14, rc, 2);
            skillinit(15, rc, 0);
            skillinit(16, rc, 0);
            skillinit(17, rc, 0);
            skillinit(18, rc, 0);
            skillinit(108, rc, 5);
            skillinit(109, rc, 5);
            skillinit(101, rc, 4);
            skillinit(102, rc, 3);
            skillinit(173, rc, 5);
            skillinit(174, rc, 3);
            skillinit(170, rc, 3);
            skillinit(177, rc, 4);
            skillinit(301, rc, 4);
            skillinit(189, rc, 3);
        }
    }
    else if (dbidn == u8"warmage"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 4)
            {
                return 5;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            classname = u8"魔法戦士"s;
        }
        if (dbmode == 11)
        {
            classname = u8"魔法戦士"s;
            buff = lang(
                u8"魔法戦士は戦士と魔法使いの中間的な職業で、より打撃に重点を置いています。魔法を使いこなすためにも、バランスをとり成長させることが必要でしょう。"s,
                u8"The Warmage. Not really a Wizard, not really a Warrior, the Warmage is a believer that stabbing things that are on fire is better than just stabbing them or setting them on fire. Good with swords, armor, books and casting. Their only weakness is that without specialization, they won't truely excel in a field. Still when your motto is: \"Everything worth doing is worth overdoing\", you don't really care."s);
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(3, rc) = u8"warmage"s;
            cequipment = 5;
            skillinit(10, rc, 6);
            skillinit(11, rc, 6);
            skillinit(12, rc, 2);
            skillinit(13, rc, 0);
            skillinit(14, rc, 0);
            skillinit(15, rc, 4);
            skillinit(16, rc, 7);
            skillinit(17, rc, 0);
            skillinit(18, rc, 0);
            skillinit(100, rc, 4);
            skillinit(101, rc, 3);
            skillinit(173, rc, 3);
            skillinit(150, rc, 4);
            skillinit(164, rc, 3);
            skillinit(174, rc, 5);
            skillinit(170, rc, 4);
            skillinit(169, rc, 4);
            skillinit(172, rc, 4);
        }
    }
    else if (dbidn == u8"tourist"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 4)
            {
                return 0;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            classname = u8"観光客"s;
        }
        if (dbmode == 11)
        {
            classname = u8"観光客"s;
            buff = lang(
                u8"観光客はこの世界における伝統的な職業で、予想を裏切らないほど軟弱です。"s,
                u8"The Tourist. They have no strengths, they have no weaknesses. They don't have anything really. Oh they can fish, I'll give you that, but if you want a real challenge to build something from the ground up, this is the way to go. After all, you have to teach them everything. Only for those who have a good amount of time to spare. You can even write your own motto if you want."s);
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(3, rc) = u8"tourist"s;
            cequipment = 0;
            skillinit(10, rc, 0);
            skillinit(11, rc, 0);
            skillinit(12, rc, 0);
            skillinit(13, rc, 0);
            skillinit(14, rc, 0);
            skillinit(15, rc, 0);
            skillinit(16, rc, 0);
            skillinit(17, rc, 0);
            skillinit(18, rc, 0);
            skillinit(185, rc, 5);
            skillinit(182, rc, 3);
        }
    }
    else if (dbidn == u8"pianist"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 4)
            {
                return 3;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            classname = u8"ピアニスト"s;
        }
        if (dbmode == 11)
        {
            classname = u8"ピアニスト"s;
            buff = lang(
                u8"ピアニストは演奏を生業とする孤高の職業です。彼らは常にピアノを背負っているため、重荷に耐える能力があります。"s,
                u8"The Pianist. Where the Farmer has all the practical skills, the Pianist has all the impractical ones. Still, they can read a book, play a tune, make jewelry, and since they are expected to haul a piano around, they get real good with weight lifting. Their Motto: \"The whole world is my stage!\" And they believe it too."s);
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(3, rc) = u8"pianist"s;
            cequipment = 3;
            skillinit(10, rc, 6);
            skillinit(11, rc, 0);
            skillinit(12, rc, 4);
            skillinit(13, rc, 5);
            skillinit(14, rc, 6);
            skillinit(15, rc, 0);
            skillinit(16, rc, 4);
            skillinit(17, rc, 8);
            skillinit(18, rc, 0);
            skillinit(183, rc, 6);
            skillinit(153, rc, 19);
            skillinit(150, rc, 4);
            skillinit(165, rc, 6);
            skillinit(174, rc, 6);
            skillinit(179, rc, 5);
            skillinit(171, rc, 4);
            skillinit(301, rc, 3);
        }
    }
    else if (dbidn == u8"gunner"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 4)
            {
                return 4;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            classname = u8"機工兵"s;
        }
        if (dbmode == 11)
        {
            classname = u8"機工兵"s;
            buff = lang(""s, ""s);
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(3, rc) = u8"gunner"s;
            cequipment = 4;
            skillinit(10, rc, 0);
            skillinit(11, rc, 2);
            skillinit(12, rc, 5);
            skillinit(13, rc, 8);
            skillinit(14, rc, 5);
            skillinit(15, rc, 4);
            skillinit(16, rc, 3);
            skillinit(17, rc, 0);
            skillinit(18, rc, 0);
            skillinit(110, rc, 5);
            skillinit(173, rc, 4);
            skillinit(150, rc, 3);
            skillinit(154, rc, 4);
            skillinit(189, rc, 3);
        }
    }
    else if (dbidn == u8"priest"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 4)
            {
                return 6;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            classname = u8"神官"s;
        }
        if (dbmode == 11)
        {
            classname = u8"神官"s;
            buff = lang(
                u8"神官は魔法の能力と供に、若干の肉弾戦への適正を持っています。彼らは信仰する神から、最大限の恩恵を受けることができるでしょう。"s,
                u8"The Priest. The Faithful, the devout. They bring the words of their God to the world, one battered heretic at a time. Good with all armors, shields, divine magic, blunt weapons, and reading. The Priest is a handful, though depending on their God, they may have hidden pratfalls as well. If the motto: \"A hymn a day,, will keep me away, Sinner!\" appeals to you, choose this."s);
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(3, rc) = u8"priest"s;
            cequipment = 6;
            skillinit(10, rc, 2);
            skillinit(11, rc, 2);
            skillinit(12, rc, 0);
            skillinit(13, rc, 2);
            skillinit(14, rc, 2);
            skillinit(15, rc, 10);
            skillinit(16, rc, 7);
            skillinit(17, rc, 2);
            skillinit(18, rc, 0);
            skillinit(103, rc, 3);
            skillinit(168, rc, 3);
            skillinit(150, rc, 5);
            skillinit(154, rc, 5);
            skillinit(174, rc, 5);
            skillinit(170, rc, 3);
            skillinit(169, rc, 4);
            skillinit(181, rc, 5);
            skillinit(172, rc, 5);
        }
    }
    else if (dbidn == u8"claymore"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 4)
            {
                return 8;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            classname = u8"クレイモア"s;
        }
        if (dbmode == 11)
        {
            classname = u8"クレイモア"s;
            buff = lang(
                u8"クレイモアは半人半妖の血が流れる俊敏な剣士です。銀眼の斬殺者と呼ばれる彼女達は、身の丈ほどの長さの大剣を自在に扱います。耐久力は低めですが、軽いみのこなしと敏感な目で、相手の攻撃を軽々とかわすことができます。"s,
                u8"The Claymore. Half-human, with silver eyes and inhuman evasive capabilities, the Claymores are a mostly female class, as the males have… problems. Their weapon of choice is the Claymore, hence their name, and they prefer light armor, relying on their great speed and skills of evasion to protect them. They heal fast, but the healing comes at a price. Their bodies are unstable, their motto unknown."s);
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(3, rc) = u8"claymore"s;
            cequipment = 8;
            skillinit(10, rc, 9);
            skillinit(11, rc, 3);
            skillinit(12, rc, 7);
            skillinit(13, rc, 6);
            skillinit(14, rc, 0);
            skillinit(15, rc, 0);
            skillinit(16, rc, 4);
            skillinit(17, rc, 0);
            skillinit(18, rc, 0);
            skillinit(100, rc, 6);
            skillinit(167, rc, 7);
            skillinit(152, rc, 5);
            skillinit(173, rc, 7);
            skillinit(187, rc, 4);
            skillinit(154, rc, 6);
            skillinit(171, rc, 5);
            skillinit(150, rc, 4);
        }
    }
    return 0;
}



} // namespace elona
