#pragma once

#include <new>

#include "NewbornConfig.hpp"

namespace Newborn {

// Don't want to override global C allocation functions, as our API is
// different.

void* malloc(size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);
void free(void* ptr, size_t size);

}
