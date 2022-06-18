#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "buku.c"

#define MxN 255
#define cls system("cls");
#define symbl printf("--> ");
#define enter printf("Tekan 'Enter' untuk melanjutkan...");

int template_fitur ();

void clear_buff();
void ascii_art ();
void main_menu ();
void book_management ();
void people_management ();
void default_input();
void load_data ();

void displayBuku ();
void insertBuku ();
void searchBuku ();
void updateBuku ();

void displayPeople ();
void pinjamBuku ();
void returnBuku ();

void memberManagement ();
void addMembership ();
void deleteMembership ();
void updateMembership ();

AVLBuku list_buku = NULL;

FILE *fp;

int main () {
    int option;
    int option_case_1;
    int option_case_2;
    load_data();

    do {
        cls
        ascii_art();
        main_menu();
        option = template_fitur();

        // Main switch
        switch (option) {
            // Untuk manajemen buku
            case 1:
                cls
                ascii_art();
                book_management();
                option_case_1 = template_fitur();
                switch (option_case_1) {
                    case 1:
                        displayBuku();
                        printf("\n\n");
                        enter getchar();
                        break;

                    case 2:
                        insertBuku();
                        break;

                    case 3:
                        searchBuku();
                        break;

                    case 4:
                        updateBuku();
                        break;

                    case 88:
                        break;

                    default:
                        default_input();
                        break;
                }
                break;

            // Untuk manajemen peminjam
            case 2:
                cls
                ascii_art();
                people_management();
                option_case_2 = template_fitur();
                switch (option_case_2) {
                    case 1:
                        /* code */
                        break;

                    case 2:
                        /* code */
                        break;

                    case 3:
                        /* code */
                        break;

                    case 4:
                        cls
                        ascii_art();
                        memberManagement();
                        int option_member = template_fitur();
                        switch (option_member) {
                            case 1:
                                addMembership();
                                break;

                            case 2:
                                /* code */
                                break;

                            case 3:
                                /* code */
                                break;

                            case 00:
                                break;

                            default:
                                default_input();
                                break;
                        }

                        break;

                    case 88:
                        break;

                    default:
                        default_input();
                        break;
                }
                getchar();
                break;

            // Exit
            case 0:
                cls
                ascii_art();
                printf("Terima Kasih!\n");
                break;

            default:
                default_input();
                break;
        }

    } while (option != 0);


    return 0;
}

// Main Function
void clear_buff() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF) {};
}

void ascii_art () {
    printf ("  _    ___ ___ ___    _   _____   __    _   ___ ___  ___ \n");
    printf (" | |  |_ _| _ ) _ \\  /_\\ | _ \\ \\ / /   /_\\ | _ \\ _ \\/ __|\n");
    printf (" | |__ | || _ \\   / / _ \\|   /\\ V /   / _ \\|  _/  _/\\__ \\\n");
    printf (" |____|___|___/_|_\\/_/ \\_\\_|_\\ |_|   /_/ \\_\\_| |_|  |___/\n");
    printf ("----------------------------------------------------------\n");
}

void main_menu () {
    printf("1. Kelola Buku\n");
    printf("2. Kelola Peminjam\n");
    printf("0. EXIT\n");
    printf ("----------------------------------------------------------\n");
}

void book_management () {
    printf("1.  List Buku\n");
    printf("2.  Tambah Buku Baru\n");
    printf("3.  Cari Buku\n");
    printf("4.  Update Buku\n");
    printf("88. KEMBALI\n");
    printf ("----------------------------------------------------------\n");
}

void people_management () {
    printf("1.  List Peminjam\n");
    printf("2.  Peminjaman Buku\n");
    printf("3.  Pengembalian Buku\n");
    printf("4.  Membership\n");
    //printf("5. Reminder\n");
    printf("00. AWAL\n");
    printf ("----------------------------------------------------------\n");
}

void template_akhir () {
    printf("\n\nBuku berhasil ditambahkan\n");
    enter getchar();
}

void default_input () {
    cls
    ascii_art();
    printf("Invalid Input\n\n");
    enter getch();
}

void load_data () {
    DataBuku temp;
    fp = fopen("dataBuku.txt", "r");
    while (fscanf(fp,"%[^#]#%[^#]#%d\n", temp.judul, temp.pengarang, &temp.qty) != EOF) {
        AVLBuku_Insert(&list_buku, temp);
    }
    fclose(fp);
}

