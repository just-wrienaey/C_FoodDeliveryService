//Created by: KHAN, Renee Althea F.

/*
    ACTIONS: 
    • Display the Menu for the Day. Displays the menu of dishes for the day and the price.

    • Send Order to Chef. The ordered food from the customer are added to the list of pending order and at the same time sent to the chef. Most recent order is added last in the list.

    • List Pending Order. Displays ordered dish that are not prepared/cooked yet with the corresponding dish number code and customer number who ordered the dish.

    • List Current Customers and ordered food. Displays customer number and ordered food of current customers. Previous customers should not be displayed.
    
    • Send Driver. Sends the driver to deliver food to the customer.

    • Display Income for the Day. Displays the number of customers who paid, the total amount paid, and the total income for the day.

    • Display the Dishes Served for the Day. Displays the number of ordered dishes for the day with code and the price per dish. 

    • Close the restaurant. Manager opts to close the restaurant whether it has reached the maximum number of customers (up to 10) or not.
    
    • Exit. Exits waiter action and returns to the Main Menu. 

*/


#include "header.h"

void displayMenu()
{
	/*formatting: count spaces of the last string (price) by subracting the no. of characters from the dish string (e.g. "clubhouse") 
	from 13 and adding two (spaces) and the number of characters of the price string (e.g. "Php 95.00").*/
	printf("--------------TODAY'S MENU--------------\n\n");
	   
    printf("SNACK\n");
    printf("%s \t %s  %11s \n", "1100", "Burger w Fries", "Php 120.00");
    printf("%s \t %s  %15s \n", "1200", "Clubhouse", "Php 95.00"); 
    printf("%s \t %s  %11s \n\n", "1300", "Hotdog on Bun", "Php 75.00");

	printf("PASTA\n");
    printf("%s \t %s  %16s \n", "2100", "Spaghetti", "Php 150.00"); 
    printf("%s \t %s  %18s \n", "2200", "Lasagna", "Php 240.00");
    printf("%s \t %s  %12s \n\n", "2300", "Mac 'n Cheese", "Php 110.00"); 
	
	printf("DRINK\n");
    printf("%s \t %s  %20s \n", "3100", "Coke", "Php 50.00"); 
    printf("%s \t %s  %16s \n", "3200", "Iced tea", "Php 45.00"); 
    printf("%s \t %s  %12s \n", "3300", "Orange Juice", "Php 45.00");
    
    printf("%s%s%s%s \n", "----------", "----------", "----------", "----------");
}

void sendOrderToChef(int currentCustomers, Customer customer[], PendingOrders pending[]){

    printf("\n\n%s%sSENDING ORDERS TO CHEF%s%s\n\n", "~~~~~~~~~~", "~~~~~~~~~~", "~~~~~~~~~~","~~~~~~~~~~");

    int i, j, k=0;
    bool found = false;

    for(i=0; i<currentCustomers; i++){

        for(j=0; j<MAX_ORDERS; j++){
            if(strcmp(customer[i].orders[j].status,"Pending")==0 && strcmp(customer[i].status,"Waiting")==0){
                printf("%d \t %s \t (customer # %d)\n", customer[i].orders[j].code, customer[i].orders[j].name, customer[i].customerNum);
                pending[k].code = customer[i].orders[j].code;
                strcpy(pending[k].name, customer[i].orders[j].name);
                pending[k].customerNum = customer[i].customerNum;
                k++; // added: December 14, 2023 // bug fixed: only one dish is sent to chef
                strcpy(customer[i].orders[j].status,"Sent to chef"); //added: December 14, 2023; avoid resending orders
                found = true;
            }

        }
        
    }

    if(!found)
        printf("No orders to send at the moment");


}

void listPendingOrders(int currentCustomers, Customer customer[]){

    //Display: order, order code, customer
    //Orders that are not prepared or cooked yet: status != cooking/packed

    printf("\n\n%s%sPENDING ORDERS%s%s\n\n", "~~~~~~~~~~", "~~~~~~~~~~", "~~~~~~~~~~","~~~~~~~~~~");

    int i, j;
    bool found = false;

    for(i=0; i<currentCustomers; i++){

        for(j=0; j<MAX_ORDERS; j++){
            if(strcmp(customer[i].orders[j].status,"Packed")!=0 && customer[i].orders[j].code!=-1){
                printf("%-10s \t %d \t %-11s \t (customer # %d)\n", customer[i].orders[j].status, customer[i].orders[j].code, customer[i].orders[j].name, customer[i].customerNum);
                found = true;
            }

        }
        
    }

    if(!found)
        printf("No pending orders at the moment");

}

void listCurrentCustomers(int currentCustomers, Customer customer[]){

    //Display: customer number (+ name), ordered food (+ order code) 
    //only current: status == booking/waiting

    printf("\n\n%s%sCURRENT CUSTOMER%s%s\n\n", "~~~~~~~~~~", "~~~~~~~~~~", "~~~~~~~~~~","~~~~~~~~~~");

    int i, j;

    for(i=0; i<currentCustomers; i++){
        if(strcmp(customer[i].status, "Received Order")!=0){
            printf("Customer # %d \t Name: %s \n", customer[i].customerNum, customer[i].name);
            
            for(j=0; j<MAX_ORDERS; j++){

                if (customer[i].orders[j].code!=-1)
                    printf("\t %d \t %s \n", customer[i].orders[j].code, customer[i].orders[j].name);
            }

            printf("\n");

        }
    }


}

