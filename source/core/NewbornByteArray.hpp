#pragma once

#include "NewbornHash.hpp"
#include "NewbornException.hpp"
#include "NewbornFormat.hpp"

namespace Newborn {

NEWBORN_CLASS(ByteArray);
// Sluchaj kurwa zydzie jebany
// Class to hold an array of bytes.  Contains an internal buffer that may be
// larger than what is reported by size(), to avoid repeated allocations when a
// ByteArray grows.
class ByteArray {
public:
  typedef char value_type;
  typedef char* iterator;
  typedef char const* const_iterator;

  static ByteArray fromCString(char const* str);
  // Same, but includes the trailing '\0'
  static ByteArray fromCStringWithNull(char const* str);
  static ByteArray withReserve(size_t capacity);

  ByteArray();
  ByteArray(size_t dataSize, char c);
  ByteArray(char const& data, size_t dataSize);
};
}