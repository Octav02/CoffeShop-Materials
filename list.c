#include "list.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

List* createEmptyList(destroyFunction f) {
    List *rez = malloc(sizeof(List));
    rez->capacity = 2;
    rez->elements = malloc(sizeof(ElemType) * rez->capacity);
    rez->length = 0;
    rez->deleteElement = f;
    return rez;
}

void destroyList(List *list) {
    for (int i = 0; i < sizeOfList(list); i++)
        list -> deleteElement(list->elements[i]);
    free(list->elements);
    free(list);
}

ElemType getElement(List *list, int pos) {
    return list->elements[pos];
}


int sizeOfList(List *list) {
    return list->length;
}

void ensureCapacity(List *list) {
    if (list->length < list->capacity)
        return;
    int newCapacity = list->capacity + 2;
    ElemType *newElements = malloc(sizeof(ElemType) * newCapacity);

    for (int i = 0; i < list->length; i++)
        newElements[i] = list->elements[i];

    free(list->elements);
    list->elements = newElements;
    list->capacity = newCapacity;
}

void addElementToList(List *list, ElemType element) {
    ensureCapacity(list);
    list->elements[list->length] = element;
    list->length++;
}

void deleteElementFromList(List *list, int index) {
    for (int i = index; i < sizeOfList(list) - 1; i++)
        list->elements[i] = list->elements[i + 1];
    list->length--;
}

void updateElementFromList(List *list, int index, ElemType updatedElement) {
    list->elements[index] = updatedElement;
}


List* createCopyOfList(List *list, copyFunction f) {
    List* copyList = createEmptyList(list->deleteElement);
    for (int i = 0; i < sizeOfList(list); i++) {
        ElemType current = getElement(list, i);
        addElementToList(copyList, current);
    }
    return copyList;
}

void testCreateList() {
    List * list = createEmptyList((destroyFunction) destroyMaterial);
    assert(sizeOfList(list) == 0);
    destroyList(list);
}

void testIterateList() {
    List* list = createEmptyList((destroyFunction) destroyMaterial);
    Material* material = createMaterial("n1", "p1", 20);
    Material* material1 = createMaterial("n2", "p2", 40);
    addElementToList(list, material);
    Material* material2 = getElement(list, 0);
    assert(material2->quantity == 20);

    addElementToList(list, material1);
    int length = sizeOfList(list);
    assert(length == 2);
    updateElementFromList(list, 0, createMaterial("n2", "p2", 40));
    material2 = getElement(list, 0);
    assert(material2->quantity == 40);
    deleteElementFromList(list, 1);
    length = sizeOfList(list);
    assert(length == 1);
    length = sizeOfList(list);
    assert(length == 1);
    Material *elem = getElement(list, 1);
    assert(elem->quantity == 40);
    destroyList(list);

}

void testCopyList() {
    List* list1 = createEmptyList((destroyFunction) destroyMaterial);
    addElementToList(list1, createMaterial("n1", "p1", 20));
    addElementToList(list1, createMaterial("n2", "p2", 40));
    List* list2 = createCopyOfList(list1, (copyFunction) copyMaterial);
    assert(sizeOfList(list1) == sizeOfList(list2));
    Material *element = getElement(list2, 0);
    assert(element->quantity == 20);
}

void testListOfLists() {
    List* list1 = createEmptyList((destroyFunction) destroyList);
    List* list2 = createEmptyList((destroyFunction) destroyMaterial);
    addElementToList(list2, createMaterial("1","1",1));
    addElementToList(list2, createMaterial("2","2",2));
    addElementToList(list2, createMaterial("3","3",3));
    addElementToList(list1,list2);
    assert(sizeOfList(list1) == 1);
}

void testEnsureCapacity() {
    List *list = createEmptyList((destroyFunction) destroyMaterial);
    for (int i = 0; i < 2; i++)
        addElementToList(list, createMaterial("da", "NU", i));
    ensureCapacity(list);
    assert(sizeOfList(list) == 2);
    addElementToList(list, createMaterial("da", "NU", 4));
    assert(sizeOfList(list) == 3);
}