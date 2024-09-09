#include "NewbornImageStretchWidget.hpp"

namespace Newborn {

ImageStretchWidget::ImageStretchWidget(ImageStretchSet const& imageStretchSet, GuiDirection direction)
  : m_imageStretchSet(imageStretchSet), m_direction(direction) {

}

void ImageStretchWidget::renderImpl() {
  context()->drawImageStretchSet(m_imageStretchSet, RectF(screenBoundRect()), m_direction);
}

}
