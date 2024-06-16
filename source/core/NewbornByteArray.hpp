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

  void copyTo(char* data, size_t pos, size_t len) const;

  void writeFrom(char const* data, size_t pos, size_t len);

  ByteArray sub(size_t b, size_t s) const;
  ByteArray left(size_t s) const;
  ByteArray right(size_t s) const;

  void trimLeft(size_t s);
  void trimRight(size_t s);

  size_t diffChar(ByteArray const& b) const;
  int compare(ByteArray const& b) const;

  template <typename Combiner>
  ByteArray combineWith(Combiner&& combine, ByteArray const& rhs, bool extend = false);

  ByteArray andWith(ByteArray const& rhs, bool extend = false);
  ByteArray orWith(ByteArray const& rhs, bool extend = false);
  ByteArray xorWith(ByteArray const& rhs, bool extend = false);

  iterator begin();
  iterator end();
  
  const_iterator begin() const;
  const_iterator end() const;

  void insert(size_t pos, char byte);
  iterator insert(const_iterator pos, char byte);
  void push_back(char byte);

  char& operator[](size_t i);
  char operator[](size_t i) const;
  char at(size_t i) const;

  bool operator<(ByteArray const& b) const;
  bool operator==(ByteArray const& b) const;
  bool operator!=(ByteArray const& b) const;

private:
  char* m_data;
  size_t m_capacity;
  size_t m_size;
};

template <>
struct hash<ByteArray> {
  size_t operator()(ByteArray const& b) const;
};

std::ostream& operator<<(std::ostream& os, ByteArray const& b);

inline void ByteArray::clear() {
    resize(0);
}

inline void ByteArray::resize(size_t size) {
    reserve(size);
    m_size = size;
}

inline void ByteArray::append(ByteArray const& b) {
    append(b.ptr(), b.size());
}

inline void ByteArray::append(const char* data, size_t len) {
  resize(m_size + len);
  std::memcpy(m_data + m_size - len, data, len);
}
}