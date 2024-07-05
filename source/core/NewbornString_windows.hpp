#pragma once

#include <windows.h>

#include "NewbornString.hpp"

namespace Newborn {

String utf16ToString(WCHAR const* s);
unique_ptr<WCHAR[]> stringToUtf16(String const& s);

}
