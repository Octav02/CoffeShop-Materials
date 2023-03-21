#include "service.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>


int addMaterial(CoffeeShop *coffeeShop, char *name, char *producer, int quantity) {
    Material *material = createMaterial(name, producer, quantity);
    int errors = validateMaterial(material);
    if (errors != 0)
        return errors;
    for (int i = 0; i < coffeeShop->materialList->length; i++) {
        Material *material1 = coffeeShop->materialList->elements[i];
        if (!strcmp(material1->name, name) && !strcmp(material1->producer, producer)) {
            material1->quantity += quantity;
            coffeeShop->materialList->elements[i] = material1;
            List *toUndo = createCopyOfList(coffeeShop->materialList, (copyFunction) copyMaterial);
            addElementToList(coffeeShop->undoList, toUndo);
            return 0;
        }
    }
    List *toUndo = createCopyOfList(coffeeShop->materialList, (copyFunction) copyMaterial);
    addElementToList(coffeeShop->undoList, toUndo);
    addElementToList(coffeeShop->materialList, material);
    return 0;

}

int updateMaterial(CoffeeShop *coffeeShop, int pos, char *newName, char *newProducer, int quantity) {
    Material *material = createMaterial(newName, newProducer, quantity);
    int errors = validateMaterial(material);
    if (errors != 0)
        return errors;
    pos -= 1;
    List *toUndo = createCopyOfList(coffeeShop->materialList, (copyFunction) copyMaterial);
    addElementToList(coffeeShop->undoList, toUndo);
    updateElementFromList(coffeeShop->materialList, pos, material);
    return 0;
}

Material *getMaterial(List *list, char *name, char *producer) {
    Material *WantedMaterial = createMaterial("", "", -1);
    for (int i = 0; i < sizeOfList(list); i++) {
        Material *currentMaterial = getElement(list, i);
        if (!strcmp(currentMaterial->name, name) && !strcmp(currentMaterial->producer, producer)) {
            strcpy(WantedMaterial->name, currentMaterial->name);
            strcpy(WantedMaterial->producer, currentMaterial->producer);
            WantedMaterial->quantity = currentMaterial->quantity;
        }
    }
    return WantedMaterial;
}
//

int undo(CoffeeShop *coffeeShop) {
    if (sizeOfList(coffeeShop->undoList) == 0)
        return 1;
    List *l = coffeeShop->undoList->elements[sizeOfList(coffeeShop->undoList) - 1];
    deleteElementFromList(coffeeShop->undoList, sizeOfList(coffeeShop->undoList) - 1);
    destroyList(coffeeShop->materialList);
    coffeeShop->materialList = l;
    return 0;
}

int deleteMaterial(CoffeeShop *coffeeShop, int pos) {
    pos -= 1;
    List *toUndo = createCopyOfList(coffeeShop->materialList, (copyFunction) copyMaterial);
    addElementToList(coffeeShop->undoList, toUndo);
    deleteElementFromList(coffeeShop->materialList, pos);
    return 0;
}

List *getAllMaterials(List *list) {
    List *result = createCopyOfList(list, (copyFunction) createCopyOfList);
    return result;
}

int sizeOfMaterialList(List *list) {
    return sizeOfList(list);
}


int getAllMaterialsByName(List *list, char *name) {
    int result = 0;
    for (int i = 0; i < sizeOfList(list); i++) {
        Material *material1 = list->elements[i];
        if (!strcmp(material1->name, name))
            result += material1->quantity;
    }
    return result;
}

//
List *getMaterialsWithStartingLetter(List *list, char letter) {
    List *result = createEmptyList((destroyFunction) destroyMaterial);
    int len = sizeOfList(list);
    for (int i = 0; i < len; i++) {
        Material *material1 = list->elements[i];
        if (material1->name[0] == letter)
            addElementToList(result, material1);
    }
    return result;
}

List *getMaterialsWithLessQuantity(List *list, int quantity) {
    List *result = createEmptyList((destroyFunction) destroyMaterial);
    int len = sizeOfList(list);
    for (int i = 0; i < len; i++) {
        Material *material1 = list->elements[i];
        if (material1->quantity < quantity)
            addElementToList(result, getElement(list, i));
    }
    return result;
}

List *getMaterialsOrderedByQuantity(List *list, int order) {
    List *result = createCopyOfList(list, (copyFunction) copyMaterial);
    int len = sizeOfList(result);
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            Material *material1 = list->elements[i];
            Material *material2 = list->elements[j];
            if (order == 1) {
                if (material1->quantity > material2->quantity) {
                    ElemType aux = result->elements[i];
                    result->elements[i] = result->elements[j];
                    result->elements[j] = aux;
                }
            } else if (order == 0) {
                if (material1->quantity < material2->quantity) {
                    ElemType aux = result->elements[i];
                    result->elements[i] = result->elements[j];
                    result->elements[j] = aux;
                }
            } else {
                return list;
            }
        }
    }
    return result;
}

