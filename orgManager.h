#ifndef ORGMANAGER_H_INCLUDED
#define ORGMANAGER_H_INCLUDED

#include <iostream>
#define info(p) p->info
#define next(p) p->next
#define first(L) ((L).first)
#define last(L) ((L).last)

using namespace std;

struct organisasi {
    string nama;
    string kontak;
    int tahunBerdiri;
};

typedef struct elemenOrg *adr_org;
typedef organisasi infotypeOrg;

struct departemen {
    string nama;
    string koor;
    int jumlahAnggota;
};

typedef struct elemenDep *adr_dep;
typedef departemen infotypeDep;

struct elemenOrg {
    adr_org prev;
    infotypeOrg info;
    adr_dep departemen;
    adr_org next;
};

struct elemenDep {
    infotypeDep info;
    adr_dep next;
};

struct ListOrg {
    adr_org first;
    adr_org last;
};

struct ListDep {
    adr_dep first;
};

void menu();
bool isEmpty(ListOrg L);

void createListOrg(ListOrg &L);
adr_org createElmOrg(infotype x);
void insertLastOrg(ListOrg &L, adr_org P);
void deleteFirstOrg(ListOrg &L, adr_org &P);
void deleteAfterOrg(ListOrg &L, adr_org Prec, adr_org &P);
void deleteLastOrg(ListOrg &L, adr_org &P);
void deleteOrgById(ListOrg &L, string id);
void showOrgOnly(ListOrg L);
adr_org searchOrgById(ListOrg L, string X);


#endif // ORGMANAGER_H_INCLUDED
