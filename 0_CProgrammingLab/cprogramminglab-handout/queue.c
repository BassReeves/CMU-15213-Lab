/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    if(q){
      q->head = NULL;
      q->tail=NULL;
      q->queuesize=0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    if(q==NULL)
      return;
    /* Free queue structure */
    list_ele_t*ele=q->head;
    while (ele!=NULL)
    {
      free(ele->value);
      list_ele_t*temp=ele;
      ele=ele->next;
      free(temp);
    }
    
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if(q==NULL)
      return false;
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if(newh==NULL){
      //printf("Fail to create a new node");
      return false;
    }
    newh->next=NULL;
    newh->value=malloc(strlen(s)+1);
    if(newh->value==NULL)
    {
      //printf("Fail to malloc memmory for the string!");
      free(newh);
      return false;      
    }
    strcpy(newh->value,s);
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if(q->queuesize==0){
      q->tail=newh;
      q->head=newh;
    }
    else{
      newh->next=q->head;
      q->head=newh;
    }
    ++q->queuesize;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if(q==NULL)
      return false;
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if(newh==NULL)
    {
      //printf("Fail to create a new node");
      return false;
    }
    newh->value=malloc(strlen(s)+1);
    newh->next=NULL;
    if(newh->value==NULL)
    {
      //printf("Fail to malloc memmory for the string!");
      free(newh);
      return false;      
    }
    strcpy(newh->value,s);
    if(q->queuesize==0){
      q->head=newh;
      q->tail=newh;
    }    
    else{
      q->tail->next=newh;
      q->tail=newh;
    }
    ++q->queuesize;
    return true;
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if(q==NULL||q->queuesize==0||sp==NULL)
      return false;
    
    /* You need to fix up this code. */
    list_ele_t *temp=q->head;
    if (sp) {
      int i;
      for (i = 0; i < bufsize - 1 && *(temp->value + i) != '\0'; ++i) {
          *(sp + i) = *(temp->value + i);
      }
      *(sp + i) = '\0';
    }
    q->head=temp->next;
    free(temp->value);
    free(temp);
    --q->queuesize;
    printf("*******%s\n",sp);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if(q==NULL)
     return 0;
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->queuesize;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if(q==NULL||q->head==NULL)
      return;
    list_ele_t *oldhead = q->head, *oldtail = q->tail;
    // Start reversing
    list_ele_t *curr = q->head, *prev = NULL, *next = NULL;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    q->head = oldtail;
    q->tail = oldhead;
}

