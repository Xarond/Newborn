#pragma once

#include "NewbornException.hpp"

namespace Newborn {

// Function that does nothing and takes any number of arguments
template <typename... T>
void nothing(T&&...) {}

template <typename ToType>
struct construct {
    template <typename... FromTypes>
    ToType operator()(FromTypes&&... fromTypes) const {
        return ToType(std::forward<FromTypes>(fromTypes)...);
    }
};

struct identity {
    template <typename U>
    constexpr decltype(auto) operator()(U&& v) const {
        return std::forward<U>(v);
    }
};

template <typename Func>
struct SwallowReturn {
    template <typename... T>
    void operator()(T&&... args) {
        func(std::forward<T>(args)...);
    }

    Func func;
};

template <typename Func>
SwallowReturn<Func> swallow(Func f) {
    return SwallowReturn<Func>{std::move(f)};
}

struct Empty {
    bool operator==(Empty const) const {
        return true;
    }

    bool operator<(Empty const) const {
        return false;
    }
};

template <typename FirstFunction, typename SecondFunction>
struct FunctionComposer {
    FirstFunction f1;
    SecondFunction f2;

    template <typename... T>
    decltype(auto) operator()(T&&... args) {
        return f1(f2(std::forward))
    }
};

template <typename FirstFunction, typename SecondFunction>
decltype(auto) compose(FirstFunction&& firstFunction, SecondFunction&& secondFunction) {
    return FunctionComposer<FirstFunction, SecondFunction>{std::move(std::forward<FirstFunction>(firstFunction)), std::move(std::forward<SecondFunction>(secondFunction))}
}
template <typename FirstFunction, typename SecondFunction, typename ThirdFunction, typename... RestFunctions>
decltype(auto) compose(FirstFunction firstFunction, SecondFunction secondFunction, ThirdFunction thirdFunction, RestFunctions... restFunctions) {
  return compose(std::forward<FirstFunction>(firstFunction), compose(std::forward<SecondFunction>(secondFunction), compose(std::forward<ThirdFunction>(thirdFunction), std::forward<RestFunctions>(restFunctions)...)));
}

template <typename Container, typename Value, typename Function>
Value fold(Container const& l, Value v, Function f) {
    auto i = l.begin();
    auto e = l.end();
    while (i != e) {
        v = f(v, *i);
        ++i;
    }
    return v;
}

template <typename Container, typename Function>
typename Container::value_type fold1(Container const& l, Function f) {
    typename Container::value_type res = {};
    typename Container::const_iterator i = l.begin();
    typename Container::const_iterator e = l.end();

    if(i == e)
        return res;

    res = *i;
    ++i;
    while (i != e) {
        res =f(res, *i);
        ++i;
    }
    return res;
}

template <typename Container>
Container intersect(Container const& a, Container const& b) {
    Container r;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(r, r.end()));
    return r;
}

template <typename MapType1, typename MapType2>
bool mapMerge(MapType1& targetMap, MapType2 const& sourceMap, bool overwrite = false) {
  bool noCommonKeys = true;
  for (auto i = sourceMap.begin(); i != sourceMap.end(); ++i) {
    auto res = targetMap.insert(*i);
    if (!res.second) {
      noCommonKeys = false;
      if (overwrite)
        res.first->second = i->second;
    }
  }
  return noCommonKeys;
}

template <typename MapType1, typename MapType2>
bool mapsEqual(MapType1 const& m1, MapType2 const& m2) {
  if (&m1 == &m2)
    return true;

  if (m1.size() != m2.size())
    return false;

  for (auto const& m1pair : m1) {
    auto m2it = m2.find(m1pair.first);
    if (m2it == m2.end() || !(m2it->second == m1pair.second))
      return false;
  }

  return true;
}


//TODO: FINISH ALGORITHM
// MAKE LIST HEADER
}