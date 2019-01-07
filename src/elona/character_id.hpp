#pragma once

#include <string>



namespace elona
{

/**
 * Substitutes old integer-based Character::id. It...
 * - is initialized by 0, core.bug.
 * - can be serialized/deserialized.
 *   - NOTE: old ids and new are *not* compatible with each other.
 * - can be comperable with old id.
 * - can be implicitly constructible by old id.
 * - can *not* be implicitly convertible to old id.
 */
struct CharacterId
{
    CharacterId()
    {
    }



    CharacterId(const std::string& value)
        : _value(value)
    {
    }



    CharacterId(int legacy_id);


    CharacterId(const CharacterId&) = default;
    CharacterId(CharacterId&&) = default;
    CharacterId& operator=(const CharacterId&) = default;
    CharacterId& operator=(CharacterId&&) = default;


    CharacterId& operator=(int legacy_id)
    {
        return *this = CharacterId{legacy_id};
    }


    bool operator==(int legacy_id) const;


    bool operator!=(int legacy_id) const
    {
        return !(*this == legacy_id);
    }


    bool operator==(const CharacterId& other) const
    {
        return _value == other._value;
    }


    bool operator!=(const CharacterId& other) const
    {
        return !(*this == other);
    }


    const std::string& get() const
    {
        return _value;
    }


    int to_integer() const;


    template <typename Archive>
    void serialize(Archive& ar)
    {
        ar(_value);
    }



private:
    std::string _value = "core.bug";
};

} // namespace elona
