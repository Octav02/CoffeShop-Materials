#include "material.h"

#include <string.h>
#include <assert.h>
#include <stdlib.h>

Material *createMaterial(char *name, char *producer, int quantity) {
    Material *rez = malloc(sizeof(Material));
    size_t nrC = strlen(name) + 1;
    if (nrC == 1) nrC = 2;
    rez->name = malloc(sizeof(char) * nrC);
    strcpy(rez->name, name);
    nrC = strlen(producer) + 1;
    if (nrC == 1) nrC = 2;
    rez->producer = malloc(sizeof(char) * nrC);
    strcpy(rez->producer, producer);
    rez->quantity = quantity;
    return rez;
}

void destroyMaterial(Material *material) {
    free(material->producer);
    free(material->name);
    free(material);
}

int validateMaterial(Material *material) {
    if (strlen(material->name) == 0)
        return 1;
    if (strlen(material->producer) == 0)
        return 2;
    if (material->quantity < 0)
        return 3;
    return 0;
}


Material *copyMaterial(Material *material) {
    Material *rez = createMaterial(material->name, material->producer, material->quantity);
    return rez;
}

void testCreateDestroy() {
    Material *material = createMaterial("Name", "Producer", 10);
    assert(material != NULL);
    assert(strcmp(material->name, "Name") == 0);
    assert(strcmp(material->producer, "Producer") == 0);
    assert(material->quantity == 10);
    destroyMaterial(material);
}

void testCopy() {
    Material *material = createMaterial("Name", "Producer", 10);
    Material *copy = copyMaterial(material);
    assert(copy != NULL);
    assert(strcmp(copy->name, "Name") == 0);
    assert(strcmp(copy->producer, "Producer") == 0);
    assert(copy->quantity == 10);
    destroyMaterial(material);
    destroyMaterial(copy);
}

void testValidate() {
    Material *material = createMaterial("", "Producer", 10);
    assert(validateMaterial(material) == 1);
    destroyMaterial(material);

    material = createMaterial("Name", "", 10);
    assert(validateMaterial(material) == 2);
    destroyMaterial(material);

    material = createMaterial("Name", "Producer", -1);
    assert(validateMaterial(material) == 3);
    destroyMaterial(material);

    material = createMaterial("Name", "Producer", 10);
    assert(validateMaterial(material) == 0);
    destroyMaterial(material);
}