#include "ui.h"
#include "service.h"
#include "stdio.h"

void printMenu() {
    printf("1.Add Material\n2.Update Material\n3.Delete\n4.Get Material\n5.Print All\n6.Get Material quantity\n7.Filter By Starting Letter\n8.Filter By Less Quantity\n9.Sort By Name\n10.Sort By Quantity\n0.Exit\n");
}

void addMaterialUI(CoffeeShop* coffeeShop) {
    char name[30], producer[30];
    name[0] = '\0';
    producer[0] = '\0';
    int quantity = 1;
    printf("Name : ");
    scanf("%s", name);
    printf("Producer : ");
    scanf("%s", producer);
    printf("Quantity : ");
    scanf_s("%d", &quantity);

    int res = addMaterial(coffeeShop, name, producer, quantity);
    if (res != 0)
        printf("There was an error\n");
    else
        printf("Element added successfully\n");

}

void updateMaterialUI(CoffeeShop* coffeeShop) {
    char newName[30], newProducer[30];
    newName[0] = '\0';
    newProducer[0] = '\0';
    int newQuantity = 0, pos = 0;
    printListUI(coffeeShop->materialList);
    printf("Position : ");
    scanf_s("%d", &pos);
    printf("New Name : ");
    scanf("%s", newName);
    printf("New Producer : ");
    scanf("%s", newProducer);
    printf("New Quantity : ");
    scanf_s("%d", &newQuantity);

    int res = updateMaterial(coffeeShop, pos, newName, newProducer, newQuantity);
    if (res != 0)
        printf("There was an error %d\n", res);
    else
        printf("Element added successfully\n");

}

void removeMaterialUI(CoffeeShop* coffeeShop) {
    int pos = 0;
    printListUI(coffeeShop->materialList);
    printf("Position : ");
    scanf_s("%d", &pos);
    int res = deleteMaterial(coffeeShop, pos);
    if (res != 0)
        printf("There was an error\n");
    else
        printf("Element added successfully\n");

}

void getMaterialUI(CoffeeShop* coffeeShop) {
    char name[30], producer[30];
    name[0] = '\0';
    producer[0] = '\0';
    printf("Name : ");
    scanf("%s", name);
    printf("Producer : ");
    scanf("%s", producer);
    Material * material = getMaterial(coffeeShop->materialList, name, producer);
    if (material->quantity == -1)
        printf("The searched material does not exist\n");
    else
        printf("Searched Material: Name  %s | Producer  %s | Quantity  %d\n", material->name, material->producer,
               material->quantity);
}

void printListUI(List *list) {

    if (sizeOfMaterialList(list) != 0) {
        for (int i = 0; i < sizeOfMaterialList(list); i++) {
            Material * material = list->elements[i];
            printf("Material %d: Name  %s | Producer  %s | Quantity  %d", i + 1, material->name,
                   material->producer, material->quantity);
        }
        printf("\n");
    } else {
        printf("There are no materials in the list\n");
    }
}

void getMaterialByNameUI(CoffeeShop* coffeeShop) {
    char name[30];
    name[0] = '\0';
    printf("Name : ");
    scanf("%s", name);
    int qt = getAllMaterialsByName(coffeeShop->materialList, name);
    printf("The selected material has a quantity of %d\n", qt);
}

void filterByStartingLetterUI(CoffeeShop* coffeeShop) {
    char letter;
    printf("Letter :");
    scanf("%c", &letter);
    List *filterResult = getMaterialsWithStartingLetter(coffeeShop->materialList,letter);
    printListUI(filterResult);
    destroyList(filterResult);
}

void filterByLessQuantityUI(CoffeeShop* coffeeShop) {
    int quantity = 0;
    printf("Quantity : ");
    scanf("%d", &quantity);
    List* filterResult = getMaterialsWithLessQuantity(coffeeShop->materialList, quantity);
    printListUI(filterResult);
    destroyList(filterResult);
}

void undoUI(CoffeeShop* coffeeShop) {
    int res = undo(coffeeShop);
    if (res == 1)
        printf("There was an error\n");
    else
        printf("Undo success\n");
}

void sortByNameUI(CoffeeShop* coffeeShop) {
    int order = 0;
    printf("Order (0-descending 1-ascending) : ");
    scanf("%d", &order);
    List* filterResult = getMaterialsOrderedByName(coffeeShop->materialList, order);
    printListUI(filterResult);
    destroyList(filterResult);
}

void sortByQuantityUI(CoffeeShop* coffeeShop) {
    int order = 0;
    printf("Order (0-descending 1-ascending) : ");
    scanf("%d", &order);
    List* filterResult = getMaterialsOrderedByQuantity(coffeeShop->materialList, order);
    printListUI(filterResult);
    destroyList(filterResult);
}

void runUI(CoffeeShop* coffeeShop) {
    int running = 1;
    while (running) {

        printMenu();
        int cmd = 0;
        printf("Introdu Comanda : ");
        scanf_s("%d", &cmd);
        switch (cmd) {
            case 1: {
                addMaterialUI(coffeeShop);
                break;
            }
            case 2: {
                updateMaterialUI(coffeeShop);
                break;
            }
            case 3: {
                removeMaterialUI(coffeeShop);
                break;
            }
            case 4: {
                getMaterialUI(coffeeShop);
                break;
            }
            case 5: {
                printListUI(coffeeShop->materialList);
                break;
            }
            case 6: {
                getMaterialByNameUI(coffeeShop);
                break;
            }
            case 7: {
                filterByStartingLetterUI(coffeeShop);
                break;
            }
            case 8: {
                filterByLessQuantityUI(coffeeShop);
                break;
            }
            case 9: {
                sortByNameUI(coffeeShop);
                break;
            }
            case 10: {
                sortByQuantityUI(coffeeShop);
                break;
            }
            case 11: {
                undoUI(coffeeShop);
                break;
            }
            case 0: {
                destroyList(coffeeShop->materialList);
                destroyList(coffeeShop->undoList);
                printf("Bye !\n");
                running = 0;
            }
            default: {
                continue;
            }
        }
    }
}
