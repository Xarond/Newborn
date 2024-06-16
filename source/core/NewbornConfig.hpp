#pragma once

#include "NewbornPch.hpp"

namespace Newborn {

// Some common std namespaces includes
using std::size_t;

using std::swap;
using std::move;

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
using std::make_unique;
using std::static_pointer_cast;
using std::dynamic_pointer_cast;
using std::const_pointer_cast;
using std::enable_shared_from_this;

using std::pair;
using std::make_pair;

using std::tuple;
using std::make_tuple;
using std::tuple_element;
using std::get;
using std::tie;
using std::ignore;

using std::initializer_list;

using std::min;
using std::max;

using std::bind;
using std::function;
using std::forward;
using std::mem_fn;
using std::ref;
using std::cref;
using namespace std::placeholders;
using namespace std::string_literals;

using std::prev;
//using std::next;

using std::atomic;
using std::atomic_flag;
using std::atomic_load;
using std::atomic_store;

#ifndef NDEBUG
#define NEWBORN_DEBUG 1
constexpr bool DebugEnabled = true;
#else
constexpr bool DebugEnabled = false;
#endif

size_t const NPos = (size_t)(-1);

typedef int64_t StreamOffset;

#define _unused(x) ((void)x)

#define NEWBORN_CLASS(ClassName)                                  \
  class ClassName;                                                \
  using ClassName##Ptr = std::shared_ptr<ClassName>;              \
  using ClassName##ConstPtr = std::shared_ptr<const ClassName>;   \
  using ClassName##WeakPtr = std::weak_ptr<ClassName>;            \
  using ClassName##ConstWeakPtr = std::weak_ptr<const ClassName>; \
  using ClassName##UPtr = std::unique_ptr<ClassName>;             \
  using ClassName##ConstUPtr = std::unique_ptr<const ClassName>

#define NEWBORN_STRUCT(StructName)                                  \
  struct StructName;                                                \
  using StructName##Ptr = std::shared_ptr<StructName>;              \
  using StructName##ConstPtr = std::shared_ptr<const StructName>;   \
  using StructName##WeakPtr = std::weak_ptr<StructName>;            \
  using StructName##ConstWeakPtr = std::weak_ptr<const StructName>; \
  using StructName##UPtr = std::unique_ptr<StructName>;             \
  using StructName##ConstUPtr = std::unique_ptr<const StructName>

  #define NEWBORN_QUOTE(name) #name
  #define NEWBORN_STR(macro) NEWBORN_QUOTE(macro)
}

