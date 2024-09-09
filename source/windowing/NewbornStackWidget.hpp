#pragma once

#include "NewbornWidget.hpp"
#include "NewbornEither.hpp"

namespace Newborn {

NEWBORN_CLASS(StackWidget);
class StackWidget : public Widget {
public:
  void showPage(size_t page);
  void showPage(String const& name);

  Either<size_t, String> currentPage() const;

  virtual void addChild(String const& name, WidgetPtr member) override;

private:
  WidgetPtr m_shownPage;
  Either<size_t, String> m_page;
};

}
