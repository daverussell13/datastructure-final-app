#define MxN 255
#define ull unsigned long long
#include <stdio.h>
#include <string.h>

typedef struct {
  char judul[MxN];
  char pengarang[MxN];
  char nik_peminjam[MxN];
  ull no_pinjaman;
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

void insertArray(ArrayPinjaman* a, Pinjaman element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->arr = (Pinjaman*)realloc(a->arr, a->size * sizeof(Pinjaman));
  }
  a->arr[a->used++] = element;
}

void freeArray(ArrayPinjaman *a) {
  free(a->arr);
  a->arr = NULL;
  a->used = a->size = 0;
}

Pinjaman newPinjaman(const char* judul, const char* pengarang, const char* nik, ull no) {

}