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

template <typename Iterable, typename Functor>
bool any(Iterable const& iter, Functor const& f) {
    return any(std::begin(iter), std::end(iter), f);
}

template <typename Iterable>
bool any(Iterable const& iter) {
    typedef decltype(*std::begin(iter)) IteratorValue;
    std::function<bool(IteratorValue)> compare = [](IteratorValue const& i) { return (bool)i; };
    return any(std::begin(iter), std::end(iter), compare);
}

template <typename Iterator, typename Functor>
bool all(Iterator iterBegin, Iterator iterEnd, Functor const& f) {
    for (; iterBegin != iterEnd; iterBegin++)
        if (!f(*iterBegin))
            return false;
        return true;
}

template <typename Iterator>
bool all(Iterator const& iterBegin, Iterator const& iterEnd) {
  typedef typename std::iterator_traits<Iterator>::value_type IteratorValue;
  std::function<bool(IteratorValue)> compare = [](IteratorValue const& i) { return (bool)i; };
  return all(iterBegin, iterEnd, compare);
}

template <typename Iterable, typename Functor>
bool all(Iterable const& iter, Functor const& f) {
  return all(std::begin(iter), std::end(iter), f);
}

template <typename Iterable>
bool all(Iterable const& iter) {
  typedef decltype(*std::begin(iter)) IteratorValue;
  std::function<bool(IteratorValue)> compare = [](IteratorValue const& i) { return (bool)i; };
  return all(std::begin(iter), std::end(iter), compare);
}
}