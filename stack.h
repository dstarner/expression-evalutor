#include <stdlib.h>

#ifndef bool
#define bool int
#define true 1
#define false 0
#endif

struct stack_node{
        struct stack_node* next;
        int val;
};

struct stack_node* init_node(int val){
        struct stack_node* res;
        res = malloc(sizeof(*res)); 
        res->val = val;
        res->next = NULL; 
        return res;
}

struct stack{
        struct stack_node *top;
        int size;
};

struct stack* init_stack(){
        struct stack* st;
        st = malloc(sizeof(*st));
        st->size=0;
        st->top=NULL;
        return st;

}

bool is_empty(struct stack* st){
        return st->size == 0;
}

void push(int val, struct stack* st){
        struct stack_node* node;
        node=init_node(val); 
        node-> next = st->top;
        st->top=node;
        st->size++;
}

int pop(struct stack* st){
        struct stack_node* node = st->top;
        st->top = node->next;
        int val = node->val;
        st->size--;
        free(node);
        return val;

}

