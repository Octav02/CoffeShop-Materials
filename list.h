#pragma once

#include "material.h"

typedef void *ElemType;

typedef void(*DestroyFunction)(ElemType);

typedef ElemType(*CopyFunction)(ElemType);

typedef struct {
    ElemType *elements;
    int length;
    int capacity;
    DestroyFunction deleteElement;
    CopyFunction copyElement;
} List;

/* This function creates a new empty List object by dynamically allocating memory for it and initializes its fields
 * length, capacity, elements, deleteElement, and copyElement
 * with the values provided as arguments. It returns a pointer to the created object.*/
List *createEmptyList(DestroyFunction f1, CopyFunction f2);

/*This function deallocates the memory that was dynamically allocated for a given List object.
 * It first calls the deleteElement function on each element of the list to
 * deallocate any dynamically allocated memory for those elements.
 * It then frees the memory allocated for the elements field,
 * and finally frees the memory allocated for the object itself.*/
void destroyList(List *list);

/*This function returns the element of a List object at a given position,
 * specified by the pos argument.*/
ElemType get(List *list, int pos);

/*This function returns the length of a List object,
 * which is the number of elements it currently holds.*/
int size(List *list);

/*This function adds a new element to the end of a List object.
 * It first ensures that the list has enough capacity, and
 * then appends the new element to the end of the elements array and
 * increments the length field.*/
void add(List *list, ElemType element);

/*This function updates an element of a List object at a given position s
 * pecified by the pos argument with the value provided
 * as the element argument. If the pos argument is out of range, the function returns -1.
 * Otherwise, it replaces the old element with the new element and returns 0.*/
int update(List *list, int pos, ElemType element);

/*This function removes an element from a List object at a given position
 * specified by the pos argument. If the pos argument is out of range, the function returns -1.
 * Otherwise, it allocates a new array with capacity increased by 2 and copies all elements except the one
 * at the specified position into the new array. It then frees the memory allocated
 * for the old array and updates the elements and length fields of the List object.*/
int removeElement(List *list, int pos);

/*This function creates a new List object by making a copy of an existing one.
 * It uses the createEmptyList function to allocate memory
 * for the new object and initialize its fields with the same values as the original object.
 * It then copies each element of the original list
 * into the new list by calling the copyElement function on each element and appending the result to the new list.
 * It then returns a pointer to the created object.*/
List *copyList(List *list);

void testCreateDestroyList();

void testCRUDList();

void testCopyList();
