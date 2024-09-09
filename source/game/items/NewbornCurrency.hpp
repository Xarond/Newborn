#pragma once

#include "NewbornItem.hpp"

namespace Newborn {

NEWBORN_CLASS(CurrencyItem);

class CurrencyItem : public Item {
public:
  CurrencyItem(Json const& config, String const& directory);

  virtual ItemPtr clone() const override;

  virtual String pickupSound() const override;

  String currencyType();

  // Value of a single instance of this currency
  uint64_t currencyValue();

  // Total value of all currencies (so currencyValue * count)
  uint64_t totalValue();

private:
  String m_currency;
  uint64_t m_value;
};

}
