#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MaxToppingOrderAllow  4
#define MaxOrder  50
#define CountListTopping (sizeof (ListTopping) / sizeof (const char *))
#define PriceEachTopping 1
#define DeliveryCharge  8
#define ArrayToppingSize 100
#define ArrayOrderPizzaSize 100

enum Shipment {
    CARDORDER, COLLECT, DELIVERY
};

// pointer array of toping available
char * ListTopping[] ={
    "Bacon",
    "Olives",
    "Ham",
    "Mushrooms",
    "Pineapple",
    "Salami",
    "Anchovies"
};

enum Size {
    SMALL, MEDIUM, LARGE
};

struct Topping {
    char name[100];
    int counter;
};

struct Pizza {
    enum Size size;
    double price;
    char *listTopping[ArrayToppingSize]; //
    int counter;

};

struct Order {
    char name[30];
    int phone;
    char address[100];
    struct Pizza listOrder[ArrayOrderPizzaSize];
    int counter;
};


void PizzaSetup();
void shopHeaderInfo();
void toppingHeaderInfo();
void addTopping();
void addOrder();
void cartOrderInfo(enum Shipment type);
void shipmentSummary();
void clearCartOrder(int byShipment);
int myAtoi(char* str);
char* getSizeName(int size);
int isNumber(char s[12]);

struct Pizza pizza;
struct Order order;

int main() {
    shopHeaderInfo();
    PizzaSetup();
    return 0;
}

// List of menu option available in the shop.

void shopHeaderInfo() {
    printf("|-----------------------------------------------|\n");
    printf("|\t Pizza Shop \t\t\t\t|\n");
    printf("|-----------------------------------------------|\n");
    printf("|Press 0, 1, 2, 3, 4, 5 and 6 for the operations|\n");
    printf("|-----------------------------------------------|\n");
    printf("| 0: Exit \t\t\t\t\t|\n");
    printf("| 1: For Small Pizza  \t\t\t\t|\n");
    printf("| 2: For Medium Pizza \t\t\t\t|\n");
    printf("| 3: For Large  Pizza \t\t\t\t|\n");
    printf("| 4: View Order Cart Info \t\t\t\t|\n");
    printf("| 5: For Order Shipment \t\t\t|\n");
    printf("| 6: Clear Order Cart \t\t\t\t|\n");
    printf("|-----------------------------------------------|\n");
}

// List of topping option available for the pizza.

void toppingHeaderInfo() {
    printf("|-----------------------------------------------|\n");
    printf("|\t Topping available are \t\t\t|\n");
    printf("|-----------------------------------------------|\n");
    int id = 1;
    //Topping t;
    for (int i = 0; i < CountListTopping; i++) {
        printf("| %d: %s \t\t\t\t\t|\n", (i + 1), ListTopping[i]);
    }
    printf("|-----------------------------------------------|\n");
    printf("| Zero '0' for return to previous order section \t\t\t\t|\n");
    printf("|-----------------------------------------------|\n");
}

void PizzaSetup() {
    order.counter = -1;
    int operationInput = -1;
    char tempOrder[3];
    do {
        printf("Order Size: ");
        // Taking input operations from the console.
        //operationInput = getchar();
        // use of scanf
        scanf("%s", tempOrder);
        operationInput = myAtoi(tempOrder); // convert char or string into number.
        //gets(tempOrder);
        switch (operationInput) {
            case 0: // pizza application is close.
                printf("Thank you for visiting Pizza shop.\n\n");
                exit(0);
                break;
            case 1: // Small Pizza Size operation
            {
                pizza.size = SMALL;
                pizza.price = 5.0;
                pizza.counter = -1;
                toppingHeaderInfo();
                addTopping();
                addOrder(); // adding pizza list as order.
                shopHeaderInfo();

            }
                break;
            case 2: // Medium Pizza Size operation
            {
                pizza.size = MEDIUM;
                pizza.price = 8.0;
                pizza.counter = -1;
                toppingHeaderInfo();
                addTopping();
                addOrder(); // adding pizza list as order.
                shopHeaderInfo();
            }
                break;
            case 3: // Large Pizza Size operation
            {
                pizza.size = LARGE;
                pizza.price = 12.0;
                pizza.counter = -1;
                toppingHeaderInfo();
                addTopping();
                addOrder(); // adding pizza list as order.
                shopHeaderInfo();
            }
                break;
            case 4: // Display of order information in cart.
                cartOrderInfo(CARDORDER);
                break;
            case 5: // Display of order summary
                shipmentSummary();
                clearCartOrder(1);
                break;
            case 6: // Clearing cart information.
                clearCartOrder(0);
                break;
            default:
                printf("Invalid Order operation Id.\n\n");
                break;
        }
    } while (operationInput != 0);
}

