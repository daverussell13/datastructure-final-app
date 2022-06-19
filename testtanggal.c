#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MxN 255
#define ll long long int
#define ld long double

int main() {
  /* initialize */
  int y=2022, m=6, d=19;
  struct tm t = { .tm_year=y-1900, .tm_mon=m-1, .tm_mday=d };
  /* modify */
  t.tm_mday += 7;
  mktime(&t);
  /* show result */
  char format[MxN];
  strftime(format, sizeof(format), "%A, %d %m %Y",&t);
  printf("%s\n", format); /* prints: Sun Mar 16 00:00:00 1980 */
  return 0;
}