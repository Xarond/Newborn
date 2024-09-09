#pragma once

#include "NewbornList.hpp"

NEWBORN_STRUCT(PreviewTile);

NEWBORN_CLASS(PreviewTileTool);

namespace Newborn {

class PreviewTileTool {
public:
  virtual ~PreviewTileTool() {}
  virtual List<PreviewTile> previewTiles(bool shifting) const = 0;
};

}
