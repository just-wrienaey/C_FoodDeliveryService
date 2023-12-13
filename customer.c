



/*

    ACTIONS:

    ORDER: 
        maximum of 3 dishes
        not taken if current number of customers is 5 or if Resto is closed

    PAY:
        pay through e-wallet
        show bill

    DISPLAY STATUS:
        "booking" - when placing an order
        "waitng" - order is paid & food is being prepared
        "received order" - when order is received & delivered

*/

#include "chef.c"

int isOrderValid(Menu menu[], int orderCode){
    int i;
    for(i=0; i<9; i++)
        if(menu[i].code == orderCode)
            return i;
    
    return -1;
}

void displayOrders(Customer customer){

    int i;

    printf("%s%s%s%s\n", "----------", "----------", "----------", "----------");
    printf("%s%sORDERS%s%s\n", "       ", "          ", "          ", "       ");
    printf("%s%s%s%s\n\n", "----------", "----------", "----------", "----------");

    printf("%s \t %s  %16s \n", "code", "item", "price");

    for(i=0; i<MAX_ORDERS; i++){

        if( customer.orders[i].code != -1){
            printf("%d \t %-15s  %s%.2f \n", customer.orders[i].code, customer.orders[i].name, "Php ", customer.orders[i].price);

        }
    }

    
    printf("%s%s%s%s\n\n", "----------", "----------", "----------", "----------");
}

void order(Menu menu[], int customerNum, Customer customer[]){

    printf("\n\n%s%sORDER FOOD%s%s\n\n", "~~~~~~~~~~", "~~~~~~~~~~", "~~~~~~~~~~","~~~~~~~~~~");

    char customerName[50];
    int order;
    int orderIndices[MAX_ORDERS];
    int a;
    for(a=0; a<MAX_ORDERS; a++){
        orderIndices[a] = -1;
    }

    bool valid = 1;

    displayMenu();
    printf("Enter customer name: \n");
    scanf(" %s", customer[customerNum].name);

    customer[customerNum].customerNum = customerNum + 1;

    printf("You are customer #%d\n", customer[customerNum].customerNum );

    int counter = 0;
    do{
        printf("\nEnter the code of your order: (enter \"0\" when done) \n");
        scanf(" %d", &order);

        if (order == 0){
            if(orderIndices[0] == -1){
                printf("Please place an order");
            }else{
                printf("Order's complete!\n");
                valid = false;
            }
            
        }
        else if(isOrderValid(menu, order)!=-1){
            orderIndices[counter] = isOrderValid(menu, order);
            counter++;
        } else 
            printf("Invalid order code.");
        
        if(counter==MAX_ORDERS)
            valid = false;

    } while (valid);
    
    int i;
    customer[customerNum].totalBill = 0;
    for(i=0; i<MAX_ORDERS; i++){
        if( orderIndices[i] != -1){
            strcpy(customer[customerNum].orders[i].status, "Pending");
            customer[customerNum].orders[i].code = menu[orderIndices[i]].code;
            customer[customerNum].orders[i].price = menu[orderIndices[i]].price;
            strcpy(customer[customerNum].orders[i].name, menu[orderIndices[i]].name );
            customer[customerNum].totalBill += menu[orderIndices[i]].price;
        }
    }

    displayOrders(customer[customerNum]);
    strcpy(customer[customerNum].status, "Booking");

    printf("Orders placed! Please proceed to payment. \nReturning to customer menu. . .\n");

 }

void pay(Customer customer[], int currentCustomers){

    printf("\n\n%s%sPAY BILL%s%s\n\n", "~~~~~~~~~~", "~~~~~~~~~~", "~~~~~~~~~~","~~~~~~~~~~");
    int custNum;
    float payment = 0;
    char opt;
    printf("Enter customer number: ");
    scanf(" %d", &custNum);


    if(custNum<1 || custNum>currentCustomers)
        printf("Customer does not exist!");
    else{
        
        custNum--; //decrement to get index

        if(strcmp(customer[custNum].status, "Booking")!=0)
            printf("You have already paid.");
        else{

            printf("Your total bill is %.2f\n\n", customer[custNum].totalBill);

            do{

                printf("Check your orders? \n[Y] yes \t[N] no\n");
                scanf(" %c", &opt);

                switch(opt){
                    case 'Y':
                        displayOrders(customer[custNum]);
                    case 'N':
                        do{

                            printf("Enter payment: ");
                            scanf(" %f", &payment);

                            float change = payment - customer[custNum].totalBill;

                            if(change < 0)
                                printf("PAYMENT NOT ACCEPTED. Please pay the exact amount! \n");
                            else if (change>0){
                                printf("Change: %.2f\n", change);
                                strcpy(customer[custNum].status, "Waiting");
                            }
                            else
                            {
                                printf("Exact amount paid.\n"); 
                                strcpy(customer[custNum].status, "Waiting");
                            }
                                

                        }while(customer[custNum].totalBill>payment);
                        break;
                    default:
                        printf("Invalid input. Please try again");

                }

            }while(opt!='Y' && opt!='N');


        }

    }


}

void displayCustomerStatus(Customer customer[], int currentCustomers){

    int custNum;

    printf("\n\n%s%sDISPLAY STATUS%s%s\n\n", "~~~~~~~~~~", "~~~~~~~~~~", "~~~~~~~~~~","~~~~~~~~~~");
    printf("Enter customer number: ");
    scanf(" %d", &custNum);

    if(custNum<1 || custNum>currentCustomers)
        printf("Customer does not exist!");
    else{

        custNum--; //decrement to get index

        printf("Customer: %s\n", customer[custNum].name);
        printf("Status: %s\n", customer[custNum].status);

    }

}

void displayCustomerNum(Customer customer[]){

    char name[50];
    bool found = false;

    printf("\n\n%s%sDISPLAY NUMBER%s%s\n\n", "~~~~~~~~~~", "~~~~~~~~~~", "~~~~~~~~~~","~~~~~~~~~~");
    printf("Enter your name: ");
    scanf(" %s", name);

    int i;
    for(i=0; i<MAX_CUSTOMERS; i++){
        if(strcmp(name, customer[i].name) == 0){
            printf("You are customer #%d", customer[i].customerNum);
            found = true;
        }
    }

    if(!found){
        printf("Customer not found!");
    }

}

int customerMenu(int currentCustomers, Customer customer[], Menu menu[]){

    printf("\nGood day customer!!");

    int i;
    char opt;
    int pending;

    do{
        
        printf("\n\nChoose an action below: \n");
        printf("[a] order\n");
        printf("[b] pay\n");
        printf("[c] display customer number\n");
        printf("[d] display order status\n");
        printf("[e] exit\n");

        scanf(" %c", &opt);

        pending = 0;
        for(i=0; i<currentCustomers; i++)
            if((customer[i].status,"Order Received")!=0)
                pending++;

        switch(opt){
            case 'a':
                if(currentCustomers<10 && pending<5)
                {
                    order(menu, currentCustomers, customer);
                    currentCustomers ++;
                }
                else if(currentCustomers==10)
                    printf("Max customers reached. Restaurant is closed.");
                else 
                    printf("Restaurant is accommodating too many customers at the moment. Please stand by.");
                break;
            case 'b':
                pay(customer, currentCustomers);
                break;
            case 'c':
                displayCustomerNum(customer);
                break;
            case 'd':
                displayCustomerStatus(customer, currentCustomers);
                break;
            case 'e':
                printf("Returning to main menu. . .\n");
                break;
            default:
                printf("Invalid input. Please try again.\n");
        }

    }while(opt != 'e');

    return currentCustomers;

}