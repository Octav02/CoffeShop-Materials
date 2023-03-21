#include "list.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

List createEmptyList() {
    List rez;
    rez.capacity = 5;
    rez.elements = malloc(sizeof(ElemType) * rez.capacity);
    rez.length = 0;
    return rez;
}

void destroyList(List *list) {
    list->length = 0;
    for (int i = 0; i < sizeOfList(list); i++)
        destroyMaterial(&list->elements[i]);
    free(list->elements);
    list->length = 0;
    list->elements = NULL;
}

ElemType getElement(List *list, int pos) {
    return list->elements[pos];
}

int getPosition(List *list, ElemType element) {
    int pos = -1;
    for (int i = 0; i < sizeOfList(list) && pos == -1; i++)
        if (!strcmp(element.name, list->elements[i].name) && !strcmp(element.producer, list->elements[i].producer))
            pos = i;

    return pos;
}

int sizeOfList(List *list) {
    return list->length;
}

void ensureCapacity(List *list) {
    if (list->length < list->capacity)
        return;
    int newCapacity = list->capacity + 5;
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

void deleteElementFromList(List *list, ElemType element) {
    //Finding the element with matching name
    int pos = getPosition(list, element);
    if (pos == -1)
        return;
    for (int i = pos; i < sizeOfList(list) - 1; i++)
        list->elements[i] = list->elements[i + 1];
    list->length--;
}

void updateElementFromList(List *list, ElemType element, ElemType updatedElement) {
    int pos = getPosition(list, element);
    if (pos == -1)
        return;
    list->elements[pos] = updatedElement;
}


List createCopyOfList(List *list) {
    List copyList = createEmptyList();
    for (int i = 0; i < sizeOfList(list); i++) {
        ElemType current = getElement(list, i);
        addElementToList(&copyList, current);
    }
    return copyList;
}

void testCreateList() {
    List list = createEmptyList();
    assert(sizeOfList(&list) == 0);
}

void testIterateList() {
    List list = createEmptyList();
    addElementToList(&list, createMaterial("n1", "p1", 20));
    assert(list.elements[0].quantity == 20);
    int position = getPosition(&list, createMaterial("n1", "p1", 20));
    assert(position == 0);

    addElementToList(&list, createMaterial("n2", "p2", 40));
    int length = sizeOfList(&list);
    assert(length == 2);
    updateElementFromList(&list, createMaterial("n1", "p1", 20), createMaterial("n1", "p1", 80));
    assert(list.elements[0].quantity == 80);
    updateElementFromList(&list, createMaterial("n4", "p1", 20), createMaterial("n1", "p1", 80));

    deleteElementFromList(&list, createMaterial("n1", "p1", 80));
    length = sizeOfList(&list);
    assert(length == 1);
    deleteElementFromList(&list, createMaterial("n1", "p1", 80));
    length = sizeOfList(&list);
    assert(length == 1);
    ElemType elem = getElement(&list, 1);
    assert(elem.quantity == 40);

    for (int i = 0; i < length; i++) {
        ElemType current = getElement(&list, i);
        assert(!strcmp(current.name, list.elements[i].name));
        assert(!strcmp(current.producer, list.elements[i].producer));
        assert(current.quantity == list.elements[i].quantity);
    }
    destroyList(&list);
    assert(sizeOfList(&list) == 0);
    assert(list.elements == NULL);
}

void testCopyList() {
    List list1 = createEmptyList();
    addElementToList(&list1, createMaterial("n1", "p1", 20));
    addElementToList(&list1, createMaterial("n2", "p2", 40));
    List list2 = createCopyOfList(&list1);
    assert(sizeOfList(&list1) == sizeOfList(&list2));
    ElemType element = getElement(&list2, 0);
    assert(element.quantity == 20);
    for (int i = 0; i < sizeOfList(&list1); i++) {
        ElemType elem1 = getElement(&list1, i);
        ElemType elem2 = getElement(&list2, i);
        assert(!strcmp(elem1.name, elem2.name));
        assert(!strcmp(elem1.producer, elem2.producer));
        assert(elem1.quantity == elem2.quantity);
    }
}

void testEnsureCapacity() {
    List list = createEmptyList();
    for (int i = 0; i < 5; i++)
        addElementToList(&list, createMaterial("da", "NU", i));
    ensureCapacity(&list);
    assert(sizeOfList(&list) == 5);
    addElementToList(&list, createMaterial("da", "NU", 4));
    assert(sizeOfList(&list) == 6);
}