#ifndef MEMBER_INCLUDED
#define MEMBER_INLCUDED

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "pinjaman.c"

#define MxN 255
#define AVLMember NodeMember* // Macro pointer NodeMember (root)
#define ull unsigned long long

typedef struct {
  ull *arr;
  size_t used;
  size_t size;
} ArrayNoPinjaman;

void initArrayNoPinjaman(ArrayNoPinjaman *a, size_t initialSize) {
  a->arr = (ull*)malloc(initialSize * sizeof(ull));
  a->used = 0;
  a->size = initialSize;
}

void insertArrayNoPinjaman(ArrayNoPinjaman *a, ull no_pinjaman) {
  if (a->used == a->size) {
    a->size *= 2;
    a->arr = (ull*)realloc(a->arr, a->size * sizeof(ull));
  }
  a->arr[a->used++] = no_pinjaman;
}

void freeArrayNoPinjaman(ArrayNoPinjaman *a) {
  free(a->arr);
  a->arr = NULL;
  a->used = a->size = 0;
}

void deleteArrayNoPinjaman(ArrayNoPinjaman *a, ull no_pinjaman) {
  ArrayNoPinjaman temp;
  temp.arr = (ull*)malloc(10 * sizeof(ull));
  temp.size = 10;
  temp.used = 0;
  int notFound = 1;
  for (int i = 0; i < a->used; i++) {
    if (a->arr[i] != no_pinjaman) {
      insertArrayNoPinjaman(&temp, a->arr[i]);
      notFound = 0;
    }
  }
  if (notFound) return;
  freeArrayNoPinjaman(a);
  *a = temp;
}

typedef struct {
  char nama[MxN];
  char no_hp[MxN];
  char alamat[MxN];
  char nik[MxN];
  ArrayNoPinjaman list_pinjaman;
} DataMember;

typedef struct node_member {
  DataMember data;
  struct node_member* right;
  struct node_member* left;
  int height;
} NodeMember;

int maxHeightMember(int a, int b) {
  return (a > b) ? a : b;
}

int heightMember(AVLMember node) {
  return node ? node->height : 0;
}

int balanceFactorMember(AVLMember node) {
  return heightMember(node->left) - heightMember(node->right);
}

AVLMember getPredecessorMember(AVLMember node) {
  AVLMember pred = node->left;
  while (pred->right) {
    pred = pred->right;
  }
  return pred;
}

