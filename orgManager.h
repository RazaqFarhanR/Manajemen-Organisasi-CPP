#ifndef ORGMANAGER_H_INCLUDED
#define ORGMANAGER_H_INCLUDED

#include <iostream>
#define info(p) p->info
#define prev(P) P->prev
#define next(p) p->next
#define first(L) ((L).first)
#define last(L) ((L).last)

using namespace std;

struct organisasi {
    string id;
    string nama;
    int tahunBerdiri;
};

typedef struct elemenOrg *adr_org;
typedef organisasi infotypeOrg;

struct departemen {
    string nama;
    string koor;
    int jumlahAnggota;
};

typedef struct elemenDep *adr_dept;
typedef departemen infotypeDept;

struct elemenOrg {
    adr_org prev;
    infotypeOrg info;
    adr_dept nextDept;
    adr_org next;
};

struct elemenDep {
    infotypeDept info;
    adr_dept next;
};

struct ListOrg {
    adr_org first;
    adr_org last;
};

struct ListDept {
    adr_dept first;
};

void menu(ListOrg &L);
bool isEmpty(ListOrg L);
bool isEmptyDept(ListDept LD);

// ADT Organisasi
void createListOrg(ListOrg &L);
adr_org createElmOrg(infotypeOrg X);
void insertFirstOrg(ListOrg &L, adr_org P);
void insertLastOrg(ListOrg &L, adr_org P);
void deleteFirstOrg(ListOrg &L, adr_org &P);
void deleteAfterOrg(ListOrg &L, adr_org Prec, adr_org &P);
void deleteLastOrg(ListOrg &L, adr_org &P);
void deleteOrgById(ListOrg &L, string id);
void showOrgOnly(ListOrg L);
adr_org searchOrgById(ListOrg L, string X);

// ADT Departemen
void createListDept(ListDept &LD);
adr_dept createElmDept(infotypeDept X);
void insertFirstDept(ListDept &LD, adr_dept PD);
void insertLastDept(ListDept &LD, adr_dept PD);
adr_dept searchDept(ListOrg LO, string X);
void deleteFirstDept(ListDept &LD, adr_dept &P);
void deleteAfterDept(ListDept &LD, adr_dept Prec, adr_dept &P);
void deleteLastDept(ListDept &LD, adr_dept &P);
void handleDeleteDept(ListOrg &L, string X);

//General
void connectDeptToOrg();
void showAllOrgWithDept();
void calculateDeptOnOrg();

//Menu Utils
void handlerAddOrg(ListOrg &LO);
void handlerAddDept(ListOrg &LO);

#endif // ORGMANAGER_H_INCLUDED
