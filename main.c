#include "material.h"
#include "list.h"
#include "service.h"
#include "ui.h"
#include <stdio.h>
#include <crtdbg.h>

void runAllTests();

int main() {
    List list = createEmptyList();
    runAllTests();
    runUI(&list);
    _CrtDumpMemoryLeaks();
    return 0;
}

void runAllTests() {
    testCRUD();
    testCreateDestroyValidate();
    testCreateList();
    testIterateList();
    testCopyList();
    testFiltering();
    testEnsureCapacity();
}
