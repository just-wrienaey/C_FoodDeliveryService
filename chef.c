void chefMenu(){

    printf("Good day chef!!\n\n");

    char opt;

    do{
        
        printf("Choose an action below: \n");
        printf("[a] receive order\n");
        printf("[b] cook n dishes\n");
        printf("[c] pack order\n");
        printf("[d] exit\n");

        scanf(" %c", &opt);

        switch(opt){
            // case 'a':
            //     receiveOrder();
            //     break;
            // case 'b':
            //     cook();
            //     break;
            // case 'c':
            //     packOrder();
            //     break;
            case 'd':
                printf("Returning to main menu. . .");
                break;
            default:
                printf("Invalid input. Please try again.");
        }

    }while(opt != 'd');

}