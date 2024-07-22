#pragma once

#include "NewbornVersionOptionParser.hpp"
#include "NewbornRoot.hpp"

namespace Newborn {

class RootLoader : public VersionOptionParser {
public:
    struct Defaults {
        Json additionalAssetsSettings;

        Json additionalDefaultConfiguration;

        Maybe<String> logFile;

        LogLevel logLevel;

        bool quiet;

        Maybe<String> runtimeConfigFile;
    };

    RootLoader(Defaults defaults);

    pair<Root::Settings, Options> parseOrDie(StringList const& cmdLineArguments) const;
    pair<RootUPtr, Options> initOrDie(StringList const& cmdLineArguments) const;

    pair<Root::Settings, Options> commandParseOrDie(int arc, char** argv);
    pair<RootUPtr, Options> commandInitOrDie(int argc, char** argv);

private:
    Root::Settings rootSettingsForOptions(Options const& options) const;

    Defaults m_defaults;
};

}