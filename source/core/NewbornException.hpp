#pragma once

#include "NewbornMemory.hpp"
#include "NewbornOutputProxy.hpp"

#include <string>
#include <sstream>

namespace Newborn {

template <typename... T>
std::string strf(fmt::format_string<T...> fmt, T&&... args);

class NewbornException : public std::exception {
public:
  template <typename... Args>
  static NewbornException format(fmt::format_string<Args...> fmt, Args const&... args);

  NewbornException() noexcept;
  virtual ~NewbornException() noexcept;

  explicit NewbornException(std::string message, bool genStackTrace = true) noexcept;
  explicit NewbornException(std::exception const& cause) noexcept;
  NewbornException(std::string message, std::exception const& cause) noexcept;

  virtual char const* what() const noexcept override;

  // If the given exception is really NewbornException, then this will call
  // NewbornException::printException, otherwise just prints std::exception::what.
  friend void printException(std::ostream& os, std::exception const& e, bool fullStacktrace);
  friend std::string printException(std::exception const& e, bool fullStacktrace);
  friend OutputProxy outputException(std::exception const& e, bool fullStacktrace);

protected:
  NewbornException(char const* type, std::string message, bool genStackTrace = true) noexcept;
  NewbornException(char const* type, std::string message, std::exception const& cause) noexcept;

private:
  // Takes the ostream to print to, whether to print the full stacktrace.  Must
  // not bind 'this', may outlive the exception in the case of chained
  // exception causes.
  function<void(std::ostream&, bool)> m_printException;

  // m_printException will be called without the stack-trace to print
  // m_whatBuffer, if the what() method is invoked.
  mutable std::string m_whatBuffer;
};

void printException(std::ostream& os, std::exception const& e, bool fullStacktrace);
std::string printException(std::exception const& e, bool fullStacktrace);
OutputProxy outputException(std::exception const& e, bool fullStacktrace);

void printStack(char const* message);

// Log error and stack-trace and possibly show a dialog box if available, then
// abort.
void fatalError(char const* message, bool showStackTrace);
void fatalException(std::exception const& e, bool showStackTrace);

#ifdef NEWBORN_DEBUG
#define debugPrintStack() \
  { Newborn::printStack("Debug: file " NEWBORN_STR(__FILE__) " line " NEWBORN_STR(__LINE__)); }
#define newbornAssert(COND)                                                                                \
  {                                                                                                     \
    if (COND)                                                                                           \
      ;                                                                                                 \
    else                                                                                                \
      Newborn::fatalError("assert failure in file " NEWBORN_STR(__FILE__) " line " NEWBORN_STR(__LINE__), true); \
  }
#else
#define debugPrintStack() \
  {}
#define newbornAssert(COND) \
  {}
#endif

#define NEWBORN_EXCEPTION(ClassName, BaseName)                                                                                       \
  class ClassName : public BaseName {                                                                                             \
  public:                                                                                                                         \
    template <typename... Args>                                                                                                   \
    static ClassName format(fmt::format_string<Args...> fmt, Args const&... args) {                                               \
      return ClassName(strf(fmt, args...));                                                                                       \
    }                                                                                                                             \
    ClassName() : BaseName(#ClassName, std::string()) {}                                                                          \
    explicit ClassName(std::string message, bool genStackTrace = true) : BaseName(#ClassName, std::move(message), genStackTrace) {} \
    explicit ClassName(std::exception const& cause) : BaseName(#ClassName, std::string(), cause) {}                               \
    ClassName(std::string message, std::exception const& cause) : BaseName(#ClassName, std::move(message), cause) {}              \
                                                                                                                                  \
  protected:                                                                                                                      \
    ClassName(char const* type, std::string message, bool genStackTrace = true) : BaseName(type, std::move(message), genStackTrace) {} \
    ClassName(char const* type, std::string message, std::exception const& cause)                                                 \
      : BaseName(type, std::move(message), cause) {}                                                                              \
  }

NEWBORN_EXCEPTION(OutOfRangeException, NewbornException);
NEWBORN_EXCEPTION(IOException, NewbornException);
NEWBORN_EXCEPTION(MemoryException, NewbornException);

template <typename... Args>
NewbornException NewbornException::format(fmt::format_string<Args...> fmt, Args const&... args) {
  return NewbornException(strf(fmt, args...));
}

}
