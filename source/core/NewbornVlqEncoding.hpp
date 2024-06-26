#pragma once

#include "NewbornMemory.hpp"

namespace Newborn {


template <typename OutputIterator>
size_t writeVlqU(uint64_t x, OutputIterator out) {
  size_t i;
  for (i = 9; i > 0; --i) {
    if (x & ((uint64_t)(127) << (i * 7)))
      break;
  }

  for (size_t j = 0; j < i; ++j)
    *out++ = (uint8_t)((x >> ((i - j) * 7)) & 127) | 128;

  *out++ = (uint8_t)(x & 127);
  return i + 1;
}

inline size_t vlqUSize(uint64_t x) {
  size_t i;
  for (i = 9; i > 0; --i) {
    if (x & ((uint64_t)(127) << (i * 7)))
      break;
  }
  return i + 1;
}


template <typename InputIterator>
size_t readVlqU(uint64_t& x, InputIterator in, size_t maxBytes = 10) {
  x = 0;
  for (size_t i = 0; i < min<size_t>(10, maxBytes); ++i) {
    uint8_t oct = *in++;
    x = (x << 7) | (uint64_t)(oct & 127);
    if (!(oct & 128))
      return i + 1;
  }

  return NPos;
}


template <typename OutputIterator>
size_t writeVlqI(int64_t v, OutputIterator out) {
  uint64_t target;

  // If negative, then add 1 to properly encode -2^63
  if (v < 0)
    target = ((-(v + 1)) << 1) | 1;
  else
    target = v << 1;

  return writeVlqU(target, out);
}

inline size_t vlqISize(int64_t v) {
  uint64_t target;

  if (v < 0)
    target = ((-(v + 1)) << 1) | 1;
  else
    target = v << 1;

  return vlqUSize(target);
}


template <typename InputIterator>
size_t readVlqI(int64_t& v, InputIterator in, size_t maxBytes = 10) {
  uint64_t source;
  size_t bytes = readVlqU(source, in, maxBytes);
  if (bytes == NPos)
    return NPos;

  bool negative = (source & 1);

  // If negative, then need to undo the +1 transformation to encode -2^63
  if (negative)
    v = -(int64_t)(source >> 1) - 1;
  else
    v = (int64_t)(source >> 1);

  return bytes;
}

}
