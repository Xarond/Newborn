#pragma once

#include <map>
#include <unordered_map>

#include "NewbornFlatHashMap.hpp"
#include "NewbornList.hpp"

namespace Newborn {

NEWBORN_EXCEPTION(MapException, NewbornException);

template <typename BaseMap>
class MapMixin : public BaseMap {
public:
    typedef BaseMap Base;

    typedef typename Base::iterator iterator;
    typedef typename Base::const_iterator const_iterator;

    typedef typename Base::key_type key_type;
    typedef typename Base::mapped_type mapped_type;
    typedef typename Base::valu_type value_type;

    typedef typename std::decay<mapped_type>::type* mapped_ptr;
    typedef typename std::decay<mapped_type>::typeconst * mapped_const_ptr;
    
    template <typename MapType>
    static MapMixin from(MapType const& m);

    using Base::Base;

    List<key_type> keys() const;
    List<mapped_type> values() const;
    List<pair<key_type, mapped_type>> pairs() const;

    bool contains(key_type const& k) const;

    bool remove(key_type const& k);

    bool removeValues(mapped_type const& v);

    mapped_type take(key_type const& k);

    Maybe<mapped_type> maybeTake(key_type const& k);

    mapped_type& get(key_type const& k);
    mapped_type const& get(key_type const& k) const;

    mapped_type value(key_type const& k, mapped_type d = mapped_type()) const;

    Maybe<mapped_type> maybe(key_type const& k) const;

    mapped_const_ptr ptr(key_type const& k) const;
    mapped_ptr ptr(key_type const& k);

    key_type keyOf(mapped_type const& v) const;

    List<key_type> keysOf(mapped_type const& v) const;

    bool hasValue(mapped_type const& v) const;

    using Base::insert;

    pair<iterator, bool> insert(key_type k, mapped_type v);

    mapped_type& add(key_type k, mapped_type v);
    mapped_type& set(key_type k, mapped_type v);

