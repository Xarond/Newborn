//*************************
// Jakub Joszko 2024
//*************************
#include "NewbornSecureRandom.hpp"
#include <windows.h>
#include <wincrypt.h>

namespace Newborn {

ByteArray secureRandomBytes(size_t size) {
  HCRYPTPROV context = 0;
  auto res = ByteArray(size, '\0');

  CryptAcquireContext(&context, 0, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
  auto success = CryptGenRandom(context, size, (PBYTE)res.ptr());
  CryptReleaseContext(context, 0);

  if (!success)
    throw NewbornException("Could not read random bytes from source.");

  return res;
}

}
