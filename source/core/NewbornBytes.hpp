#pragma once

#include "NewbornMemory.hpp"

namespace Newborn {

enum class ByteOrder {
  BigEndian,
  LittleEndian,
  NoConversion
};

ByteOrder platformByteOrder();

void swapByteOrder(void* ptr, size_t len);
void swapByteOrder(void* dest, void const* src, size_t len);
}