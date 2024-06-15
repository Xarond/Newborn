#pragma once

#include <new>

#include "NewbornConfig.hpp"

namespace Newborn {
void* malloc(size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);
void free(void* ptr, size_t size);
}  // namespace Newborn