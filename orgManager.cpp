#include "orgManager.h"

void menu(ListOrg &L){
    int pilih = 0;

    do {
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
        cout << "0. Keluar" << endl;
        cout << "=======================================" << endl;
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
                searchShowDept(L);
                break;
            case 8:
                handlerDeleteDept(L);
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
    nextDept(P) = NULL;

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
        cout << "[info]List kosong, tidak ada data yang bisa dihapus.\n";
        return;
    }

    adr_org P = searchOrgById(L, id);
    if (P == NULL){
        cout << "[info]Organisasi tidak ditemukan" << endl;
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
        cout << "[info] Organisasi tidak ditemukan" << endl;
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
        cout << "[info] Organisasi tidak ditemukan" << endl;
        return NULL;
    };
};

void showOrgOnly(ListOrg L){
    if (isEmpty(L)) {
        cout << "[Info] List Kosong" << endl;
    } else {
        adr_org P = first(L);
        cout << "\n===================================================" << endl;
        cout << "                  LIST ORGANISASI                  " << endl;
        cout << "===================================================" << endl;
        while (P != NULL) {
            // Menghitung jumlah departemen
            int deptCount = 0;
            adr_dept currentDept = nextDept(P);
            while (currentDept != NULL) {
                deptCount++;
                currentDept = next(currentDept);
            }

            // Menampilkan informasi organisasi
            cout << "ID Organisasi       : " << info(P).id << endl;
            cout << "Nama Organisasi     : " << info(P).nama << endl;
            cout << "Tahun Berdiri       : " << info(P).tahunBerdiri << endl;
            cout << "Jumlah Departemen   : " << deptCount << endl;
            cout << "---------------------------------------------" << endl;

            P = next(P);
        }
        cout << "===================================================" << endl;
        cout << endl;
    }
};

