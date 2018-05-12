#ifndef TIMER_HPP
#define TIMER_HPP
#include <chrono>

/*!
 * \brief A timer class where done() will return true if the timer has "gone
 * off".
 */
class Timer {
 public:
  Timer(double max_seconds);
  bool done();


private:
  std::chrono::high_resolution_clock::time_point start;
  double max;
};
#endif /* TIMER_HPP */
