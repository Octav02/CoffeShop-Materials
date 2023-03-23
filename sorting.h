#include "list.h"

typedef int(*CompareFunction)(void*obj1, void*obj2);

void sort(List* list, CompareFunction f);