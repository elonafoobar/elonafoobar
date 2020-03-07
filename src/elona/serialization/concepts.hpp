#pragma once

#include <type_traits>



namespace elona::serialization::concepts
{

namespace impl
{

template <typename>
struct is_iarchive : std::false_type
{
};

template <typename>
struct is_oarchive : std::false_type
{
};


template <typename...>
std::false_type has_serialize_method(long);

template <
    typename T,
    typename Archive,
    typename = decltype(std::declval<T>().serialize(std::declval<Archive&>()))>
std::true_type has_serialize_method(int);

} // namespace impl



template <typename T>
inline constexpr bool is_iarchive_v = impl::is_iarchive<T>::value;

template <typename T>
inline constexpr bool is_oarchive_v = impl::is_oarchive<T>::value;


template <typename T, typename Archive>
inline constexpr bool has_serialize_method_v =
    decltype(impl::has_serialize_method<T, Archive>(0)){};

} // namespace elona::serialization::concepts



/**
 * Internal macros to simplify template specialization.
 *
 * Usage:
 * struct IArchive
 * {
 *     // snip
 * };
 *
 * ELONA_SERIALIZATION_CONCEPTS_IMPL_IS_IARCHIVE(IArchive)
 */
#define ELONA_SERIALIZATION_CONCEPTS_IMPL_IS_IARCHIVE(T) \
    namespace elona::serialization::concepts::impl \
    { \
    template <> \
    struct is_iarchive<T> : std::true_type \
    { \
    }; \
    }

#define ELONA_SERIALIZATION_CONCEPTS_IMPL_IS_OARCHIVE(T) \
    namespace elona::serialization::concepts::impl \
    { \
    template <> \
    struct is_oarchive<T> : std::true_type \
    { \
    }; \
    }



#define ELONA_SERIALIZATION_ENABLE_IF(condition) \
    ::std::enable_if_t<(condition), ::std::nullptr_t> = nullptr


#define ELONA_SERIALIZATION_CONCEPTS_HAS_SERIALIZE_METHOD(T, Archive) \
    ELONA_SERIALIZATION_ENABLE_IF(( \
        ::elona::serialization::concepts::has_serialize_method_v<T, Archive>))
