#pragma once

#include "NewbornOptionParser.hpp"
#include "NewbornVersion.hpp"

namespace Newborn {

// Option parser that accepts -h to print the help and exit and -v to print the
// version and exit.
class VersionOptionParser : public OptionParser {
public:
  static void printVersion(std::ostream& os);

  VersionOptionParser();

  // Parse the command line options, or, in the case of an error, -h, or -v,
  // prints the appropriate text and immediately exits.
  Options parseOrDie(StringList const& cmdLineArguments) const;

  // First sets the command name based on argv[0], then calls parseOrDie.
  Options commandParseOrDie(int argc, char** argv);
};

}
