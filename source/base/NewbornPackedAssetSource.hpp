#pragma once

#include "NewbornOrderedMap.hpp"
#include "NewbornFile.hpp"
#include "NewbornDirectoryAssetSource.hpp"

namespace Newborn {
NEWBORN_CLASS(PackedAssetSource);

class PackedAssetSource : public AssetSource {
    typedef function<void(size_t, size_t, String, String)> BuildProgressCallback;

    static void build (DirectoryAssetSource& directorySource, String const& targetPackedFile, 
        StringList const& extensionSorting = {}, BuildProgressCallback progressCallback = {});
    
    PackedAssetSource(String const& packedFileName);

    JsonObject metadata() const override;
    StringList assetPaths() const override;

    IODevicePtr open(String const& path) override;
    ByteArray read(String const& path) override;

    private:
    FilePtr m_packedFile;
    JsonObject m_metadata;
    OrderedHashMap<String, pair<uint64_t, uint64_t>> m_index;
    };
}