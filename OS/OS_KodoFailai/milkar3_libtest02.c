/* Mildaras Karvelis milkar3 */
/* Failas: milkar3_sablonas.c */
#include <stdio.h>
#include <dlfcn.h>

typedef int (*FunctionType)(int);

int main() {
    void* handle;
    FunctionType vp_testlib;

    // Įkeliame biblioteką
    handle = dlopen("./libloginas02a.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Klaida: Nepavyko įkelti bibliotekos: %s\n", dlerror());
        return 1;
    }

    // Gauname funkcijos adresą
    vp_testlib = (FunctionType) dlsym(handle, "vp_testlib");
    if (!vp_testlib) {
        fprintf(stderr, "Klaida: Nepavyko rasti funkcijos: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    // Iškviečiame funkciją
    int result = vp_testlib(5);
    printf("Funkcijos rezultatas: %d\n", result);

    // Uždarome biblioteką
    dlclose(handle);

    return 0;
}
