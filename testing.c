#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pinjaman.c"

#define MxN 255
#define ll long long int
#define ld long double

ArrayPinjaman list_pinjaman;

int main() {
  initArrayPinjaman(&list_pinjaman, 10);
  insertArrayPinjaman(&list_pinjaman, newPinjaman("test","test","12031230123",0,0,0));
  for (int i = 0; i < list_pinjaman.used; i++) {
    printf (
      "%s %s %s\n",
      list_pinjaman.arr[i].judul,
      list_pinjaman.arr[i].pengarang,
      list_pinjaman.arr[i].nik_peminjam
    );
    printf("Tanggal Peminjaman : "); printFormattedDate(&list_pinjaman.arr[i].tanggal_peminjaman); printf("\n");
    printf("Tanggal Deadline : "); printFormattedDate(&list_pinjaman.arr[i].tanggal_deadline); printf("\n");
  }
  struct tm satu = {
    .tm_mday = 19,
    .tm_mon = 6 - 1,
    .tm_year = 2022 - 1900
  };

  struct tm dua = {
    .tm_mday = 22,
    .tm_mon = 6 - 1,
    .tm_year = 2022 - 1900
  };

  printf("%d\n",getDiffDay(satu, dua));
  return 0;
}