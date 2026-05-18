#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int money = 500;

/* ---------- PRODUCT STRUCT ---------- */
typedef struct {
    char name[50];
    int price;
    int stock;
} Item;

/* ---------- INVENTORY ---------- */
char inventory[100][50];
int quantityHistory[100];
int spentHistory[100];
int invCount = 0;

/* ---------- MENUS ---------- */

Item drinksMenu[] = {
    {"Mango Juice",40,5},
    {"Milk Tea",60,5},
    {"Coke",50,5},
    {"Water",20,5}
};

Item snacksMenu[] = {
    {"Chips",30,5},
    {"Fries",50,5},
    {"Burger Bites",70,5},
    {"Popcorn",40,5}
};

Item sweetsMenu[] = {
    {"Chocolate",60,5},
    {"Ice Cream",80,5},
    {"Candy",20,5},
    {"Cake Slice",90,5}
};

Item mealsMenu[] = {
    {"Burger",100,5},
    {"Chicken Rice",90,5},
    {"Hotdog",60,5},
    {"Sandwich",80,5}
};

/* ---------- ADD INVENTORY ---------- */

void addInventory(char name[], int qty, int totalPrice)
{
    strcpy(inventory[invCount], name);
    quantityHistory[invCount] = qty;
    spentHistory[invCount] = totalPrice;
    invCount++;
}

/* ---------- VIEW INVENTORY ---------- */

void viewInventory()
{
    if(invCount == 0)
    {
        printf("\nNo purchases yet.\n");
        return;
    }

    printf("\n===== PURCHASE HISTORY =====\n");

    for(int i=0;i<invCount;i++)
    {
        printf("%s | Quantity: %d | Cost: ₱%d\n",
               inventory[i],
               quantityHistory[i],
               spentHistory[i]);
    }
}

/* ---------- PURCHASE ---------- */

void processPurchase(Item menu[], int choice)
{
    int qty;

    if(menu[choice].stock <= 0)
    {
        printf("Out of stock.\n");
        return;
    }

    printf("Enter quantity: ");
    scanf("%d",&qty);

    int total = qty * menu[choice].price;

    if(total > money)
    {
        printf("Not enough money.\n");
        return;
    }

    if(qty > menu[choice].stock)
    {
        printf("Insufficient stock.\n");
        return;
    }

    money -= total;
    menu[choice].stock -= qty;

    addInventory(menu[choice].name, qty, total);

    printf("\nPurchased %d x %s\n",
           qty,
           menu[choice].name);

    printf("Remaining balance: ₱%d\n",money);
}

/* ---------- VIEW PRODUCTS ---------- */

void viewProducts()
{
    int cat;

    printf("\n1.Drinks\n");
    printf("2.Snacks\n");
    printf("3.Sweets\n");
    printf("4.Meals\n");

    printf("Choice: ");
    scanf("%d",&cat);

    Item *menu=NULL;

    if(cat==1) menu=drinksMenu;
    else if(cat==2) menu=snacksMenu;
    else if(cat==3) menu=sweetsMenu;
    else if(cat==4) menu=mealsMenu;
    else return;

    for(int i=0;i<4;i++)
    {
        printf("%d. %s ₱%d Stock:%d\n",
               i+1,
               menu[i].name,
               menu[i].price,
               menu[i].stock);
    }

    int item;
    printf("Choose item: ");
    scanf("%d",&item);

    processPurchase(menu,item-1);
}

/* ---------- MAIN ---------- */

int main()
{
    int choice;

    do{
        printf("\n===== VENDING MACHINE =====\n");
        printf("Balance: ₱%d\n",money);

        printf("1. View Products\n");
        printf("2. View Inventory\n");
        printf("3. Exit\n");

        printf("Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                viewProducts();
                break;

            case 2:
                viewInventory();
                break;

            case 3:
                printf("Goodbye!\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    }while(choice!=3);

    return 0;
}