    template <typename MapType>
    bool merge(MapType const& m, bool overwrite = false);
    bool operator==(MapMixin const& m) const;
};
template <typename BaseMap>
std::ostream& operator<<(std::ostream& os, MapMixin<BaseMap> const& m);

template <typename Key, typename Value, typename Compare = std::less<Key>, typename Allocator = std::allocator<pair<Key const, Value>>>
using Map = MapMixin<std::map<Key, Value, Compare, Allocator>>;

template <typename Key, typename Value, typename Hash = hash<Key>, typename Equals = std::equal_to<Key>, typename Allocator = std::allocator<pair<Key const, Value>>>
using HashMap = MapMixin<FlatHashMap<Key, Value, Hash, Equals, Allocator>>;

template <typename Key, typename Value, typename Hash = hash<Key>, typename Equals = std::equal_to<Key>, typename Allocator = std::allocator<pair<Key const, Value>>>
using StableHashMap = MapMixin<std::unordered_map<Key, Value, Hash, Equals, Allocator>>;

template <typename BaseMap>
template <typename MapType>
auto MapMixin<BaseMap>::from(MapType const& m) -> MapMixin {
  return MapMixin(m.begin(), m.end());
}

template <typename BaseMap>
auto MapMixin<BaseMap>::keys() const -> List<key_type> {
  List<key_type> klist;
  for (const_iterator i = Base::begin(); i != Base::end(); ++i)
    klist.push_back(i->first);
  return klist;
}

template <typename BaseMap>
auto MapMixin<BaseMap>::values() const -> List<mapped_type> {
  List<mapped_type> vlist;
  for (const_iterator i = Base::begin(); i != Base::end(); ++i)
    vlist.push_back(i->second);
  return vlist;
}

template <typename BaseMap>
auto MapMixin<BaseMap>::pairs() const -> List<pair<key_type, mapped_type>> {
  List<pair<key_type, mapped_type>> plist;
  for (const_iterator i = Base::begin(); i != Base::end(); ++i)
    plist.push_back(*i);
  return plist;
}

template <typename BaseMap>
bool MapMixin<BaseMap>::contains(key_type const& k) const {
  return Base::find(k) != Base::end();
}

template <typename BaseMap>
bool MapMixin<BaseMap>::remove(key_type const& k) {
  return Base::erase(k) != 0;
}

template <typename BaseMap>
bool MapMixin<BaseMap>::removeValues(mapped_type const& v) {
  bool removed = false;
  const_iterator i = Base::begin();
  while (i != Base::end()) {
    if (i->second == v) {
      Base::erase(i++);
      removed = true;
    } else {
      ++i;
    }
  }
  return removed;
}

template <typename BaseMap>
auto MapMixin<BaseMap>::take(key_type const& k) -> mapped_type {
  if (auto v = maybeTake(k))
    return v.take();
  throw MapException(strf("Key '{}' not found in Map::take()", outputAny(k)));
}

template <typename BaseMap>
auto MapMixin<BaseMap>::maybeTake(key_type const& k) -> Maybe<mapped_type> {
  const_iterator i = Base::find(k);
  if (i != Base::end()) {
    mapped_type v = std::move(i->second);
    Base::erase(i);
    return v;
  }

  return {};
}

template <typename BaseMap>
auto MapMixin<BaseMap>::get(key_type const& k) -> mapped_type& {
  iterator i = Base::find(k);
  if (i == Base::end())
    throw MapException(strf("Key '{}' not found in Map::get()", outputAny(k)));
  return i->second;
}

template <typename BaseMap>
auto MapMixin<BaseMap>::get(key_type const& k) const -> mapped_type const& {
  const_iterator i = Base::find(k);
  if (i == Base::end())
    throw MapException(strf("Key '{}' not found in Map::get()", outputAny(k)));
  return i->second;
}

template <typename BaseMap>
auto MapMixin<BaseMap>::value(key_type const& k, mapped_type d) const -> mapped_type {
  const_iterator i = Base::find(k);
  if (i == Base::end())
    return d;
  else
    return i->second;
}

template <typename BaseMap>
auto MapMixin<BaseMap>::maybe(key_type const& k) const -> Maybe<mapped_type> {
  auto i = Base::find(k);
  if (i == Base::end())
    return {};
  else
    return i->second;
}

template <typename BaseMap>
auto MapMixin<BaseMap>::ptr(key_type const& k) const -> mapped_const_ptr {
  auto i = Base::find(k);
  if (i == Base::end())
    return nullptr;
  else
    return &i->second;
}

template <typename BaseMap>
auto MapMixin<BaseMap>::ptr(key_type const& k) -> mapped_ptr {
  auto i = Base::find(k);
  if (i == Base::end())
    return nullptr;
  else
    return &i->second;
}

template <typename BaseMap>
auto MapMixin<BaseMap>::keyOf(mapped_type const& v) const -> key_type {
  for (const_iterator i = Base::begin(); i != Base::end(); ++i) {
    if (i->second == v)
      return i->first;
  }
  throw MapException(strf("Value '{}' not found in Map::keyOf()", outputAny(v)));
}

template <typename BaseMap>
auto MapMixin<BaseMap>::keysOf(mapped_type const& v) const -> List<key_type> {
  List<key_type> keys;
  for (const_iterator i = Base::begin(); i != Base::end(); ++i) {
    if (i->second == v)
      keys.append(i->first);
  }
  return keys;
}

template <typename BaseMap>
auto MapMixin<BaseMap>::hasValue(mapped_type const& v) const -> bool {
  for (const_iterator i = Base::begin(); i != Base::end(); ++i) {
    if (i->second == v)
      return true;
  }
  return false;
}

template <typename BaseMap>
auto MapMixin<BaseMap>::insert(key_type k, mapped_type v) -> pair<iterator, bool> {
  return Base::insert(value_type(std::move(k), std::move(v)));
}

template <typename BaseMap>
auto MapMixin<BaseMap>::add(key_type k, mapped_type v) -> mapped_type& {
  auto pair = Base::insert(value_type(std::move(k), std::move(v)));
  if (!pair.second)
    throw MapException(strf("Entry with key '{}' already present.", outputAny(k)));
  else
    return pair.first->second;
}

template <typename BaseMap>
auto MapMixin<BaseMap>::set(key_type k, mapped_type v) -> mapped_type& {
  auto i = Base::find(k);
  if (i != Base::end()) {
    i->second = std::move(v);
    return i->second;
  } else {
    return Base::insert(value_type(std::move(k), std::move(v))).first->second;
  }
}

template <typename BaseMap>
template <typename OtherMapType>
bool MapMixin<BaseMap>::merge(OtherMapType const& m, bool overwrite) {
  return mapMerge(*this, m, overwrite);
}

template <typename BaseMap>
bool MapMixin<BaseMap>::operator==(MapMixin const& m) const {
  return this == &m || mapsEqual(*this, m);
}

template <typename MapType>
void printMap(std::ostream& os, MapType const& m) {
  os << "{ ";
  for (auto i = m.begin(); i != m.end(); ++i) {
    if (m.begin() == i)
      os << "\"";
    else
      os << ", \"";
    os << i->first << "\" : \"" << i->second << "\"";
  }
  os << " }";
}

template <typename BaseMap>
std::ostream& operator<<(std::ostream& os, MapMixin<BaseMap> const& m) {
  printMap(os, m);
  return os;
}

}

template <typename BaseMap>
struct fmt::formatter<Newborn::MapMixin<BaseMap>> : ostream_formatter {};