AVLMember newNodeMember (DataMember data) {
  AVLMember node = (AVLMember)malloc(sizeof(NodeMember));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

AVLMember rightRotateMember(AVLMember root) {
  AVLMember left = root->left;
  AVLMember leftRight = root->right;

  left->right = root;
  root->left = leftRight;

  root->height = 1 + maxHeightMember(heightMember(root->left), heightMember(root->right));
  left->height = 1 + maxHeightMember(heightMember(left->left), heightMember(left->right));

  return left;
}

AVLMember leftRotateMember(AVLMember root) {
  AVLMember right = root->right;
  AVLMember rightLeft = right->left;

  right->left = root;
  root->right = rightLeft;

  root->height = 1 + maxHeightMember(heightMember(root->left), heightMember(root->right));
  right->height = 1 + maxHeightMember(heightMember(right->left), heightMember(right->right));

  return right;
}

AVLMember selfBalanceMember(AVLMember root) {
  root->height = 1 + maxHeightMember(heightMember(root->left), heightMember(root->right));
  int bf_root = balanceFactorMember(root);

  if (bf_root > 1) {
    if (balanceFactorMember(root->left) >= 0) {
      return rightRotateMember(root);
    }
    else {
      root->left = leftRotateMember(root->left);
      return rightRotateMember(root);
    }
  }
  else if (bf_root < -1) {
    if (balanceFactorMember(root->right) <= 0) {
      return leftRotateMember(root);
    }
    else {
      root->right = rightRotateMember(root->right);
      return leftRotateMember(root);
    }
  }
  else return root;
}

AVLMember insertNodeMember(AVLMember root, DataMember data) {
  if (root == NULL) return newNodeMember(data);
  else if (strcmp(data.nik, root->data.nik) < 0) root->left = insertNodeMember(root->left, data);
  else if (strcmp(data.nik, root->data.nik) > 0) root->right = insertNodeMember(root->right, data);
  else return root;
  return selfBalanceMember(root);
}

AVLMember deleteNodeMember(AVLMember root, const char* nik) {
  if (root == NULL) return NULL;
  else if (strcmp(nik, root->data.nik) < 0) root->left = deleteNodeMember(root->left, nik);
  else if (strcmp(nik, root->data.nik) > 0) root->right = deleteNodeMember(root->right, nik);
  else {
    // 1 child or leaf
    if (root->left == NULL || root->right == NULL) {
      AVLMember temp = root->right ? root->right : root->left;
      free(root);
      root = temp;
      if (!root) return root;
    }
    // 2 child
    else {
      AVLMember pred = getPredecessorMember(root);
      root->data = pred->data;
      root->left = deleteNodeMember(root->left, pred->data.nik);
    }
  }
  return selfBalanceMember(root);
}

// Core Functions
DataMember newDataMember (
  const char* nama,
  const char* no_hp,
  const char* alamat,
  const char* nik
) {
  DataMember dataMember;
  strcpy(dataMember.nama, nama);
  strcpy(dataMember.no_hp, no_hp);
  strcpy(dataMember.alamat, alamat);
  strcpy(dataMember.nik, nik);
  initArrayNoPinjaman(&dataMember.list_pinjaman, 10);
  return dataMember;
}

void addNoPinjaman(AVLMember member, ull no_pinjaman) {
  insertArrayNoPinjaman(&member->data.list_pinjaman, no_pinjaman);
}

void removeNoPinjaman(AVLMember member, ull no_pinjaman) {
  deleteArrayNoPinjaman(&member->data.list_pinjaman, no_pinjaman);
}

void AVLMember_Insert(AVLMember* root, DataMember data) { *root = insertNodeMember(*root, data); }

void AVLMember_Delete(AVLMember* root, const char* nik) { *root = deleteNodeMember(*root, nik); }

void printDataPinjaman(DataMember member_data, ArrayPinjaman list_pinjaman) {
  int arridx = 0;
  ull arr[member_data.list_pinjaman.used+1];
  for (int i = 0; i < member_data.list_pinjaman.used; i++) {
    Pinjaman dataPinjaman = list_pinjaman.arr[member_data.list_pinjaman.arr[i]];
    if (dataPinjaman.status == 'b') arr[arridx++] = member_data.list_pinjaman.arr[i];
  }
  if (arridx) {
    printf("\n%s - %s\n",member_data.nik, member_data.nama);
    puts("=============================");
    puts("List Pinjaman : ");
    for (int i = 0; i < arridx; i++) {
      Pinjaman dataPinjaman = list_pinjaman.arr[arr[i]];
      printf(" %d. %s (%s)\n",i+1,dataPinjaman.judul,dataPinjaman.pengarang);
      printf("    Deadline : "); printFormattedDate(&dataPinjaman.tanggal_deadline); printf("\n");
    }
  }
}

void AVLMember_DisplayAllPeminjam(AVLMember root, ArrayPinjaman list_pinjaman) {
  if (root) {
    AVLMember_DisplayAllPeminjam(root->left, list_pinjaman);
    if (root->data.list_pinjaman.used) printDataPinjaman(root->data, list_pinjaman);
    AVLMember_DisplayAllPeminjam(root->right, list_pinjaman);
  }
}

AVLMember AVLMember_Search(AVLMember root, const char* nik) {
  if (root == NULL) return NULL;
  else if (strcmp(nik, root->data.nik) < 0) return AVLMember_Search(root->left, nik);
  else if (strcmp(nik, root->data.nik) > 0) return AVLMember_Search(root->right, nik);
  else return root;
}

int AVLMember_Update(AVLMember root, const char* nik, char* nama, char* no_hp, char* alamat) {
  if (root == NULL) return 0;
  else if (strcmp(nik, root->data.nik) < 0) return AVLMember_Update(root->left, nik, nama, no_hp, alamat);
  else if (strcmp(nik, root->data.nik) > 0) return AVLMember_Update(root->right, nik, nama, no_hp, alamat);
  else {
    strcpy(root->data.alamat,alamat);
    strcpy(root->data.nama,nama);
    strcpy(root->data.no_hp,no_hp);
    return 1;
  }
}

void AVLMember_WriteAllData(AVLMember root, FILE *fp) {
  if (root) {
    AVLMember_WriteAllData(root->left, fp);
    fprintf(fp,"%s#%s#%s#%s\n", root->data.nama, root->data.no_hp, root->data.alamat, root->data.nik);
    AVLMember_WriteAllData(root->right, fp);
  }
}

#endif