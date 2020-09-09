#pragma once

#include "../serialization/concepts.hpp"
#include "detail/shared_id.hpp"



// Defines several kinds of strongly-typed IDs.
namespace elona::data
{

namespace detail
{

template <typename _Tag>
struct _Id
{
    /// Constructs empty ID.
    _Id() = default;


    /// Constructs ID from @a id.
    explicit _Id(const char* id)
        : _inner(id)
    {
    }


    /// Constructs ID from @a id.
    explicit _Id(const std::string& id)
        : _inner(id)
    {
    }


    /// Constructs ID from @a static_id.
    /// This implicit conversion ctor takes only char array with static size,
    /// typically string literals.
    template <size_t N>
    _Id(const char (&static_id)[N])
        : _inner(static_id)
    {
    }


    /// Check equality with @a other.
    bool operator==(const _Id& other) const noexcept
    {
        return _inner == other._inner;
    }


    /// Check equality with @a other.
    bool operator!=(const _Id& other) const noexcept
    {
        return _inner != other._inner;
    }


    /// Converts itself to string.
    const std::string& get() const noexcept
    {
        return _inner.get();
    }


    /// Calculates hash value of the ID.
    size_t hash() const noexcept
    {
        return std::hash<SharedId>{}(_inner);
    }



    template <typename Archive>
    void serialize(Archive& ar)
    {
        /* clang-format off */
        if constexpr (serialization::concepts::is_iarchive_v<Archive>)
        {
            std::string tmp;
            ar(tmp);
            _inner = tmp;
        }
        else
        {
            std::string tmp = _inner.get();
            ar(tmp);
        }
        /* clang-format on */
    }



private:
    SharedId _inner;
};



struct _PrototypeIdTag
{
};

struct _InstanceIdTag
{
};

struct _FullyQualifiedIdTag
{
};

} // namespace detail



/// Represents prototype ID.
using PrototypeId = detail::_Id<detail::_PrototypeIdTag>;

/// Represents instance ID.
using InstanceId = detail::_Id<detail::_InstanceIdTag>;

/// Represents fully-qualified ID.
using FullyQualifiedId = detail::_Id<detail::_FullyQualifiedIdTag>;



constexpr char id_separator = '#';



/**
 * Make a fully-qualified ID from the given @a prototype_id and @a instance_id.
 *
 * Example:
 * make_fqid("core.chara", "core.putit") == "core.chara#core.putit"
 */
inline FullyQualifiedId make_fqid(
    PrototypeId prototype_id,
    InstanceId instance_id)
{
    return FullyQualifiedId{
        prototype_id.get() + id_separator + instance_id.get()};
}

} // namespace elona::data



namespace std
{

template <typename Tag>
struct hash<::elona::data::detail::_Id<Tag>>
{
    size_t operator()(::elona::data::detail::_Id<Tag> id) const
    {
        return id.hash();
    }
};

} // namespace std
