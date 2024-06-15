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
    using ClassNameUPtr = std::unique_ptr<ClassName>;


#define NEWBORN_STRUCT(StructName)
    struct StructName;
    using StructNameUPtr = std::unique_ptr<StructName>;
}