#pragma once

#include "material.h"

/*"Abstract" definition of ElemType
*This is the main type of elements contained in List
 */
typedef void *ElemType;

typedef void(*destroyFunction)(ElemType);

typedef ElemType(*copyFunction)(ElemType);

/*
 * List definition
 *
 */
typedef struct {
    ElemType *elements;
    int length;
    int capacity;
    destroyFunction deleteElement;
} List;

// Preconditions: None
// Parameters: None
// Postconditions: A new empty list is created and returned.
// Return: The created empty list.
List *createEmptyList(destroyFunction f);

// Preconditions: A valid pointer to a list.
// Parameters: A pointer to the list that needs to be destroyed.
// Postconditions: The memory allocated for the list and its elements is freed.
// Return: None.
void destroyList(List *list);

// Preconditions: A valid pointer to a list
// Parameters: A pointer to the list
// Postconditions: The function verifies if the list has enough space to hold a new element. otherwise it allocates more space
// Returns: -
void ensureCapacity(List *list);

// Preconditions: A valid pointer to a list and a valid position in the list (0 <= pos < size of list).
// Parameters: A pointer to the list and the position of the element that needs to be retrieved.
// Postconditions: None.
// Return: The element located at the specified position in the list.
ElemType getElement(List *list, int pos);

// Preconditions: A valid pointer to a list.
// Parameters: A pointer to the list.
// Postconditions: None.
// Return: The number of elements in the list.
int sizeOfList(List *list);

// Preconditions: A valid pointer and a valid element that needs to be added to the list.
// Parameters: A pointer to the list and the element that needs to be added.
// Postconditions: The element is added at the end of the list.
// Return: None.
void addElementToList(List *list, ElemType element);



// Preconditions: A valid pointer to a list and a valid element that needs to be deleted from the list.
// Parameters: A pointer to the list and the element that needs to be deleted.
// Postconditions: If the element is found in the list, it will be deleted. If the element is not found, the function does nothing.
// Return: None.
void deleteElementFromList(List *list, int index);

// Preconditions: A valid pointer to a list a valid element that needs to be updated, and a valid updated element.
// Parameters: A pointer to the list, the element that needs to be updated, and the updated element.
// Postconditions: If the element is found in the list, it will be updated with the new element. If the element is not found, the function does nothing.
// Return: None.
void updateElementFromList(List *list, int index, ElemType updatedElement);

// Preconditions: A valid pointer to a list.
// Parameters: A pointer to the list.
// Postconditions: A new list containing the same elements as the original list is created and returned. The two lists do not share the same memory.
// Return: The newly created list.
List *createCopyOfList(List *list, copyFunction f);

void testCreateList();

void testIterateList();

void testCopyList();

void testListOfLists();

void testEnsureCapacity();