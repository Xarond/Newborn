#pragma once

namespace Newborn {

NEWBORN_CLASS(Image);
Image scaleNearest(Image const& srcImage, Vec2F const& scale);
Image scaleBilinear(Image const& srcImage, Vec2F const& scale);
Image scaleBicubic(Image const& srcImage, Vec2F const& scale);

}