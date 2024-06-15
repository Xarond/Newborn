#pragma once
//will create this shit later :<
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

#define STAR_CLASS(ClassName)                                     \
  class ClassName;                                                \
  using ClassName##Ptr = std::shared_ptr<ClassName>;              \
  using ClassName##ConstPtr = std::shared_ptr<const ClassName>;   \
  using ClassName##WeakPtr = std::weak_ptr<ClassName>;            \
  using ClassName##ConstWeakPtr = std::weak_ptr<const ClassName>; \
  using ClassName##UPtr = std::unique_ptr<ClassName>;             \
  using ClassName##ConstUPtr = std::unique_ptr<const ClassName>

#define STAR_STRUCT(StructName)                                     \
  struct StructName;                                                \
  using StructName##Ptr = std::shared_ptr<StructName>;              \
  using StructName##ConstPtr = std::shared_ptr<const StructName>;   \
  using StructName##WeakPtr = std::weak_ptr<StructName>;            \
  using StructName##ConstWeakPtr = std::weak_ptr<const StructName>; \
  using StructName##UPtr = std::unique_ptr<StructName>;             \
  using StructName##ConstUPtr = std::unique_ptr<const StructName>
}