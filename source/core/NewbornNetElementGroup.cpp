//*************************
// Jakub Joszko 2024
//*************************
#include "NewbornNetElementGroup.hpp"

namespace Newborn {

void NetElementGroup::addNetElement(NetElement* element, bool propagateInterpolation) {
  newbornAssert(!m_elements.any([element](auto p) { return p.first == element; }));

  element->initNetVersion(m_version);
  if (m_interpolationEnabled && propagateInterpolation)
    element->enableNetInterpolation(m_extrapolationHint);
  m_elements.append(pair<NetElement*, bool>(element, propagateInterpolation));
}

void NetElementGroup::clearNetElements() {
  m_elements.clear();
}

void NetElementGroup::initNetVersion(NetElementVersion const* version) {
  m_version = version;
  for (auto& p : m_elements)
    p.first->initNetVersion(m_version);
}

void NetElementGroup::netStore(DataStream& ds) const {
  for (auto& p : m_elements)
    p.first->netStore(ds);
}

void NetElementGroup::netLoad(DataStream& ds) {
  for (auto& p : m_elements)
    p.first->netLoad(ds);
}

void NetElementGroup::enableNetInterpolation(float extrapolationHint) {
  m_interpolationEnabled = true;
  m_extrapolationHint = extrapolationHint;
  for (auto& p : m_elements) {
    if (p.second)
      p.first->enableNetInterpolation(extrapolationHint);
  }
}

void NetElementGroup::disableNetInterpolation() {
  m_interpolationEnabled = false;
  m_extrapolationHint = 0;
  for (auto& p : m_elements) {
    if (p.second)
      p.first->disableNetInterpolation();
  }
}

void NetElementGroup::tickNetInterpolation(float dt) {
  if (m_interpolationEnabled) {
    for (auto& p : m_elements)
      p.first->tickNetInterpolation(dt);
  }
}

bool NetElementGroup::writeNetDelta(DataStream& ds, uint64_t fromStep) const {
  if (m_elements.size() == 0) {
    return false;
  } else if (m_elements.size() == 1) {
    return m_elements[0].first->writeNetDelta(ds, fromStep);
  } else {
    bool deltaWritten = false;
    for (uint64_t i = 0; i < m_elements.size(); ++i) {
      if (m_elements[i].first->writeNetDelta(m_buffer, fromStep)) {
        deltaWritten = true;
        ds.writeVlqU(i + 1);
        ds.writeBytes(m_buffer.data());
        m_buffer.clear();
      }
    }
    if (deltaWritten)
      ds.writeVlqU(0);
    return deltaWritten;
  }
}

void NetElementGroup::readNetDelta(DataStream& ds, float interpolationTime) {
  if (m_elements.size() == 0) {
    throw IOException("readNetDelta called on empty NetElementGroup");
  } else if (m_elements.size() == 1) {
    m_elements[0].first->readNetDelta(ds, interpolationTime);
  } else {
    uint64_t readIndex = ds.readVlqU();
    for (uint64_t i = 0; i < m_elements.size(); ++i) {
      if (readIndex == 0 || readIndex - 1 > i) {
        if (m_interpolationEnabled)
          m_elements[i].first->blankNetDelta(interpolationTime);
      } else if (readIndex - 1 == i) {
        m_elements[i].first->readNetDelta(ds, interpolationTime);
        readIndex = ds.readVlqU();
      } else {
        throw IOException("group indexes out of order in NetElementGroup::readNetDelta");
      }
    }
  }
}

void NetElementGroup::blankNetDelta(float interpolationTime) {
  if (m_interpolationEnabled) {
    for (auto& p : m_elements)
      p.first->blankNetDelta(interpolationTime);
  }
}

}
