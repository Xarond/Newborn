#pragma once

#include <QString>

#include "NewbornString.hpp"

namespace Newborn {

inline String toSString(QString const& str) {
  return String(str.toUtf8().data());
}

inline QString toQString(String const& str) {
  return QString::fromUtf8(str.utf8Ptr(), str.utf8Size());
}

}
