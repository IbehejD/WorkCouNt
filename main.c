#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// Aplication menu
void vypis_menu(void)
{
    printf("Welcome to WorkCoutNt app");
    printf("\n\n");
    printf("1 - Add training\n");
    printf("2 - Print trainings\n");
    printf("3 - Konec\n");
    printf("\n");
    printf("Your choice: ");
}

// Vyžádá si od uživatele data osoby a tu následně přidá do seznamu
void enter_training(training_list_t *training_list_p)
{    
    training_t *training_p = make_training();
    add_training(training_list_p, training_p);


    printf("\nDay: ");
    scanf("%d", &training_p->date.day);
    printf("Month: ");
    scanf("%d", &training_p->date.month);
    printf("Year: ");
    scanf("%d", &training_p->date.year);
    
    char answer = ' ';
    exercise_t ex_buffer[20];
    int exercise_count = 0;

    while (answer != '0'){
        printf("\n0 - No\n");
        printf("1 - Yes\n\n");

        printf("Want you add exercise?: ");
        scanf(" %c", &answer);

        if (answer == '1'){

            char name[51];
            printf("\nName of exexrcise: ");
            scanf("%50s", name);

            ex_buffer[exercise_count].name_p = make_string(name);


            printf("Series: ");
            scanf("%d", &ex_buffer[exercise_count].series);
            printf("Repetitions: ");
            scanf("%d", &ex_buffer[exercise_count].repetitions);

            printf("\nExercise saved\n\n");

            exercise_count++;
        }

        if(exercise_count == 20){
            printf("Maximum amount of exercises was reached");
            break;
        }
    }

    exercises_lists_t *exercises_list_p;
    exercises_list_p = malloc(exercise_count*sizeof(exercise_t));
    exercises_list_p->count = exercise_count;

    for(int i = 0; i < exercise_count; i++){
        exercises_list_p->arr[i] = ex_buffer[i];
    }
    

    training_p->exercises_list_p = exercises_list_p;
    printf("Training was saved!\n");
}

void wait()
{
    printf("\nTo continue press enter...");
    while (!getchar()) { } // Empty bufferu
    getchar();
}

int main(void) {
    // Make new training list
    training_list_t *training_list_p = make_training_list();
    
    // MENU
    char answer = ' ';
    while (answer != '3')
    {
        vypis_menu();
        scanf(" %c", &answer);
        switch (answer){
            case '1': // Add training
                enter_training(training_list_p);
                break;
            case '2': // Print trainings
                print_training_list(training_list_p);                
                wait();
                break;
            default:
                printf("error");
        }
    }
    // free memory
    free_training_list(training_list_p);

    return 0;
}