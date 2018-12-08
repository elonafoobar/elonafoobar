#pragma once

#include <string>

#include "defines.hpp"

// Supresses "unused variable" warning due to Boost.Flyweight library in Clang
// compiler.
#ifdef ELONA_COMPILER_CLANG
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#endif

#include <boost/flyweight.hpp>
#include <boost/flyweight/no_locking.hpp>
#include <boost/flyweight/no_tracking.hpp>

#ifdef ELONA_COMPILER_CLANG
#pragma clang diagnostic pop
#endif



namespace elona
{

// Share memory across common instances of string IDs.
//
// Locking: The game is only single-threaded, so having a flyweight
// locking policy is unnecessary. It also causes aborts on exit.
// Tracking: Unnecessary use of memory.
using SharedId = boost::flyweight<
    std::string,
    boost::flyweights::no_tracking,
    boost::flyweights::no_locking>;

} // namespace elona
