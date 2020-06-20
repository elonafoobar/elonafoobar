#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>



namespace elona::eobject
{

struct Id
{
public:
    Id() noexcept
        : Id(nil())
    {
    }



    Id(const Id&) noexcept = default;
    Id(Id&&) noexcept = default;
    Id& operator=(const Id&) noexcept = default;
    Id& operator=(Id&&) noexcept = default;



    static Id nil() noexcept
    {
        static boost::uuids::nil_generator gen;
        return Id{gen()};
    }



    static Id generate()
    {
        static boost::uuids::random_generator gen;
        return Id{gen()};
    }



    static Id from_string(const std::string& s)
    {
        static boost::uuids::string_generator gen;
        return Id{gen(s)};
    }



    std::string to_string() const
    {
        return boost::uuids::to_string(_inner);
    }



    bool is_nil() const noexcept
    {
        return _inner.is_nil();
    }



    bool operator==(const Id& other) const noexcept
    {
        return _inner == other._inner;
    }


    bool operator!=(const Id& other) const noexcept
    {
        return !(*this == other);
    }



    size_t hash_value() const noexcept
    {
        return boost::uuids::hash_value(_inner);
    }



    template <typename Archive>
    void serialize(Archive& ar)
    {
        for (auto& b : _inner)
        {
            ar(b);
        }
    }



private:
    boost::uuids::uuid _inner;



    explicit Id(const boost::uuids::uuid& inner)
        : _inner(inner)
    {
    }
};

} // namespace elona::eobject



namespace std
{

template <>
struct hash<::elona::eobject::Id>
{
    size_t operator()(const ::elona::eobject::Id& value) const noexcept
    {
        return value.hash_value();
    }
};

} // namespace std
