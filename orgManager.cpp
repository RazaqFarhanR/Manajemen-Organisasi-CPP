#include "orgManager.h"

void menu(ListOrg &L){
    int pilih = 0;
    cout << "=======================================" << endl;
    cout << "     SISTEM PENGELOLAAN ORGANISASI     " << endl;
    cout << "=======================================" << endl;
    cout << "1. Tambah organisasi" << endl;
    cout << "2. Tampilkan semua organisasi" << endl;
    cout << "3. Hapus organisasi dan semua departemennya" << endl;
    cout << "4. Cari organisasi" << endl;
    cout << "5. Tambah departemen ke organisasi" << endl;
    cout << "6. Tampilkan organisasi beserta departemennya" << endl;
    cout << "7. Cari departemen dalam organisasi" << endl;
    cout << "8. Hapus departemen dari organisasi" << endl;
    cout << "9. Hitung jumlah departemen dalam organisasi" << endl;
    cout << "0. Keluar" << endl;
    cout << "=======================================" << endl;

    do {
        cout << "? Masukkan nomor menu (0 untuk keluar): ";
        cin >> pilih;

        if (pilih == 0) {
            cout << "Keluar dari program. Terima kasih!\n";
            break;
        }

        switch (pilih){
            case 1:
                handlerAddOrg(L);
                break;
            case 2:
                showOrgOnly(L);
                break;
            case 3:
                handlerDeleteOrg(L);
                break;
            case 4:
                searchShowOrg(L);
                break;
            case 5:
                handlerAddDept(L);
                break;
            case 6:
                showAllOrgWithDept(L);
                break;
            case 7:
                cout << "pilihan 7" << endl;
                break;
            case 8:
                cout << "pilihan 8" << endl;
                break;
            case 9:
                cout << "pilihan 9" << endl;
                break;
            default:
                cout << "! Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilih != 0);
};

//====================
// Organisasi Utils
//====================
void createListOrg(ListOrg &L){
    first(L) = NULL;
};

adr_org createElmOrg(infotypeOrg X){
    adr_org P = new elemenOrg;
    info(P).id = X.id;
    info(P).nama = X.nama;
    info(P).tahunBerdiri = X.tahunBerdiri;
    next(P) = NULL;

    return P;
};

bool isEmpty(ListOrg L){
    return (first(L) == NULL);
};

void insertFirstOrg(ListOrg &L, adr_org P){
    if (first(L) != NULL && last(L) != NULL) {
        next(P) = first(L);
        prev(first(L)) = P;
        first(L) = P;
    } else {
        first(L) = P;
        last(L) = P;
    }
}

void insertLastOrg(ListOrg &L, adr_org P){
    if (first(L) != NULL && last(L) != NULL) {
        prev(P) = last(L);
        next(last(L)) = P;
        last(L) = P;
    } else {
        first(L) = P;
        last(L) = P;
    }
};

void deleteFirstOrg(ListOrg &L, adr_org &P){
    if (!isEmpty(L)){
        P = first(L);
        if (first(L) == last(L)){
            first(L) = NULL;
            last(L) = NULL;
        } else {
            first(L) = next(P);
            prev(first(L)) = NULL;
        }

        next(P) = NULL;
    }
};

void deleteLastOrg(ListOrg &L, adr_org &P){
    if (!isEmpty(L)){
        P = last(L);
        if (first(L) == last(L)){
            first(L) = NULL;
            last(L) = NULL;
        } else {
            last(L) = prev(P);
            next(last(L)) = NULL;
        }

        prev(P) = NULL;
    }
};

void deleteAfterOrg(ListOrg &L, adr_org Prec, adr_org &P) {
    if (!isEmpty(L)) {
        P = next(Prec);
        if (P != NULL) {
            if (next(P) == NULL) {
                next(Prec) = NULL;
            }
            else {
                next(Prec) = next(P);
                prev(next(P)) = Prec;
            }
            next(P) = NULL;
            prev(P) = NULL;
        }
    }
}

void deleteOrgById(ListOrg &L, string id){
    if (L.first == NULL) {
        cout << "List kosong, tidak ada data yang bisa dihapus.\n";
        return;
    }

    adr_org P = searchOrgById(L, id);
    if (P == NULL){
        cout << "Organisasi tidak ditemukan" << endl;
        return;
    }
    if (P == first(L)){
        deleteFirstOrg(L, P);
    } else {
        if (next(P) == NULL){
            deleteLastOrg(L, P);
        } else {
            adr_org Q = first(L);
            while (next(Q) != P){
                Q = next(Q);
            }
            //cout << info(Q).id;
            deleteAfterOrg(L, Q, P);
        }
    }
    cout << "[Info]Data dengan Id " << info(P).id << " berhasil dihapus" << endl;
}

adr_org searchOrgById(ListOrg L, string X){
    if (first(L) == NULL){
        cout << "[info] List Kosong" << endl;
        return NULL;
    } else {
        adr_org P = first(L);
        while(P != NULL){
            if (info(P).id == X){
                return P;
            };
            P = next(P);
        };
        return NULL;
    };
};

adr_org searchOrgByNama(ListOrg L, string X){
    if (first(L) == NULL){
        cout << "[info] List Kosong" << endl;
        return NULL;
    } else {
        adr_org P = first(L);
        while(P != NULL){
            if (info(P).nama == X){
                return P;
            };
            P = next(P);
        };
        return NULL;
    };
};

void showOrgOnly(ListOrg L){
    if(isEmpty(L)){
        cout << "List Kosong" << endl;
    } else {
       adr_org P = first(L);
       printf("\n");
       cout << "List Organisasi:" << endl;
       while (P != NULL){
            cout << "ID: " << info(P).id << endl;
            cout << "Organisasi: " << info(P).nama << endl;
            cout << "Tahun Berdiri: " << info(P).tahunBerdiri << endl;
            cout << "---------------------------------------------" << endl;
            P = next(P);
       };
       cout << endl;
    }
};

//====================
// Departement Utils
//====================

bool isEmpty(ListDept LD){
    return (first(LD) == NULL);
};

adr_dept createElmDept(infotypeDept X){
    adr_dept P = new elemenDep;
    info(P).nama = X.nama;
    info(P).koor = X.koor;
    info(P).jumlahAnggota = X.jumlahAnggota;
    next(P) = NULL;

    return P;
}

void insertFirstDept(ListDept &LD, adr_dept PD) {
    if (first(LD) == NULL) {
        first(LD) = PD;
    } else {
        next(PD) = first(LD);
        first(LD) = PD;
    }
}

void insertLastDept(ListDept &LD, adr_dept PD){
    if(first(LD) == NULL){
        first(LD) = PD;
    } else {
        adr_dept last = first(LD);
        while (next(last) != NULL){
            last = next(last);
        };
        next(last) = PD;
    }
};

void deleteFirstDept(ListDept &LD, adr_dept PD){
    if (first(LD) != NULL) {
        PD = first(LD);
        if (next(PD) == NULL) {
            first(LD) = NULL;
        } else {
            first(LD) = next(PD);
            next(PD) = NULL;
        }
    }
};

void deleteLastDept(ListDept &LD, adr_dept PD){
    if (first(LD) != NULL) {
        adr_dept Q = first(LD);
        if (next(Q) == NULL) {
            first(LD) = NULL;
        } else {
            while (next(next(Q)) != NULL){
                Q = next(Q);
            }
            PD = next(Q);
            next(Q) = NULL;
        };
    };
};

void deleteAfterOrg(ListDept &LD, adr_dept Prec, adr_dept &P){
    if (first(LD) != NULL){
        P = next(Prec);
        if (Prec == first(LD) && next(Prec) == NULL) {
            first(LD) = NULL;
        } else if (next(Prec) == NULL){
            adr_dept Q = first(LD);
            while (next(next(Q)) != NULL){
                Q = next(Q);
            };
            P = next(Q);
            next(Q) = NULL;
        } else {
            next(Prec) = next(P);
            next(P) = NULL;
        };
    };
};

adr_dept searchDept(ListDept &LD, string X){
    if (first(LD) == NULL){
        cout << "List Kosong" << endl;
    } else {
        adr_dept P = first(LD);
        while(P != NULL){
            if (info(P).nama == X){
                return P;
            };
            P = next(P);
        };
        return NULL;
    };
};


//====================
// Menu Utils
//====================
void handlerAddOrg(ListOrg &LO){
    infotypeOrg x;
    adr_org P;

    cout << " > Masukan id Organisasi: ";
    cin >> x.id;
    cout << " > Masukan nama Organisasi: ";
    cin >> x.nama;
    cout << " > Masukan tahun berdiri Organisasi: ";
    cin >> x.tahunBerdiri;
    P = createElmOrg(x);

    if(first(LO) == NULL){
        insertFirstOrg(LO, P);
    } else {
        insertLastOrg(LO, P);
    }

    cout << "[info] Data berhasil disimpan" << endl;
    cout << endl;
}

void searchShowOrg(ListOrg L){
    int pilih;
    string keyword;
    adr_org P;

    do {
        cout << "? Ingin mencari organasasi berdasarkan apa?" << endl;;
        cout << " 1. Id" << endl;
        cout << " 2. Nama" << endl;
        cout << " 0. Kembali" << endl;
        cout << "? Masukkan nomor menu (0 untuk kembali): ";
        cin >> pilih;

        if (pilih == 0) {
            break;
        }

        switch (pilih){
            case 1:
                cout << "? Masukkan Id Organisasi: ";
                cin >> keyword;
                P = searchOrgById(L, keyword);
                if (P == NULL){
                    cout << "[info] Organisasi tidak ditemukan" << endl;
                } else {
                    cout << P << endl;
                }
                cout << endl;
                break;
            case 2:
                cout << "? Masukkan Nama Organisasi: ";
                cin >> keyword;
                P = searchOrgByNama(L, keyword);
                if (P == NULL){
                    cout << "[info] Organisasi tidak ditemukan" << endl;
                } else {
                    cout << P << endl;
                }
                cout << endl;
                break;
        }
    } while (pilih != 0);
    cout << endl;
}

void handlerDeleteOrg(ListOrg &LO){
    string id, input;
    adr_org P;
    showOrgOnly(LO);
    bool run = true;

    do {
        cout << "? Masukan Id Organisasi yang ingin dihapus: ";
        cin >> id;
        P = searchOrgById(LO, id);
        if (P != NULL){
            cout << "? Apakah anda yakin ingin manghapus " << info(P).nama << " beserta departemennya[Y/n]: ";
            deleteOrgById(LO, id);
        } else {
            cout << "[info] Organisasi tidak ditemukan" << endl;
            cout << "? Apakah anda ingin mencari lagi[Y/n]: ";
            cin >> input;
            if (input == "n" || input == "N" || input == "no" || input == "No"){
                run = false;
            }
        }

    } while (run == true);
    cout << endl;
}

void handlerAddDept(ListOrg &L){
    infotypeDept x;
    string keyword;
    adr_dept PD;
    adr_org PO;

    cout << " > Masukan ID organisasi yang akan ditambahkan departemen: ";
    cin >> keyword;

    PO = searchOrgById(L, keyword);

    cout << " ! Masukan data dept yang akan dimasukan ke " << info(PO).nama << endl;
    cout << "  > Masukan nama departemen: ";
    cin >> x.nama;
    cout << "  > Masukan nama kordinator: ";
    cin >> x.koor;
    cout << "  > Masukan jumlah anggota: ";
    cin >> x.jumlahAnggota;
    PD = createElmDept(x);

    PO->nextDept = PD;
}

void showAllOrgWithDept(ListOrg orgList) {
    adr_org currentOrg = orgList.first;

    if (!currentOrg) {
        cout << "Tidak ada organisasi untuk ditampilkan." << endl;
        return;
    }

    // Header organisasi
    cout << "---------------------------------------------------" << endl;
    cout << "ID"
         << "Nama Organisasi"
         << "Tahun Berdiri" << endl;
    cout << "---------------------------------------------------" << endl;

    while (currentOrg) {
        // Tampilkan informasi organisasi
        cout << currentOrg->info.id
             <<currentOrg->info.nama
             << currentOrg->info.tahunBerdiri << endl;

        cout << "  Departemen:" << endl;
        // Tampilkan departemen terkait jika ada
        adr_dept currentDept = currentOrg->nextDept;
        if (currentDept) {
            int deptIndex = 1; // Menandakan urutan departemen
            while (currentDept) {
                cout << "    " << deptIndex++ << ". " << currentDept->info.nama << endl;
                cout << "       Koordinator: " << currentDept->info.koor << endl;
                cout << "       Jumlah Anggota: " << currentDept->info.jumlahAnggota << endl;
                cout << "---------------------------------------------------" << endl;
                currentDept = currentDept->next;
            }
        } else {
            cout << "    Tidak ada departemen." << endl;
        }

        currentOrg = currentOrg->next;
    }
}
