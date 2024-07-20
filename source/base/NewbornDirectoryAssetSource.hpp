#pragma once

#include "NewbornAssetSource.hpp"
#include "NewbornString.hpp"

namespace Newborn {

NEWBORN_CLASS(DirectoryAssetSource);

class DirectoryAssetSource : public AssetSource {
public:
    DirectoryAssetSource(String const& baseDirectory, StringList const& ignorePatterns = {});

    JsonObject metadata() const override;
    StringList assetPaths() const override;

    IODevicePtr open(String const& path) override;
    ByteArray read(String const& path) override;

    // Converts an asset path to the path on the filesystem
    String toFilesystem(String const& path) const;

    // Update metadata file or add a new one.
    void setMetadata(JsonObject metadata);

    private:
    void scanAll(String const& assetDirectory, StringList& output) const;

    String m_baseDirectory;
    List<String> m_ignorePatterns;
    Maybe<String> m_metadataFile;
    JsonObject m_metadata;
    StringList m_assetPaths;
    };

}