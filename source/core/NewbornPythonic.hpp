#pragma once

#include "NewbornAlgorithm.hpp"

namespace Newborn {

template <typename Iterator, typename Functor>
bool any(Iterator iterBegin, Iterator iterEnd, Functor const& f) {
    for (; iterBegin != iterEnd; iterBegin++)
        if (f(*iterBegin))
            return true;
        return false;
}

}