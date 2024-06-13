#include "linked_queue.h"

struct linked_queue* lqInit () {
    struct linked_queue* new_lq = (struct linked_queue*)malloc(sizeof(struct linked_queue));
    if (new_lq==NULL) {
        DEBUG_INFO("Failed to make space for new linked queue");
        perror("");
        return NULL;
    }
    new_lq->head = (struct linked_node*)malloc(sizeof(struct linked_node));
    if (new_lq->head==NULL) {
        DEBUG_INFO("Failed to make space for new node");
        perror("");
        goto malloc_error;
    }
    new_lq->tail = new_lq->head;
    new_lq->head->next=NULL;

    return new_lq;

malloc_error:
    free(new_lq);
    return NULL;
}

bool lqIsEmpty (struct linked_queue* lq) {
    if(lq==NULL) return false;
    return lq->head==lq->tail;
}

bool lqIN (struct linked_queue* lq,LQ_ELEM_TYPE* data,bool (* cpData)(LQ_ELEM_TYPE* dst,LQ_ELEM_TYPE* src)) {
    //check things
    if (lq==NULL) {
        DEBUG_INFO("invalid input queue");
        perror("");
        return NULL;
    }

    //make space
    struct linked_node* new_node = (struct linked_node*)malloc(sizeof(struct linked_node));
    if (new_node==NULL) {
        DEBUG_INFO("Failed to make space for new node");
        perror("");
        return NULL;
    }
    new_node->data = (LQ_ELEM_TYPE*)malloc(sizeof(LQ_ELEM_TYPE));

    //copy data
    if (!cpData(new_node->data,data)) {
        DEBUG_INFO("Failed to copy data");
        perror("");
        goto cp_error;
    }

    //if all is good
    new_node->next = NULL;
    lq->tail->next = new_node;
    lq->tail = lq->tail->next;
    return true;

cp_error:
    free(new_node);
    return false;
}

bool lqHead (struct linked_queue* lq,LQ_ELEM_TYPE* data,bool (* cpData)(LQ_ELEM_TYPE* dst,LQ_ELEM_TYPE* src)) {
    //check things
    if (lq==NULL||lqIsEmpty(lq)) {
        DEBUG_INFO("invalid input queue");
        perror("");
        return NULL;
    }

    //copy data
    if (!cpData(data,lq->head->next->data)) {
        DEBUG_INFO("Failed to copy data");
        perror("");
        goto cp_error;
    }

    return true;

cp_error:
    return false;
}

bool lqOut (struct linked_queue* lq,LQ_ELEM_TYPE* data,bool (* cpData)(LQ_ELEM_TYPE* dst,LQ_ELEM_TYPE* src),void (* clearData)(LQ_ELEM_TYPE* data)) {
    if (data!=NULL)
        if (lqHead(lq,data,cpData)==false) return false;

    //remove the first data node
    struct linked_node* p = lq->head->next;
    if(p==lq->tail) lq->tail=lq->head;
    lq->head->next = p->next;
    if(clearData) clearData(p->data);
    else free(p->data);
    free(p);
    return true;
}

LQ_ELEM_TYPE* lqFirst (struct linked_queue* lq) {
    return lq->head->next->data;
}

void lqDestroy (struct linked_queue* lq,void (* clearData)(LQ_ELEM_TYPE* data)) {
    //check things
    if (lq==NULL) {
        DEBUG_INFO("invalid input queue");
        perror("");
        return;
    }

    while(!lqIsEmpty(lq))
        lqOut(lq,NULL,NULL,clearData);

    free(lq->head);
    free(lq);
}