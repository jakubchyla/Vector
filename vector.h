#ifndef ASM_VECTOR
#define ASM_VECTOR

#include <stddef.h>


typedef struct vector_s Vector;


/*
*   Constructs new vector
*
*   parameters:
*       size_t item_size: size of item to store in vector
*
*   returns:
*       a pointer to vector, otherwise NULL
*
*   errno:
*       EINVAL: item_size = 0
*       ENOMEM: allocation error
*/
Vector* Vector_new(size_t item_size);

/*
*   Frees vector
*
*   parameters:
*       Vector *vector: vector pointer
*/
void Vector_free(Vector *vector);

/*
*   Returns number of elements in vector
*
*   parameters:
*       Vector *vector: vector pointer
*
*   returns:
*       number of elements in vector
*/
size_t Vector_length(Vector *vector);

/*
*   Returns pointer to item from specified index
*
*   parameters:
*       Vector *vector: vector pointer
*       size_t index: index from which data is returned
*
*   returns:
*       pointer to vector element at specified index, otherwise NULL
*
*   errno:
*       ERANGE: index out of range
*/
void* Vector_get(Vector *vector, size_t index);

/* 
*   Returns copy of item from specified index
*
*   parameters:
*       Vector *vector: vector pointer
*       size_t index: index from which data is returned
*
*    returns:
*        pointer to copied item, otherwise NULL
*
*    errno:
*        ERANGE: index out of range
*        ENOMEM: allocation error
*/
void* Vector_get_copy(Vector *vector, size_t index);


/*
*   Sets value of item at specified index
*
*   parameters:
*       Vector *vector: vector pointer
*       size_t index: item's index
*       void *item: pointer to new value
*
*   returns:
*       0 on success, -1 on error
*
*   errno:
*       ERANGE: index out of range
*/
int Vector_set(Vector *vector, size_t index, const void *item);


/*
*   Inserts item at specified index
*
*   parameters:
*       Vector *vector: vector pointer
*       size_t index: index at which item is inserted
*       void *item: pointer to item to be inserted
*
*   returns:
*       0 on success, -1 otherwise
*
*   errno:
*       EINVAL: pointer to item is NULL
*       ENOMEM: allocation error
*/
int Vector_insert(Vector *vector, size_t index, const void *item);


/*
*   Deletes element from vector
*
*   parameters:
*       Vector *vector: vector pointer
*       size_t index: index from which element is deleted
*
*   returns:
*       0 on success, otherwise -1
*
*   errno:
*       ERANGE: index out of range
*/
int Vector_delete(Vector *vector, size_t index);


/*
*   Appends item to the end of vector
*
*   parameters:
*       Vector *vector: vector pointer
*       void *item: pointer to the item
*
*   returns:
*       0 on success, otherwise -1
*
*   errno:
*       ENOMEM: allocation error
*       EINVAL: pointer to item is NULL
*/
int Vector_push_back(Vector *vector, const void *item);


/*
*   Deletes last element
*
*   parameters:
*       Vector *vector: vector pointer
*/
void Vector_pop_back(Vector *vector);


/*
*   Swaps 2 elements
*
*   parameters:
*       Vector *vector: vector pointer
*       size_t index1, index2: indexes of elements that are swapped
*
*   errno:
*       ENOMEM: allocation error
*       EINVAL: pointer to vector is NULL
*/
int Vector_swap(Vector *vector, size_t index1, size_t index2);

#endif
