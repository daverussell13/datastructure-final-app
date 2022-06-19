#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buku.c"
#include "member.c"
#include "pinjaman.c"

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
AVLMember list_member = NULL;
ArrayPinjaman list_pinjaman;

int no_pinjaman = 0;

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
                        pinjamBuku();
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
                                deleteMembership();
                                break;

                            case 3:
                                updateMembership();
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
    enter
}

void load_data () {
    DataBuku tempBuku;
    DataMember tempMember;
    Pinjaman tempPeminjam;
    initArrayPinjaman(&list_pinjaman, 10);

    fp = fopen("dataBuku.txt", "r");
    while (fscanf(fp,"%[^#]#%[^#]#%d\n", tempBuku.judul, tempBuku.pengarang, &tempBuku.qty) != EOF) {
        AVLBuku_Insert(&list_buku, tempBuku);
    }

    fp = fopen("dataMember.txt", "r");
    while (fscanf(fp, "%[^#]#%[^#]#%[^#]#%[^\n]\n", tempMember.nama, tempMember.no_hp, tempMember.alamat, tempMember.nik) != EOF) {
        AVLMember_Insert(&list_member, newDataMember(tempMember.nama,tempMember.no_hp,tempMember.alamat,tempMember.nik));
    }

    fp = fopen("dataPeminjam.txt", "r");
    while (
        fscanf (
            fp, "%[^#]#%[^#]#%[^#]#%d/%d/%d#%d/%d/%d#%d/%d/%d#%c ",
            tempPeminjam.nik_peminjam,
            tempPeminjam.judul,
            tempPeminjam.pengarang,
            &tempPeminjam.tanggal_peminjaman.tm_mday,
            &tempPeminjam.tanggal_peminjaman.tm_mon,
            &tempPeminjam.tanggal_peminjaman.tm_year,
            &tempPeminjam.tanggal_deadline.tm_mday,
            &tempPeminjam.tanggal_deadline.tm_mon,
            &tempPeminjam.tanggal_deadline.tm_year,
            &tempPeminjam.tanggal_pengembalian.tm_mday,
            &tempPeminjam.tanggal_pengembalian.tm_mon,
            &tempPeminjam.tanggal_pengembalian.tm_year,
            &tempPeminjam.status
        ) != EOF) {
        insertArrayPinjaman(&list_pinjaman, tempPeminjam);
        AVLMember peminjam = AVLMember_Search(list_member, tempPeminjam.nik_peminjam);
        addNoPinjaman(peminjam, no_pinjaman++);
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
    cls
    int i;
    char nik[MxN];
    Pinjaman dataPinjaman;

    ascii_art();
    printf("Input NIK\t: "); scanf("%s", nik); clear_buff();
    AVLMember orang = AVLMember_Search(list_member, nik);

    if (orang) {
        cls
        int option;
        char judul[MxN];
        char pengarang[MxN];

        ascii_art();
        printf("Judul Buku\t\t: "); scanf("%[^\n]", judul); clear_buff();
        printf("Pengarang\t\t: "); scanf("%[^\n]", pengarang); clear_buff();
        AVLBuku buku = AVLBuku_Search(list_buku, judul, pengarang);

        if (buku && buku->data.qty) {
            addNoPinjaman(orang, no_pinjaman++);
            buku->data.qty--;
            printf("\n\nDeadline :\n");
            printf("1. Set Otomatis (7 hari)\n");
            printf("2. Set Manual\n");
            symbl scanf("%d", &option); clear_buff();

            if (option == 1) {
                dataPinjaman = newPinjaman(judul, pengarang, nik, 0, 0, 0);
                insertArrayPinjaman(&list_pinjaman, dataPinjaman);
                printf("helo \n");
            }
            else {
                cls
                int tanggal_deadline;
                int bulan_deadline;
                int tahun_deadline;
                ascii_art();
                printf("Judul Buku\t\t: %s\n", judul);
                printf("Pengarang\t\t: %s\n", pengarang);
                printf("\nTanggal Deadline\t: "); scanf("%d", &tanggal_deadline); clear_buff();
                printf("Tahun Deadline\t\t: "); scanf("%d", &bulan_deadline); clear_buff();
                printf("Bulan Deadline\t\t: "); scanf("%d", &bulan_deadline); clear_buff();
                dataPinjaman = newPinjaman(judul, pengarang, nik, tanggal_deadline, bulan_deadline, tahun_deadline);
                insertArrayPinjaman(&list_pinjaman, dataPinjaman);
            }
        }
        else {
            printf("\nBuku tidak ditemukan!\n");
            enter getchar();
            return;
        }

        // write data pinjaman
        fp = fopen("dataPeminjam.txt", "w");
        for (i = 0; i < list_pinjaman.used; i++) {
            fprintf(
                fp, "%s#%s#%s#%d/%d/%d#%d/%d/%d#%d/%d/%d#%c\n",
                list_pinjaman.arr[i].nik_peminjam,
                list_pinjaman.arr[i].judul,
                list_pinjaman.arr[i].pengarang,
                dataPinjaman.tanggal_peminjaman.tm_mday,
                dataPinjaman.tanggal_peminjaman.tm_mon,
                dataPinjaman.tanggal_peminjaman.tm_year,
                dataPinjaman.tanggal_deadline.tm_mday,
                dataPinjaman.tanggal_deadline.tm_mon,
                dataPinjaman.tanggal_deadline.tm_year,
                dataPinjaman.tanggal_pengembalian.tm_mday,
                dataPinjaman.tanggal_pengembalian.tm_mon,
                dataPinjaman.tanggal_pengembalian.tm_year,
                dataPinjaman.status
            );
        }

        fp = fopen("dataBuku.txt", "w");
        AVLBuku_WriteAllData(list_buku, fp);
        fclose(fp);
        printf("Data peminjam berhasil ditambahkan!\n");
        enter getchar();
    }
    else {
        printf("\nData tidak ditemukan!\n");
        enter getchar();
        return;
    }
}

void returnBuku () {

}

// Membership
void memberManagement () {
    printf("1.  Tambah Membership\n");
    printf("2.  Hapus Membership\n");
    printf("3.  Update Membership\n");
    printf("88. Kembali\n");
    printf ("----------------------------------------------------------\n");
}

void addMembership () {
    cls

    char nama [MxN];
    char no_hp [MxN];
    char alamat [MxN];
    char nik [MxN];

    ascii_art();
    printf("Nama\t\t: "); scanf("%[^\n]", nama); clear_buff();
    printf("No. HP\t\t: "); scanf("%[^\n]", no_hp); clear_buff();
    printf("Alamat\t\t: "); scanf("%[^\n]", alamat); clear_buff();
    printf("NIK\t\t: "); scanf("%[^\n]", nik); clear_buff();

    AVLMember_Insert(&list_member, newDataMember(nama, no_hp, alamat, nik));
    fp = fopen("dataMember.txt", "w");
    AVLMember_WriteAllData(list_member, fp);
    fclose(fp);

    printf("\n\nPendaftaran membership a.n %s, berhasil!\n", nama);
    AVLMember_Display(list_member);
    enter getchar();
}

void deleteMembership () {
    cls
    char nik[MxN];

    ascii_art();
    printf("Input NIK\t: "); scanf("%s", nik); clear_buff();
    AVLMember nyari = AVLMember_Search(list_member, nik);

    if (nyari) {
        printf("\nData a.n %s, berhasil dihapus!\n", nyari->data.nama);
        AVLMember_Delete(&list_member, nik);
        fp = fopen("dataMember.txt", "w");
        AVLMember_WriteAllData(list_member, fp);
        fclose(fp);
        enter getchar();
    }
    else {
        printf("\nData tidak ditemukan!\n");
        enter getchar();
        return;
    }
}

void updateMembership () {
    cls
    char nik[MxN];

    ascii_art();
    printf("Input NIK\t\t: "); scanf("%s", nik); clear_buff();
    AVLMember nyari = AVLMember_Search(list_member, nik);

    if (nyari) {
        int option;
        char nama[MxN];
        char no_hp[MxN];
        char alamat[MxN];

        printf("\nData yang ingin diubah?\n");
        printf("1. Nama\n");
        printf("2. No Hp\n");
        printf("3. Alamat\n");
        symbl scanf("%d", &option); clear_buff();
        printf("\n");

        switch (option) {
            case 1:
                printf("Nama Baru\t: "); scanf("%[^\n]", nama); clear_buff();
                AVLMember_Update(list_member, nik, nama, nyari->data.no_hp, nyari->data.alamat);
                break;

            case 2:
                printf("No HP Baru\t: "); scanf("%s", no_hp); clear_buff();
                AVLMember_Update(list_member, nik, nyari->data.nama, no_hp, nyari->data.alamat);
                break;

            case 3:
                printf("Alamat Baru\t: "); scanf("%[^\n]", alamat); clear_buff();
                AVLMember_Update(list_member, nik, nyari->data.nama, nyari->data.no_hp, alamat);
                break;

            default:
                default_input();
                break;
        }

        fp = fopen("dataMember.txt", "w");
        AVLMember_WriteAllData(list_member, fp);
        fclose(fp);
        printf("\nData member berhasil diupdate!\n");
        enter getchar();
    }
    else {
        printf("\nData tidak ditemukan!\n");
        enter getchar();
        return;
    }
}