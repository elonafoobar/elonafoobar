#pragma once
#include <string>
#include <boost/flyweight.hpp>
#include <boost/flyweight/no_locking.hpp>
#include <boost/flyweight/no_tracking.hpp>

namespace elona
{

// Share memory across common instances of string IDs.
//
// Locking: The game is only single-threaded, so having a flyweight
// locking policy is unnecessary. It also causes aborts on exit.
// Tracking: Unnecessary use of memory.
typedef boost::flyweight<
    std::string,
    boost::flyweights::no_tracking,
    boost::flyweights::no_locking>
    shared_id;

} // namespace elona
