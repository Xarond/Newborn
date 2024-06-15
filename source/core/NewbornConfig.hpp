#pragma once
//will create this shit later :<
#include "NewbornPch.hpp"

namespace Newborn {

// Some common std namespaces includes
using std::size_t;

using std::swap;
using std::move;

using std::unique_ptr;

#define NEWBORN_CLASS(ClassName)
    class Classname;
    using ClassName##ConstUPtr = std::unique_ptr<const ClassName>


#define NEWBORN_STRUCT(StructName)
    struct StructName;
    using StructName##ConstUPtr = std::unique_ptr<const StructName>
}