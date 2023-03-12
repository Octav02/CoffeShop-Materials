#include "service.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

int addMaterial(List *list, char *name, char *producer, int quantity) {
    ElemType material;
    material = createMaterial(name, producer, quantity);
    int errors = validateMaterial(material);
    int pos = getPosition(list, material);
    if (pos != -1)
        list->elements[pos].quantity += quantity;
    else {
        if (errors == 0)
            addElementToList(list, material);
    }
    return errors;

}

int updateMaterial(List *list, char *name, char *producer, char *newName, char *newProducer, int quantity) {
    ElemType newMaterial;
    newMaterial = createMaterial(newName, newProducer, quantity);
    int errors = validateMaterial(newMaterial);
    if (errors != 0)
        return errors;

    ElemType material;
    material = createMaterial(name, producer, quantity);
    int pos = getPosition(list, material);
    if (pos == -1)
        return pos;
    updateElementFromList(list, material, newMaterial);
    return 0;
}

ElemType getMaterial(List *list, char *name, char *producer) {
    ElemType WantedMaterial = createMaterial("", "", -1);
    for (int i = 0; i < sizeOfList(list); i++) {
        ElemType currentMaterial = getElement(list, i);
        if (!strcmp(currentMaterial.name, name) && !strcmp(currentMaterial.producer, producer)) {
            strcpy(WantedMaterial.name, currentMaterial.name);
            strcpy(WantedMaterial.producer, currentMaterial.producer);
            WantedMaterial.quantity = currentMaterial.quantity;
        }
    }
    return WantedMaterial;
}

int deleteMaterial(List *list, char *name, char *producer) {
    ElemType material = getMaterial(list, name, producer);
    if (material.quantity == -1)
        return -1;
    deleteElementFromList(list, material);
    return 0;
}

List getAllMaterials(List *list) {
    List result = createEmptyList();
    result = createCopyOfList(list);
    return result;
}

int sizeOfMaterialList(List *list) {
    return sizeOfList(list);
}

int getAllMaterialsByName(List *list, char *name) {
    int result = 0;
    for (int i = 0; i < sizeOfList(list); i++)
        if (!strcmp(list->elements[i].name, name))
            result += list->elements[i].quantity;
    return result;
}

void testCRUD() {
    List list = createEmptyList();
    int res = addMaterial(&list, "m1", "p1", 20);
    assert(sizeOfMaterialList(&list) == 1);
    assert(res == 0);
    res = addMaterial(&list, "", "p1", 20);
    assert(res == 1);
    assert(sizeOfMaterialList(&list) == 1);

    res = addMaterial(&list, "1", "", 20);
    assert(res == 2);
    assert(sizeOfMaterialList(&list) == 1);

    res = addMaterial(&list, "1", "2", -30);
    assert(res == 3);
    assert(sizeOfMaterialList(&list) == 1);

    res = updateMaterial(&list, "m1", "p1", "m2", "p2", 30);
    assert(res == 0);
    ElemType material = getMaterial(&list, "m2", "p2");
    assert(!strcmp(material.name, "m2"));
    assert(!strcmp(material.producer, "p2"));
    assert(material.quantity == 30);

    res = updateMaterial(&list, "m2", "p2", "", "p2", 30);
    assert(res == 1);
    res = updateMaterial(&list, "m2", "p2", "m2", "", 30);
    assert(res == 2);
    res = updateMaterial(&list, "m2", "p2", "m2", "p2", -45);
    assert(res == 3);
    res = updateMaterial(&list, "m1", "21", "45", "p2", 30);
    assert(res == -1);

    res = addMaterial(&list, "m2", "p1", 20);
    assert(res == 0);
    int qt = getAllMaterialsByName(&list, "m2");
    assert(qt == 50);

    List list2 = getAllMaterials(&list);
    assert(sizeOfMaterialList(&list2) == 2);

    res = deleteMaterial(&list, "m2", "p1");
    assert(res == 0);
    assert(sizeOfMaterialList(&list) == 1);
    res = deleteMaterial(&list, "m2", "p1");
    assert(res == -1);
    assert(sizeOfMaterialList(&list) == 1);

    res = addMaterial(&list, "m2", "p2", 20);
    assert(res == 0);
    assert(list.elements[0].quantity == 50);

}