List *getMaterialsOrderedByName(List *list, int order) {
    List *result = createCopyOfList(list, (copyFunction) copyMaterial);
    int len = sizeOfList(result);
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            Material *material1 = list->elements[i];
            Material *material2 = list->elements[j];
            if (order == 1) {

                if (strcmp(material1->name, material2->name) > 0) {
                    ElemType aux = result->elements[i];
                    result->elements[i] = result->elements[j];
                    result->elements[j] = aux;
                }
            } else if (order == 0) {
                if (strcmp(material1->name, material2->name) < 0) {
                    ElemType aux = result->elements[i];
                    result->elements[i] = result->elements[j];
                    result->elements[j] = aux;
                }
            } else {
                return list;
            }
        }
    }
    return result;
}

CoffeeShop createCoffeeShop() {
    CoffeeShop rez;
    rez.materialList = createEmptyList((destroyFunction) destroyMaterial);
    rez.undoList = createEmptyList((destroyFunction) destroyList);
    return rez;
}

void testCRUD() {
    CoffeeShop coffeeShop = createCoffeeShop();
    int res = addMaterial(&coffeeShop, "m1", "p1", 20);
    assert(sizeOfMaterialList(coffeeShop.materialList) == 1);
    assert(sizeOfList(coffeeShop.materialList) == 1);
    assert(res == 0);
    res = addMaterial(&coffeeShop, "", "p1", 30);
    res = addMaterial(&coffeeShop, "m1", "p1", 30);
    Material *material2 = getElement(coffeeShop.materialList, 0);
    assert(material2->quantity == 50);
    material2 = getMaterial(coffeeShop.materialList, "m1", "p1");
    res = updateMaterial(&coffeeShop, 0, "m1", "m2", 20);
    assert(res == 0);
    res = updateMaterial(&coffeeShop, 0, "", "m2", 20);
    res = addMaterial(&coffeeShop, "m1", "p2", 30);
    assert(getAllMaterialsByName(coffeeShop.materialList, "m1") == 80);
    deleteMaterial(&coffeeShop, 2);
    assert(sizeOfList(coffeeShop.materialList) == 1);

    List *list2 = getAllMaterials(coffeeShop.materialList);
    destroyList(list2);

}

void testUndo() {
    CoffeeShop coffeeShop = createCoffeeShop();
    int res = addMaterial(&coffeeShop, "m1", "p1", 20);
    assert(sizeOfList(coffeeShop.materialList) == 1);
    assert(sizeOfList(coffeeShop.undoList) == 1);
    res = undo(&coffeeShop);
    assert(res == 0);
    assert(sizeOfList(coffeeShop.materialList) == 0);
    res = undo(&coffeeShop);
}

void testFiltering() {
    CoffeeShop coffeeShop = createCoffeeShop();

    addMaterial(&coffeeShop, "dan", "o2", 4);
    addMaterial(&coffeeShop, "rob", "ewq", 5);
    addMaterial(&coffeeShop, "d", "titan", 2);
    assert(sizeOfMaterialList(coffeeShop.materialList) == 3);
    List *filterResult = getMaterialsWithStartingLetter(coffeeShop.materialList, 'd');
    Material *material1 = getElement(filterResult, 0);
    Material *material2 = getElement(filterResult, 1);
    assert(material1->quantity == 4);
    assert(material2->quantity == 2);

    filterResult = getMaterialsWithLessQuantity(coffeeShop.materialList, 5);
    assert(sizeOfMaterialList(filterResult) == 2);
    material1 = getElement(filterResult, 0);
    material2 = getElement(filterResult, 1);
    assert(material1->quantity == 4);
    assert(material2->quantity == 2);
    filterResult = getMaterialsOrderedByQuantity(coffeeShop.materialList, 1);
    material1 = getElement(filterResult, 0);
    assert(material1->quantity == 2);
    assert(sizeOfMaterialList(filterResult) == 3);

    filterResult = getMaterialsOrderedByQuantity(coffeeShop.materialList, 0);
    material1 = getElement(filterResult, 0);
    assert(material1->quantity == 5);
    assert(sizeOfMaterialList(filterResult) == 3);
//
    filterResult = getMaterialsOrderedByQuantity(coffeeShop.materialList, 6);
    material1 = getElement(filterResult, 0);
    assert(material1->quantity == 4);
    assert(sizeOfMaterialList(filterResult) == 3);
//
    filterResult = getMaterialsOrderedByName(coffeeShop.materialList, 1);
    material1 = getElement(filterResult, 0);
    assert(material1->quantity == 2);
    assert(sizeOfMaterialList(filterResult) == 3);
//
    filterResult = getMaterialsOrderedByName(coffeeShop.materialList, 0);
    material1 = getElement(filterResult, 0);
    assert(material1->quantity == 5);
    assert(sizeOfMaterialList(filterResult) == 3);
//
    filterResult = getMaterialsOrderedByName(coffeeShop.materialList, 6);
    material1 = getElement(filterResult, 0);
    assert(material1->quantity == 4);
    assert(sizeOfMaterialList(filterResult) == 3);

}