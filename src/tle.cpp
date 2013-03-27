
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "tle.hpp"

TLE::TLE()
{
}

TLE::~TLE()
{
}

bool TLE::set(const std::string& line1, const std::string& line2)
{
  std::string tmpstr;

  // validation by checksum
  bool valid1 = validation(line1);
  bool valid2 = validation(line2);

  if (!(valid1 & valid2)) return false;

  line[0] = line1;
  line[1] = line2;

  int lno,num[2],exp[2];
  char s[5];

// *** parse line 1 ***
  tmpstr = line1;
  if (tmpstr[33] == ' ') tmpstr[33] = '+';
  if (tmpstr[44] == ' ') tmpstr[44] = '+';
  if (tmpstr[53] == ' ') tmpstr[53] = '+';
  if (tmpstr[64] == ' ') tmpstr[64] = '0';
  if (tmpstr[65] == ' ') tmpstr[65] = '0';
  if (tmpstr[66] == ' ') tmpstr[66] = '0';
  if (tmpstr[67] == ' ') tmpstr[67] = '0';

  std::sscanf(tmpstr.c_str(),
              "%1d %5d%c %2d%3d%3c %2d%12lf %1c%9lf %1c%5lf%1c%1d %1c%5lf%1c%1d %1c %4d",
              &lno,&num[0],&classification,
              &IDYY,&IDNY,IDPL,&epoch_year,&epoch_day,
              &s[0],&dmotion,
              &s[1],&ddmotion,&s[2],&exp[0],
              &s[3],&BSTAR,&s[4],&exp[1],
              &ephemeris,&elemnum);

  IDPL[3] = '\0';
  exp[0]   *=  (s[2] == '-')? -1.0: 1.0;
  exp[1]   *=  (s[4] == '-')? -1.0: 1.0;
  dmotion  *= ((s[0] == '-')? -1.0: 1.0) * 2.0;
  ddmotion *= ((s[1] == '-')? -1.0: 1.0) * 6.0 * 10e-6 * pow(10.0,exp[0]);
  BSTAR    *= ((s[3] == '-')? -1.0: 1.0)       * 10e-6 * pow(10.0,exp[1]);

// *** parse line 2 ***
  tmpstr = line2;
  if (tmpstr[ 8] == ' ') tmpstr[ 8] = '0';
  if (tmpstr[ 9] == ' ') tmpstr[ 9] = '0';
  if (tmpstr[10] == ' ') tmpstr[10] = '0';
  if (tmpstr[17] == ' ') tmpstr[17] = '0';
  if (tmpstr[18] == ' ') tmpstr[18] = '0';
  if (tmpstr[19] == ' ') tmpstr[19] = '0';
  if (tmpstr[34] == ' ') tmpstr[34] = '0';
  if (tmpstr[35] == ' ') tmpstr[35] = '0';
  if (tmpstr[36] == ' ') tmpstr[36] = '0';
  if (tmpstr[43] == ' ') tmpstr[43] = '0';
  if (tmpstr[44] == ' ') tmpstr[44] = '0';
  if (tmpstr[45] == ' ') tmpstr[45] = '0';

  std::sscanf(tmpstr.c_str(),
              "%1d %5d %8lf %8lf %7lf %8lf %8lf %11lf%5d",
              &lno,&num[1],
              &inclination,&ascension,&eccentricity,
              &perigee,&anomaly,&motion,&revolution);

  eccentricity *= 10e-8;

// *** check ***
  if (num[0] != num[1]) return false;
  number = num[0];

  return true;
}

bool TLE::validation(const std::string& line)
{
  const char* str = line.c_str();
  const size_t s = line.size() - 1;
  const int checksum = std::atoi(&str[s]);

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

