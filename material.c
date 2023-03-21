#include "material.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
Material* createMaterial(char *name, char *producer, int quantity) {
    Material *rez = malloc(sizeof(Material));
    size_t len = strlen(name) + 1;
    rez->name = malloc(sizeof(char) * len);
    strcpy_s(rez->name, len, name);
    len = strlen(producer) + 1;
    rez->producer = malloc(sizeof(char) * len);
    strcpy_s(rez->producer, len, producer);
    rez->quantity = quantity;
    return rez;
}

void destroyMaterial(Material *material) {
    free(material -> name);
    free(material -> producer);
    free(material);
}

Material* copyMaterial(Material *material) {
    return createMaterial(material->name, material->producer, material->quantity);
}

int validateMaterial(Material* material) {
    if (strlen(material->name) == 0)
        return 1;
    if (strlen(material->producer) == 0)
        return 2;
    if (material->quantity < 0)
        return 3;
    return 0;
}

void testCreateDestroyValidate() {
    Material* material = createMaterial("Arabica", "P1", 1000);
    assert(!strcmp(material->name, "Arabica"));
    assert(!strcmp(material->producer, "P1"));
    assert(material->quantity == 1000);
    Material* copMaterial = copyMaterial(material);
    assert(!strcmp(copMaterial->name, "Arabica"));
    assert(!strcmp(copMaterial->producer, "P1"));
    assert(copMaterial->quantity == 1000);
    assert(validateMaterial(material) == 0);
    destroyMaterial(material);
    destroyMaterial(copMaterial);

    material = createMaterial("","Da",32);
    assert(validateMaterial(material) == 1);
    Material *material1 = createMaterial("Africana", "", 1000);
    assert(validateMaterial(material1) == 2);
    Material* material2 = createMaterial("Robusta", "P2", -40);
    assert(validateMaterial(material2) == 3);
    destroyMaterial(material1);
    destroyMaterial(material2);

}