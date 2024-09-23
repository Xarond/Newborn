#include "NewbornOptionParser.hpp"
#include "NewbornIterator.hpp"

namespace Newborn {

void OptionParser::setCommandName(String commandName) {
  m_commandName = std::move(commandName);
}

void OptionParser::setSummary(String summary) {
  m_summary = std::move(summary);
}

void OptionParser::setAdditionalHelp(String help) {
  m_additionalHelp = std::move(help);
}

void OptionParser::addSwitch(String const& flag, String description) {
  if (!m_options.insert(flag, Switch{flag, std::move(description)}).second)
    throw OptionParserException::format("Duplicate switch '-{}' added", flag);
}

void OptionParser::addParameter(String const& flag, String argument, RequirementMode requirementMode, String description) {
  if (!m_options.insert(flag, Parameter{flag, std::move(argument), requirementMode, std::move(description)}).second)
    throw OptionParserException::format("Duplicate flag '-{}' added", flag);
}

void OptionParser::addArgument(String argument, RequirementMode requirementMode, String description) {
  m_arguments.append(Argument{std::move(argument), requirementMode, std::move(description)});
}

pair<OptionParser::Options, StringList> OptionParser::parseOptions(StringList const& arguments) const {
  Options result;
  StringList errors;
  bool endOfFlags = false;

  auto it = makeSIterator(arguments);
  while (it.hasNext()) {
    auto const& arg = it.next();
    if (arg == "--") {
      endOfFlags = true;
      continue;
    }

    if (!endOfFlags && arg.beginsWith("-")) {
      String flag = arg.substr(1);
      auto option = m_options.maybe(flag);
      if (!option) {
        errors.append(strf("No such option '-{}'", flag));
        continue;
      }

      if (option->is<Switch>()) {
        result.switches.add(std::move(flag));
      } else {
        auto const& parameter = option->get<Parameter>();
        if (!it.hasNext()) {
          errors.append(strf("Option '-{}' must be followed by an argument", flag));
          continue;
        }
        String val = it.next();
        if (parameter.requirementMode != Multiple && result.parameters.contains(flag)) {
          errors.append(strf("Option with argument '-{}' specified multiple times", flag));
          continue;
        }
        result.parameters[std::move(flag)].append(std::move(val));
      }

    } else {
      result.arguments.append(arg);
    }
  }

  for (auto const& pair : m_options) {
    if (pair.second.is<Parameter>()) {
      auto const& na = pair.second.get<Parameter>();
      if (na.requirementMode == Required && !result.parameters.contains(pair.first))
        errors.append(strf("Missing required flag with argument '-{}'", pair.first));
    }
  }

  size_t minimumArguments = 0;
  size_t maximumArguments = 0;
  for (auto const& argument : m_arguments) {
    if ((argument.requirementMode == Optional || argument.requirementMode == Required) && maximumArguments != NPos)
      ++maximumArguments;
    if (argument.requirementMode == Required)
      ++minimumArguments;
    if (argument.requirementMode == Multiple)
      maximumArguments = NPos;
  }
  if (result.arguments.size() < minimumArguments)
    errors.append(strf(
        "Too few positional arguments given, expected at least {} got {}", minimumArguments, result.arguments.size()));
  if (result.arguments.size() > maximumArguments)
    errors.append(strf(
        "Too many positional arguments given, expected at most {} got {}", maximumArguments, result.arguments.size()));

  return {std::move(result), std::move(errors)};
}

void OptionParser::printHelp(std::ostream& os) const {
  if (!m_commandName.empty() && !m_summary.empty())
    format(os, "{}: {}\n\n", m_commandName, m_summary);
  else if (!m_commandName.empty())
    format(os, "{}:\n\n", m_commandName);
  else if (!m_summary.empty())
    format(os, "{}\n\n", m_summary);

  String cmdLineText;

  for (auto const& p : m_options) {
    if (p.second.is<Switch>()) {
      cmdLineText += strf(" [-{}]", p.first);
    } else {
      auto const& parameter = p.second.get<Parameter>();
      if (parameter.requirementMode == Optional)
        cmdLineText += strf(" [-{} <{}>]", parameter.flag, parameter.argument);
      else if (parameter.requirementMode == Required)
        cmdLineText += strf(" -{} <{}>", parameter.flag, parameter.argument);
      else if (parameter.requirementMode == Multiple)
        cmdLineText += strf(" [-{} <{}>]...", parameter.flag, parameter.argument);
    }
  }

  for (auto const& p : m_arguments) {
    if (p.requirementMode == Optional)
      cmdLineText += strf(" [<{}>]", p.argumentName);
    else if (p.requirementMode == Required)
      cmdLineText += strf(" <{}>", p.argumentName);
    else
      cmdLineText += strf(" [<{}>...]", p.argumentName);
  }

  if (m_commandName.empty())
    format(os, "Command Line Usage:{}\n", cmdLineText);
  else
    format(os, "Command Line Usage: {}{}\n", m_commandName, cmdLineText);

  for (auto const& p : m_options) {
    if (p.second.is<Switch>()) {
      auto const& sw = p.second.get<Switch>();
      if (!sw.description.empty())
        format(os, "  -{}\t- {}\n", sw.flag, sw.description);
    }
    if (p.second.is<Parameter>()) {
      auto const& parameter = p.second.get<Parameter>();
      if (!parameter.description.empty())
        format(os, "  -{} <{}>\t- {}\n", parameter.flag, parameter.argument, parameter.description);
    }
  }

  for (auto const& p : m_arguments) {
    if (!p.description.empty())
      format(os, "  <{}>\t- {}\n", p.argumentName, p.description);
  }

  if (!m_additionalHelp.empty())
    format(os, "\n{}\n", m_additionalHelp);
}

}
