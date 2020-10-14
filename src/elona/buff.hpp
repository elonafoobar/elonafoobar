#pragma once

#include "data/id.hpp"
#include "optional.hpp"
#include "typedefs.hpp"



namespace elona
{

struct Character;



struct Buff
{
    /// ID
    data::InstanceId id{};

    /// Power
    lua_int power{};

    /// Left turns
    lua_int turns{};
};



struct BuffList
{
    using storage_type = std::vector<Buff>;
    using iterator = storage_type::iterator;
    using const_iterator = storage_type::const_iterator;



    size_t size() const noexcept
    {
        return _buffs.size();
    }


    Buff& operator[](size_t index)
    {
        return _buffs.at(index);
    }

    const Buff& operator[](size_t index) const
    {
        return _buffs.at(index);
    }


    void push_back(const Buff& buff)
    {
        _buffs.push_back(buff);
    }


    iterator erase(iterator pos)
    {
        return _buffs.erase(pos);
    }


    iterator begin()
    {
        return _buffs.begin();
    }

    iterator end()
    {
        return _buffs.end();
    }

    const_iterator begin() const
    {
        return _buffs.begin();
    }

    const_iterator end() const
    {
        return _buffs.end();
    }

    const_iterator cbegin() const
    {
        return _buffs.cbegin();
    }

    const_iterator cend() const
    {
        return _buffs.cend();
    }



private:
    std::vector<Buff> _buffs;
};



/// Calculates the duration of buff @a id with the given @a power.
int buff_calc_duration(data::InstanceId id, int power);

/// Gets the description of buff @a id with the given @a power.
std::string buff_get_description(data::InstanceId id, int power);

/// Applies buff @a id 's effect with the given @a power to @a chara.
void buff_apply(Character& chara, data::InstanceId id, int power);

/// Queries whether @a chara has buff @a id or not.
bool buff_has(const Character& chara, data::InstanceId id);

/// Gets @a chara 's buff @a id if he/she has it.
optional_ref<const Buff> buff_find(const Character& chara, data::InstanceId id);

/// Adds buff @a id to @a chara with the given @a power, @a turns, and @a doer.
void buff_add(
    Character& chara,
    data::InstanceId id,
    int power,
    int turns,
    optional_ref<const Character> doer = none);

/// Remove @a chara 's buff at @a itr.
BuffList::iterator buff_remove_at(Character& chara, BuffList::iterator itr);

} // namespace elona
