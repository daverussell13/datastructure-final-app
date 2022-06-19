#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "member.c"

#define MxN 255
#define ll long long int
#define ld long double

AVLMember list_member;

int main() {
  AVLMember_Insert(&list_member, newDataMember("test","123123123","test","123"));
  AVLMember_Insert(&list_member, newDataMember("test","123123123","test","1123"));
  AVLMember_Insert(&list_member, newDataMember("test","123123123","test","11231233"));
  AVLMember_Insert(&list_member, newDataMember("test","123123123","test","1212313"));
  AVLMember_Insert(&list_member, newDataMember("test","123123123","test","12123893"));
  AVLMember orangnya = AVLMember_Search(list_member, "123");
  addNoPinjaman(orangnya, 12);
  addNoPinjaman(orangnya, 112);
  addNoPinjaman(orangnya, 10);
  addNoPinjaman(orangnya, 113);
  addNoPinjaman(orangnya, 18);
  addNoPinjaman(orangnya, 39);
  addNoPinjaman(orangnya, 40);
  printf("%s %s %s\n",orangnya->data.nama, orangnya->data.nik, orangnya->data.no_hp);
  for (int i = 0; i < orangnya->data.list_pinjaman.used; i++) {
    printf("%llu ", orangnya->data.list_pinjaman.arr[i]);
  }
  printf("\n");
  removeNoPinjaman(orangnya, 39);
  removeNoPinjaman(orangnya, 90);
  removeNoPinjaman(orangnya, 113);
  for (int i = 0; i < orangnya->data.list_pinjaman.used; i++) {
    printf("%llu ", orangnya->data.list_pinjaman.arr[i]);
  }
  return 0;
}