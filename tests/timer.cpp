#include "timer.hpp"

Timer::Timer(double max_seconds)
  :start{std::chrono::high_resolution_clock::now()}, max{max_seconds}
{}

bool Timer::done() {
  using namespace std::chrono;
  high_resolution_clock::time_point now = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(now - start);
  return time_span.count() >= max;
}
