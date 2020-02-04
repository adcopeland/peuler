#include <iostream>
#include <ctime>

static constexpr time_t ONE_DAY = 60*60*24;

struct tm makeStart() {
  struct tm result = {0};
  result.tm_mday = 1;
  result.tm_mon  = 0;
  result.tm_year = 1901 - 1900;
  return result;
}

struct tm makeEnd() {
  struct tm result = {0};
  result.tm_mday = 31;
  result.tm_mon  = 11;
  result.tm_year = 2000 - 1900;
  return result;
}

bool isSunday(const struct tm& t) {
  return t.tm_wday == 0;
}

int main() {
  struct tm current = makeStart();
  time_t currentTime = mktime(&current);

  struct tm end = makeEnd();
  const time_t endTime = mktime(&end);

  int numSundays = 0;
  while (currentTime < endTime) {
    gmtime_r(&currentTime, &current);
    if (isSunday(current) && current.tm_mday == 1) {
      ++numSundays;
    }
    currentTime += ONE_DAY;
  }

  std::cout << numSundays << "\n";
}
