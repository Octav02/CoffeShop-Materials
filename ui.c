#include "ui.h"
#include "stdio.h"

void printMenu() {
    printf("1.Add Material\n2.Update Material\n3.Delete\n4.Get Material\n5.Print All\n6.Get Material quantity\n7.Filter By Starting Letter\n8.Filter By Less Quantity\n9.Sort By Name\n10.Sort By Quantity\n0.Exit\n");
}

void addMaterialUI(List *list) {
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

    int res = addMaterial(list, name, producer, quantity);
    if (res != 0)
        printf("There was an error\n");
    else
        printf("Element added successfully\n");

}

void updateMaterialUI(List *list) {
    char name[30], producer[30], newName[30], newProducer[30];
    name[0] = '\0';
    producer[0] = '\0';
    newName[0] = '\0';
    newProducer[0] = '\0';
    int newQuantity = 0;
    printf("Name : ");
    scanf("%s", name);
    printf("Producer : ");
    scanf("%s", producer);
    printf("New Name : ");
    scanf("%s", newName);
    printf("New Producer : ");
    scanf("%s", newProducer);
    printf("New Quantity : ");
    scanf_s("%d", &newQuantity);

    int res = updateMaterial(list, name, producer, newName, newProducer, newQuantity);
    printf("%s\n%s\n%d",  newName, newProducer, newQuantity);
    if (res != 0)
        printf("There was an error %d\n", res);
    else
        printf("Element added successfully\n");

}

void removeMaterialUI(List *list) {
    char name[30], producer[30];
    name[0] = '\0';
    producer[0] = '\0';
    printf("Name : ");
    scanf("%s", name);
    printf("Producer : ");
    scanf("%s", producer);
    int res = deleteMaterial(list, name, producer);
    if (res != 0)
        printf("There was an error\n");
    else
        printf("Element added successfully\n");

}

void getMaterialUI(List *list) {
    char name[30], producer[30];
    name[0] = '\0';
    producer[0] = '\0';
    printf("Name : ");
    scanf("%s", name);
    printf("Producer : ");
    scanf("%s", producer);
    ElemType material = getMaterial(list, name, producer);
    if (material.quantity == -1)
        printf("The searched material does not exist\n");
    else
        printf("Searched Material: Name  %s | Producer  %s | Quantity  %d\n", material.name, material.producer,
               material.quantity);
}

void printListUI(List *list) {
    List printList = getAllMaterials(list);
    if (sizeOfMaterialList(&printList) != 0) {
        for (int i = 0; i < sizeOfMaterialList(&printList); i++) {
            printf("Material %d: Name  %s | Producer  %s | Quantity  %d", i + 1, printList.elements[i].name,
                   printList.elements[i].producer, printList.elements[i].quantity);
        }
        printf("\n");
    } else {
        printf("There are no materials in the list\n");
    }
}

void getMaterialByNameUI(List *list) {
    char name[30];
    name[0] = '\0';
    printf("Name : ");
    scanf("%s", name);
    int qt = getAllMaterialsByName(list, name);
    printf("The selected material has a quantity of %d\n", qt);
}

void filterByStartingLetterUI(List *list) {
    char letter;
    printf("Letter :");
    scanf("%c", &letter);
    List filterResult = getMaterialsWithStartingLetter(list,letter);
    printListUI(&filterResult);
    destroyMaterialList(&filterResult);
}

void filterByLessQuantityUI(List * list) {
    int quantity = 0;
    printf("Quantity : ");
    scanf("%d", &quantity);
    List filterResult = getMaterialsWithLessQuantity(list, quantity);
    printListUI(&filterResult);
    destroyMaterialList(&filterResult);
}

void sortByNameUI(List* list) {
    int order = 0;
    printf("Order (0-descending 1-ascending) : ");
    scanf("%d", &order);
    List filterResult = getMaterialsOrderedByName(list, order);
    printListUI(&filterResult);
    destroyMaterialList(&filterResult);
}

void sortByQuantityUI(List* list) {
    int order = 0;
    printf("Order (0-descending 1-ascending) : ");
    scanf("%d", &order);
    List filterResult = getMaterialsOrderedByQuantity(list, order);
    printListUI(&filterResult);
    destroyMaterialList(&filterResult);
}

void runUI(List *list) {
    int running = 1;
    while (running) {

        printMenu();
        int cmd = 0;
        printf("Introdu Comanda : ");
        scanf_s("%d", &cmd);
        switch (cmd) {
            case 1: {
                addMaterialUI(list);
                break;
            }
            case 2: {
                updateMaterialUI(list);
                break;
            }
            case 3: {
                removeMaterialUI(list);
                break;
            }
            case 4: {
                getMaterialUI(list);
                break;
            }
            case 5: {
                printListUI(list);
                break;
            }
            case 6: {
                getMaterialByNameUI(list);
                break;
            }
            case 7: {
                filterByStartingLetterUI(list);
                break;
            }
            case 8: {
                filterByLessQuantityUI(list);
                break;
            }
            case 9: {
                sortByNameUI(list);
                break;
            }
            case 10: {
                sortByQuantityUI(list);
                break;
            }
            case 0: {
                destroyMaterialList(list);
                printf("Bye !\n");
                running = 0;
            }
            default: {
                continue;
            }
        }
    }
}

