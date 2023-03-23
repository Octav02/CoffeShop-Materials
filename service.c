#include "service.h"
#include "sorting.h"
#include <string.h>
#include <assert.h>

CoffeeShop createCoffeeShop() {
    CoffeeShop rez;
    rez.materialList = createEmptyList((DestroyFunction) destroyMaterial, (CopyFunction) copyMaterial);
    rez.undoList = createEmptyList((DestroyFunction) destroyList, (CopyFunction) copyList);
    return rez;
}

void destroyCoffeeShop(CoffeeShop *coffeeShop) {
    destroyList(coffeeShop->materialList);
    destroyList(coffeeShop->undoList);
}

int addMaterial(CoffeeShop *coffeeShop, char *name, char *producer, int quantity) {
    Material *material = createMaterial(name, producer, quantity);
    int res = validateMaterial(material);
    if (res != 0) {
        destroyMaterial(material);
        return res;
    }
    for (int i = 0; i < size(coffeeShop->materialList); i++) {
        Material *current = get(coffeeShop->materialList, i);
        if (!strcmp(current->name, name) && !strcmp(current->producer, producer)) {
            List *toUndo = copyList(coffeeShop->materialList);
            current->quantity += quantity;
            add(coffeeShop->undoList, toUndo);
            destroyMaterial(material);
            return 0;
        }
    }
    List *toUndo = copyList(coffeeShop->materialList);
    add(coffeeShop->materialList, material);
    add(coffeeShop->undoList, toUndo);

    return 0;
}

int updateMaterial(CoffeeShop *coffeeShop, int pos, char *name, char *producer, int quantity) {
    Material *material = createMaterial(name, producer, quantity);
    if (pos >= coffeeShop->materialList->length || pos < 0) {
        destroyMaterial(material);
        return -1;
    }
    int res = validateMaterial(material);
    if (res != 0) {
        destroyMaterial(material);
        return res;
    }
    List *toUndo = copyList(coffeeShop->materialList);
    destroyMaterial(coffeeShop->materialList->elements[pos]);
    res = update(coffeeShop->materialList, pos, material);
    add(coffeeShop->undoList, toUndo);
    return res;
}

int removeMaterial(CoffeeShop *coffeeShop, int pos) {
    if (pos >= coffeeShop->materialList->length || pos < 0) {
        return -1;
    }
    List *toUndo = copyList(coffeeShop->materialList);

    int res = removeElement(coffeeShop->materialList,pos);
    add(coffeeShop->undoList, toUndo);
    return res;
}

Material *getMaterial(CoffeeShop *coffeeShop, int pos) {
    Material * res = get(coffeeShop->materialList, pos);
    return res;
}

int undo(CoffeeShop *coffeeShop) {
    if (size(coffeeShop->undoList) <= 0)
        return 1;
    List *modified = get(coffeeShop->undoList,size(coffeeShop->undoList) - 1);
    coffeeShop ->undoList->length -= 1;
    destroyList(coffeeShop->materialList);
    coffeeShop->materialList = modified;
    return 0;
}

int sizeOfMaterialList(CoffeeShop *coffeeShop) {
    return size(coffeeShop->materialList);
}

int getAllMaterialsByName(CoffeeShop *coffeeShop, char *name) {
    int res = 0;
    for (int i = 0; i < size(coffeeShop->materialList); i++) {
        Material * current = get(coffeeShop->materialList,i);
        if (!strcmp(current->name, name))
            res += current->quantity;
    }
    return res;
}

List *getAllMaterials(CoffeeShop *coffeeShop) {
    return coffeeShop->materialList;
}

List *getAllMaterialsWithStartingLetter(CoffeeShop *coffeeShop, char letter) {
    List* res = createEmptyList((DestroyFunction) destroyMaterial, (CopyFunction) copyMaterial);
    for (int i = 0; i < size(coffeeShop->materialList); i++) {
        Material * current = get(coffeeShop->materialList, i);
        if (current->name[0] == letter)
            add(res,res->copyElement(current));
    }
    return res;
}

List *getMaterialsWithLessQuantity(CoffeeShop *coffeeShop, int quantity) {
    List* res = createEmptyList((DestroyFunction) destroyMaterial, (CopyFunction) copyMaterial);
    for (int i = 0; i < size(coffeeShop->materialList); i++) {
        Material * current = get(coffeeShop->materialList, i);
        if (current->quantity < quantity)
            add(res,res->copyElement(current));
    }
    return res;
}

int cmpNameAsc(Material* m1, Material* m2) {
    return strcmp(m1->name, m2->name);
}

