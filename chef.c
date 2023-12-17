//Created by: KHAN, Renee Althea F.

/*
    ACTIONS:

    • Receives Order. Commands the Chef to accept the order from the Manager. This must be chosen first before Cook N Dishes task. 
    • Cook N dishes. The chef chooses the first N dishes from the list of pending order and cooks them. N must be inputted at the beginning of the program where N can be from 1 to 3. 
    • Pack Food. Packs the cooked ordered dish and sends to the manager. This should remove the dish from the list of pending order
    • Exit. Exits chef action and returns to the Main Menu.
*/



#include "manager.c"

void receiveOrder(Customer customer[], PendingOrders pending[]){

    int i = 0, j;
    bool found = false;

    printf("\n\n%s%sRECEIVE ORDERS%s%s\n\n", "~~~~~~~~~~", "~~~~~~~~~~", "~~~~~~~~~~","~~~~~~~~~~");
    if(customer[0].customerNum==-1)
        printf("There are no orders yet!");
    else{

        while(pending[i].customerNum!=-1){

            if(pending[i].code!=0){
                printf("Preparing %s for customer # %d. . .\n", pending[i].name, customer[pending[i].customerNum-1].customerNum);
                found = true;

                for(j=0; j<MAX_ORDERS; j++){
                    
                    if(found==true)
                        if (customer[pending[i].customerNum-1].orders[j].code == pending[i].code && strcmp(customer[pending[i].customerNum-1].orders[j].status, "Sent to chef")==0){
                            strcpy(customer[pending[i].customerNum-1].orders[j].status, "Preparing");
                            found = true;
                        }

                }
            }

            i++;

        }

    }


}

int cook(int currentCustomers, Customer customer[]){

    int i, j, n;

    printf("\n\n%s%sCOOK ORDERS%s%s\n\n", "~~~~~~~~~~", "~~~~~~~~~~", "~~~~~~~~~~","~~~~~~~~~~");
    if(customer[0].customerNum==-1)
        printf("There are no orders received yet!");
    else{

        printf("How many dishes can you cook? \n");
        scanf(" %d", &n);

        for(i=0; i<currentCustomers; i++){

            for(j=0; j<MAX_ORDERS; j++){
                if(strcmp(customer[i].orders[j].status,"Preparing") == 0){
                    strcpy(customer[i].orders[j].status,"Cooking");
                    printf("Cooking %s for customer # %d. . .\n", customer[i].orders[j].name, customer[i].customerNum);
                    n--;

                    if(n==0){
                        return 0;
                    }

                }
            }
        }

    }

    return -1;

}

void packOrder(int currentCustomers, Customer customer[]){

    int i, j;

    printf("\n\n%s%sPACK ORDERS%s%s\n\n", "~~~~~~~~~~", "~~~~~~~~~~", "~~~~~~~~~~","~~~~~~~~~~");
    if(customer[0].customerNum==-1)
        printf("There are no orders yet!");
    else{

        for(i=0; i<currentCustomers; i++){

            for(j=0; j<MAX_ORDERS; j++){
                if(strcmp(customer[i].orders[j].status,"Cooking") == 0){
                    strcpy(customer[i].orders[j].status,"Packed");
                    strcpy(customer[i].status,"Order is on the way!");
                    printf("Packing %s for customer # %d. . .\n", customer[i].orders[j].name, customer[i].customerNum);

                }
            }
        }

    }


}

void chefMenu(int currentCustomers, Customer customer[], PendingOrders pending[]){

    printf("\nGood day chef!!");

    char opt;
    int result;

    do{
        
        printf("\n\nChoose an action below: \n");
        printf("[a] receive order\n");
        printf("[b] cook n dishes\n");
        printf("[c] pack order\n");
        printf("[d] exit\n");

        scanf(" %c", &opt);

        switch(opt){
            case 'a':
                receiveOrder(customer, pending);
                break;
            case 'b': 
                if (cook(currentCustomers, customer) == 0)
                    printf("Finished cooking!");
                break;
            case 'c':
                packOrder(currentCustomers, customer);
                break;
            case 'd':
                printf("Returning to main menu. . .\n");
                break;
            default:
                printf("Invalid input. Please try again.\n");
        }

    }while(opt != 'd');

}
