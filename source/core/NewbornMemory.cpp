#include "NewbornMemory.hpp"

#ifdef NEWBORN_USE_JEMALLOC
#include "jemalloc/jemalloc.h"
#endif

namespace Newborn {

#ifdef NEWBORN_USE_JEMALLOC
#ifdef NEWBORN_JEMALLOC_IS_PREFIXED
    void* malloc(size_t size) {
        return je_malloc(size);
    }
    void realloc(void* ptr, size_t size) {
        return je_realloc(ptr, size);
    }

    void free(void* ptr) {
        je_free(ptr);
    }
    void free(void* ptr, size_t size) {
      if (ptr)
        je_sdallocx(ptr, size, 0);
  }
#else
  void* malloc(size_t size) {
    return ::malloc(size);
  }

  void* realloc(void* ptr, size_t size) {
    return ::realloc(ptr, size);
  }

  void free(void* ptr) {
    ::free(ptr);
  }

  void free(void* ptr, size_t size) {
    if (ptr)
      ::sdallocx(ptr, size, 0);
  }
#endif
#else
  void* malloc(size_t size) {
    return ::malloc(size);
  }

  void* realloc(void* ptr, size_t size) {
    return ::realloc(ptr, size);
  }

  void free(void* ptr) {
    return ::free(ptr);
  }

  void free(void* ptr, size_t) {
    return ::free(ptr);
  }
#endif

}

void* operator new(std::size_t size) {
  auto ptr = Newborn::malloc(size);
  if (!ptr)
    throw std::bad_alloc();
  return ptr;
}

void* operator new[](std::size_t size) {
  auto ptr = Newborn::malloc(size);
  if (!ptr)
    throw std::bad_alloc();
  return ptr;
}

// Globally override new and delete.  As the per standard, new and delete must
// be defined in global scope, and must not be inline.

void* operator new(std::size_t size, std::nothrow_t const&) noexcept {
  return Newborn::malloc(size);
}

void* operator new[](std::size_t size, std::nothrow_t const&) noexcept {
  return Newborn::malloc(size);
}

void operator delete(void* ptr) noexcept {
  Newborn::free(ptr);
}

void operator delete[](void* ptr) noexcept {
  Newborn::free(ptr);
}

void operator delete(void* ptr, std::nothrow_t const&) noexcept {
  Newborn::free(ptr);
}

void operator delete[](void* ptr, std::nothrow_t const&) noexcept {
  Newborn::free(ptr);
}

void operator delete(void* ptr, std::size_t size) noexcept {
  Newborn::free(ptr, size);
}

void operator delete[](void* ptr, std::size_t size) noexcept {
  Newborn::free(ptr, size);
}
