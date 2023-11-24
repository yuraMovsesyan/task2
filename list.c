#include <stdio.h>
#include <stdlib.h>


typedef  struct Node *link; /*  pointer to list node */
typedef  char elemtype; /*  list element type */
typedef struct Node {                    /* list node type */
                         elemtype elem;  /* element type */
                         link next;      /* pointer to the next node */
                    } node;

typedef link list; /* list type (pointer to the first node) */

void print (list p)
{
    while (p!=NULL) {
        putchar (p->elem);
        p=p->next;
    }
}


void rec_print (list p)
/* recursive  version of print */ 
{
    if (p==NULL)return;

    putchar(p->elem);
    rec_print (p->next);
}

void rec_reverse_print (list p) 
/* recursive  version of printing a list in reverse order */
{
    if (p==NULL) return;

    rec_print (p->next);
    putchar(p->elem);
}

void reverse_print (link beg) 
/* printing a list in reverse order */ 
{
   link cur, end=NULL;
       
   while(end != beg){
       for( cur=beg; cur->next!=end; cur=cur->next);
       putchar(cur->elem);
       end=cur;
   }
}

list create (char *s)
/* create list with elements from string s */
{ 
    link cur;
    list res;
    if (*s=='\0') return NULL;
    res=cur=(link) malloc (sizeof (node));
    cur->elem=*s++;
    while (*s!='\0') {
        cur=cur->next=(list) malloc(sizeof (node));
        cur->elem=*s++;
    }
    cur->next=NULL;
    return res;
}

void push(list *pl, elemtype el){ 
/* put element on the stack */
    link tmp = malloc(sizeof(node));
    tmp->elem = el;
    tmp->next = *pl;
    *pl = tmp;
}

elemtype pop(list *pl){
/* take  element from the stack */
    elemtype tmp;
    link p = *pl;
    if (*pl == NULL){
        fprintf(stderr, "Error: empty stack\n");
        exit(1);
    }
    tmp = p->elem;
    *pl = p->next;
    free(p);
    return tmp;
}


int empty (list p){
/* is stack empty? */
    return p==NULL;
}

int rec_count(list p){
/* count number of  list elements */
    if (p == NULL) return 0;
    return 1 + rec_count(p->next) ;
}

int maximum (list p){
/* find the maximum value in the non-empty list*/
    int max;    
    max = p->elem;
    while(p != NULL){
        if(p->elem > max) max = p->elem;
        p = p->next;
    }
    return max;
}

void in_last(list *p, char c){
/* insert element c at the end */
    link q;
    link t;
    q = malloc(sizeof(node));
    q->elem = c;
    q->next = NULL;
    if(empty(*p))
        *p = q;
    else{
        t = *p;
        while(t->next != NULL) t = t->next;
        t->next = q;
    }    
}

void del_first(list *p){
/* remove first element */
    link t;
    
    if(empty(*p)) return;
   
    t = *p;
    *p = (*p)->next;
    free(t);
}

void del_second(list *p){
/* remove second element */
    link t;

    if(empty(*p) || empty((*p)->next))
        return;
 
    t = (*p)->next;
    (*p)->next = (*p)->next->next;
    free(t);
}

void del_last(list *p){
 /* remove last element */
    link t;

    if(empty(*p))
        return;
    if((*p)->next == NULL){
        free(*p);
        *p = NULL;
        return;
    }
   
    t = *p;
    while(t->next->next != NULL){
        t = t->next;
    }
    free(t->next);
    t->next = NULL;
}

int ordered(list p){ 
/* check ordered   non-decreasing  non-empty list */
    int prev;
   
    prev = p->elem;
    while(p != NULL){
        if(p->elem >= prev){
            prev = p->elem;
        }
        else
            return 0;
        p = p->next;
    }
    return 1;
}

void exchange(list p){ 
/* exchange first and last */
    link q = p;
    elemtype tmp;

    if(empty(p) || p->next == NULL)
        return;
    
    while(q ->next != NULL){
        q = q ->next;
    }
    tmp = p->elem;
    p->elem = q->elem;
    q->elem = tmp;
    
}

list copy(list p){ 
/* build new list -- copy of p */
    if(empty(p))
        return NULL;
    link t, q;
    q = t = malloc(sizeof(node));
    t ->elem = p->elem;
    p = p->next;
    while(p != NULL){
        t->next = malloc(sizeof(node));
        t = t ->next;
        t ->elem = p->elem;
        p = p->next;
        
    }
    t->next = NULL;
    return q;
}

list rec_copy(list p){ 
/* recursive copying */
    link t;
    if(empty(p))
        return NULL;
    t = malloc(sizeof(node));
    t ->elem = p->elem;
    t ->next = rec_copy(p->next);
    return t;
}

void del_befor_a (list * lp) { 
/* delete list element before 'a' */
    link q;
    if (*lp==NULL || (*lp)->next == NULL) return;
    while( (*lp)->next != NULL) {
        if ((*lp)->next->elem == 'a') {
            q=*lp; *lp=(*lp)->next;
            free(q);
        }
        else  lp=&((*lp)->next);
    } 
}

void del_befor (list * lp, char s) {
    link q;
    if (*lp==NULL || (*lp)->next == NULL) return;
    while( (*lp)->next != NULL) {
        if ((*lp)->next->elem == s) {
            q=*lp; *lp=(*lp)->next;
            free(q);
        }
        else  lp=&((*lp)->next);
    } 
}

void del_symbol (list * lp, char s) {
    link q;
    if (*lp==NULL) return;
    while( (*lp) != NULL) {
        if ((*lp)->elem == s) {
            q=*lp; *lp=(*lp)->next;
            free(q);
        }
        else  lp=&((*lp)->next);
    } 
}

int main()
{
    list lst;
    lst = create("bcccca");
    list lst_copy;
    lst_copy = rec_copy(lst);

    del_symbol(&lst_copy, 'c');

    rec_print(lst_copy);
}
