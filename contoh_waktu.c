#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "member.c"
#include <time.h>

#define MxN 255
#define ll long long int
#define ld long double
#define tm struct tm

int IsDateValid( const int nDay, const int nMonth, const int nYear ) {
    tm tmDate;
    memset(&tmDate,0,sizeof(tm));
    tmDate.tm_mday = nDay;
    tmDate.tm_mon = (nMonth - 1);
    tmDate.tm_year = (nYear - 1900);

    tm tmValidateDate;
    memcpy(&tmValidateDate,&tmDate,sizeof(tm));

    time_t timeCalendar = mktime(&tmValidateDate);
    if(timeCalendar == (time_t)-1)
        return 0;

    return (
        (tmDate.tm_mday == tmValidateDate.tm_mday) &&
    (tmDate.tm_mon == tmValidateDate.tm_mon) &&
    (tmDate.tm_year == tmValidateDate.tm_year) &&
    (tmDate.tm_hour == tmValidateDate.tm_hour) &&
    (tmDate.tm_min == tmValidateDate.tm_min) &&
    (tmDate.tm_sec == tmValidateDate.tm_sec) );
}

int main() {
  // IsDateValid(29,2,2021) ? printf("Valid") : printf("Not Valid");
  tm tmDate;
  memset(&tmDate,0,sizeof(tm));
  tmDate.tm_mday = 2;
  tmDate.tm_mon = (6 - 1);
  tmDate.tm_year = (2022 - 1900);

  tm tmValidateDate;
  memcpy(&tmValidateDate,&tmDate,sizeof(tm));

  time_t hari_ini = mktime(&tmValidateDate);

  memset(&tmDate,0,sizeof(tm));
  tmDate.tm_mday = 20;
  tmDate.tm_mon = (6 - 1);
  tmDate.tm_year = (2022 - 1900);

  memcpy(&tmValidateDate,&tmDate,sizeof(tm));

  time_t hari_lusa = mktime(&tmValidateDate);

  // hari ini
  time_t t = time(NULL);
  tm time = *localtime(&t);


  printf("jarak antara kedua hari adalah : %d hari\n",(int)difftime(t,hari_ini)/86400);
  return 0;
}