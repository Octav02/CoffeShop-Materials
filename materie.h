#pragma once

typedef struct {
    char name[30];
    char producer[30];
    int quantity;
} Material;

// Preconditions: Valid non-null pointers to character arrays for name and producer, and a non-negative integer for quantity.
// Parameters: The name, producer, and quantity of the new "Material" object that needs to be created.
// Postconditions: A new "Material" object is created and returned.
// Return: The newly created "Material" object.
Material createMaterial(char *name, char *producer, int quantity);

// Preconditions: A valid pointer to a "Material" object that needs to be destroyed.
// Parameters: A pointer to the "Material" object that needs to be destroyed.
// Postconditions: The memory allocated for the "Material" object is freed.
// Return: None.
void destroyMaterial(Material *material);

// Preconditions: A "Material" object.
// Parameters: The "Material" object that needs to be validated.
// Postconditions: None.
// Return: 1 if the name is empty, 2 if the producer is empty, 3 if the quantity is less than 0, and 0 otherwise.
int validateMaterial(Material material);

void testCreateDestroyValidate();