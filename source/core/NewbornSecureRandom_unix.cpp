//*************************
// Jakub Joszko 2024
//*************************
#include "NewbornSecureRandom.hpp"
#include "NewbornFile.hpp"

namespace Newborn {

ByteArray secureRandomBytes(size_t size) {
  return File::open("/dev/urandom", IOMode::Read)->readBytes(size);
}

}
