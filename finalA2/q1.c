#include "q1.h"

/*
 * A basic menu based structure has been provided
*/

int main(void){

    //Our three Linked Lists
    struct car *available_head = NULL;
	struct car *rented_head = NULL;
	struct car *repair_head = NULL;

    int choice;
    char plate[7];
    int mileage;
    double profit;
    struct car *temp_car;

    //Read the data from the file
    read_file_into_list("available.txt", &available_head);
    read_file_into_list("rented.txt", &rented_head);
    read_file_into_list("repair.txt", &repair_head);

    do
    {
        prompt();

        printf("Enter a Choice: ");
        scanf("%d", &choice);
        
        /*
         * You will need to add all the cases
         * Call the appropriate functions
         * You would also need to save data to disc upon exit
         * File Format: plate,mileage,return_date
         * Error Handling needs to happen too
        */

        switch (choice)
        {
        case 1:
            
            printf("Enter the plate number (6 characters): ");
            scanf("%6s", plate);
            printf("Enter the mileage: ");
            scanf("%d", &mileage);
            if (is_plate_in_list(available_head, plate))
            {
                printf("Plate number already exists in the list.\n");
            }
            else
            {
                available_head = insert_to_list(&available_head, plate, mileage, -1);
                printf("Car added to the available-for-rent list.\n");
            }
            
            break;
        
        case 2:
            printf("Enter the plat number (6 characters): ");
            scanf("%6s", plate);
            printf("Enter the mileage: ");
            scanf("%d", &mileage);
            temp_car = remove_car_from_list(&rented_head, plate);
            if (temp_car != NULL){
                profit = profit_calculator(temp_car->mileage, mileage);
                printf("The profit for this car is: %.2lf\n", profit);
                available_head = insert_to_list(&available_head, plate, mileage, -1);
                free(temp_car);
            }else{
                printf("Car not found in the rented list.\n");
            }
            break;

        case 3:
            printf("Enter the plat number of returned car (6 characters): ");
            scanf("%s", plate);
            temp_car = remove_car_from_list(&rented_head, plate);
            if (temp_car != NULL){
                repair_head = insert_to_list(&repair_head, plate, temp_car->mileage, -1);
                printf("Car added to the repair list.\n");
                free(temp_car);
            }else{
                printf("Car not found in the repair list.\n");
            }
            break;

        case 4:
            printf("Enter the plat number of the car to be transferred (6 characters): ");
            scanf("%s", plate);
            temp_car = remove_car_from_list(&repair_head, plate);
            if (temp_car != NULL){
                available_head = insert_to_list(&available_head, plate, temp_car->mileage, -1);
                printf("Car transferred to the available-for-rent list.\n");
                free(temp_car);
            }else{
                printf("Car not found in the repair list.\n");
            }
            break;

        case 5:
            rent_first_available_car(&available_head, &rented_head);
            write_list_to_file("available.txt", available_head);
            write_list_to_file("rented.txt", rented_head);
            break;

        case 6:
            //Print all the lists
            printf("Available-for-rent list:\n");
            print_list(available_head);
            printf("Rented list:\n");
            print_list(rented_head);
            printf("Repair list:\n");
            print_list(repair_head);
            break;

        case 7:
            //quit and save to file
            write_list_to_file("available.txt", available_head);
            write_list_to_file("rented.txt", rented_head);
            write_list_to_file("repair.txt", repair_head);
            free_list(&available_head);
            free_list(&rented_head);
            free_list(&repair_head);
            printf("Data saved! Exiting...\n");
            exit(0);
            break;

        
        default:
            printf("Invalid choice. Please try again.\n");

        }

        
    } while (true);
    

    return 0;
}





