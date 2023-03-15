#pragma once

#include "list.h"


// Preconditions: Valid non-null pointers to a List object and character arrays for name and producer, and a non-negative integer for quantity.
// Parameters: A pointer to a List object, the name, producer, and quantity of the new "Material" object to be added to the list.
// Postconditions: A new "Material" object is created and added to the list. If the Material object already exists, it adds the quantity to the specified Material
// Return: 0 if the material was successfully added to the list, (1,2,3- based on validation function and -1 if elem found in list) if there was an error.
int addMaterial(List *list, char *name, char *producer, int quantity);

// Preconditions: Valid non-null pointers to a List object and character arrays for name and producer, and a non-negative integer for quantity.
// Parameters: A pointer to a List object, the name, producer, and quantity of the "Material" object to be updated in the list.
// Postconditions: The "Material" object is updated with the given name, producer, and quantity.
// Return: 0 if the material was successfully updated,  (1,2,3- based on validation function and -1 if elem not-found in list) if there was an error.
int updateMaterial(List *list, char *name, char *producer, char *newName, char *newProducer, int quantity);

// Preconditions: Valid non-null pointers to a List object and a character array for name.
// Parameters: A pointer to a List object, the name of the "Material" object to be deleted from the list.
// Postconditions: The "Material" object with the given name is deleted from the list.
// Return: 0 if the material was successfully deleted, -1 if there was an error(not found).
int deleteMaterial(List *list, char *name, char *producer);

// Preconditions: Valid non-null pointers to a List object and a character array for name.
// Parameters: A pointer to a List object, the name of the "Material" object to be retrieved from the list.
// Postconditions: The "Material" object with the given name is returned from the list.
// Return: The "Material" object with the given name, An invalid Material Object if not found in list..
ElemType getMaterial(List *list, char *name, char *producer);

// Preconditions: Valid non-null pointer to a List object.
// Parameters: A pointer to a List object.
// Postconditions: A copy of the list containing all "Material" objects is returned.
// Return: A new list containing all "Material" objects in the original list.
List getAllMaterials(List *list);

// Preconditions: A valid pointer to a material list.
// Parameters: A pointer to the material list.
// Postconditions: None.
// Return: The number of elements in the list.
int sizeOfMaterialList(List *list);

// Preconditions: Valid non-null pointer to a List object and character array for name.
// Parameters: A pointer to a List object, the name of the Material that we want to get all the quantity(independent of producer).
// Postconditions: An integer that represents the quantity of all materials with the same name(independent of producer).
// Return: An integer that represents the quantity of all materials with the same name(independent of producer).
int getAllMaterialsByName(List *list, char *name);

void testCRUD();