#pragma once
#include <string>

// Assumes that a compiler just ignores unknown pragmas.
// Supresses "unused variable" warning due to Boost.Flyweight library.
// This warning is reported only by Clang.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#include <boost/flyweight.hpp>
#include <boost/flyweight/no_locking.hpp>
#include <boost/flyweight/no_tracking.hpp>
#pragma clang diagnostic pop



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