void addTopping() {
    int toppingNo = -1;
    int countOrderTopping = -1;
    char tempInput[3];
    printf("Select the topping types\n");
    do {
        printf("Topping type No.: ");
        // Taking input operations from the console.
        scanf("%s", tempInput);
        toppingNo = myAtoi(tempInput);
        if (toppingNo == 0) {
            printf("\n\n");
            break;
        } else if (toppingNo > 7) {
            printf("Invalid topping type Id. Check Id!.\n\n");
        } else if (toppingNo > 0 && toppingNo <= 7) // only 7 topping option available
        {
            if (countOrderTopping > MaxToppingOrderAllow) // Maximum 4 topping is allowed
            {
                printf("\n Maximum topping reached i.e %d \n", countOrderTopping);
                printf("\n Type zero 0 for return: ");
                scanf("%d", toppingNo);
                //gets(toppingNo);
                if (toppingNo == 0) {
                    break;
                }
                break;
            } else if (toppingNo > CountListTopping) {
                printf("Topping order not found.Try again!.\n");
            } else {
                // Adding topping option to available pizza
                pizza.listTopping[++pizza.counter] = (ListTopping[toppingNo - 1]);
                printf("%s has been added.\n\n", ListTopping[toppingNo - 1]);
                countOrderTopping++;
            }
        }
    } while (toppingNo != 0);
}

void addOrder() { // Always start the loop from 0 and count will always be counter +1;
    // if the count = 0, means order = 1
    order.listOrder[++order.counter] = pizza;
    for (int i = 0; i <= pizza.counter; i++) {
        pizza.listTopping[i] = NULL;
    }
    pizza.counter = -1;
}

void cartOrderInfo(enum Shipment type) {
    double total = 0.0;
    printf("|---------------------------------------------------------------|\n");
    printf("|\t\t PIZZA ITEMS \t\t\t\t\t|\n");

    if (order.counter >= 0) {
        printf("| Size \t\t Price \t\t\t Toppings \t\t|\n");
        printf("|---------------------------------------------------------------|\n");
        for (int i = 0; i <= order.counter; i++) {
            // for (Pizza p : order->listOrder)
            struct Pizza p = order.listOrder[i];
            char builder[100];
            sprintf(builder, "| %s \t\t $%.2f \t\t ", getSizeName(p.size), p.price);
            total += p.price;
            if (p.counter < 0) {
                printf("%s No topping. \t\t|\n", builder);
                printf("|---------------------------------------------------------------|\n");
            } else {
                int countTemp = -1;
                total += (p.counter + 1) * PriceEachTopping; // counter starts from zero.Som counter = 0 means one 1.
                for (int i = 0; i <= p.counter; i++) {
                    if (countTemp == -1) {
                        printf("%s %s each $%d \t|\n", builder, p.listTopping[i], PriceEachTopping);
                        countTemp++;
                    } else {
                        printf("|\t\t\t\t\t %s each $%d \t|\n", p.listTopping[i], PriceEachTopping);
                    }
                }
                //printf("|\t\t\t\t\t  total topping: $%d \t|\n", p.counter);
                printf("|---------------------------------------------------------------|\n");
            }
        }
        int extraCharge = 0;
        if (type == DELIVERY) {
            if (total < 30) {
                total += DeliveryCharge;
                extraCharge = DeliveryCharge;
            }
        }
        printf("| \t\t Extra charge: \t\t $%d \n", extraCharge);
        printf("| Total \t Order:%d  \t\t $%.2f \t\t\t|\n", (order.counter + 1), total);
        //printf("| Total \t Order:" + order->counter + "\t\t $" + total + "");
    } else {
        printf("| Empty pizza items in order cart.\t\t|\n");
    }
    printf("|---------------------------------------------------------------|\n");
}

