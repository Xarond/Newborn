//*************************
// Jakub Joszko 2024
//*************************
#include "NewbornTime.hpp"
#include "NewbornMathCommon.hpp"
#include "NewbornLexicalCast.hpp"

namespace Newborn {

double Time::timeSinceEpoch() {
  return ticksToSeconds(epochTicks(), epochTickFrequency());
}

int64_t Time::millisecondsSinceEpoch() {
  return ticksToMilliseconds(epochTicks(), epochTickFrequency());
}

double Time::monotonicTime() {
  return ticksToSeconds(monotonicTicks(), monotonicTickFrequency());
}

int64_t Time::monotonicMilliseconds() {
  return ticksToMilliseconds(monotonicTicks(), monotonicTickFrequency());
}

int64_t Time::monotonicMicroseconds() {
  return ticksToMicroseconds(monotonicTicks(), monotonicTickFrequency());
}

String Time::printDuration(double time) {
  String hours;
  String minutes;
  String seconds;
  String milliseconds;

  if (time >= 3600) {
    int numHours = (int)time / 3600;
    hours = strf("{} hour{}", numHours, numHours == 1 ? "" : "s");
  }
  if (time >= 60) {
    int numMinutes = (int)(time / 60) % 60;
    minutes = strf("{} minute{}", numMinutes, numMinutes == 1 ? "" : "s");
  }
  if (time >= 1) {
    int numSeconds = (int)time % 60;
    seconds = strf("{} second{}", numSeconds, numSeconds == 1 ? "" : "s");
  }

  int numMilliseconds = round(fmod(time, 1.0) * 1000);
  milliseconds = strf("{} millisecond{}", numMilliseconds, numMilliseconds == 1 ? "" : "s");

  return String::joinWith(", ", hours, minutes, seconds, milliseconds);
}

String Time::printCurrentDateAndTime(String format) {
  return printDateAndTime(epochTicks(), format);
}

double Time::ticksToSeconds(int64_t ticks, int64_t tickFrequency) {
  return ticks / (double)tickFrequency;
}

int64_t Time::ticksToMilliseconds(int64_t ticks, int64_t tickFrequency) {
  int64_t ticksPerMs = (tickFrequency + 500) / 1000;
  return (ticks + ticksPerMs / 2) / ticksPerMs;
}

int64_t Time::ticksToMicroseconds(int64_t ticks, int64_t tickFrequency) {
  int64_t ticksPerUs = (tickFrequency + 500000) / 1000000;
  return (ticks + ticksPerUs / 2) / ticksPerUs;
}

int64_t Time::secondsToTicks(double seconds, int64_t tickFrequency) {
  return round(seconds * tickFrequency);
}

int64_t Time::millisecondsToTicks(int64_t milliseconds, int64_t tickFrequency) {
  return milliseconds * ((tickFrequency + 500) / 1000);
}

int64_t Time::microsecondsToTicks(int64_t microseconds, int64_t tickFrequency) {
  return microseconds * ((tickFrequency + 500000) / 1000000);
}

Clock::Clock(bool start) {
  m_elapsedTicks = 0;
  m_running = false;
  if (start)
    Clock::start();
}

Clock::Clock(Clock const& clock) {
  operator=(clock);
}

Clock& Clock::operator=(Clock const& clock) {
  m_elapsedTicks = clock.m_elapsedTicks;
  m_lastTicks = clock.m_lastTicks;
  m_running = clock.m_running;

  return *this;
}

void Clock::reset() {
  RecursiveMutexLocker locker(m_mutex);
  updateElapsed();
  m_elapsedTicks = 0;
}

void Clock::stop() {
  RecursiveMutexLocker locker(m_mutex);
  m_lastTicks.reset();
  m_running = false;
}

void Clock::start() {
  RecursiveMutexLocker locker(m_mutex);
  m_running = true;
  updateElapsed();
}

bool Clock::running() const {
  RecursiveMutexLocker locker(m_mutex);
  return m_running;
}

double Clock::time() const {
  RecursiveMutexLocker locker(m_mutex);
  updateElapsed();
  return Time::ticksToSeconds(m_elapsedTicks, Time::monotonicTickFrequency());
}

int64_t Clock::milliseconds() const {
  RecursiveMutexLocker locker(m_mutex);
  updateElapsed();
  return Time::ticksToMilliseconds(m_elapsedTicks, Time::monotonicTickFrequency());
}

void Clock::setTime(double time) {
  RecursiveMutexLocker locker(m_mutex);
  updateElapsed();
  m_elapsedTicks = Time::secondsToTicks(time, Time::monotonicTickFrequency());
}

void Clock::setMilliseconds(int64_t millis) {
  RecursiveMutexLocker locker(m_mutex);
  updateElapsed();
  m_elapsedTicks = Time::millisecondsToTicks(millis, Time::monotonicTickFrequency());
}

void Clock::adjustTime(double timeAdjustment) {
  RecursiveMutexLocker locker(m_mutex);
  setTime(max<double>(0.0, time() + timeAdjustment));
}

void Clock::adjustMilliseconds(int64_t millisAdjustment) {
  RecursiveMutexLocker locker(m_mutex);
  setMilliseconds(milliseconds() + millisAdjustment);
}

void Clock::updateElapsed() const {
  if (!m_running)
    return;

  int64_t currentTicks = Time::monotonicTicks();

  if (m_lastTicks)
    m_elapsedTicks += (currentTicks - *m_lastTicks);

  m_lastTicks = currentTicks;
}

Timer Timer::withTime(double timeLeft, bool start) {
  Timer timer;
  timer.setTime(-timeLeft);
  if (start)
    timer.start();
  return timer;
}

Timer Timer::withMilliseconds(int64_t millis, bool start) {
  Timer timer;
  timer.setMilliseconds(-millis);
  if (start)
    timer.start();
  return timer;
}

Timer::Timer() : Clock(false) {
  setTime(0.0);
}

Timer::Timer(Timer const& timer)
  : Clock(timer) {}

Timer& Timer::operator=(Timer const& timer) {
  Clock::operator=(timer);
  return *this;
}

void Timer::restart(double timeLeft) {
  Clock::setTime(-timeLeft);
  Clock::start();
}

void Timer::restartWithMilliseconds(int64_t millisecondsLeft) {
  Clock::setMilliseconds(-millisecondsLeft);
  Clock::start();
}

double Timer::timeLeft(bool negative) const {
  double timeLeft = -Clock::time();
  if (!negative)
    timeLeft = max(0.0, timeLeft);
  return timeLeft;
}

int64_t Timer::millisecondsLeft(bool negative) const {
  int64_t millisLeft = -Clock::milliseconds();
  if (!negative)
    millisLeft = max<int64_t>(0, millisLeft);
  return millisLeft;
}

bool Timer::timeUp() const {
  return Clock::time() >= 0.0;
}

}
