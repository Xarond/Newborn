#pragma once

#include "NewbornVariant.hpp"
#include "NewbornImage.hpp"
#include "NewbornPoly.hpp"
#include "NewbornJson.hpp"
#include "NewbornBiMap.hpp"
#include "NewbornRefPtr.hpp"

namespace Newborn {

NEWBORN_EXCEPTION(RendererException, NewbornException);

class Texture;
typedef RefPtr<Texture> TexturePtr;

NEWBORN_CLASS(TextureGroup);
NEWBORN_CLASS(RenderBuffer);
NEWBORN_CLASS(Renderer);

enum class TextureAddressing {
    Clamp,
    Wrap
};
extern EnumMap<TextureAddressing> const TextureAddressingNames;

enum class TextureFiltering {
    Nearest,
    Linear
};
extern EnumMap<TextureFiltering> const TextureFilteringNames;

enum class TextureGroupSize {
    Small,
    Medium,
    Large
};

struct RenderVertex {
    Vec2F screenCoordinate;
    Vec2F textureCoordinate;
    Vec4B color;
    float param1;
};

class RenderTriangle {
public:
    RenderTriangle() = default;
    RenderTriangle(Vec2F posA, Vec2F posB, Vec2F posC, Vec4B color = Vec4B::filled(255), float param1 = 0.0f);
    RenderTriangle(TexturePtr tex, Vec2F posA, Vec2F uvA, Vec2F posB, Vec2F uvB, Vec2F posC, Vec2F uvC, Vec4B color = Vec4B::filled(255), float param1 = 0.0f);

    TexturePtr texture;
    RenderVertex a, b, c;
};

class RenderQuad {
public:
    RenderQuad() = default;
    RenderQuad(Vec2F posA, Vec2F posB, Vec2F posC, Vec2F posD, Vec4B color = Vec4B::filled(255), float param1 = 0.0f);
    RenderQuad(TexturePtr tex, Vec2F minScreen, float textureScale = 1.0f, Vec4B color = Vec4B::filled(255), float param1 = 0.0f);
    RenderQuad(TexturePtr tex, RectF const& screenCoords, Vec4B color = Vec4B::filled(255), float param1 = 0.0f);
    RenderQuad(TexturePtr tex, Vec2F posA, Vec2F uvA, Vec2F posB, Vec2F uvB, Vec2F posC, Vec2F uvC, Vec2F posD, Vec2F uvD, Vec4B color = Vec4B::filled(255), float param1 = 0.0f);
    RenderQuad(TexturePtr tex, RenderVertex vA, RenderVertex vB, RenderVertex vC, RenderVertex vD);
    RenderQuad(RectF const& rect, Vec4B color = Vec4B::filled(255), float param1 = 0.0f);

    TexturePtr texture;
    RenderVertex a, b, c, d;
};

class RenderPoly {
public:
    RenderPoly() = default;
    RenderPoly(List<Vec2F> const& verts, Vec4B color, float param1 = 0.0f);

    TexturePtr texture;
    List<RenderVertex> vertexes;
};

RenderQuad renderTexturedRect(TexturePtr texture, Vec2F minScreen, float textureScale = 1.0f, Vec4B color = Vec4B::filled(255), float param1 = 0.0f);
RenderQuad renderTexturedRect(TexturePtr texture, RectF const& screenCoords, Vec4B color = Vec4B::filled(255), float param1 = 0.0f);
RenderQuad renderFlatRect(RectF const& rect, Vec4B color, float param1 = 0.0f);
RenderPoly renderFlatPoly(PolyF const& poly, Vec4B color, float param1 = 0.0f);

typedef Variant<RenderTriangle, RenderQuad, RenderPoly> RenderPrimitive;

class Texture : public RefCounter {
public:
    virtual ~Texture() = default;

    virtual Vec2U size() const = 0;
    virtual TextureFiltering filtering() const = 0;
    virtual TextureAddressing addressing() const = 0;
};

class TextureGroup {
public:
    virtual ~TextureGroup() = default;

    virtual TextureFiltering filtering() const = 0;
    virtual TexturePtr create(Image const& texture) = 0;
};

class RenderBuffer {
public:
    virtual ~RenderBuffer() = default;

    // Transforms the given primitives into a form suitable for the underlying
    // graphics system and stores it for fast replaying.
    virtual void set(List<RenderPrimitive>& primitives) = 0;
};
typedef Variant<bool, int, float, Vec2F, Vec3F, Vec4F> RenderEffectParameter;

class Renderer {
public:
    virtual ~Renderer() = default;

    virtual String rendererId() const = 0;
    virtual Vec2U screenSize() const = 0;

    virtual void loadConfig(Json const& config) = 0;

    virtual void loadEffectConfig(String const& name, Json const& effectConfig, StringMap<String> const& shaders) = 0;

    virtual void setEffectParameter(String const& parameterName, RenderEffectParameter const& parameter) = 0;
    virtual void setEffectTexture(String const& textureName, ImageView const& image) = 0;
    virtual bool switchEffectConfig(String const& name) = 0;

    virtual void setScissorRect(Maybe<RectI> const& scissorRect) = 0;

    virtual TexturePtr createTexture(Image const& texture,
        TextureAddressing addressing = TextureAddressing::Clamp,
        TextureFiltering filtering = TextureFiltering::Nearest) = 0;
    virtual void setSizeLimitEnabled(bool enabled) = 0;
    virtual void setMultiTexturingEnabled(bool enabled) = 0;
    virtual void setMultiSampling(unsigned multiSampling) = 0;
    virtual TextureGroupPtr createTextureGroup(TextureGroupSize size = TextureGroupSize::Medium, TextureFiltering filtering = TextureFiltering::Nearest) = 0;
    virtual RenderBufferPtr createRenderBuffer() = 0;

    virtual List<RenderPrimitive>& immediatePrimitives() = 0;
    virtual void render(RenderPrimitive primitive) = 0;
    virtual void renderBuffer(RenderBufferPtr const& renderBuffer, Mat3F const& transformation = Mat3F::identity()) = 0;

    virtual void flush(Mat3F const& transformation = Mat3F::identity()) = 0;
};

}