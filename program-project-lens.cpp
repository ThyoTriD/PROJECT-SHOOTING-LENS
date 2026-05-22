#include <iostream>
#include <stdio.h>    
#include <stdlib.h>   
#include <iomanip>

using namespace std;

struct Node {
    char  id[50];
    char  nama[100];
    char  kategori[50];
    char  spesifikasi[150];
    char  lokasiRak[100];
    char  status[50];
    int   stok;
    Node* kanan; 
    Node* kiri;  
};

int totalItem = 0; 

void salinString(char* tujuan, const char* asal) {
    int i = 0;
    while (asal[i] != '\0') { tujuan[i] = asal[i]; i++; }
    tujuan[i] = '\0';
}

int bandingkanString(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}

bool mengandungString(const char* haystack, const char* needle) {
    if (!haystack || !needle) return false;
    int hLen = 0, nLen = 0;
    while (haystack[hLen] != '\0') hLen++;
    while (needle[nLen] != '\0') nLen++;
    
    if (nLen == 0) return true;
    if (nLen > hLen) return false;
    
    for (int i = 0; i <= hLen - nLen; i++) {
        bool match = true;
        for (int j = 0; j < nLen; j++) {
            char h = haystack[i + j], n = needle[j];
            if (h >= 'A' && h <= 'Z') h += 32;
            if (n >= 'A' && n <= 'Z') n += 32;
            if (h != n) { match = false; break; }
        }
        if (match) return true;
    }
    return false;
}

Node* buatNode(const char* id, const char* nama, const char* kategori, const char* spesifikasi, 
                      const char* lokasiRak, const char* status, int stok) {
    
    Node* newNode = (Node*)malloc(sizeof(Node)); 
    
    salinString(newNode->id, id);
    salinString(newNode->nama, nama);
    salinString(newNode->kategori, kategori);
    salinString(newNode->spesifikasi, spesifikasi);
    salinString(newNode->lokasiRak, lokasiRak);
    salinString(newNode->status, status);
    
    newNode->stok  = stok;
    newNode->kanan = NULL; 
    newNode->kiri  = NULL;  
    
    return newNode;
}

void sisipNodeBelakang(Node** head, const char* id, const char* nama, const char* kategori, 
                       const char* spesifikasi, const char* lokasiRak, const char* status, int stok) {
    Node* newNode = buatNode(id, nama, kategori, spesifikasi, lokasiRak, status, stok);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* bantu = *head;
        while (bantu->kanan != NULL) bantu = bantu->kanan;
        bantu->kanan = newNode;
        newNode->kiri = bantu;
    }
    totalItem++;
}

void tukarData(Node* a, Node* b) {
    char strBantu[150]; 
    salinString(strBantu, a->id); salinString(a->id, b->id); salinString(b->id, strBantu);
    salinString(strBantu, a->nama); salinString(a->nama, b->nama); salinString(b->nama, strBantu);
    salinString(strBantu, a->kategori); salinString(a->kategori, b->kategori); salinString(b->kategori, strBantu);
    salinString(strBantu, a->spesifikasi); salinString(a->spesifikasi, b->spesifikasi); salinString(b->spesifikasi, strBantu);
    salinString(strBantu, a->lokasiRak); salinString(a->lokasiRak, b->lokasiRak); salinString(b->lokasiRak, strBantu);
    salinString(strBantu, a->status); salinString(a->status, b->status); salinString(b->status, strBantu);
    int stokBantu = a->stok; a->stok = b->stok; b->stok = stokBantu;
}

void quickSortNama(Node* awal, Node* akhir) {
    if (akhir == NULL || awal == akhir || awal == akhir->kanan) return;
    Node* low = awal; Node* high = akhir;
    char pivot[100]; salinString(pivot, awal->nama);
    while (true) {
        while (low != akhir->kanan && bandingkanString(low->nama, pivot) < 0) low = low->kanan;
        while (high != awal->kiri && bandingkanString(high->nama, pivot) > 0) high = high->kiri;
        bool lsh = false; Node* c = low;
        while (c != NULL && c != akhir->kanan) { if (c == high) { lsh = true; break; } c = c->kanan; }
        if (lsh && low != high) { tukarData(low, high); low = low->kanan; high = high->kiri; }
        else { if (low == high) { low = low->kanan; high = high->kiri; } break; }
    }
    if (awal != high && awal != high->kanan) quickSortNama(awal, high);
    if (low != akhir && low->kiri != akhir) quickSortNama(low, akhir);
}

void cetakHeaderTabel() {
    cout << "=========================================================================================================\n";
    cout << left << setw(12) << "ID" << "| " << setw(20) << "Nama Alat" << "| " 
         << setw(15) << "Kategori" << "| " << setw(20) << "Spesifikasi" << "| " 
         << setw(15) << "Lokasi" << "| " << "Stok" << endl;
    cout << "---------------------------------------------------------------------------------------------------------\n";
}

