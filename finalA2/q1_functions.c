#include "q1.h"


/* function will display the primary user interface
    This is already done for you*/
void prompt(void){

  printf("1. Add a new car to the available-for-rent list,\n");
  printf("2. Add a returned car to the available-for-rent list,\n");
  printf("3. Add a returned car to the repair list,\n");
  printf("4. Transfer a car from the repair list to the available-for-rent list,\n");
  printf("5. Rent the first available car,\n");
  printf("6. Print all the lists,\n");
  printf("7. Quit.\n");
  //printf("Enter your choice: ");
  //scanf("%d", &choice);
}

/**
 * Inserts a new car into the linked list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @param mileage Integer representing the car's mileage.
 * @param return_date Integer representing the car's return date, you can have -1 represent no return date.
 * @return Pointer to the newly added car in the list.
 */
struct car * insert_to_list(struct car ** head, char plate[], int mileage, int return_date){
    struct car *new_car = malloc(sizeof(struct car));
    strcpy(new_car->plate, plate);
    new_car->mileage = mileage;
    new_car->return_date = return_date;
    new_car->next = NULL;
    new_car->next = *head;
    *head = new_car;
    return new_car;
}


void rent_first_available_car(struct car **available_head, struct car **rented_head){
    if (*available_head == NULL){
        printf("No car available for rent.\n");
    }

    struct car *car_to_rent = remove_first_from_list(available_head);
    if (car_to_rent == NULL){
        printf("No car available for rent.\n");
        return;
    }

    *rented_head = insert_to_list(rented_head, car_to_rent->plate, car_to_rent->mileage, car_to_rent->return_date);
    printf("Car rented: %s\n", car_to_rent->plate);
    free(car_to_rent);


    
}

/**
 * Prints all the cars in the list.
 * @param head Pointer to the head of the list.
 * This function prints out the car details, it should not print return date if it does not exist.
 */
void print_list(struct car *head){
    while (head != NULL)
    {
        printf("Plate: %s, Mileage: %d", head->plate, head->mileage);
        if (head->return_date != -1)
        {
            printf(", Return Date: %d", head->return_date);
        }
        printf("\n");
        head = head->next;
    }
    
}

/**
 * Checks if a car's plate is already in the list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Boolean value indicating if the plate is found.
 */
bool is_plate_in_list(struct car * head, char plate[]){
    while (head != NULL)
    {
        if (strcmp(head->plate, plate) == 0)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}

/**
 * Swaps two cars in the list.
 * @param a Pointer to the first car.
 * @param b Pointer to the second car.
 * Swaps the plate, mileage, and return date of two cars.
 */
void swap(struct car *a, struct car *b){
    char temp_plate[7];
    int temp_mileage, temp_return_date;

    //swap plates
    strcpy(temp_plate, a->plate);
    strcpy(a->plate, b->plate);
    strcpy(b->plate, temp_plate);

    //swap mileage
    temp_mileage = a->mileage;
    a->mileage = b->mileage;
    b->mileage = temp_mileage;

    //swap return date
    temp_return_date = a->return_date;
    a->return_date = b->return_date;
    b->return_date = temp_return_date;
}

/**
 * Sorts the list of cars based on mileage or return date.
 * @param head Pointer to the head of the list.
 * @param sort_by_mileage Boolean to sort by mileage.
 * @param sort_by_return_date Boolean to sort by return date.
 */
void sort_list(struct car ** head, bool sort_by_mileage, bool sort_by_return_date){
    if (*head == NULL || (*head)->next == NULL){
        return;
    }

    struct car *current, *index;

    for (current = *head; current->next != NULL; current = current->next)
    {
        for (index = current->next; index != NULL; index = index->next)
        {
            if (sort_by_mileage)
            {
                if (current->mileage > index->mileage)
                {
                    swap(current, index);
                }
            }
        }
    }
}


/**
 * Removes a car from the list by its plate number.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Pointer to the removed car.
 */
struct car * remove_car_from_list(struct car **head, char plate[]){
    struct car *prev = NULL, *curr = *head;
    while (curr != NULL && strcmp(curr->plate, plate) != 0)
    {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL)
    {
        return NULL;
    }
    if (prev == NULL)
    {
        *head = curr->next;
    }else{
        prev->next = curr->next;
    }
    return curr;
}

/**
 * Removes the first car from the list.
 * @param head Pointer to the head of the list.
 * @return Pointer to the removed car.
 */
struct car * remove_first_from_list(struct car **head){
    if (*head == NULL)
    {
        return NULL;
    }
    struct car *temp = *head;
    *head = (*head)->next;
    return temp;
}

/**
 * Calculates the profit based on the mileage difference.
 * @param initial_mileage Integer representing the car's starting mileage.
 * @param final_mileage Integer representing the car's final mileage.
 * @return Double value representing the calculated profit.
 */
double profit_calculator(int initial_mileage, int final_mileage){
    double rate_per_milage = 0.1;
    return (final_mileage - initial_mileage) * rate_per_milage;
}

/**
 * Writes the list of cars to a file.
 * The file would be in the format: plate,mileage,return_date
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 * Writes the details of each car in the list to a file.
 */
void write_list_to_file(char *filename, struct car *head){
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file: %s .\n", filename);
        return;
    }

    //struct car *current = head;

    while (head != NULL)
    {
        fprintf(file, "%s,%d,%d\n", head->plate, head->mileage, head->return_date);
        head = head->next;
    }
    fclose(file);
}

/**
 * Reads car details from a file and adds them to the list.
 * The file would be in the format: plate,mileage,return_date
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 * Reads data from the file and inserts each car into the list.
 */
void read_file_into_list(char *filename, struct car **head){
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s .\n", filename);
        return;
    }
    char plate[7];
    int mileage, return_date;
    while(fscanf(file, "%6s,%d,%d\n", plate, &mileage, &return_date) == 3){
        insert_to_list(head, plate, mileage, return_date);
    }
    fclose(file);
}

/**
 * Prints the date in the format of year/month/day.
 * @param date Integer representing the date in YYMMDD format.
 */
void date(int date){
    int year = date / 10000;
    int month = (date % 10000) / 100;
    int day = date % 100;

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        printf("Invalid date formate: %d\n", date);
    }
    else
    {
        printf("Date is Valid: Year: %d, Month: %d, Day: %d\n", year, month, day);
    }
}

/**
 * Frees all the memory allocated for the cars in the list.
 * @param head Pointer to the head of the list.
 * Frees each car node in the list.
 */
void free_list(struct car ** head){
    struct car *temp;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

