#include "q1.h"

/*
 * A basic menu based structure has been provided
*/

int main(){

    //Our three Linked Lists
    struct car *available_head = NULL;
	struct car *rented_head = NULL;
	struct car *repair_head = NULL;

    read_file_into_list("available.txt", &available_head);
    read_file_into_list("rented.txt", &rented_head);
    read_file_into_list("repair.txt", &repair_head);

    int choice;

    do
    {
        prompt();

        printf("Enter a Choice: ");
        scanf("%d", &choice);
        char plate[7];
        int mileage, return_date;
        
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
                printf("Enter plate number and mileage: ");
                scanf("%s %d", plate, &mileage);
                if (!is_plate_in_list(available_head, plate)) {
                    insert_to_list(&available_head, plate, mileage, -1);
                    sort_list(&available_head, true, false);
                    printf("Car added to available-for-rent list.\n");
                } else {
                    printf("Error: Duplicate plate number.\n");
                }
                break;

            case 2:
                printf("Enter plate number and mileage: ");
                scanf("%s %d", plate, &mileage);
                if (is_plate_in_list(rented_head, plate)) {
                    struct car *returned_car = remove_car_from_list(&rented_head, plate);
                    insert_to_list(&available_head, plate, mileage, -1);
                    sort_list(&available_head, true, false);
                    double charge = profit_calculator(returned_car->mileage, mileage);
                    printf("Car returned to available-for-rent. Charge: $%.2f\n", charge);
                } else {
                    printf("Error: Car not found in rented list.\n");
                }
                break;

            case 3:
                printf("Enter plate number and mileage: ");
                scanf("%s %d", plate, &mileage);
                if (is_plate_in_list(rented_head, plate)) {
                    remove_car_from_list(&rented_head, plate);
                    insert_to_list(&repair_head, plate, mileage, -1);
                    printf("Car added to repair list.\n");
                } else {
                    printf("Error: Car not found in rented list.\n");
                }
                break;

            case 4:
                printf("Enter plate number: ");
                scanf("%s", plate);
                if (is_plate_in_list(repair_head, plate)) {
                    struct car *repaired_car = remove_car_from_list(&repair_head, plate);
                    insert_to_list(&available_head, plate, repaired_car->mileage, -1);
                    sort_list(&available_head, true, false);
                    printf("Car transferred from repair to available-for-rent list.\n");
                } else {
                    printf("Error: Car not found in repair list.\n");
                }
                break;

            case 5:
                printf("Enter return date (yymmdd): ");
                scanf("%d", &return_date);
                struct car *rented_car = remove_first_from_list(&available_head);
                if (rented_car != NULL) {
                    insert_to_list(&rented_head, rented_car->plate, rented_car->mileage, return_date);
                    sort_list(&rented_head, false, true);
                    printf("Car rented: %s\n", rented_car->plate);
                } else {
                    printf("No cars available for rent.\n");
                }
                break;

            case 6:
                printf("Available-for-rent cars:\n");
                print_list(available_head);
                printf("Rented cars:\n");
                print_list(rented_head);
                printf("Cars in repair:\n");
                print_list(repair_head);
                break;

            case 7:
                // Write to files and exit
                write_list_to_file("available.txt", available_head);
                write_list_to_file("rented.txt", rented_head);
                write_list_to_file("repair.txt", repair_head);
                printf("Data saved. Exiting program.\n");
                free_list(&available_head);
                free_list(&rented_head);
                free_list(&repair_head);
                return 0;
        
        default:
            printf("Error: Invalid choice. Please enter a number between 1 and 7.\n");
                break;
        }
        
    } while (true);
    

    return 0;
}