void cetakBarisTabel(Node* item) {
    cout << left << setw(12) << item->id << "| " << setw(20) << item->nama << "| " 
         << setw(15) << item->kategori << "| " << setw(20) << item->spesifikasi << "| " 
         << setw(15) << item->lokasiRak << "| " << item->stok << endl;
}

void cariBerasarkanID(Node* head, const char* idCari) {
    Node* bantu = head;
    cetakHeaderTabel();
    while (bantu != NULL) {
        if (bandingkanString(bantu->id, idCari) == 0) {
            cetakBarisTabel(bantu);
            cout << "=========================================================================================================\n";
            return; 
        }
        bantu = bantu->kanan;
    }
    cout << "\n[INFO] Data dengan ID '" << idCari << "' tidak ditemukan.\n";
    cout << "=========================================================================================================\n";
}

void cariBerdasarkanNama(Node* head, const char* namaCari) {
    Node* bantu = head;
    int count = 0;
    cetakHeaderTabel();
    while (bantu != NULL) {
        if (mengandungString(bantu->nama, namaCari)) {
            cetakBarisTabel(bantu); count++;
        }
        bantu = bantu->kanan;
    }
    cout << "=========================================================================================================\n";
    cout << "Total ditemukan: " << count << " item.\n";
}

void cariBerdasarkanKategori(Node* head, const char* kategoriCari) {
    Node* bantu = head;
    int count = 0;
    cetakHeaderTabel();
    while (bantu != NULL) {
        if (bandingkanString(bantu->kategori, kategoriCari) == 0) {
            cetakBarisTabel(bantu); count++;
        }
        bantu = bantu->kanan;
    }
    cout << "=========================================================================================================\n";
    cout << "Total ditemukan: " << count << " item.\n";
}

void cariBerdasarkanStatus(Node* head, const char* statusCari) {
    Node* bantu = head;
    int count = 0;
    cetakHeaderTabel();
    while (bantu != NULL) {
        if (bandingkanString(bantu->status, statusCari) == 0) {
            cetakBarisTabel(bantu); count++;
        }
        bantu = bantu->kanan;
    }
    cout << "=========================================================================================================\n";
    cout << "Total ditemukan: " << count << " item.\n";
}

void cariBerdasarkanStok(Node* head, int stokMin, int stokMax) {
    Node* bantu = head;
    int count = 0;
    cetakHeaderTabel();
    while (bantu != NULL) {
        if (bantu->stok >= stokMin && bantu->stok <= stokMax) {
            cetakBarisTabel(bantu); count++;
        }
        bantu = bantu->kanan;
    }
    cout << "=========================================================================================================\n";
    cout << "Total ditemukan: " << count << " item.\n";
}

void tampilkanData(Node* head) {
    if (!head) { cout << "\nINFO :Data Inventaris Masih Kosong.\n"; return; }
    cetakHeaderTabel();
    while (head) {
        cetakBarisTabel(head);
        head = head->kanan;
    }
    cout << "=========================================================================================================\n";
}

void hapusNode(Node** head, const char* idHapus) {
    if (*head == NULL) {
        cout << "\n[INFO] Data masih kosong.\n";
        return;
    }

    Node* bantu = *head;
    bool ketemu = false;

    while (bantu != NULL) {
        if (bandingkanString(bantu->id, idHapus) == 0) {
            ketemu = true;
            break;
        }
        bantu = bantu->kanan;
    }

    if (!ketemu) {
        cout << "\n[INFO] Alat dengan ID '" << idHapus << "' tidak ditemukan.\n";
        return;
    }

    if (*head == bantu) {
        *head = bantu->kanan;
        if (*head != NULL) {
            (*head)->kiri = NULL;
        }
    } 
    else {
        bantu->kiri->kanan = bantu->kanan;
        if (bantu->kanan != NULL) {
            bantu->kanan->kiri = bantu->kiri;
        }
    }

    free(bantu);
    totalItem--;
    cout << "\n[SISTEM] Data berhasil dihapus!\n";
}

void simpanKeFile(Node* head) {
    FILE* file = fopen("datalens.txt", "wb"); 
    if (!file) return;
    Node* bantu = head;
    while (bantu != NULL) {
        fwrite(bantu, sizeof(Node), 1, file);
        bantu = bantu->kanan;
    }
    fclose(file);
}

void muatDariFile(Node** head) {
    FILE* file = fopen("datalens.txt", "rb"); 
    if (!file) return;
    while (true) {
        Node* baru = (Node*)malloc(sizeof(Node));
        if (fread(baru, sizeof(Node), 1, file) != 1) {
            free(baru); break;
        }
        baru->kanan = NULL; baru->kiri = NULL;
        if (*head == NULL) *head = baru;
        else {
            Node* t = *head;
            while (t->kanan != NULL) t = t->kanan;
            t->kanan = baru; baru->kiri = t;
        }
        totalItem++;
    }
    fclose(file);
}

