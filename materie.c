#include "materie.h"
#include <string.h>
#include <assert.h>

Material createMaterial(char *name, char *producer, int quantity) {
    Material rez;
    strcpy_s(rez.name, sizeof(rez.name), name);
    strcpy_s(rez.producer, sizeof(rez.producer), producer);
    rez.quantity = quantity;
    return rez;
}

void destroyMaterial(Material *material) {
    material->name[0] = '\0';
    material->producer[0] = '\0';
    material->quantity = -1;
}

int validateMaterial(Material material) {
    if (strlen(material.name) == 0)
        return 1;
    if (strlen(material.producer) == 0)
        return 2;
    if (material.quantity < 0)
        return 3;
    return 0;
}

void testCreateDestroyValidate() {
    Material material = createMaterial("Arabica", "P1", 1000);
    assert(!strcmp(material.name, "Arabica"));
    assert(!strcmp(material.producer, "P1"));
    assert(material.quantity == 1000);
    assert(validateMaterial(material) == 0);


    destroyMaterial(&material);
    assert(strlen(material.name) == 0);
    assert(strlen(material.producer) == 0);
    assert(material.quantity == -1);

    assert(validateMaterial(material) == 1);
    Material material1 = createMaterial("Africana", "", 1000);
    assert(validateMaterial(material1) == 2);
    Material material2 = createMaterial("Robusta", "P2", -40);
    assert(validateMaterial(material2) == 3);
}