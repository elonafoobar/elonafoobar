#pragma once

#include <unordered_map>

#include "../data/id.hpp"
#include "../typedefs.hpp"



namespace elona
{

/// Represents one "skill", stats, spells, skills and resistances.
struct Skill
{
    /// Current level
    lua_int level{};

    /// Base level
    lua_int base_level{};

    /// Experience
    lua_int experience{};

    /// Potential
    lua_int potential{};
};



/**
 * A table from skill ID to skill data.
 */
struct SkillTable
{
    SkillTable() noexcept = default;

    SkillTable(const SkillTable&) = default;
    SkillTable(SkillTable&&) = default;
    SkillTable& operator=(const SkillTable&) = default;
    SkillTable& operator=(SkillTable&&) = default;



    /**
     * Gets skill level of @a id.
     *
     * @param id Skill ID
     * @return The current skill level or 0 if not found.
     */
    lua_int level(data::InstanceId id) const noexcept
    {
        if (const auto itr = _skills.find(id); itr != _skills.end())
        {
            return itr->second.level;
        }
        else
        {
            return 0;
        }
    }



    /**
     * Set skill level of @a id.
     *
     * @param id Skill ID
     * @param new_value Skill level
     */
    void set_level(data::InstanceId id, lua_int new_value)
    {
        _skills[id].level = new_value;
    }



    /**
     * Add skill level of @a id.
     *
     * @param id Skill ID
     * @param delta Skill level
     */
    void add_level(data::InstanceId id, lua_int delta)
    {
        _skills[id].level += delta;
    }



    /**
     * Gets base skill level of @a id.
     *
     * @param id Skill ID
     * @return The base skill level or 0 if not found.
     */
    lua_int base_level(data::InstanceId id) const noexcept
    {
        if (const auto itr = _skills.find(id); itr != _skills.end())
        {
            return itr->second.base_level;
        }
        else
        {
            return 0;
        }
    }



    /**
     * Set base skill level of @a id.
     *
     * @param id Skill ID
     * @param new_value Base skill level
     */
    void set_base_level(data::InstanceId id, lua_int new_value)
    {
        _skills[id].level = new_value;
    }



    /**
     * Add base skill level of @a id.
     *
     * @param id Skill ID
     * @param delta Base skill level
     */
    void add_base_level(data::InstanceId id, lua_int delta)
    {
        _skills[id].level += delta;
    }



    /**
     * Gets experience of @a id.
     *
     * @param id Skill ID
     * @return The experience or 0 if not found.
     */
    lua_int experience(data::InstanceId id) const noexcept
    {
        if (const auto itr = _skills.find(id); itr != _skills.end())
        {
            return itr->second.experience;
        }
        else
        {
            return 0;
        }
    }



    /**
     * Set experience of @a id.
     *
     * @param id Skill ID
     * @param new_value Experience
     */
    void set_experience(data::InstanceId id, lua_int new_value)
    {
        _skills[id].level = new_value;
    }



    /**
     * Add experience of @a id.
     *
     * @param id Skill ID
     * @param delta Experience
     */
    void add_experience(data::InstanceId id, lua_int delta)
    {
        _skills[id].level += delta;
    }



    /**
     * Gets potential of @a id.
     *
     * @param id Skill ID
     * @return The potential or 0 if not found.
     */
    lua_int potential(data::InstanceId id) const noexcept
    {
        if (const auto itr = _skills.find(id); itr != _skills.end())
        {
            return itr->second.potential;
        }
        else
        {
            return 0;
        }
    }



    /**
     * Set potential of @a id.
     *
     * @param id Skill ID
     * @param new_value Potential
     */
    void set_potential(data::InstanceId id, lua_int new_value)
    {
        _skills[id].level = new_value;
    }



    /**
     * Add potential of @a id.
     *
     * @param id Skill ID
     * @param delta Potential
     */
    void add_potential(data::InstanceId id, lua_int delta)
    {
        _skills[id].level += delta;
    }



    /**
     * Clear all skill boosts.
     */
    void clear_all_boosts() noexcept
    {
        for (auto&& [_id, skill] : _skills)
        {
            skill.level = skill.base_level;
        }
    }



    Skill& get(data::InstanceId id)
    {
        return _skills[id];
    }



private:
    std::unordered_map<data::InstanceId, Skill> _skills;
};

} // namespace elona
