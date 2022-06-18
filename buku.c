#ifndef BUKU_INCLUDED
#define BUKU_INCLUDED

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MxN 255
#define AVLBuku NodeBuku* // Macro pointer NodeBuku (root)

typedef struct {
  char judul[MxN];
  char pengarang[MxN];
  int qty;
} DataBuku;

typedef struct node {
  DataBuku data;
  struct node* left;
  struct node* right;
  int height;
} NodeBuku;

int maxHeightBuku(int a, int b) {
  return (a > b) ? a : b;
}

int heightBuku(AVLBuku node) {
  return node ? node->height : 0;
}

int balanceFactorBuku(AVLBuku node) {
  return heightBuku(node->left) - heightBuku(node->right);
}

AVLBuku getPredecessorBuku(AVLBuku node) {
  AVLBuku pred = node->left;
  while (pred->right) {
    pred = pred->right;
  }
  return pred;
}

AVLBuku newNodeBuku (DataBuku data) {
  AVLBuku node = (AVLBuku)malloc(sizeof(NodeBuku));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

AVLBuku rightRotateBuku(AVLBuku root) {
  AVLBuku left = root->left;
  AVLBuku leftRight = root->right;

  left->right = root;
  root->left = leftRight;

  root->height = 1 + maxHeightBuku(heightBuku(root->left), heightBuku(root->right));
  left->height = 1 + maxHeightBuku(heightBuku(left->left), heightBuku(left->right));

  return left;
}

AVLBuku leftRotateBuku(AVLBuku root) {
  AVLBuku right = root->right;
  AVLBuku rightLeft = right->left;

  right->left = root;
  root->right = rightLeft;

  root->height = 1 + maxHeightBuku(heightBuku(root->left), heightBuku(root->right));
  right->height = 1 + maxHeightBuku(heightBuku(right->left), heightBuku(right->right));

  return right;
}

AVLBuku selfBalanceBuku(AVLBuku root) {
  root->height = 1 + maxHeightBuku(heightBuku(root->left), heightBuku(root->right));
  int bf_root = balanceFactorBuku(root);

  if (bf_root > 1) {
    if (balanceFactorBuku(root->left) >= 0) {
      return rightRotateBuku(root);
    }
    else {
      root->left = leftRotateBuku(root->left);
      return rightRotateBuku(root);
    }
  }
  else if (bf_root < -1) {
    if (balanceFactorBuku(root->right) <= 0) {
      return leftRotateBuku(root);
    }
    else {
      root->right = rightRotateBuku(root->right);
      return leftRotateBuku(root);
    }
  }
  else return root;
}

AVLBuku insertNodeBuku(AVLBuku root, DataBuku data) {
  if (root == NULL) return newNodeBuku(data);
  else if (strcmp(data.judul, root->data.judul) < 0) root->left = insertNodeBuku(root->left, data);
  else if (strcmp(data.judul, root->data.judul) > 0) root->right = insertNodeBuku(root->right, data);
  else {
    if (strcmp(data.pengarang, root->data.pengarang) < 0) root->left = insertNodeBuku(root->left, data);
    else if (strcmp(data.pengarang, root->data.pengarang) > 0) root->right = insertNodeBuku(root->right, data);
    else {
      root->data.qty += data.qty;
      return root;
    }
  }
  return selfBalanceBuku(root);
}

AVLBuku deleteNodeBuku(AVLBuku root, const char* judul, const char* pengarang) {
  if (root == NULL) return NULL;
  else if (strcmp(judul, root->data.judul) < 0) root->left = deleteNodeBuku(root->left, judul, pengarang);
  else if (strcmp(judul, root->data.judul) > 0) root->right = deleteNodeBuku(root->right, judul, pengarang);
  else {
    if (strcmp(pengarang, root->data.pengarang) < 0) root->left = deleteNodeBuku(root->left, judul, pengarang);
    else if (strcmp(pengarang, root->data.pengarang) > 0) root->right = deleteNodeBuku(root->right, judul, pengarang);
    else {
      // 1 child or leaf
      if (root->left == NULL || root->right == NULL) {
        AVLBuku temp = root->right ? root->right : root->left;
        free(root);
        root = temp;
        if (!root) return root;
      }
      // 2 child
      else {
        AVLBuku pred = getPredecessorBuku(root);
        root->data = pred->data;
        root->left = deleteNodeBuku(root->left, pred->data.judul, pred->data.pengarang);
      }
    }
  }
  return selfBalanceBuku(root);
}

// CORE FUNCTIONS (Yang dipake function2 ini aja)
// Buat data buku
DataBuku newDataBuku(const char* judul, const char* pengarang, int qty) {
  DataBuku dataBuku;
  strcpy(dataBuku.judul, judul);
  strcpy(dataBuku.pengarang, pengarang);
  dataBuku.qty = qty;
  return dataBuku;
}

// Insert
void AVLBuku_Insert(AVLBuku* root, DataBuku data) { *root = insertNodeBuku(*root, data); }

// Delete
void AVLBuku_Delete(AVLBuku* root, const char* judul, const char* pengarang) { *root = deleteNodeBuku(*root, judul, pengarang); }

// Searching
AVLBuku AVLBuku_Search (AVLBuku root, const char* judul, const char* pengarang) {
  if (root == NULL) return NULL;
  else if (strcmp(judul, root->data.judul) < 0) return AVLBuku_Search(root->left, judul, pengarang);
  else if (strcmp(judul, root->data.judul) > 0) return AVLBuku_Search(root->right, judul, pengarang);
  else {
    if (strcmp(pengarang, root->data.pengarang) < 0) return AVLBuku_Search(root->left, judul, pengarang);
    else if (strcmp(pengarang, root->data.pengarang) > 0) return AVLBuku_Search(root->right, judul, pengarang);
    else return root;
  }
}

// Update hanya quantity (1 artinya ada, 0 artinya gada biar gausah cape2 search lagi)
int AVLBuku_UpdateQty (AVLBuku root, const char* judul, const char* pengarang, int new_qty) {
  if (root == NULL) return 0;
  else if (strcmp(judul, root->data.judul) < 0) return AVLBuku_UpdateQty(root->left, judul, pengarang, new_qty);
  else if (strcmp(judul, root->data.judul) > 0) return AVLBuku_UpdateQty(root->right, judul, pengarang, new_qty);
  else {
    if (strcmp(pengarang, root->data.pengarang) < 0) return AVLBuku_UpdateQty(root->left, judul, pengarang, new_qty);
    else if (strcmp(pengarang, root->data.pengarang) > 0) return AVLBuku_UpdateQty(root->right, judul, pengarang, new_qty);
    else {
      root->data.qty = new_qty;
      return 1;
    }
  }
}

// Inorder Traversal (DEBUG DOANG NTAR TAMPILANNYA BAGUSIN)
void displayFormat(DataBuku data, int* no) {
  printf("\nNo %d\n", *no);
  puts("================");
  printf("Judul : %s\n", data.judul);
  printf("Pengarang : %s\n", data.pengarang);
  printf("Quantity : %d\n\n", data.qty);
  (*no)++;
}

void AVLBuku_Display(AVLBuku root, int* no) {
  if (root) {
    AVLBuku_Display(root->left, no);
    displayFormat(root->data, no);
    AVLBuku_Display(root->right, no);
  }
}

void AVLBuku_WriteAllData(AVLBuku root, FILE *fp) {
  if (root) {
    AVLBuku_WriteAllData(root->left, fp);
    fprintf(fp,"%s#%s#%d\n", root->data.judul, root->data.pengarang, root->data.qty);
    AVLBuku_WriteAllData(root->right, fp);
  }
}

#endif