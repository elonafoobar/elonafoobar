#pragma once

#include <unordered_map>



namespace elona
{



struct buff_data
{
    enum class type_t
    {
        buff,
        hex,
        food,
    };


    int id;
    type_t type;
};



class buff_db
{
public:
    buff_db();

    void initialize();

    const buff_data& operator[](int id) const
    {
        return storage.at(id);
    }


private:
    std::unordered_map<int, buff_data> storage;
};


inline buff_db the_buff_db;



// 1   "聖なる盾", "Holy Shield"
// 2   "沈黙の霧", "Mist of Silence"
// 3   "リジェネレーション", "Regeneration"
// 4   "元素保護", "Elemental Shield"
// 5   "加速", "Speed"
// 6   "鈍足", "Slow"
// 7   "英雄", "Hero"
// 8   "脆弱の霧", "Mist of Frailness"
// 9   "元素の傷跡", "Element Scar"
// 10  "ホーリーヴェイル", "Holy Veil"
// 11  "ナイトメア", "Nightmare"
// 12  "知者の加護", "Divine Wisdom"
// 13  "天罰", "Punishment"
// 14  "ルルウィの憑依", "Lulwy's Trick"
// 15  "インコグニート", "Incognito"
// 16  "死の宣告", "Death Word"
// 17  "ブースト", "Boost"
// 18  "契約", "Contingency"
// 19  "幸運", "Luck"
// 20  "筋力の成長", "Grow Strength"
// 21  "耐久の成長", "Grow Endurance"
// 22  "器用の成長", "Grow Dexterity"
// 23  "感覚の成長", "Grow Perception"
// 24  "学習の成長", "Grow Learning"
// 25  "意思の成長", "Grow Will"
// 26  "魔力の成長", "Grow Magic"
// 27  "魅力の成長", "Grow Charisma"
// 28  "速度の成長", "Grow Speed"



} // namespace elona
