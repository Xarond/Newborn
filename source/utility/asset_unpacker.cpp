#include "NewbornPackedAssetSource.hpp"
#include "NewbornTime.hpp"
#include "NewbornJsonExtra.hpp"
#include "NewbornFile.hpp"

using namespace Newborn;

int main(int argc, char** argv) {
    try {
        double startTime = Time::monotonicTime();

        if (argc != 3) {
            cerrf("Usage: {} <asset pak path> <target output directory>\n", argv[0]);
            cerrf("If the target output directory does not exist it will be created\n");
            return 1;
        }

        String inputFile = argv[1];
        String outputFolderPath = argv[2];

        PackedAssetSource assetPack(inputFile);

        if (!File::isDirectory(outputFolderPath))
            File::makeDirectory(outputFolderPath);

        File::changeDirectory(outputFolderPath);

        auto allFiles = assetPack.assetPaths();

        for (auto file : allFiles) {
            try {
                auto fileData = assetPack.read(file);
                auto relativePath = "." + file;
                auto relativeDir = File::dirName(relativePath);
                File::makeDirectoryRecursive(relativeDir);
                File::writeFile(fileData, relativePath);
            } catch (AssetSourceException const& e) {
                cerrf("Could not open file: {}\n", file);
                cerrf("Reason: {}\n", outputException(e, false));
            }
        }

        auto metadata = assetPack.metadata();
        if (!metadata.empty())
            File::writeFile(Json(std::move(metadata)).printJson(2), "_metadata");

        coutf("Unpacked assets to {} in {}\n", outputFolderPath, Time::monotonicTime() - startTime);
        return 0;
    } catch (std::exception const& e){
        cerrf("Exception caught: {}\n", outputException(e, true));
        return 1;
    }
}