// Clearing the array of order
void clearCartOrder(int byShipment) {
    if (order.counter > -1) {
        struct Pizza p; // Empty p.
        for (int i = 0; i <= order.counter; i++) {
            order.listOrder[i] = pizza;
            order.counter = -1;
        }
        if (!byShipment)
            printf("Removed Pizza items in the Order cart.\n");

    } else {
        printf("Order cart is already empty.\n\n");
    }
}

// Shipment information display
void shipmentSummary() {
    if (order.counter < 0) {
        printf("No pizza items in the order cart. Make your order.\n");
    } else {
        printf("|-----------------------------------------------|\n");
        printf("|\t Shipment Information \t\t|\n");
        printf("| Note: Additional delivery $%d charge if total is less than $30 \t|\n", DeliveryCharge);
        printf("|-----------------------------------------------|\n");
        printf("|Press 0, 1, 2 and for the operations|\n");
        printf("|-----------------------------------------------|\n");
        printf("| 0: Return to Main Menu \t\t\t\t\t|\n");
        printf("| 1: Self Collect \t\t\t\t|\n");
        printf("| 2: Delivery \t\t\t\t|\n");
        printf("|-----------------------------------------------|\n");
        int shipmentMethodId = -1;
        do {
            char name[30], address[100];
            char tempOrder[3];
            int phone = 0;
            printf("Shipment Method Type No.: ");
            // Taking input operation from the console.
            scanf("%s", tempOrder);
            //gets(tempOrder);
            shipmentMethodId = myAtoi(tempOrder);

            switch (shipmentMethodId) {
                case 0:
                    shipmentMethodId = 0; // breaking out of do while loop
                    break;
                case 1: // self pickup option
                    n :
                    printf("Your name:");
                    scanf("%s", name);
                    if (name == "")
                        goto n;
                    p:
                    printf("Phone:");
                    char temp[12];
                    scanf("%s", temp);
                    if (!isNumber(temp))
                        goto p;
                    phone = myAtoi(temp);

                    strcpy(order.name, name);
                    order.phone = phone;
                    printf("\n Your order summary\n");
                    printf("Name: %s \t Phone: %d \n", order.name, order.phone);
                    cartOrderInfo(COLLECT);
                    shipmentMethodId = 0; // for exiting the currnt while loop and return to main menu.
                    printf("\n Thank you for ordering.\n\nYour new order, please.\n\n");
                    break;
                case 2: // Delivery option 
                    lname :
                            printf("Your name:");
                    scanf("%s", name);
                    if (name == "")
                        goto lname;
                lphone:
                    printf("Phone:");
                    char a[12];
                    scanf("%s", a);
                    if (!isNumber(a))
                        goto lphone;
                    phone = myAtoi(a);
                laddress:
                    printf("Address:");
                    scanf("%s", address);
                    if (name == "")
                        goto laddress;
                    strcpy(order.name, name);
                    order.phone = phone;
                    strcpy(order.address, address);
                    printf("\n Your order summary\n");
                    printf("Name: %s \t Phone: %d \t Address: %s \n\n", order.name, order.phone, order. address);
                    cartOrderInfo(DELIVERY);
                    shipmentMethodId = 0;
                    printf("\n Thank you for ordering.\n\nYour new order.Please\n\n");
                    break;
                default:
                    printf("Invalid method Id. Check shipment method type Id.\n\n");
            }
        } while (shipmentMethodId != 0);
    }
}

char* getSizeName(int size) {
    switch (size) {
        case 0: return "Small";
        case 1: return "Medium";
        case 2: return "Large";
            /* etc... */
    }
}

int myAtoi(char* str) {
    int res = 0; // Initialize result
    // Iterate through all characters of input string and  update result
    for (int i = 0; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';
    return res;
}

int isNumber(char s[12]) {
    int valid;
    int len = strlen(s);
    if (len > 0) {
        valid = 1;
        for (int i = 0; i < len; ++i) {
            if (!isdigit(s[i])) {
                valid = 0;
                break;
            }
        }
    }
    return valid;
}

