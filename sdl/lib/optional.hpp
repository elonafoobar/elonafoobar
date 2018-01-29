#pragma once


#if __has_include(<optional>)

# include <optional>
# define ELONA_LIB_NAMESPACE_OPTIONAL std

#elif __has_include(<experimental/optional>)

# include <experimental/optional>
# define ELONA_LIB_NAMESPACE_OPTIONAL std::experimental

#else
# error "Not found <optional> and <experimental/optional>"
#endif


namespace lib
{


using ELONA_LIB_NAMESPACE_OPTIONAL::optional;
using ELONA_LIB_NAMESPACE_OPTIONAL::make_optional;
using ELONA_LIB_NAMESPACE_OPTIONAL::nullopt;


}



#undef ELONA_LIB_NAMESPACE_OPTIONAL
