#include "list.h"

#include <assert.h>
#include <stdlib.h>
/* This function creates a new empty List object by dynamically allocating memory for it and initializes its fields
 * length, capacity, elements, deleteElement, and copyElement
 * with the values provided as arguments. It returns a pointer to the created object.*/
List *createEmptyList(DestroyFunction f1, CopyFunction f2) {
    List *rez = malloc(sizeof(List));
    rez->length = 0;
    rez->capacity = 2;
    rez->elements = malloc(sizeof(ElemType) * rez->capacity);
    rez->deleteElement = f1;
    rez->copyElement = f2;
    return rez;
}
/*This function deallocates the memory that was dynamically allocated for a given List object.
 * It first calls the deleteElement function on each element of the list to
 * deallocate any dynamically allocated memory for those elements.
 * It then frees the memory allocated for the elements field,
 * and finally frees the memory allocated for the object itself.*/
void destroyList(List *list) {
    for (int i = 0; i < list->length; i++)
        list->deleteElement(list->elements[i]);
    free(list->elements);
    free(list);
}
/*This function returns the element of a List object at a given position,
 * specified by the pos argument.*/
ElemType get(List *list, int pos) {
    return list->elements[pos];
}
int size(List *list) {
    return list->length;
}

void ensureCapacity(List *list) {
    if (list->length < list->capacity) {
        return; //we have room
    }
    ElemType *newElements = malloc(sizeof(ElemType) * (list->capacity + 2));
    for (int i = 0; i < list->length; i++) {
        newElements[i] = list->elements[i];
    }
    free(list->elements);
    list->elements = newElements;
    list->capacity += 2;
}

void add(List *list, ElemType element) {
    ensureCapacity(list);
    list->elements[list->length++] = element;
}

int update(List *list, int pos, ElemType element) {
    if (pos >= list->length || pos < 0)
        return -1;
    list->elements[pos] = element;
    return 0;
}

int removeElement(List *list, int pos) {
    if (pos >= list->length || pos < 0)
        return -1;
    ElemType *newElements = malloc(sizeof(ElemType) * (list->capacity + 2));
    int k = 0;
    for (int i = 0; i < list->length; i++) {
        if (i != pos)
            newElements[k++] = list->elements[i];
        else
            list->deleteElement(list->elements[i]);
    }

    free(list->elements);
    list->elements = newElements;
    list->length -= 1;
    return 0;
}

List *copyList(List *list) {
    List *rez = createEmptyList(list->deleteElement, list->copyElement);
    for (int i = 0; i < size(list); i++) {
        ElemType current = get(list, i);
        add(rez, rez->copyElement(current));
    }
    return rez;
}

void testCreateDestroyList() {
    List *list1 = createEmptyList((DestroyFunction) destroyMaterial, (CopyFunction) copyMaterial);
    assert(list1->length == 0);
    assert(list1->capacity == 2);
    destroyList(list1);
}

void testCRUDList() {
    Material *material1 = createMaterial("da", "nu", 1);
    Material *material2 = createMaterial("2", "2", 2);
    Material *material3 = createMaterial("1", "1", 1);
    List *list = createEmptyList((DestroyFunction) destroyMaterial, (CopyFunction) copyMaterial);
    ensureCapacity(list);
    add(list, material1);
    add(list, material2);
    assert(size(list) == 2);
    ensureCapacity(list);
    Material *material4 = get(list, 0);
    assert(material4 == material1);
    int res = update(list, 6, material4);
    assert(res == -1);
    res = removeElement(list, 6);
    assert(res == -1);
    res = update(list, 0, material3);
    assert(res == 0);
    res = removeElement(list, 0);
    assert(res == 0);
    assert(size(list) == 1);
    destroyMaterial(material1);
    destroyList(list);
}

void testCopyList() {
    Material *material1 = createMaterial("da", "nu", 1);
    Material *material2 = createMaterial("2", "2", 2);
    List *list = createEmptyList((DestroyFunction) destroyMaterial, (CopyFunction) copyMaterial);
    add(list, material1);
    add(list, material2);
    List* list2 = copyList(list);
    assert(size(list2) == 2);
    destroyList(list);
    destroyList(list2);
}
