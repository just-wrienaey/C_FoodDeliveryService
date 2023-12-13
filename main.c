// December 12, 2023 
// 2:20pm - 9:40pm meals and breaks included approx. 5 hours (main and customer)
// 10pm - 11pm (manager 80%) 
// December 13, 2023
// 12:25pm - 3:10 (Completed all functions and requirements)
// Testing and debugging

#include "customer.c"

int main(){
    char opt;

    Customer customer[MAX_CUSTOMERS]; //without typedef, this is "struct Customer customer"

    int i, j;
    
    for(i=0; i<MAX_CUSTOMERS; i++){
        customer[i].customerNum = -1;
        customer[i].totalBill = -1;

        for(j=0; j<MAX_ORDERS; j++){
            customer[i].orders[j].code = -1;
            customer[i].orders[j].price = -1;
        }
  
    }

    int currentCustomers=0;

    PendingOrders pending[MAX_CUSTOMERS*9];

    for(i=0; i<MAX_CUSTOMERS*9; i++){
        pending[i].code = -1;
        strcpy(pending[i].name, "");
        pending[i].customerNum = -1;
    }

    Menu menu[9] = {{1100, "Burger w Fries", 120.00}, {1200, "Clubhouse", 95.00}, {1300, "Hotdog on Bun", 75.00}, 
                {2100, "Spaghetti", 150.00}, {2200, "Lasagna", 240.00}, {2300, "Mac 'n Cheese", 110.00}, 
                {3100, "Coke", 50.00}, {3200, "Iced tea", 45.00}, {3300, "Orange juice", 45.00} };
    
    do{

        printf("Welcome to Renee's Food Deliver Service!\n");

        printf("\n\nChoose your role below:");
        printf("\n[a] Customer");
        printf("\n[b] Manager");
        printf("\n[c] Chef");
        printf("\n[d] Exit\n");
        scanf(" %c", &opt);

        switch(opt){
            case 'a':
                currentCustomers = customerMenu(currentCustomers,customer, menu);
                break;
            case 'b':
                managerMenu(currentCustomers, customer, menu, pending);
                break;
            case 'c':
                chefMenu(currentCustomers, customer, pending);
                break;
            case 'd':
                printf("Thank you! Exiting program. . .");
                break;
            default:
                printf("Invalid input. Please try again.");

        }

    } while(opt != 'd');

    return 0;
}