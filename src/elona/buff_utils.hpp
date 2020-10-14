#pragma once

#include "buff.hpp"
#include "character.hpp"



namespace elona
{

template <typename Predicate>
void buff_remove_if(Character& chara, Predicate&& should_remove)
{
    auto& buffs = chara.buffs;

    for (auto itr = buffs.begin(), end = buffs.end(); itr != end;)
    {
        if (should_remove(*itr))
        {
            itr = buff_remove_at(chara, itr);
        }
        else
        {
            ++itr;
        }
    }
}



template <typename Predicate>
void buff_remove_if_reverse(Character& chara, Predicate&& should_remove)
{
    auto& buffs = chara.buffs;

    for (intptr_t i = static_cast<intptr_t>(buffs.size()) - 1; 0 <= i; --i)
    {
        if (should_remove(buffs[i]))
        {
            (void)buff_remove_at(chara, buffs.begin() + i);
        }
    }
}



/// Deletes buff of @a id from @a chara 's buffs.
inline void buff_remove(Character& chara, data::InstanceId id)
{
    buff_remove_if(chara, [id](const auto& buff) { return buff.id == id; });
}

} // namespace elona
