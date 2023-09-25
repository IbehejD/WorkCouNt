#ifndef LIST_H
#define LIST_H

// Exercise
typedef struct exercise {
    char *name_p;
    int repetitions;
    int series;
} exercise_t;

typedef struct exercises_list{
    int count;
    exercise_t *arr; 
} exercises_lists_t;

// Date
typedef struct date{ //TODO opt
    unsigned int day;
    unsigned int month; 
    unsigned int year; 
} date_t;

// Training
typedef struct training {
    date_t date;
    exercises_lists_t *exercises_list_p;
    struct training *next_p; 
    struct training *prev_p; 
} training_t;

// Training list 
typedef struct training_list {
    int count;
    training_t *head_p;
    training_t *tail_p;
} training_list_t;

training_list_t *make_training_list();

void free_training_list(training_list_t *training_list_p);

training_t *make_training(); //TODO remove training???

void add_training(training_list_t *training_list_p, training_t *training_p);

void print_training_list(training_list_t *training_list_p);

char* make_string(char *source_p);

#endif  /* LIST_H */