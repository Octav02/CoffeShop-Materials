
#include "ui.h"

void runAllTests();

int main() {
    runAllTests();
    CoffeeShop coffeeShop = createCoffeeShop();
    runUI(&coffeeShop);
    return 0;
}

void runAllTests() {
    testCreateDestroy();
    testCopy();
    testValidate();
    testCreateDestroyList();
    testCRUDList();
    testCopyList();
    testCreateCoffeeShop();
    testCRUDService();
    testUndo();
    testFiltering();
    testSorting();
}