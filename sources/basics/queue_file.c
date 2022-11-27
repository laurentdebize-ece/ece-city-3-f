//
// Created by eleuc on 16/11/2022.
//

#include "../../includes/basics/queue_file.h"

Queue_t *create_queue(void *data){
    Queue_t *queue = malloc(sizeof(Queue_t));
    queue->data = data;
    queue->next = NULL;
    queue->prev = NULL;
    return queue;
}

void add_to_back_queue(Queue_t **queue, void *data){
    if (*queue == NULL){
        *queue = create_queue(data);
        (*queue)->next = *queue;
        (*queue)->prev = *queue;
    }
    else {
        Queue_t *new = create_queue(data);
        (*queue)->prev->next = new;
        new->prev = (*queue)->prev;
        (*queue)->prev = new;
        new->next = (*queue);
    }
}

void add_to_front_queue(Queue_t **queue, void *data){
    if (*queue == NULL){
        *queue = create_queue(data);
        (*queue)->next = *queue;
        (*queue)->prev = *queue;
    }
    else {
        Queue_t *new = create_queue(data);
        new->prev = (*queue);
        new->next = (*queue)->next;
        (*queue)->next->prev = new;
        (*queue)->next = new;
        *queue = new;
    }
}

void retirer_premier_queue(Queue_t **queue){
    Queue_t *tmp = *queue;
    if(tmp->next == tmp || tmp->next == NULL) {
        free(tmp);
        *queue = NULL;
    }
    else {
        tmp->next->prev = tmp->prev;
        tmp->prev->next = tmp->next;
        *queue = tmp->next;
        free(tmp);
    }
}

void free_queue(Queue_t **queue){
    while(*queue != NULL){
        retirer_premier_queue(queue);
    }
}
