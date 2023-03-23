#pragma once

typedef struct {
    char *name;
    char *producer;
    int quantity;
} Material;

/*This function creates a new Material object by dynamically allocating memory for it
 * and initializes its fields name, producer, and quantity with the values provided as arguments.
 * It returns a pointer to the created object.*/
Material *createMaterial(char *name, char *producer, int quantity);
/*This function deallocates the memory that was dynamically allocated for a given Material object.
 * It first frees the memory allocated for the producer and name fields,
 * and then frees the memory allocated for the object itself.*/
void destroyMaterial(Material *material);
/*This function checks if a given Material object is valid. It returns an error code as follows:
 * 1 if the name field is empty, 2 if the producer field is empty, 3 if the quantity field is negative,
 * and 0 otherwise.*/
int validateMaterial(Material *material);

Material *copyMaterial(Material *material);
/*This function creates a new Material object by making a copy of an existing one.
 * It uses the createMaterial function to allocate memory for the new object and initialize its fields with the same values as the original object.
 * It then returns a pointer to the created object.*/
void testCreateDestroy();

void testCopy();

void testValidate();
