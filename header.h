//Created by: KHAN, Renee Althea F.

// header file containing libraries, structs and function prototypes

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CUSTOMERS 10
#define MAX_ORDERS 3

struct Order{
    int code;
    char name[50];
    float price;
    char status[20]; // pending, preparing (received by chef), cooking or packed
};

typedef struct Customer{ // typedef struct Customer = struct name 
    char name[50];
    char status[20];
    int customerNum;
    float totalBill;
    struct Order orders[3];
}Customer; // struct nametag (replaces "struct Customer")

typedef struct Menu{
    int code;
    char name[50];
    float price;
}Menu;

typedef struct PendingOrders{
    int code; // change to 0 when food is cooked
    char name[50];
    int customerNum; 
    
}PendingOrders;

//MANAGER ACTIONS

bool managerMenu(int currentCustomers, Customer customer[], Menu menu[], PendingOrders pending[]);
void displayMenu();
void sendOrderToChef(int currentCustomers, Customer customer[], PendingOrders pending[]);
void listPendingOrders(int currentCustomers, Customer customer[]);
void listCurrentCustomers(int currentCustomers, Customer customer[]);
void sendDriver(int currentCustomers, Customer customer[]);
void displayIncome(int currentCustomers, Customer customer[]);
void displayDishesServed(int currentCustomers, Menu menu[], Customer customer[]);

//CHEF ACTIONS
void Order(PendingOrders pending[]);
int cook(int currentCustomers, Customer customer[]);
void packOrder(int currentCustomers, Customer customer[]);
void chefMenu(int currentCustomers, Customer customer[], PendingOrders pending[]);

//CUSTOMER ACTIONS
int isOrderValid(Menu menu[], int orderCode);
void displayOrders(Customer customer);
void order(Menu menu[], int customerNum, Customer customer[]);
void pay(Customer customer[], int currentCustomers);
void displayCustomerStatus(Customer customer[], int currentCustomers);
void displayCustomerNum(Customer customer[]);
int customerMenu(bool closed, int currentCustomers, Customer customer[], Menu menu[]);
