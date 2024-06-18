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

struct SliceIndex {
    SliceIndex() : index(0), given(false) {}
    SliceIndex(int i) : index(i), given(true) {}

    int index;
    int given;
};

SliceIndex const SliceNil = SliceIndex();

template <typename Res, typename In>
Res slice(In const& r, SliceIndex a, SliceIndex b = SliceIndex(), int j = 1) {
  int size = (int)r.size();
  int start, end;

  // Throw exception on j == 0?
  if (j == 0 || size == 0)
    return Res();

  if (!a.given) {
    if (j > 0)
      start = 0;
    else
      start = size - 1;
  } else if (a.index < 0) {
    if (-a.index > size - 1)
      start = 0;
    else
      start = size - -a.index;
  } else {
    if (a.index > size)
      start = size;
    else
      start = a.index;
  }

  if (!b.given) {
    if (j > 0)
      end = size;
    else
      end = -1;
  } else if (b.index < 0) {
    if (-b.index > size - 1) {
      end = -1;
    } else {
      end = size - -b.index;
    }
  } else {
    if (b.index > size - 1) {
      end = size;
    } else {
      end = b.index;
    }
  }

  if (start < end && j < 0)
    return Res();
  if (start > end && j > 0)
    return Res();

  Res returnSlice;
  int i;
  for (i = start; i < end; i += j)
    returnSlice.push_back(r[i]);

  return returnSlice;
}

template <typename T>
T slice(T const& r, SliceIndex a, SliceIndex b = SliceIndex(), int j = 1)  {
    return slice<T, T>(r, a, b, j);
}

template <typename IteratorT>
class ZipWrapperIterator {
private:
    IteratorT current;
    IteratorT last;
    bool atEnd;

public:
    typedef IteratorT Iterator;
    typedef decltype(*std::declval<Iterator>()) IteratorValue;
    typedef tuple<IteratorValue> value_type;

    ZipWrapperIterator() : atEnd(true) {}

    ZipWrapperIterator(Iterator current, Iterator last) : current(current), last(last) {
        atEnd = current == last;
    }

    ZipWrapperIterator operator++() {
        if (!atEnd) {
            ++current;
            atEnd = current == last;
        }

        return *this;
    }

    value_type operator*() const {
        return std::tuple<IteratorValue>(*current);
    }

    bool operator==(ZipWrapperIterator const& rhs) const {
        return (atEnd && rhs.atEnd) || (!atEnd && !rhs.atEnd && current == rhs.current && last == rhs.last);
    }

    bool operator!=(ZipWrapperIterator const& rhs) const {
        return !(*this == rhs);
  }

    explicit operator bool() const {
        return !atEnd;
  }

    ZipWrapperIterator begin() const {
        return *this;
  }

    ZipWrapperIterator end() const {
        return ZipWrapperIterator();
  }
};
}