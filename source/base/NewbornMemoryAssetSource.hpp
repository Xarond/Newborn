#pragma once

#include "NewbornAssetSource.hpp"
#include "NewbornIODevice.hpp"

namespace Newborn {

NEWBORN_CLASS(MemoryAssetSource);
NEWBORN_CLASS(Image);

class MemoryAssetSource : public AssetSource {

public:
    MemoryAssetSource(String const& name, JsonObject metadata = JsonObject());

    String name() const;
    JsonObject metadata() const override;
    StringList assetPaths() const override;

    IODevicePtr open(String const& path) override;

    bool empty() const;
    bool contains(String const& path) const;
    bool erase(String const& path);
    void set(String const& path, ByteArray data);
    void set(String const& path, Image const& image);
    void set(String const& path, Image&& image);
    ByteArray read(String const& path) override;
    ImageConstPtr image(String const& path);
private:
    typedef Variant<ByteArray, ImagePtr> FileEntry;

    String m_name;
    JsonObject m_metadata;
    StringMap<FileEntry> m_files;
};
}