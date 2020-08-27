#pragma once

#include "../serialization/concepts.hpp"
#include "../shared_id.hpp"



// Defines several kinds of strongly-typed IDs.
namespace elona
{
namespace data
{

/// Represents prototype ID.
struct PrototypeId
{
    /// Constructs empty ID.
    PrototypeId() = default;


    /// Constructs ID from @a id.
    explicit PrototypeId(SharedId id)
        : _inner(id)
    {
    }


    /// Constructs ID from @a id.
    explicit PrototypeId(const char* id)
        : _inner(id)
    {
    }


    /// Constructs ID from @a id.
    explicit PrototypeId(const std::string& id)
        : _inner(id)
    {
    }


    /// Constructs ID from @a static_id.
    /// This implicit conversion ctor takes only char array with static size,
    /// typically string literals.
    template <size_t N>
    PrototypeId(const char (&static_id)[N])
        : _inner(static_id)
    {
    }


    /// Check equality with @a other.
    bool operator==(const PrototypeId& other) const noexcept
    {
        return _inner == other._inner;
    }


    /// Check equality with @a other.
    bool operator!=(const PrototypeId& other) const noexcept
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



/// Represents instance ID.
struct InstanceId
{
    /// Constructs empty ID.
    InstanceId() = default;


    /// Constructs ID from @a id.
    explicit InstanceId(SharedId id)
        : _inner(id)
    {
    }


    /// Constructs ID from @a id.
    explicit InstanceId(const char* id)
        : _inner(id)
    {
    }


    /// Constructs ID from @a id.
    explicit InstanceId(const std::string& id)
        : _inner(id)
    {
    }


    /// Constructs ID from @a static_id.
    /// This implicit conversion ctor takes only char array with static size,
    /// typically string literals.
    template <size_t N>
    InstanceId(const char (&static_id)[N])
        : _inner(static_id)
    {
    }


    /// Check equality with @a other.
    bool operator==(const InstanceId& other) const noexcept
    {
        return _inner == other._inner;
    }


    /// Check equality with @a other.
    bool operator!=(const InstanceId& other) const noexcept
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

} // namespace data
} // namespace elona



namespace std
{

template <>
struct hash<::elona::data::PrototypeId>
{
    size_t operator()(::elona::data::PrototypeId id) const
    {
        return id.hash();
    }
};



template <>
struct hash<::elona::data::InstanceId>
{
    size_t operator()(::elona::data::InstanceId id) const
    {
        return id.hash();
    }
};

} // namespace std
