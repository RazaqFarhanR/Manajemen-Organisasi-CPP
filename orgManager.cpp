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
                cout << "pilihan 3" << endl;
                break;
            case 4:
                cout << "pilihan 4" << endl;
                break;
            case 5:
                handlerAddDept(L);
                break;
            case 6:
                showOrgOnly(L);
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
    cout << "Data dengan Id " << info(P).id << " berhasil dihapus" << endl;
}

adr_org searchOrgById(ListOrg L, string X){
    if (first(L) == NULL){
        cout << "List Kosong" << endl;
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

    cout << "[info]Data berhasil disimpan" << endl;
    cout << endl;
}
