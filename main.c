#include "material.h"
#include "list.h"
#include "service.h"
#include "ui.h"
#include <stdio.h>
#include <crtdbg.h>

void runAllTests();

int main() {
    CoffeeShop coffeeShop = createCoffeeShop();
    runAllTests();
    runUI(&coffeeShop);
    _CrtDumpMemoryLeaks();
    return 0;
}

void runAllTests() {
    testCRUD();
    testCreateDestroyValidate();
    testCreateList();
    testListOfLists();
    testIterateList();
    testCopyList();
    testUndo();
    testFiltering();
    testEnsureCapacity();
}
