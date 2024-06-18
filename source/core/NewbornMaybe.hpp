#pragma once

#include "NewbornException.hpp"
#include "NewbornHash.hpp"

namespace Newborn {

NEWBORN_EXCEPTION(InvalidMaybeAccessException, NewbornException);

template <typename T>
class Maybe {
public:
  typedef T* PointerType;
  typedef T const* PointerConstType;
  typedef T& RefType;
  typedef T const& RefConstType;

  Maybe();

  Maybe(T const& t);
  Maybe(T&& t);

  Maybe(Maybe const& rhs);
  Maybe(Maybe&& rhs);
  template <typename T2>
  Maybe(Maybe<T2> const& rhs);

  ~Maybe();

  Maybe& operator=(Maybe const& rhs);
  Maybe& operator=(Maybe&& rhs);
  template <typename T2>
  Maybe& operator=(Maybe<T2> const& rhs);

  bool isValid() const;
  bool isNothing() const;
  explicit operator bool() const;

  PointerConstType ptr() const;
  PointerType ptr();

  PointerConstType operator->() const;
  PointerType operator->();

  RefConstType operator*() const;
  RefType operator*();

  bool operator==(Maybe const& rhs) const;
  bool operator!=(Maybe const& rhs) const;
  bool operator<(Maybe const& rhs) const;

  RefConstType get() const;
  RefType get();

  // Get either the contents of this Maybe or the given default.
  T value(T def = T()) const;

  // Get either this value, or if this value is none the given value.
  Maybe orMaybe(Maybe const& other) const;

  // Takes the value out of this Maybe, leaving it Nothing.
  T take();

  // If this Maybe is set, assigns it to t and leaves this Maybe as Nothing.
  bool put(T& t);

  void set(T const& t);
  void set(T&& t);

  template <typename... Args>
  void emplace(Args&&... t);

  void reset();

  // Apply a function to the contained value if it is not Nothing.
  template <typename Function>
  void exec(Function&& function);

  // Functor map operator.  If this maybe is not Nothing, then applies the
  // given function to it and returns the result, otherwise returns Nothing (of
  // the type the function would normally return).
  template <typename Function>
  auto apply(Function&& function) const -> Maybe<typename std::decay<decltype(function(std::declval<T>()))>::type>;

  // Monadic bind operator.  Given function should return another Maybe.
  template <typename Function>
  auto sequence(Function function) const -> decltype(function(std::declval<T>()));

private:
  union {
    T m_data;
  };

  bool m_initialized;
};

}