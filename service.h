#include "list.h"

typedef struct {
    List *materialList;
    List *undoList;
} CoffeeShop;

/*creates a new CoffeeShop object and initializes its member variables*/
CoffeeShop createCoffeeShop();
/*frees the memory allocated for a CoffeeShop object and its member variables*/
void destroyCoffeeShop(CoffeeShop *coffeeShop);
/*adds a new material to the coffee shop's inventory or increases
 * the quantity if the material already exists*/
int addMaterial(CoffeeShop *coffeeShop, char *name, char *producer, int quantity);
/*Updates the information of a material at a given position in the coffee shop's inventory*/
int updateMaterial(CoffeeShop *coffeeShop, int pos, char *name, char *producer, int quantity);
/*removes a material at a given position from the coffee shop's inventory*/
int removeMaterial(CoffeeShop *coffeeShop, int pos);
/* returns a pointer to the material at a given position in the coffee shop's inventory*/
Material *getMaterial(CoffeeShop *coffeeShop, int pos);
/*undoes the last modification made to the coffee shop's inventory*/
int undo(CoffeeShop *coffeeShop);
/* returns the number of materials in the coffee shop's inventory*/
int sizeOfMaterialList(CoffeeShop *coffeeShop);
/*returns the total quantity of a given material in the coffee shop's inventory*/
int getAllMaterialsByName(CoffeeShop *coffeeShop, char *name);
/*returns a pointer to the coffee shop's inventory*/
List *getAllMaterials(CoffeeShop *coffeeShop);
/*returns a list of all materials whose name starts with a given letter*/
List *getAllMaterialsWithStartingLetter(CoffeeShop *coffeeShop, char letter);
/*returns a list of all materials whose quantity is less than a given value*/
List *getMaterialsWithLessQuantity(CoffeeShop *coffeeShop, int quantity);
/*sorts the coffee shop's inventory by quantity, either in ascending or descending order.*/
List *sortByQuantity(CoffeeShop *coffeeShop, int order);
/*sorts the coffee shop's inventory by name, either in ascending or descending order.*/
List *sortByName(CoffeeShop *coffeeShop, int order);

void testCreateCoffeeShop();

void testCRUDService();

void testUndo();

void testFiltering();

void testSorting();
