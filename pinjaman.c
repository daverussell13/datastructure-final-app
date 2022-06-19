#define MxN 255
#define ull unsigned long long
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct {
  char judul[MxN];
  char pengarang[MxN];
  char nik_peminjam[MxN];
  struct tm tanggal_peminjaman;
  struct tm tanggal_pengembalian;
  struct tm tanggal_deadline;
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

void createDeadline(struct tm* deadline, int date, int month, int year) {
  memset(&deadline,0,sizeof(struct tm));
  deadline->tm_mday = date;
  deadline->tm_mon = (month - 1);
  deadline->tm_year = (year - 1900);
}

// Core functions
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
  getCurrentDate(&new_pinjaman.tanggal_peminjaman);
  memset(&new_pinjaman.tanggal_pengembalian,0,sizeof(struct tm));
  createDate(&new_pinjaman.tanggal_deadline, tanggal_deadline, bulan_deadline, tahun_deadline);
  return new_pinjaman;
}