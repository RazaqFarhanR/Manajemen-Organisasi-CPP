#include "orgManager.h"

void menu(){
    cout << "===============================================================" << endl;
    cout << "1. Insert data organisasi" << endl;
    cout << "2. Show data organisasi" << endl;
    cout << "3. Menghaspus data organisasi beserta departemennya" << endl;
    cout << "4. Mencari data organisasi" << endl;
    cout << "5. Insert data departemen" << endl;
    cout << "6. Menghubungkan data organisasi ke departemen" << endl;
    cout << "7. Menampilkan seluruh data organisasi beserta departemennya" << endl;
    cout << "8. Mencari data departemen pada organisasi tertentu" << endl;
    cout << "9. Menghapus data departemen pada organisasi tertentu" << endl;
    cout << "10. Menghitung jumlah data departemen dari organisasi tertentu" << endl;
    cout << "0. exit" << endl;
    cout << "===============================================================" << endl;
};

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

void insertLastOrg(ListOrg &L, adr_org P){
    if(first(L) == NULL){
        first(L) = P;
    } else {
        adr_org last = first(L);
        while (next(last) != NULL){
            last = next(last);
        };
        next(last) = P;
    }
};

void deleteFirstOrg(ListOrg &L, adr_org &P){
    if (!isEmpty(L)) {
        adr_org P = first(L);
        if (next(P) == NULL) {
            first(L) = NULL;
        } else {
            first(L) = next(P);
            next(P) = NULL;
        }
    }
};

void deleteLastOrg(ListOrg &L, adr_org &P){
    if (!isEmpty(L)) {
        adr_org Q = first(L);
        if (next(Q) == NULL) {
            first(L) = NULL;
        } else {
            while (next(next(Q)) != NULL){
                Q = next(Q);
            }
            P = next(Q);
            next(Q) = NULL;
        };
    };
};

void deleteAfterOrg(ListOrg &L, adr_org Prec, adr_org &P){
    if (!isEmpty(L)){
        P = next(Prec);
        if (Prec == first(L) && next(Prec) == NULL) {
            first(L) = NULL;
        } else if (next(Prec) == NULL){
            adr_org Q = first(L);
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
