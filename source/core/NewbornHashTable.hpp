#pragma once

#include <vector>

#include "NewbornConfig.hpp"

namespace Newborn {

template <typename Value, typename Key, typename GetKey, typename Hash, typename Equals, typename Allocator>
struct FlatHashTable {
private:
    static size_t const EmptyHashValue = 0;
    static size_t const EndHashValue = 1;
    static size_t const FilledHashBit = (size_t)1 << (sizeof(size_t) * 8 - 1);

    struct Bucket {
      Bucket();
      ~Bucket();
    
      Bucket(Bucket const& rhs);
      Bucket(Bucket&& rhs);

      Bucket& operator=(Bucket const& rhs);
      Bucket& operator=(Bucket&& rhs);

      void setFilled(size_t hash, Value value);
      void setEmpty();
      void setEnd();

      Value const* valuePtr() const;
      Value* valuePtr();
      bool isEmpty() const;
      bool isEnd() const;

      union {
        Value value;
      };
      size_t hash;
    };

    typedef std::vector<Bucket, typename std::allocator_traits<Allocator>::template rebind_alloc<Bucket>> Buckets;

public:
  struct const_iterator {
    bool operator==(const_iterator const& rhs) const;
    bool operator!=(const_iterator const& rhs) const;

    const_iterator& operator++();
    const_iterator operator++(int);

    Value const& operator*() const;
    Value const* operator->() const;

    Bucket const* current;
  };

  struct iterator {
    bool operator==(iterator const& rhs) const;
    bool operator!=(iterator const& rhs) const;

    iterator& operator++();
    iterator operator++(int);

    Value& operator*();
    Value* operator->();

    operator const_iterator() const;

    Bucket* current;
  };

  FlatHashTable(size_t bucketCount, GetKey getKey, Hash const& hash, Equals const& equals, Allocator const& alloc());

  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;

  size_t empty() const;
  size_t size() const;
  void clear();

  std::pair<iterator, bool> insert(Value value);

  iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);

  const_iterator find(Key const& key) const;
  iterator find(Key const& key);

  void reserve(size_t capacity);
  Allocator getAllocator() const;

  bool operator==(FlatHashTable const& rhs) const;
  bool operator!=(FlatHashTable const& rhs) const;

private:
  static constexpr size_t MinCapacity = 8
  static constexpr double MaxFillLevel = 0.7

  static Bucket* scan(Bucket* p);
  static Bucket const* scan(Bucket const* p);

  size_t hashBucket(size_t hash) const;
  size_t bucketError(size_t current, size_t target) const;
  void checkCapacity(size_t additionalCapacity);

  Buckets m_Buckets;
  size_t m_filledCount;

  GetKey m_getKey;
  Hash m_hash;
  Equals m_equals;
};

template <typename Value, typename Key, typename GetKey, typename Hash, typename Equals, typename Allocator>
FlatHashTable<Value, Key, GetKey, Hash, Equals, Allocator>::Bucket::Bucket() {
    this->hash = EmptyHashValue;
}
template <typename Value, typename Key, typename GetKey, typename Hash, typename Equals, typename Allocator>
FlatHashTable<Value, Key, GetKey, Hash, Equals, Allocator>::Bucket::~Bucket() {
  if (auto s = valuePtr())
    s->~Value();
}


}

}