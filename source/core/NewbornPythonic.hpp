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

template <typename Iterator>
bool any(Iterator const& iterBegin, Iterator const& iterEnd) {
    typedef typename std::iterator_traits<Iterator>::value_type IteratorValue;
    std::function<bool(IteratorValue)> compare = [](IteratorValue const& i) { return (bool)i; };
    return any(iterBegin, iterEnd, compare);
}
}