#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

struct node{
  
  long v;
  struct node *next;
  struct node *prev;

};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void panic(char *s) {
    fprintf(stderr, "%s\n", s);
    exit(1);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

struct list *new() {

  struct list *l = malloc(sizeof(struct list)) ;
  struct node *dH = malloc(sizeof(struct list));
  struct node *dT = malloc(sizeof(struct list));

  if (l == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
  }
  if (dH == NULL) {
      fprintf(stderr, "Out of memory!\n");
      exit(1);
  }
  if (dT == NULL) {
      fprintf(stderr, "Out of memory!\n");
      exit(1);
  }

  
  l->head = dH;
  l->tail = dT;
  dH->next = dT;
  dH->prev = NULL;
  dT->prev = dH;
  dT->next = NULL;
  l->size = 0;
  return l;
    
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

long remove_at(struct list *l, int index) {
    assert(l != NULL && index >= 0 && index < l->size);
    
    struct node *a = l->head->next;
    struct node *b = l->head->next;
    struct node *c = l->head->next;
    int i = 0;
    while (i != index){
      b = b->next;
      i++;
    }
    a=b->prev;
    c=b->next;
    double val = b->v;
    a->next= c;
    c->prev = a;
    free(b);
    l->size = l->size - 1;
    return val;
    
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void destroy(struct list *l) {

  assert(l != NULL);
  
  if(l->size == 0){
    struct node *dH = l->head;
    struct node *dT = l->tail;
    free(dH);
    free(dT);
    free(l);
  }
  else{
    while(l->size > 0){
      remove_at(l,0);
    }
    struct node *dH = l->head;
    struct node *dT = l->tail;
    free(dH);
    free(dT);
    free(l);
  }
  
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int size(struct list *l) {
    assert(l != NULL);

    return l->size;
    
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void add_tail(struct list *l, long val) {
    assert(l != NULL);

    struct node *n =  l->tail->prev; 
    struct node *h = (struct node *)malloc(sizeof(struct node));  

    if (h == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }
    
    h->v = val;
    l->tail->prev = h;
    h->prev = n;
    n->next = h;
    h->next = l->tail;
    l->size = l->size + 1;
    
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

long get(struct list *l, int index) {
    assert(l != NULL && index >= 0 && index < l->size);
    //return 0;
    struct node *n = l->head->next;
    int i = 0;
    while (i!=index){
      n=n->next;
      i++;
    }
    return n->v;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
