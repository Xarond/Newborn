#include "NewbornLayout.hpp"

namespace Newborn {

Layout::Layout() {
  markAsContainer();
}

void Layout::update(float dt) {
  Widget::update(dt);
}

}