void sendDriver(int currentCustomers, Customer customer[]){

    int i, j;
    int orderCounter, packed;

    printf("\n\n%s%sSEND DRIVER%s%s\n\n", "~~~~~~~~~~", "~~~~~~~~~~", "~~~~~~~~~~","~~~~~~~~~~");

    for(i=0; i<currentCustomers; i++){

        orderCounter = 0;
        packed = 0;
        if(strcmp(customer[i].status, "Received Order")!=0){
            for(j=0; j<MAX_ORDERS; j++){

                if(customer[i].orders[j].code!=-1){
                    orderCounter++;
                    //printf(" %s:\t", customer[i].orders[j].name); // debugging purposes
                    if (strcmp(customer[i].orders[j].status,"Packed")==0){
                        //printf(" %s", customer[i].orders[j].name); // debugging purposes
                        packed++;
                    }
                }

                //printf("\n"); // debugging purposes
                    
            }

            if(orderCounter == packed){ 
                for(j=0; j<orderCounter; j++){ // Dec 14, 2023: added loop; updates order status 
                    strcpy(customer[i].orders[j].status, "Delivered");
                }
                strcpy(customer[i].status, "Received Order"); // Dec 14, 2023: updated strcmp to strcpy
                printf("Driver sent. Delivering order to customer # %d . . .", customer[i].customerNum);
            }

        }

    }

}

void displayIncome(int currentCustomers, Customer customer[]){

    //Display: total customers, amount paid per customer, total income
    printf("\n\n%s%sDISPLAY INCOME%s%s\n\n", "~~~~~~~~~~", "~~~~~~~~~~", "~~~~~~~~~~","~~~~~~~~~~");

    int i, paidCustomers = 0;
    float totalIncome = 0;
    bool found=false;

    if(customer[0].customerNum==-1)
        printf("There are no customers yet!\n");
    else{

        printf("Transaction History: \n");
        for(i=0; i<currentCustomers; i++){
            if(strcmp(customer[i].status, "Received Order")==0){
                printf("Customer # %d \t Amount Paid: %.2f \n", customer[i].customerNum, customer[i].totalBill);

                totalIncome += customer[i].totalBill;
                paidCustomers++;
                found = true;
            }
        }

        printf("Total Customers: %d \t Total Income: %.2f \n", paidCustomers, totalIncome);
    }

    if(!found)
        printf("No food delivered at the moment.\n");

}

void displayDishesServed(int currentCustomers, Menu menu[], Customer customer[]){
    //Displays the number of ordered dishes for the day with code and the price per dish.

    int i, j, code;
    int qty[9] = {0,0,0,0,0,0,0,0,0};

    printf("\n\n%s%sDISPLAY DISHES SERVED%s%s\n\n", "~~~~~~~~~~", "~~~~~~~~~~", "~~~~~~~~~~","~~~~~~~~~~");


    for(i=0; i<currentCustomers; i++){

        if(strcmp(customer[i].status,"Received Order")==0)
            //printf("%s \t", customer[i].status); //debugging purposes
            for(j=0; j<MAX_ORDERS; j++){
                //printf("%s \t %s\n", customer[i].orders[j].name, customer[i].orders[j].status); //debugging purposes
                if(strcmp(customer[i].orders[j].status,"Delivered")==0){ // Dec. 14, 2023 // updated Packed --> Delivered

                    code = customer[i].orders[j].code;
                    switch(code){
                        case 1100:
                            qty[1]++;
                            break;
                        case 1200:
                            qty[2]++;
                            break;
                        case 1300:
                            qty[3]++;
                            break;
                        case 2100:
                            qty[4]++;
                            break;
                        case 2200:
                            qty[5]++;
                            break;
                        case 2300:
                            qty[6]++;
                            break;
                        case 3100:
                            qty[7]++;
                            break;
                        case 3200:
                            qty[8]++;
                            break;
                        case 3300:
                            qty[9]++;
                            break;

                    }
                    
                }

            }
            
        }

    for(i=0; i<9; i++){
        if(qty[i]!=0){
           printf("%d \t Php %.2f \t (%d)\n", menu[i].code, menu[i].price, qty[i]); 
        }
    }
}

bool closeResto(){

    printf("\n\n~ ~ ~ RESTAURANT IS CLOSED ~ ~ ~\n\n");
    return true;
}

bool managerMenu(int currentCustomers, Customer customer[], Menu menu[], PendingOrders pending[]){

    printf("\nGood day manager!!");

    char opt;

    bool close = false;

    do{

        printf("\n\nChoose an action below: \n");
        printf("[a] display menu of the day\n");
        printf("[b] send order to chef\n");
        printf("[c] list pending orders\n");
        printf("[d] list current customers and ordered food\n");
        printf("[e] send driver to deliver food\n");
        printf("[f] display income for the day\n");
        printf("[g] display dishes served for the day\n");
        printf("[h] close restaurant\n");
        printf("[i] exit\n");

        scanf(" %c", &opt);


        switch(opt){
            case 'a':
                displayMenu();
                break;
            case 'b':
                sendOrderToChef(currentCustomers, customer, pending);
                break;
            case 'c':
                listPendingOrders(currentCustomers, customer);
                break;
            case 'd':
                listCurrentCustomers(currentCustomers, customer);
                break;
            case 'e':
                sendDriver(currentCustomers, customer);
                break;
            case 'f':
                displayIncome(currentCustomers, customer);
                break;
            case 'g':
                displayDishesServed(currentCustomers, menu, customer);
                break;
            case 'h':
                close = closeResto();
                break;
            case 'i':
                printf("Returning to main menu. . .\n");
                break;
            default:
                printf("Invalid input. Please try again.\n");
        }

    }while( opt != 'i');

    return close;

}
