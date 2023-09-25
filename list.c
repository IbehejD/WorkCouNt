#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define NDEBUG

/**
Fuction wich makes training list storing all trainings
*/
training_list_t *make_training_list()
{
    training_list_t *training_list_p = (training_list_t *) malloc(sizeof(training_list_t));

    if (training_list_p == NULL)
    {
        printf("Out of memory. Can not make training_list_t.\n");
        exit(1);
    }

    training_list_p->head_p = NULL;
    training_list_p->tail_p = NULL;
    return training_list_p;
}

/**
Function wich makes free training list
*/
void free_training_list(training_list_t *training_list_p)
{
    training_t *curr_p = training_list_p->head_p;
    training_t *old_p;

    //iterating over all trainings
    while (curr_p != NULL)
    {   
        old_p = curr_p;
        curr_p = curr_p->next_p;

        for (int i = 0; i < old_p->exercises_list_p->count; i++){
            free(old_p->exercises_list_p->arr[i].name_p);
        }

        free(old_p->exercises_list_p->arr); //free list of exercises in training
        free(old_p); //free training
    }

    free(training_list_p); // free list
}

/**
Function which makes training 
*/
training_t *make_training() //TODO remove training???
{
    training_t *training_p = (training_t *) malloc(sizeof(training_t));
    if (training_p == NULL)
    {
        printf("Out of memory. Can not make training_p.\n");
        exit(1);
    }
    return training_p;
}

/**
Function which adds training to training list
*/
void *add_training(training_list_t *training_list_p, training_t *training_p){
    // Training list is not empty
    if (training_list_p->tail_p != NULL)
    {
        training_list_p->tail_p->next_p = training_p; // Connect last training to new training
        training_p->prev_p = training_list_p->tail_p; // Connect new training to last before training
        training_list_p->tail_p = training_p; // Save new training
    }
    else // Training list is empty
    {
        training_p->prev_p = NULL; // No training before
        training_list_p->head_p = training_p; // adding training into list 
        training_list_p->tail_p = training_p;
    }

    training_p->next_p = NULL;
}

char* make_string(char *source_p)
{
    char* target_p = (char *) malloc(sizeof(char) * (strlen(source_p) + 1));
    strcpy(target_p, source_p);
    return target_p;
}

/**
Function which print training list
*/
void print_training_list(training_list_t *training_list_p)
{
    training_t *curr_p = training_list_p->head_p;

    while (curr_p != NULL)
    {
        // training date print
        printf("%d.%d.%d:\n\n", curr_p->date.day, curr_p->date.month, curr_p->date.year);

        // printing exercises
        for(int i = 0; i<curr_p->exercises_list_p->count; i++){ 
            char *name = curr_p->exercises_list_p->arr[i].name_p;
            int series = curr_p->exercises_list_p->arr[i].series; 
            int rep = curr_p->exercises_list_p->arr[i].repetitions;
            printf("%s s:%d r:%d\n", name, series, rep);
        }

        printf("--------------------------\n");
        curr_p = curr_p->next_p; //next training
    }
}

#ifndef NDEBUG
#define EXERCISES_COUNT 3

int main(void)
{
    training_list_t * training_list_p = make_training_list();

    for(int i = 0; i<3; i++){
        training_t *training_p = make_training();
        add_training(training_list_p, training_p);

        training_p->date.day = 1; 
        training_p->date.month = 1;
        training_p->date.year = 2000;

        exercises_lists_t *exercises_list_p;
        exercise_t *exercises_p;

        exercises_p = malloc(EXERCISES_COUNT * sizeof(exercise_t));

        if (exercises_p == NULL) {
            printf("Out of memory. Can not make training_p.\n");
            exit(1);
        }

        exercises_list_p->arr = exercises_p;
        exercises_list_p->count = EXERCISES_COUNT;

        for(int i = 0; i<EXERCISES_COUNT; i++){
            exercises_list_p->arr[i].name_p = "push-up";
            exercises_list_p->arr[i].repetitions = 12;
            exercises_list_p->arr[i].series = 3;
        }

        training_p->exercises_list_p = exercises_list_p;

    }

    print_training_list(training_list_p);
    free_training_list(training_list_p);

    return 0;
}

#endif 