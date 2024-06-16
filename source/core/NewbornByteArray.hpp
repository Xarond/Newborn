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
  ByteArray(ByteArray const& b);
  ByteArray(ByteArray&& b) noexcept;
  ~ByteArray();

  ByteArray& operator=(ByteArray const& b);
  ByteArray& operator=(ByteArray&& b) noexcept;

  char const* ptr() const;
  char* ptr();

  size_t size() const;
  //Max size before rellocation
  size_t capacity() const;
  //Is zero size
  bool empty() const;
  // Set size to 0
  void clear();
  // Set size to 0 and deallocate buffer
  void reset();

  void reserve(size_t capacity);
  void resize(size_t size);
  void resize(size_t size, char f);

  void fill(char c);
  void fill(size_t size, char c);

  void append(ByteArray const& b);
  void append(char const* data, size_t len);
  void appendByte(char b);

  void copyTo(char* data, size_t len) const;
  void copyTo(char* data) const;
};
}