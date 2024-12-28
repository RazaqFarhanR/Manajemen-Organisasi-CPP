#ifndef ORGMANAGER_H_INCLUDED
#define ORGMANAGER_H_INCLUDED

#include <iostream>
#define info(p) p->info
#define prev(P) P->prev
#define next(p) p->next
#define first(L) ((L).first)
#define last(L) ((L).last)
#define nextDept(P) P->nextDept

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
adr_org searchOrgByNama(ListOrg L, string X);
void showSelectedOrg(adr_org P);

// ADT Departemen
void createListDept(ListDept &LD);
adr_dept createElmDept(infotypeDept X);
void insertFirstDept(adr_org PO, adr_dept PD);
void insertLastDept(adr_org PO, adr_dept PD);
adr_dept searchDept(adr_org PO, string X);
void deleteFirstDept(adr_org PO, adr_dept &P);
void deleteAfterDept(adr_org PO, adr_dept Prec, adr_dept &P);
void deleteLastDept(adr_org PO, adr_dept &P);
void deletDeptbyName(adr_org PO, string X);
void showSelectedDept(adr_dept PD);

//Menu Utils
void handlerAddOrg(ListOrg &LO);
void showAllOrgWithDept(ListOrg orgList);
void searchShowOrg(ListOrg LO);
void handlerDeleteOrg(ListOrg &LO);
void handlerAddDept(ListOrg &LO);
void searchShowDept(ListOrg LO);
void handlerDeleteDept(ListOrg &LO);
#endif // ORGMANAGER_H_INCLUDED
