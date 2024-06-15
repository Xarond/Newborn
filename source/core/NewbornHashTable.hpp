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
}

}