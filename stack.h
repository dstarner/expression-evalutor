#include <stdlib.h>
#include <stdio.h>

#ifndef bool
#define bool int
#define true 1
#define false 0
#endif

#include "token.h"

struct stack_node{
        struct stack_node* next;
        token val;
};

struct stack_node* init_node(token val){
        struct stack_node* res;
        res = (struct stack_node*) malloc(sizeof(*res));
        res->val = val;
        res->next = NULL; 
        return res;
}

struct stack{
        struct stack_node* top;
        int size;
};

struct stack* init_stack(){
        struct stack* st;
        st = (struct stack*) malloc(sizeof(*st));
        st->size=0;
        st->top=NULL;
        return st;

}

bool is_empty(struct stack* st){
        return st->size == 0;
}

void push(token val, struct stack* st){
        struct stack_node* node;
        node=init_node(val); 
        node-> next = st->top;
        st->top=node;
        st->size++;
}

token pop(struct stack* st){
        struct stack_node* node = st->top;
        st->top = node->next;
        token val = node->val;
        st->size--;
        free(node);
        return val;

}

token peek(struct stack* st){
	return st->top->val;
}

void destroy_stack(struct stack* st){
	struct stack_node* n = st->top;
	while(n!=NULL){
		struct stack_node* newnode=n->next;
		free(n);
		n=newnode;
	}
	free(st);
}
