#include "material.h"
#include "list.h"
#include "service.h"
#include "ui.h"

void runAllTests();

int main() {
    List list = createEmptyList();
    runAllTests();
    runUI(&list);
    return 0;
}

void runAllTests() {
    testCRUD();
    testCreateDestroyValidate();
    testCreateList();
    testIterateList();
    testCopyList();
}