int template_fitur () {
    int number;
    printf("Pilih fitur\n");
    symbl scanf("%d", &number); clear_buff();
    return number;
}

// Manajemen Buku
void displayBuku () {
    cls
    ascii_art();
    int no = 1;
    AVLBuku_Display(list_buku, &no);
}

void insertBuku () {
    cls

    char judul [MxN];
    char pengarang [MxN];
    const int qty;

    ascii_art();

    printf("Judul Buku\t\t: "); scanf("%[^\n]", judul); clear_buff();
    printf("Pengarang\t\t: "); scanf("%[^\n]", pengarang); clear_buff();
    printf("Jumlah Buku\t\t: "); scanf("%d", &qty); clear_buff();

    AVLBuku_Insert(&list_buku, newDataBuku(judul, pengarang, qty));

    fp = fopen("dataBuku.txt", "w");
    AVLBuku_WriteAllData(list_buku, fp);
    fclose(fp);
    template_akhir();
}

void searchBuku () {
    cls
    char judul [MxN];
    char pengarang [MxN];

    ascii_art();
    printf("Judul Buku\t\t: "); scanf("%[^\n]", judul); clear_buff();
    printf("Pengarang\t\t: "); scanf("%[^\n]", pengarang); clear_buff();

    AVLBuku nyari =  AVLBuku_Search(list_buku, judul, pengarang);
    if (nyari) {
        cls
        ascii_art();
        printf("Judul\t\t\t: %s\n", nyari->data.judul);
        printf("Pengarang\t\t: %s\n", nyari->data.pengarang);
        printf("Jumlah Buku\t\t: %d\n\n\n", nyari->data.qty);
        printf("Buku yang kamu cari berhasil ditemukan!\n");
        enter
    }
    else {
        printf("\nBuku yang kamu cari tidak ditemukan!\n");
        enter
    }

    getchar();
}

void updateBuku () {
    cls

    char judul [MxN];
    char pengarang [MxN];
    char newJudul [MxN];
    char newPengarang [MxN];
    int newQty;

    ascii_art();
    displayBuku();

    printf("=====================================\n\n");
    printf("Buku yang ingin diubah\n");
    printf("-------------------------\n");
    printf("Judul Buku\t\t: "); scanf("%[^\n]", judul); clear_buff();
    printf("Pengarang\t\t: "); scanf("%[^\n]", pengarang); clear_buff();

    AVLBuku nyari =  AVLBuku_Search(list_buku, judul, pengarang);
    if (nyari) {
        AVLBuku_Delete(&list_buku, judul, pengarang);
    }
    else {
        printf("\nBuku yang kamu cari tidak ditemukan!\n");
        enter getchar();
        return;
    }

    cls
    ascii_art();
    printf("Update Buku\n");
    printf("-------------------------\n");
    printf("Judul Buku\t\t: "); scanf("%[^\n]", newJudul); clear_buff();
    printf("Pengarang\t\t: "); scanf("%[^\n]", newPengarang); clear_buff();
    printf("Jumlah Buku\t\t: "); scanf("%d", &newQty);

    AVLBuku_Insert(&list_buku, newDataBuku(newJudul, newPengarang, newQty));

    fp = fopen("dataBuku.txt", "w");
    AVLBuku_WriteAllData(list_buku, fp);
    fclose(fp);

    printf("\n\nBuku berhasil diupdate\n");
    enter getchar();
}

// Peminjam Buku
void displayPeople () {

}

void pinjamBuku () {

}

void returnBuku () {

}

// Membership
void memberManagement () {
    printf("1. Tambah Membership\n");
    printf("2. Hapus Membership\n");
    printf("3. Update Membership\n");
    printf("88. Kembali\n");
    printf ("----------------------------------------------------------\n");
}

void addMembership () {
    cls

    char nama [MxN];
    char phone [MxN];
    char alamat [MxN];

    ascii_art();
    printf("Nama\t\t: "); scanf("%[^\n]", nama);
    printf("No. HP\t\t: "); scanf("%[^\n]", phone);
    printf("Alamat\t\t: "); scanf("%[^\n]", alamat);
    template_akhir();
}

void deleteMembership () {

}

void updateMembership () {

}
