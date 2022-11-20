//
// Created by eleuc on 16/11/2022.
//

#ifndef PROJET_QUEUE_FILE_H
#define PROJET_QUEUE_FILE_H

#include <stdlib.h>

typedef struct Queue_t{
    void *data;
    struct Queue_t *next;
    struct Queue_t *prev;
}Queue_t;

Queue_t *create_queue(void *data);

void add_queue(Queue_t *queue, void *data);

void retirer_premier_queue(Queue_t **queue);

void free_queue(Queue_t **queue);

#endif //PROJET_QUEUE_FILE_H
