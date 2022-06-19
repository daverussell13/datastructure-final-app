#ifndef PINJAMAN_INCLUDED
#define PINJAMAN_INCLUDED

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MxN 255
#define ull unsigned long long

typedef struct {
  char judul[MxN];
  char pengarang[MxN];
  char nik_peminjam[MxN];
  struct tm tanggal_peminjaman;
  struct tm tanggal_pengembalian;
  struct tm tanggal_deadline;
  char status; // r = returned, b = borrowed
} Pinjaman;

// Dynamic array
typedef struct {
  Pinjaman* arr;
  size_t used;
  size_t size;
} ArrayPinjaman;

void initArrayPinjaman(ArrayPinjaman* a, size_t initialSize) {
  a->arr = (Pinjaman*)malloc(initialSize * sizeof(Pinjaman));
  a->used = 0;
  a->size = initialSize;
}

void insertArrayPinjaman(ArrayPinjaman* a, Pinjaman element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->arr = (Pinjaman*)realloc(a->arr, a->size * sizeof(Pinjaman));
  }
  a->arr[a->used++] = element;
}

void freeArrayPinjaman(ArrayPinjaman *a) {
  free(a->arr);
  a->arr = NULL;
  a->used = a->size = 0;
}

void getCurrentDate(struct tm* current_date) {
  time_t t = time(NULL);
  struct tm get_date = *localtime(&t);
  current_date->tm_mday = get_date.tm_mday;
  current_date->tm_mon = get_date.tm_mon;
  current_date->tm_year = get_date.tm_year;
  time_t calendar_time = mktime(current_date);
}

void setDeadline(struct tm* deadline, int day, int month, int year) {
  deadline->tm_mday = day;
  deadline->tm_mon = (month - 1);
  deadline->tm_year = (year - 1900);
  time_t calendar_time = mktime(deadline);
}

void setDeadlineOneWeek(struct tm* deadline, int day, int month, int year) {
  deadline->tm_mday = day + 7;
  deadline->tm_mon = month;
  deadline->tm_year = year;
  time_t calendar_time = mktime(deadline);
}

// Core functions
int validateDate(int nDay, int nMonth, int nYear) {
  struct tm tmDate;
  memset(&tmDate,0,sizeof(struct tm));
  tmDate.tm_mday = nDay;
  tmDate.tm_mon = (nMonth - 1);
  tmDate.tm_year = (nYear - 1900);

  struct tm tmValidateDate;
  memcpy(&tmValidateDate,&tmDate,sizeof(struct tm));

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

int getDiffDay(struct tm time1, struct tm time2) {
  time_t time1Calendar = mktime(&time1), time2Calendar = mktime(&time2);
  return (int)difftime(time1Calendar,time2Calendar)/86400;
}

void printFormattedDate(struct tm* time) {
  char str[MxN];
  strftime(str,sizeof(str),"%A, %d %b %Y",time);
  printf("%s",str);
}

Pinjaman newPinjaman (
  const char* judul,
  const char* pengarang,
  const char* nik,
  int tanggal_deadline,
  int bulan_deadline,
  int tahun_deadline
) {
  Pinjaman new_pinjaman;
  strcpy(new_pinjaman.judul,judul);
  strcpy(new_pinjaman.pengarang,pengarang);
  strcpy(new_pinjaman.nik_peminjam,nik);
  memset(&new_pinjaman.tanggal_peminjaman,0,sizeof(struct tm));
  memset(&new_pinjaman.tanggal_pengembalian,0,sizeof(struct tm));
  memset(&new_pinjaman.tanggal_deadline,0,sizeof(struct tm));
  getCurrentDate(&new_pinjaman.tanggal_peminjaman);
  if (!tanggal_deadline && !bulan_deadline && !tahun_deadline) {
    setDeadlineOneWeek(
      &new_pinjaman.tanggal_deadline,
      new_pinjaman.tanggal_peminjaman.tm_mday,
      new_pinjaman.tanggal_peminjaman.tm_mon,
      new_pinjaman.tanggal_peminjaman.tm_year
    );
  }
  else {
    setDeadline(&new_pinjaman.tanggal_deadline, tanggal_deadline, bulan_deadline, tahun_deadline);
  }
  new_pinjaman.status = 'b';
  return new_pinjaman;
}

#endif