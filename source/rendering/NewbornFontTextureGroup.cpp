#include "NewbornFontTextureGroup.hpp"
#include "NewbornTime.hpp"
#include "NewbornImageProcessing.hpp"
#include "NewbornLogging.hpp"

namespace Newborn {

FontTextureGroup::FontTextureGroup(TextureGroupPtr textureGroup)
  : m_textureGroup(std::move(textureGroup)) {}

void FontTextureGroup::cleanup(int64_t timeout) {
  int64_t currentTime = Time::monotonicMilliseconds();
  eraseWhere(m_glyphs, [&](auto const& p) { return currentTime - p.second.time > timeout; });
}

void FontTextureGroup::switchFont(String const& font) {
  if (font.empty()) {
    m_activeFont = m_defaultFont;
    m_fontName.clear();
  }
  else if (m_fontName != font) {
    m_fontName = font;
    auto find = m_fonts.find(font);
    m_activeFont = find != m_fonts.end() ? find->second : m_defaultFont;
  }
}

String const& FontTextureGroup::activeFont() {
  return m_fontName;
}

void FontTextureGroup::addFont(FontPtr const& font, String const& name) {
  m_fonts[name] = font;
}

void FontTextureGroup::clearFonts() {
  m_fonts.clear();
  m_activeFont = m_defaultFont;
}

void FontTextureGroup::setFixedFonts(String const& defaultFontName, String const& fallbackFontName, String const& emojiFontName) {
  if (auto defaultFont = m_fonts.ptr(defaultFontName))
    m_defaultFont = m_activeFont = *defaultFont;
  if (auto fallbackFont = m_fonts.ptr(fallbackFontName))
    m_fallbackFont = *fallbackFont;
  if (auto emojiFont = m_fonts.ptr(emojiFontName))
    m_emojiFont = *emojiFont;
}

const FontTextureGroup::GlyphTexture& FontTextureGroup::glyphTexture(String::Char c, unsigned size, Directives const* processingDirectives)
{
  Font* font = getFontForCharacter(c);
  if (font == m_emojiFont.get())
    processingDirectives = nullptr;
  auto res = m_glyphs.insert(GlyphDescriptor{c, size, processingDirectives ? processingDirectives->hash() : 0, font}, GlyphTexture());
  auto& glyphTexture = res.first->second;
  if (res.second) {
    font->setPixelSize(size);
    auto renderResult = font->render(c);
    Image& image = get<0>(renderResult);
    if (processingDirectives) {
      Directives const& directives = *processingDirectives;
      Vec2F preSize = Vec2F(image.size());

      bool broken = false;
      for (auto& entry : directives->entries) {
        if (auto error = entry.operation.ptr<ErrorImageOperation>()) {
          if (auto string = error->cause.ptr<std::string>()) {
            if (!string->empty()) {
              Logger::error("Error in parsed font directives: {}", *string);
              string->clear();
            }
          } else if (auto& exception = error->cause.get<std::exception_ptr>()) {
            try
              { std::rethrow_exception(error->cause.get<std::exception_ptr>()); }
            catch (std::exception const& e)
              { Logger::error("Exception in parsed font directives: {}", e.what()); };
            exception = {};
          }
          broken |= true;
        } else {
          try { processImageOperation(entry.operation, image); }
          catch (NewbornException const& e) {
            broken |= true;
            Logger::error("Exception processing font directives for {}px '{}': {}", size, String(c), e.what());
          }
        }
      }

      if (broken) {
        glyphTexture.colored = true;
        image.forEachPixel([](unsigned x, unsigned y, Vec4B& pixel) {
          pixel = ((x + y) % 2 == 0) ? Vec4B(255, 0, 255, pixel[3]) : Vec4B(0, 0, 0, pixel[3]);
        });
      }

      glyphTexture.offset = (preSize - Vec2F(image.size())) / 2;
    }

    glyphTexture.colored |= get<2>(renderResult);
    glyphTexture.offset += Vec2F(get<1>(renderResult));
    glyphTexture.texture = m_textureGroup->create(image);
  }

  glyphTexture.time = Time::monotonicMilliseconds();
  return glyphTexture;
}

TexturePtr FontTextureGroup::glyphTexturePtr(String::Char c, unsigned size) {
  return glyphTexture(c, size, nullptr).texture;
}

TexturePtr FontTextureGroup::glyphTexturePtr(String::Char c, unsigned size, Directives const* processingDirectives) {
  return glyphTexture(c, size, processingDirectives).texture;
}

unsigned FontTextureGroup::glyphWidth(String::Char c, unsigned fontSize) {
  Font* font = getFontForCharacter(c);
  font->setPixelSize(fontSize);
  return font->width(c);
}

Font* FontTextureGroup::getFontForCharacter(String::Char c) {
  if (((c >= 0x1F600 && c <= 0x1F64F) || // Emoticons
       (c >= 0x1F300 && c <= 0x1F5FF) || // Misc Symbols and Pictographs
       (c >= 0x1F680 && c <= 0x1F6FF) || // Transport and Map
       (c >= 0x1F1E6 && c <= 0x1F1FF) || // Regional country flags
       (c >= 0x2600  && c <= 0x26FF ) || // Misc symbols 9728 - 9983
       (c >= 0x2700  && c <= 0x27BF ) || // Dingbats
       (c >= 0xFE00  && c <= 0xFE0F ) || // Variation Selectors
       (c >= 0x1F900 && c <= 0x1F9FF) || // Supplemental Symbols and Pictographs
       (c >= 0x1F018 && c <= 0x1F270) || // Various asian characters
       (c >= 65024   && c <= 65039  ) || // Variation selector
       (c >= 9100    && c <= 9300   ) || // Misc items
       (c >= 8400    && c <= 8447   ))&& // Combining Diacritical Marks for Symbols
      m_emojiFont->exists(c)
    )
    return m_emojiFont.get();
  else if (m_activeFont->exists(c) || !m_fallbackFont)
    return m_activeFont.get();
  else
    return m_fallbackFont.get();
}

}
