
#include <cstdlib>
#include "tle.hpp"

TLE::TLE()
{
}

TLE::~TLE()
{
}

bool TLE::set(const std::string& line1, const std::string& line2)
{
  // validation by checksum
  bool valid1 = validation(line1);
  bool valid2 = validation(line2);

  if (!(valid1 & valid2)) return false;

  return true;
}

bool TLE::validation(const std::string& line)
{
  const char* str = line[n].c_str();
  const size_t s = line[n].size() - 1;
  const int checksum = std::atoi(&str[s-1]);

  int sum = 0;

  for (int i=0; i < s; i++) {
    const char c = str[i];
    if ('0' <= c && c <= '9') {
      sum += c - '0';
    } else if (c == '-') {
      sum += 1;
    }
  }

  return (sum % 10 == checksum);
}

