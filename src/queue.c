#include "../inc/pathfinder.h"

int peek(pQueue** head) { 
    return (*head)->priority; 
} 

void pop(pQueue **head) { 
    pQueue *temp = *head; 
    (*head) = (*head)->next; 
    free(temp); 
} 

void push(pQueue **head, pNode *node) { 
    pQueue *start = (*head); 
    pQueue* temp = new_pqNode(node); 

    if((*head) == NULL) {
        (*head) = temp;
        return;
    }    

    if ((*head)->priority > node->full_dist) {         
        temp->next = *head; 
        (*head) = temp; 
    } 
    else { 
        while (start->next != NULL && 
                start->next->priority < node->full_dist) { 
            start = start->next; 
        }

        temp->next = start->next; 
        start->next = temp; 
    }
} 

int isEmpty(pQueue **head) { 
    return (*head) == NULL; 
} 
