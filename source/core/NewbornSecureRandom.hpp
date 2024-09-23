#pragma once

#include "NewbornByteArray.hpp"

namespace Newborn {

// Generate cryptographically secure random numbers for usage in password salts
// and such using OS facilities
ByteArray secureRandomBytes(size_t size);

}
