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
  *current_date = *localtime(&t);
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