void menuCari(Node* head) {
    char pilihan; 
    do {
        system("cls");
        cout << "=== MENU PENCARIAN DATA ===\n\n";
        cout << "1. Cari berdasarkan ID\n";
        cout << "2. Cari berdasarkan Nama\n";
        cout << "3. Cari berdasarkan Kategori\n";
        cout << "4. Cari berdasarkan Status\n";
        cout << "5. Cari berdasarkan Range Stok\n";
        cout << "0. Kembali\n";
        cout << "\nPilih: ";
        cin >> pilihan;

        if (pilihan == '1') {
            system("cls");
            char idCari[50];
            cout << "Masukkan ID: ";
            cin.ignore(); 
            cin.getline(idCari, 50); 
            cout << "\nHASIL:\n";
            cariBerasarkanID(head, idCari); 
            system("pause");
        }
        else if (pilihan == '2') {
            system("cls");
            char namaCari[100];
            cout << "Masukkan Nama: ";
            cin.ignore(); 
            cin.getline(namaCari, 100);
            cout << "\nHASIL:\n";
            cariBerdasarkanNama(head, namaCari);
            system("pause");
        }
        else if (pilihan == '3') {
            system("cls");
            char kategoriCari[50];
            cout << "Masukkan Kategori: ";
            cin.ignore(); 
            cin.getline(kategoriCari, 50);
            cout << "\nHASIL:\n";
            cariBerdasarkanKategori(head, kategoriCari);
            system("pause");
        }
        else if (pilihan == '4') {
            system("cls");
            char statusCari[50];
            cout << "Masukkan Status: ";
            cin.ignore(); 
            cin.getline(statusCari, 50);
            cout << "\nHASIL:\n";
            cariBerdasarkanStatus(head, statusCari);
            system("pause");
        }
        else if (pilihan == '5') {
            system("cls");
            int stokMin, stokMax;
            cout << "Stok Min Max: ";
            cin >> stokMin >> stokMax;
            cout << "\nHASIL:\n";
            cariBerdasarkanStok(head, stokMin, stokMax);
            system("pause");
        }
    } while (pilihan != '0');
}

int main() {
    Node* head = NULL;
    muatDariFile(&head);
    char pil; 
    
    do {
        system("cls"); 
        cout << "=== SYSTEM INVENTARIS LENS PROJECT 2026 ===\n";
        cout << "Total Data: " << totalItem << " Item\n\n";
        tampilkanData(head);
        
        cout << "\n1. Tambah Alat\n";
        cout << "2. Cari Data\n";
        cout << "3. Urutkan Nama\n";
        cout << "4. Hapus Data\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pil;

        if (pil == '1') {
            char id[50], n[100], k[50], w[50], spek[150], rak[100], stat[50]; 
            int s;
            cout << "\n[INPUT]\n";
            
            cout << "Waktu Input    : "; cin.ignore(); cin.getline(w, 50);
            cout << "ID Alat        : "; cin.getline(id, 50); 
            cout << "Nama Alat      : "; cin.getline(n, 100);
            cout << "Kategori       : "; cin.getline(k, 50);
            cout << "Spesifikasi    : "; cin.getline(spek, 150);
            cout << "Lokasi Rak     : "; cin.getline(rak, 100);
            cout << "Status         : "; cin.getline(stat, 50);
            cout << "Jumlah Stok    : "; cin >> s;
            
            sisipNodeBelakang(&head, id, n, k, spek, rak, stat, s);
            
            simpanKeFile(head); 
            cout << "\nFile berhasil disimpan!\n";
            system("pause");
        }
        else if (pil == '2') {
            menuCari(head);
        }
        else if (pil == '3') {
            Node* ekor = head;
            if (ekor) {
                while (ekor->kanan != NULL) ekor = ekor->kanan;
                quickSortNama(head, ekor);
                simpanKeFile(head); 
                cout << "\nFile telah diurutkan dan disimpan!"; 
                cin.ignore(); cin.get();
            }
        }
        else if (pil == '4') {
            system("cls");
            char idHapus[50];
            cout << "=== HAPUS DATA ===\n\n";
            tampilkanData(head);
            
            cout << "\nMasukkan ID (0 untuk batal): ";
            cin.ignore(); 
            cin.getline(idHapus, 50);
            
            if (bandingkanString(idHapus, "0") != 0) {
                hapusNode(&head, idHapus);
                simpanKeFile(head);
            }
            system("pause");
        }
    } while (pil != '0'); 

    cout << "\nMenutup program...\n";
    return 0;
}
