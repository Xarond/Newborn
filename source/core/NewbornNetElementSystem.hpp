//*************************
// Jakub Joszko 2024
//*************************
#pragma once

#include "NewbornNetElementBasicFields.hpp"
#include "NewbornNetElementFloatFields.hpp"
#include "NewbornNetElementSyncGroup.hpp"
#include "NewbornNetElementDynamicGroup.hpp"
#include "NewbornNetElementContainers.hpp"
#include "NewbornNetElementSignal.hpp"
#include "NewbornNetElementTop.hpp"

namespace Newborn {

// Makes a good default top-level NetElement group.
typedef NetElementTop<NetElementCallbackGroup> NetElementTopGroup;

}
