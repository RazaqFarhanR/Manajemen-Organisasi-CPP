#ifndef ORGMANAGER_H_INCLUDED
#define ORGMANAGER_H_INCLUDED

#include <iostream>
#define first(L) L.first
#define next(p) p->next
#define info(p) p->info

using namespace std;

struct organisasi {
    string id;
    string nama;
    int tahunBerdiri;
};

typedef struct elemenOrg *adr_org;
typedef organisasi infotype;

struct elemenOrg {
    infotype info;
    adr_org next;
};

struct ListOrg {
    adr_org first;
};

void createListOrg(ListOrg &L);
adr_org createElmOrg(infotype x);
void insertLastOrg(ListOrg &L, adr_org P);
bool isEmpty(ListOrg L);
void deleteFirstOrg(ListOrg &L, adr_org &P);
void deleteAfterOrg(ListOrg &L, adr_org Prec, adr_org &P);
void deleteLastOrg(ListOrg &L, adr_org &P);
void deleteOrgById(ListOrg &L, string id);
void showOrgOnly(ListOrg L);
adr_org searchOrgById(ListOrg L, string X);


#endif // ORGMANAGER_H_INCLUDED
