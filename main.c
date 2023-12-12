// December 12, 2023 
// 2:20pm - 9:40pm meals and breaks included approx. 5 hours (main and customer)
// 10pm - 11pm (manager 80%)

#include <stdio.h>
#include "customer.c"
#include "chef.c"

int main(){
    char opt;

    Customer customer[MAX_CUSTOMERS]; //without typedef, this is "struct Customer customer"

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
                customerMenu(customer, menu);
                break;
            case 'b':
                managerMenu(customer, menu);
                break;
            case 'c':
                chefMenu(menu);
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