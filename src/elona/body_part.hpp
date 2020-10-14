#pragma once

#include <variant>
#include <vector>

#include "data/id.hpp"
#include "eobject/eobject.hpp"
#include "typedefs.hpp"



namespace elona
{

struct Character;



struct EquipmentSlot
{
    bool is_empty() const noexcept
    {
        return std::holds_alternative<_Empty>(_equip);
    }

    bool is_unequippable() const noexcept
    {
        return std::holds_alternative<_Unequippable>(_equip);
    }

    bool is_equip() const noexcept
    {
        return std::holds_alternative<_Equip>(_equip);
    }

    OptionalItemRef equipment() const
    {
        if (const auto e = std::get_if<_Equip>(&_equip))
        {
            return e->equipment;
        }
        else
        {
            return nullptr;
        }
    }

    void equip(ItemRef new_equipment)
    {
        _equip = _Equip{new_equipment};
    }

    void unequip()
    {
        if (is_equip())
            _equip = _Empty{};
    }

    void make_equippable()
    {
        _equip = _Empty{};
    }

    void make_unequippable()
    {
        _equip = _Unequippable{};
    }



private:
    struct _Empty
    {
    };

    struct _Unequippable
    {
    };

    struct _Equip
    {
        ItemRef equipment;
    };

    std::variant<_Empty, _Unequippable, _Equip> _equip{};
};



struct BodyPart
{
public:
    /// Body part ID
    data::InstanceId id{};

private:
    /// Equipment slot
    EquipmentSlot slot{};


public:
    BodyPart() = default;


    explicit BodyPart(data::InstanceId id) noexcept
        : id(id)
    {
    }


    bool is_empty() const noexcept
    {
        return slot.is_empty();
    }

    bool is_unequippable() const noexcept
    {
        return slot.is_unequippable();
    }

    bool is_equip() const noexcept
    {
        return slot.is_equip();
    }

    OptionalItemRef equipment() const
    {
        return slot.equipment();
    }

    void equip(ItemRef new_equipment)
    {
        slot.equip(new_equipment);
    }

    void unequip()
    {
        slot.unequip();
    }

    void make_equippable()
    {
        slot.make_equippable();
    }

    void make_unequippable()
    {
        slot.make_unequippable();
    }
};



struct BodyPartList
{
    using storage_type = std::vector<BodyPart>;
    using iterator = storage_type::iterator;
    using const_iterator = storage_type::const_iterator;



    BodyPart& operator[](size_t index)
    {
        return _slots.at(index);
    }


    const BodyPart& operator[](size_t index) const
    {
        return _slots.at(index);
    }


    BodyPart& operator[](lua_index index)
    {
        return (*this)[*index.to_0_based()];
    }


    const BodyPart& operator[](lua_index index) const
    {
        return (*this)[*index.to_0_based()];
    }


    bool empty() const noexcept
    {
        return _slots.empty();
    }

    size_t size() const noexcept
    {
        return _slots.size();
    }

    void add(data::InstanceId body_part_id)
    {
        _slots.emplace_back(body_part_id);
    }


    /* clang-format off */
    iterator       begin()        { return _slots.begin();  }
    iterator       end()          { return _slots.end();    }
    const_iterator begin()  const { return _slots.begin();  }
    const_iterator end()    const { return _slots.end();    }
    const_iterator cbegin() const { return _slots.cbegin(); }
    const_iterator cend()   const { return _slots.cend();   }
    /* clang-format on */



private:
    storage_type _slots;
};



bool body_part_has_empty_slot(const Character& chara);
void body_part_gain_new_slot(Character& chara, bool show_message);
void body_part_make_unequippable(
    Character& chara,
    data::InstanceId body_part_id);
void body_part_make_equippable(Character& chara, data::InstanceId body_part_id);

} // namespace elona