int cmpNameDesc(Material* m1, Material* m2) {
    return strcmp(m2->name, m1->name);
}

int cmpQuantityAsc(Material* m1, Material* m2) {
    return m1->quantity > m2->quantity;
}

int cmpQuantityDesc(Material* m1, Material* m2) {
    return  m1->quantity < m2->quantity;
}

List *sortByQuantity(CoffeeShop *coffeeShop, int order) {
    List* list = copyList(coffeeShop->materialList);
    if(order == 0)
        sort(list, (CompareFunction) cmpQuantityAsc);
    else
        sort(list, (CompareFunction) cmpQuantityDesc);
    return list;
}

List *sortByName(CoffeeShop *coffeeShop, int order) {
    List* list = copyList(coffeeShop->materialList);
    if (order == 0) {
        sort(list, (CompareFunction) cmpNameAsc);
    } else
        sort(list, (CompareFunction) cmpNameDesc);
    return list;
}

void testCreateCoffeeShop() {
    CoffeeShop  coffeeShop = createCoffeeShop();
    destroyCoffeeShop(&coffeeShop);
}
void testCRUDService() {
    CoffeeShop  coffeeShop = createCoffeeShop();
    addMaterial(&coffeeShop,"1","1",1);
    addMaterial(&coffeeShop,"2","2",2);
    addMaterial(&coffeeShop,"2","2",-4);
    assert(sizeOfMaterialList(&coffeeShop) == 2);
    addMaterial(&coffeeShop,"1","1",2);
    Material *material = getMaterial(&coffeeShop, 0);
    assert(material->quantity == 3);

    updateMaterial(&coffeeShop,0,"4","5",20);
    material = getMaterial(&coffeeShop, 0);
    assert(material->quantity == 20);
    updateMaterial(&coffeeShop,0,"","5",20);
    updateMaterial(&coffeeShop,60,"2","2",3);

    removeMaterial(&coffeeShop,30);
    removeMaterial(&coffeeShop, 1);
    assert(sizeOfMaterialList(&coffeeShop) == 1);
    List* all = getAllMaterials(&coffeeShop);
    assert(size(all) == 1);
    destroyCoffeeShop(&coffeeShop);

}

void testUndo() {
    CoffeeShop  coffeeShop = createCoffeeShop();
    undo(&coffeeShop);
    addMaterial(&coffeeShop,"1","1",1);
    addMaterial(&coffeeShop,"2","2",2);
    assert(sizeOfMaterialList(&coffeeShop) == 2);
    undo(&coffeeShop);
    assert(sizeOfMaterialList(&coffeeShop) == 1);
    removeMaterial(&coffeeShop,0);
    assert(sizeOfMaterialList(&coffeeShop) == 0);
    undo(&coffeeShop);
    assert(sizeOfMaterialList(&coffeeShop) == 1);
    destroyCoffeeShop(&coffeeShop);
}

void testFiltering() {
    CoffeeShop  coffeeShop = createCoffeeShop();
    addMaterial(&coffeeShop,"1","1",1);
    addMaterial(&coffeeShop,"2","2",2);
    addMaterial(&coffeeShop,"1","3",4);
    addMaterial(&coffeeShop,"13","3",4);
    int res1 = getAllMaterialsByName(&coffeeShop,"1");
    assert(res1 == 5);
    List* filterResult = getAllMaterialsWithStartingLetter(&coffeeShop, '1');
    assert(size(filterResult) == 3);
    destroyList(filterResult);
    filterResult = getMaterialsWithLessQuantity(&coffeeShop, 3);
    assert(size(filterResult) == 2);
    destroyList(filterResult);
    destroyCoffeeShop(&coffeeShop);

}

void testSorting() {
    CoffeeShop  coffeeShop = createCoffeeShop();
    addMaterial(&coffeeShop, "a","1",3);
    addMaterial(&coffeeShop, "c","2",2);
    addMaterial(&coffeeShop, "b","5",1);
    List * sortResult = sortByName(&coffeeShop,0);
    Material *material = get(sortResult, 1);
    assert(material->quantity == 1);
    destroyList(sortResult);
    sortResult = sortByName(&coffeeShop,1);
    material = get(sortResult,0);
    assert(material->quantity == 2);
    destroyList(sortResult);
    sortResult = sortByQuantity(&coffeeShop,0);
    material = get(sortResult,0);
    assert(material->quantity == 1);
    destroyList(sortResult);

    sortResult = sortByQuantity(&coffeeShop,1);
    material = get(sortResult,0);
    assert(material->quantity == 3);
    destroyList(sortResult);
    destroyCoffeeShop(&coffeeShop);
}