void showSelectedOrg(adr_org P){
    if (!P) {
        cout << "Organisasi tidak ditemukan atau pointer kosong." << endl;
        return;
    }

    cout << "===================================================" << endl;
    cout << "                 DATA ORGANISASI                   " << endl;
    cout << "===================================================" << endl;
    cout << "ID Organisasi       : " << info(P).id << endl;
    cout << "Nama Organisasi     : " << info(P).nama << endl;
    cout << "Tahun Berdiri       : " << info(P).tahunBerdiri << endl;
    cout << "---------------------------------------------------" << endl;

    // Menampilkan departemen terkait
    cout << "  Daftar Departemen:" << endl;
    adr_dept currentDept = nextDept(P); // Ambil daftar departemen organisasi ini
    if (currentDept) {
        int deptIndex = 1;
        while (currentDept) {
            cout << "    " << deptIndex++ << ". Nama Departemen  : " << info(currentDept).nama << endl;
            cout << "       Koordinator      : " << info(currentDept).koor << endl;
            cout << "       Jumlah Anggota   : " << info(currentDept).jumlahAnggota << endl;
            cout << "---------------------------------------------------" << endl;
            currentDept = next(currentDept);
        }
    } else {
        cout << "    Tidak ada departemen." << endl;
    }

    cout << "===================================================" << endl;
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

void insertFirstDept(adr_org PO, adr_dept PD) {
    if (nextDept(PO) == NULL) {
        nextDept(PO) = PD;
    } else {
        next(PD) = nextDept(PO);
        nextDept(PO) = PD;
    }

    if (nextDept(PO) == PD){
        cout << "[Info] Data berhasil disimpan" << endl;
    }
}

void insertLastDept(adr_org PO, adr_dept PD){
    if(nextDept(PO) == NULL){
        nextDept(PO) = PD;
    } else {
        adr_dept last = nextDept(PO);
        while (next(last) != NULL){
            last = next(last);
        };
        next(last) = PD;
    }
};

void deleteFirstDept(adr_org PO, adr_dept &PD){
    if (nextDept(PO) != NULL) {
        PD = nextDept(PO);
        if (next(PD) == NULL) {
            nextDept(PO) = NULL;
        } else {
            nextDept(PO) = next(PD);
            next(PD) = NULL;
        }
    }
};

void deleteLastDept(adr_org PO, adr_dept &PD){
    if (nextDept(PO) != NULL) {
        adr_dept Q = nextDept(PO);
        if (next(Q) == NULL) {
            nextDept(PO) = NULL;
        } else {
            while (next(next(Q)) != NULL){
                Q = next(Q);
            }
            PD = next(Q);
            next(Q) = NULL;
        };
    };
};

void deleteAfterOrg(adr_org PO, adr_dept Prec, adr_dept &P){
    if (nextDept(PO) != NULL){
        P = next(Prec);
        if (Prec == nextDept(PO) && next(Prec) == NULL) {
            nextDept(PO) = NULL;
        } else if (next(Prec) == NULL){
            adr_dept Q = nextDept(PO);
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

void deleteDeptByName(adr_org PO, string x) {
    if (!PO || nextDept(PO) == NULL) {
        cout << "[Info] List departemen kosong atau organisasi tidak valid." << endl;
        return;
    }

    adr_dept targetDept = searchDept(PO, x);

    if (!targetDept) {
        cout << "[Info] Departemen dengan nama \"" << x << "\" tidak ditemukan." << endl;
        return;
    }

    if (targetDept == nextDept(PO)) {
        adr_dept temp;
        deleteFirstDept(PO, temp);
    } else if (next(targetDept) == NULL) {
        adr_dept temp;
        deleteLastDept(PO, temp);
    } else {
        adr_dept prec = nextDept(PO);
        while (next(prec) != targetDept) {
            prec = next(prec);
        }
        adr_dept temp;
        deleteAfterOrg(PO, prec, temp);
    }

    cout << "[Info] Departemen \"" << x << "\" berhasil dihapus." << endl;
}

adr_dept searchDept(adr_org PO, string X){
    if (nextDept(PO) == NULL){
        cout << "[Info] List Kosong" << endl;
        return NULL;
    } else {
        adr_dept P = nextDept(PO);
        while(P != NULL){
            if (info(P).nama == X){
                return P;
            };
            P = next(P);
        };
        return NULL;
        cout << "[Info] Departemen tidak ditemukan" << endl;
    };
};

void showSelectedDept(adr_dept PD){
    if (!PD) {
        cout << "[Info] departemen tidak ditemukan" << endl;
        return;
    }

    cout << "===================================================" << endl;
    cout << "                    DATA DEPARTEMEN                " << endl;
    cout << "===================================================" << endl;

    cout << "Nama Departemen  : " << info(PD).nama << endl;
    cout << "Koordinator      : " << info(PD).koor << endl;
    cout << "Jumlah Anggota   : " << info(PD).jumlahAnggota << endl;
    cout << "---------------------------------------------------" << endl;

    cout << "===================================================" << endl;
}

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
                if (P != NULL){
                    showSelectedOrg(P);
                }
                cout << endl;
                break;
            case 2:
                cout << "? Masukkan Nama Organisasi: ";
                cin >> keyword;
                P = searchOrgByNama(L, keyword);
                if (P != NULL){
                    showSelectedOrg(P);
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
            cin >> input;
            if (input == "Y" || input == "y"){
                deleteOrgById(LO, id);
            }
            cout << "? Apakah anda ingin menghapus data lain?[Y/n]: ";
            cin >> input;
            if (input == "n" || input == "N" || input == "no" || input == "No"){
                run = false;
            }
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
    adr_dept PD, q;
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

    q = nextDept(PO);
    if (q == NULL){
        insertFirstDept(PO, PD);
    } else {
        insertLastDept(PO, PD);
    }
    cout << endl;
}

void showAllOrgWithDept(ListOrg orgList) {
    adr_org currentOrg = orgList.first;

    if (!currentOrg) {
        cout << "Tidak ada organisasi untuk ditampilkan." << endl;
        return;
    }

    cout << "===================================================" << endl;
    cout << "                DATA ORGANISASI                    " << endl;
    cout << "===================================================" << endl;

    while (currentOrg) {
        cout << "ID Organisasi       : " << info(currentOrg).id << endl;
        cout << "Nama Organisasi     : " << info(currentOrg).nama << endl;
        cout << "Tahun Berdiri       : " << info(currentOrg).tahunBerdiri << endl;
        cout << "---------------------------------------------------" << endl;

        cout << "  Daftar Departemen:" << endl;
        adr_dept currentDept = nextDept(currentOrg);
        if (currentDept) {
            int deptIndex = 1;
            while (currentDept) {
                cout << "    " << deptIndex++ << ". Nama Departemen  : " << info(currentDept).nama << endl;
                cout << "       Koordinator    : " << info(currentDept).koor << endl;
                cout << "       Jumlah Anggota : " << info(currentDept).jumlahAnggota << endl;
                cout << "---------------------------------------------------" << endl;
                currentDept = next(currentDept);
            }
        } else {
            cout << "    Tidak ada departemen." << endl;
            cout << "---------------------------------------------------" << endl;
        }

        currentOrg = next(currentOrg);
    }

    cout << "===================================================" << endl;
}

void searchShowDept(ListOrg L){
    adr_org PO;
    adr_dept PD, x;
    string id, keyword, input;
    bool run = true;

    do {
        cout << "? Masukan Id Organisasi yang ingin dicari: ";
        cin >> id;
        PO = searchOrgById(L, id);
        if (PO != NULL){
            PD = nextDept(PO);
            if (PD != NULL){
                cout << "? Masukan nama departemen yang ingin dicari: ";
                cin >> keyword;
                x = searchDept(PO, keyword);
                showSelectedDept(x);
                cout << endl;
            }
        }
        cout << "? Apakah anda ingin mencari lagi[Y/n]: ";
        cin >> input;
        if (input == "n" || input == "N" || input == "no" || input == "No"){
            run = false;
        }
    } while (run == true);
}

void handlerDeleteDept(ListOrg &LO){
    string id, nama, input;
    adr_org PO;
    bool run = true;

    do {
        showOrgOnly(LO);
        cout << "? Masukan Id Organisasi yang ingin dihapus: ";
        cin >> id;
        PO = searchOrgById(LO, id);
        if (PO != NULL && nextDept(PO) != NULL){
            cout << "masuk sini";
            showSelectedOrg(PO);
            cout << "? Masukan Nama Departemen yang ingin dihapus: ";
            cin >> nama;
            adr_dept PD = searchDept(PO, nama);
            if (PD != NULL){
                cout << "? Apakah anda yakin ingin manghapus " << info(PD).nama << "?[Y/n]: ";
                cin >> input;
                if (input == "Y" || input == "y"){
                    deleteDeptByName(PO, nama);
                }
                cout << "? Apakah anda ingin menghapus data lain?[Y/n]: ";
                cin >> input;
                if (input == "n" || input == "N" || input == "no" || input == "No"){
                    run = false;
                }
            }
        } else {
            if (PO != NULL && nextDept(PO) == NULL){
                cout << "[Info] organisasi tidak memiliki departemen" << endl;
            }
            cout << "? Apakah anda ingin mencari lagi[Y/n]: ";
            cin >> input;
            if (input == "n" || input == "N" || input == "no" || input == "No"){
                run = false;
            }
        }

    } while (run == true);
    cout << endl;
}
