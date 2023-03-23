#include "sorting.h"


void sort(List *list, CompareFunction f) {
    for (int i = 0; i < size(list) - 1; i++) {
        for (int j = i + 1; j < size(list); j++) {
            void *obj1 = get(list, i);
            void *obj2 = get(list, j);
            if (f(obj1,obj2) > 0) {
                update(list, i, obj2);
                update(list, j, obj1);
            }
        }
    }
}