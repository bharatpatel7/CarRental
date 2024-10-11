#include "q1.h"

/* function will display the primary user interface
    This is already done for you*/
void prompt(){

  printf("1. Add a new car to the available-for-rent list,\n");
  printf("2. Add a returned car to the available-for-rent list,\n");
  printf("3. Add a returned car to the repair list,\n");
  printf("4. Transfer a car from the repair list to the available-for-rent list,\n");
  printf("5. Rent the first available car,\n");
  printf("6. Print all the lists,\n");
  printf("7. Quit.\n");
  printf("Enter your choice: ");
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
    struct car *new_car = (struct car *)malloc(sizeof(struct car));
    strcpy(new_car->plate, plate);
    new_car->mileage = mileage;
    new_car->return_date = return_date;
    new_car->next = *head;
    *head = new_car;
    return new_car;
}

/**
 * Prints all the cars in the list.
 * @param head Pointer to the head of the list.
 * This function prints out the car details, it should not print return date if it does not exist.
 */
void print_list(struct car *head){
        struct car *temp = head;
    while (temp != NULL) {
        printf("Plate: %s, Mileage: %d", temp->plate, temp->mileage);
        if (temp->return_date != -1) {
            printf(", Return Date: %d", temp->return_date);
        }
        printf("\n");
        temp = temp->next;
    }
    return;
}

/**
 * Checks if a car's plate is already in the list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Boolean value indicating if the plate is found.
 */
bool is_plate_in_list(struct car * head, char plate[]){
    struct car *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->plate, plate) == 0) {
            return true;
        }
        temp = temp->next;
    }
    return false;
    //return true;
}

/**
 * Swaps two cars in the list.
 * @param a Pointer to the first car.
 * @param b Pointer to the second car.
 * Swaps the plate, mileage, and return date of two cars.
 */
void swap(struct car *a, struct car *b){
    struct car temp = *a;
    *a = *b;
    *b = temp;
    //return;
}

/**
 * Sorts the list of cars based on mileage or return date.
 * @param head Pointer to the head of the list.
 * @param sort_by_mileage Boolean to sort by mileage.
 * @param sort_by_return_date Boolean to sort by return date.
 */
void sort_list(struct car ** head, bool sort_by_mileage, bool sort_by_return_date){
    struct car *i, *j;
    for (i = *head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if ((sort_by_mileage && i->mileage > j->mileage) ||
                (sort_by_return_date && i->return_date > j->return_date)) {
                swap(i, j);
            }
        }
    }
    //return;
}

/**
 * Removes a car from the list by its plate number.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Pointer to the removed car.
 */
struct car * remove_car_from_list(struct car **head, char plate[]){
    struct car *temp = *head, *prev = NULL;
    while (temp != NULL && strcmp(temp->plate, plate) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return NULL; // Car not found
    if (prev == NULL) *head = temp->next; // Car is head
    else prev->next = temp->next;
    return temp;
    //return NULL;
}

/**
 * Removes the first car from the list.
 * @param head Pointer to the head of the list.
 * @return Pointer to the removed car.
 */
struct car * remove_first_from_list(struct car **head){
    if (*head == NULL) return NULL;
    struct car *temp = *head;
    *head = (*head)->next;
    return temp;
    //return NULL;
}

/**
 * Calculates the profit based on the mileage difference.
 * @param initial_mileage Integer representing the car's starting mileage.
 * @param final_mileage Integer representing the car's final mileage.
 * @return Double value representing the calculated profit.
 */
double profit_calculator(int initial_mileage, int final_mileage){
    int distance = final_mileage - initial_mileage;
    if (distance <= 200) {
        return 80.00;
    }
    return 80.00 + 0.15 * (distance - 200);
    //return 0.00;
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
    struct car *temp = head;
    while (temp != NULL) {
        fprintf(file, "%s,%d,%d\n", temp->plate, temp->mileage, temp->return_date);
        temp = temp->next;
    }
    fclose(file);
    //return;
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
    if (file == NULL) return;
    char plate[7];
    int mileage, return_date;
    while (fscanf(file, "%6s,%d,%d", plate, &mileage, &return_date) != EOF) {
        insert_to_list(head, plate, mileage, return_date);
    }
    fclose(file);
    //return;
}

/**
 * Prints the date in the format of year/month/day.
 * @param date Integer representing the date in YYMMDD format.
 */
void date(int date){
    printf("Date: %d/%d/%d\n", date / 10000, (date / 100) % 100, date % 100);
}

/**
 * Frees all the memory allocated for the cars in the list.
 * @param head Pointer to the head of the list.
 * Frees each car node in the list.
 */
void free_list(struct car ** head) {
    struct car *temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    //return;
}
