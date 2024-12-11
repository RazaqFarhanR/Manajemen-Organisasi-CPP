#include <iostream>
#include "orgManager.h"

using namespace std;

int main()
{
    ListOrg L;
    infotypeOrg X;
    adr_org P;
    createListOrg(L);
    showOrgOnly(L);

    X.id = "001";
    X.nama = "TLKM";
    X.tahunBerdiri = 1986;
    P = createElmOrg(X);
    insertLastOrg(L, P);

    X.id = "002";
    X.nama = "TLKM";
    X.tahunBerdiri = 1986;
    P = createElmOrg(X);
    insertLastOrg(L, P);

    X.id = "003";
    X.nama = "TLKM";
    X.tahunBerdiri = 1986;
    P = createElmOrg(X);
    insertLastOrg(L, P);

    X.id = "004";
    X.nama = "TLKM";
    X.tahunBerdiri = 1986;
    P = createElmOrg(X);
    insertLastOrg(L, P);

    showOrgOnly(L);

    deleteOrgById(L, "002");

    showOrgOnly(L);

    //P = searchOrgById(L, "001");
    //if (P != NULL) {
    //    cout << P << endl;
    //} else {
    //    cout << "Data tidak ditemukan" << endl;
    //}

    return 0;
}
