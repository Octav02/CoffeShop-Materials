#include <stdio.h>
#include "ui.h"

void printMenu() {
    printf("1.Add\n2.Update\n3.Delete\n4.PrintAll\n5.PrintFilterLessQt\n6.PrintFilterStartingLetter\n7.PrintAllQuantityName\n8.SortByName\n9.SortByQuantity\n10.Undo\n0.Exit\n");
}

void printList(List* list) {
    if (size(list) == 0) {
        printf("There are no elements in the list \n");
        return;
    }
    for (int i = 0; i < size(list); i++) {
        Material * material = get(list,i);
        printf("Material %d : Name %s | Producer %s | Quantity %d \n", i + 1,material->name,material->producer,material->quantity);
    }
}

void printMaterialList(CoffeeShop* coffeeShop) {
    printList(coffeeShop->materialList);
}

void addMaterialUI(CoffeeShop* coffeeShop){
    char name[50], producer[50];
    int quantity = 0;
    name[0] = '\0';
    producer[0] = '\0';
    printf("Name : ");
    scanf("%s", name);
    printf("Producer : ");
    scanf("%s", producer);
    printf("Quantity : ");
    scanf("%d", &quantity);
    int res = addMaterial(coffeeShop,name,producer,quantity);
    if (res != 0)
        printf("There was an error ! \n");
    else
        printf("Operation succeeded ! \n");
}

void updateMaterialUI(CoffeeShop* coffeeShop) {
    printMaterialList(coffeeShop);
    char name[50], producer[50];
    int quantity = 0, pos = 0;
    name[0] = '\0';
    producer[0] = '\0';
    printf("Position : ");
    scanf("%d", &pos);
    printf("Name : ");
    scanf("%s", name);
    printf("Producer : ");
    scanf("%s", producer);
    printf("Quantity : ");
    scanf("%d", &quantity);
    int res = updateMaterial(coffeeShop,pos - 1,name,producer,quantity);
    if (res != 0)
        printf("There was an error ! \n");
    else
        printf("Operation succeeded ! \n");
}

void removeMaterialUI(CoffeeShop* coffeeShop) {
    int pos = 0;
    printf("Position : ");
    scanf("%d", &pos);
    int res = removeMaterial(coffeeShop,pos - 1);
    if (res != 0)
        printf("There was an error ! \n");
    else
        printf("Operation succeeded ! \n");
}

void filterLessQuantityUI(CoffeeShop* coffeeShop) {
    int quantity = 0;
    printMaterialList(coffeeShop);
    printf("Quantity : ");
    scanf("%d", &quantity);
    List * filterResult = getMaterialsWithLessQuantity(coffeeShop, quantity);
    printList(filterResult);
    destroyList(filterResult);
}

void filterStartingLetterUI(CoffeeShop* coffeeShop) {
    char letter = '\0';
    printf("Letter : ");
    scanf("%c", &letter);
    List *filterResult = getAllMaterialsWithStartingLetter(coffeeShop, letter);
    printList(filterResult);
    destroyList(filterResult);
}

void printAllQuantityNameUI(CoffeeShop* coffeeShop) {
    char name[50];
    name[0] = '\0';
    printf("Name : ");
    scanf("%s", name);
    int res = getAllMaterialsByName(coffeeShop,name);
    printf("The quantity for the selected material is : %d \n", res);
}

void undoUI(CoffeeShop* coffeeShop) {
    int res = undo(coffeeShop);
    if (res != 0)
        printf("There was an error ! \n");
    else
        printf("Operation succeeded ! \n");
}

void sortByNameUI(CoffeeShop* coffeeShop) {
    int order = 0;
    printf("Order : (0-Ascending 1-Descending) : ");
    scanf("%d",&order);
    List * sortResult = sortByName(coffeeShop,order);
    printList(sortResult);
    destroyList(sortResult);
}

void sortByQuantityUI(CoffeeShop * coffeeShop) {
    int order = 0;
    printf("Order : (0-Ascending 1-Descending) : ");
    scanf("%d",&order);
    List * sortResult = sortByQuantity(coffeeShop,order);
    printList(sortResult);
    destroyList(sortResult);
}

void runUI(CoffeeShop* coffeeShop) {
    int running = 1;
    while (running) {
        printMenu();
        int cmd;
        printf("Choose option : ");
        scanf("%d", &cmd);
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
                printMaterialList(coffeeShop);
                break;
            }
            case 5: {
                filterLessQuantityUI(coffeeShop);
                break;
            }
            case 6: {
                filterStartingLetterUI(coffeeShop);
                break;
            }
            case 7: {
                printAllQuantityNameUI(coffeeShop);
                break;
            }
            case 8: {
                sortByNameUI(coffeeShop);
                break;
            }
            case 9: {
                sortByQuantityUI(coffeeShop);
                break;
            }
            case 10: {
                undoUI(coffeeShop);
                break;
            }
            case 0: {
                printf("Bye !");
                destroyCoffeeShop(coffeeShop);
                running = 0;
                break;
            }
            default: {
                continue;
            }
        }
    }
}
