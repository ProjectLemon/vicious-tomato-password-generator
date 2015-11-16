#include "../include/list.h"

/**
*  Creates a new list. Functioning much as Java ArrayList
* 
* Return:     (list *) The new list
*/
list *new_list() {
    list *l = salloc(sizeof(list *));
    l[0] = salloc(sizeof(list_item *));
    l[0] -> size = 0;
    return l;
}

list_item *new_list_item(char *data) {
    list_item *temp = salloc( sizeof(list_item *) );
    temp->data = data;
    temp->size = 0;
    return temp;
}

/**
* Adds the specified item to the list
* 
* Parameter 1:  (list *) The list to add to
* Parameter 2:  (list_item *) The item to add 
*/
list *list_add(list *li, list_item *item) {
    list *l = realloc( li, (++li[0]->size*sizeof(list_item *)) );
    item->size = li[0]->size;
    l[li[0]->size-1] = item;
    return l;
}

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
bool list_contains(list *list, list_item *item) {
    for (int i = 0; i < list[0]->size; ++i) {
        if ( equals(list[i], item) ) { return TRUE; }
    }
    return FALSE;
}

/*
* Compares two list items
*
* Parameter 1: (list_item *) First item to compare
* Parameter 2: (list_item *) Second item to compare
*/
bool equals(list_item *item1, list_item *item2) {
    return strncmp(item1->data, item2->data, BUFSIZ) == 0;
}

/*
* Returns the size of the list
*
* Parameter 1: (int) Size of the list
*/
int list_get_size(list *list) {
    return list[0]->size;
}
