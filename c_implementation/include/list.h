#include "../include/common.h"

#ifndef __list__
#define __list__

typedef struct list_head {
    int size;
    struct list_item **item;
} list;

typedef struct list_item {
    char *data;
} list_item;


/**
*  Creates a new list. Functioning much as Java ArrayList
* 
* Return:     (list *) The new list
*/
list *new_list();

/**
*  Creates a new list item from the input data. Can be used directly in the list
* 
* Return:     (void *) Data that will be contained in the list item
*/
list_item *new_list_item(char *data);

/**
* Adds the specified item to the list
* 
* Parameter 1:  (list *) The list to add to
* Parameter 2:  (list_item *) The item to add 
*/
list *list_add(list *l, list_item *item);

/**
* Removes the item from the specified index in list
* 
* Parameter 1:  (list *) The list to remove from
* Parameter 2:  (int) The item to remove 
*/
void list_remove(list *l, int index);

/**
* Checks wether the specified item was in the list or not
* 
* Parameter 1:  (list *) The list to search
* Parameter 2:  (int) The item to look for
* 
* Reutn:            (bool) True/false if item was in list
*/
bool list_contains(list *l, list_item *item);


/*
* Compares two list items
*
* Parameter 1: (list_item *) First item to compare
* Parameter 2: (list_item *) Second item to compare
*/
bool equals(list_item *item1, list_item *item2);

/*
* Returns the size of the list
*
* Parameter 1: (int) Size of the list
*/
int list_get_size(list *list);

/*
* This function will remove the list and every item in it
*
*  Parameter 1: (list *) the list to remove
*/
void list_free(list *list);

#endif
