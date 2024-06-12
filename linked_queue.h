#ifndef _LINKED_QUEUE_H
#define _LINKED_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG_INFO(info) printf("file: %s:func: %s:line %d\n%s",__FILE__,__func__,__LINE__,(info))

typedef struct student{
    char* name;
    int ID;
}LQ_ELEM_TYPE;

struct linked_node {
    LQ_ELEM_TYPE* data;
    struct linked_node* next;
};

struct linked_queue {
    struct linked_node* head;
    struct linked_node* tail;
};

struct linked_queue* lqInit ();

bool lqIsEmpty (struct linked_queue* lq);

bool lqIN (struct linked_queue* lq,LQ_ELEM_TYPE* data,bool (* cpData)(LQ_ELEM_TYPE* dst,LQ_ELEM_TYPE* src));

bool lqHead (struct linked_queue* lq,LQ_ELEM_TYPE* data,bool (* cpData)(LQ_ELEM_TYPE* dst,LQ_ELEM_TYPE* src));

bool lqOut (struct linked_queue* lq,LQ_ELEM_TYPE* data,bool (* cpData)(LQ_ELEM_TYPE* dst,LQ_ELEM_TYPE* src),void (* clearData)(LQ_ELEM_TYPE* data));

LQ_ELEM_TYPE* lqFirst (struct linked_queue* lq);

void lqDestroy (struct linked_queue* lq,void (* clearData)(LQ_ELEM_TYPE* data));


#endif /*_LINKED_QUEUE_H*/