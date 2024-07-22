#pragma once

#include "NewbornOptionParser.hpp"
#include "NewbornVersion.hpp"

namespace Newborn {

class VersionOptionParser : public OptionParser {
public:
    static void printVersion(std::ostream& os);

    VersionOptionParser();

    Options parseOrDie(StringList const& cmdLineArguments) const;

    Options commandParseOrDie(int argc, char** argv);
    };
}