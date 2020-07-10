#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#include "vector.h"


#define VECTOR_INITIAL_SIZE 256


typedef struct vector_s{
    void *data;         //pointer to data
    size_t capacity;    //allocated memory
    size_t length;      //number of items
    size_t item_size;   //size of element
}Vector;


/********************
* Internal definitions
********************/


static int Vector_resize(Vector *vector, size_t capacity){
    void *new_data = realloc(vector->data, capacity * vector->item_size);
    if (!new_data){
        errno = ENOMEM;
        return -1;
    }
    vector->data = new_data;
    vector->capacity = capacity;
    return 0;
}


/********************
* External definitions
********************/


Vector* Vector_new(size_t item_size){
    if (!item_size){
        errno = EINVAL;
        return NULL;
    }
    Vector *vector = malloc(sizeof(Vector));
    if (!vector){
        errno = ENOMEM;
        return NULL;
    }

    vector->item_size = item_size;
    vector->capacity = VECTOR_INITIAL_SIZE * vector->item_size;
    vector->length = 0;
    vector->data = malloc(vector->item_size * vector->capacity);
    if (!vector->data){
        free(vector);
        errno = ENOMEM;
        return NULL;
    }

    return vector;
}


void Vector_free(Vector *vector){
    free(vector->data);
    free(vector);
}

size_t Vector_length(Vector *vector){
    return vector->length;
}

void* Vector_get(Vector *vector, size_t index){
    if (index * vector->item_size > vector->capacity){
        errno = ERANGE;
        return NULL;
    }
    void *item = vector->data + index * vector->item_size;
    return item;
}

void* Vector_get_copy(Vector *vector, size_t index){
    void *item = Vector_get(vector, index);
    if (item == NULL)
        return NULL;

    void *copy = malloc(vector->item_size);
    if (copy == NULL){
        errno = ENOMEM;
        return NULL;
    }

    memcpy(
        copy,
        item,
        vector->item_size
    );
    return item;
}


int Vector_set(Vector *vector, size_t index, const void *item){
    if (!item){
        errno = EINVAL;
        return -1;
    }
    if (index * vector->item_size >= vector->capacity){
        errno = ERANGE;
        return -1;
    }
    memcpy(
        vector->data + index * vector->item_size,
        item,
        vector->item_size
    );
    return 0;
}


int Vector_insert(Vector *vector, size_t index, const void *item){
    if (!item){
        errno = EINVAL;
        return -1;
    }
    if ((vector->length + 1) * vector->item_size >= vector->capacity)
        if(!(Vector_resize(vector, (vector->capacity) * 2)))
            return -1;

    for (size_t i = vector->length; i >= index + 1; i--){
        memcpy(
            vector->data + i * vector->item_size,
            vector->data + (i-1) * vector->item_size,
            vector->item_size
        );
    }
    memcpy(
        vector->data + index * vector->item_size,
        item,
        vector->item_size
    );

    vector->length++;
    return 0;
}


int Vector_delete(Vector *vector, size_t index){
    if (index >= vector->length){
        errno = ERANGE;
        return -1;
    }
    for (size_t i = index; i < vector->length-1; i++){
        memcpy(
            vector->data + i * vector->item_size,
            vector->data + (i+1) * vector->item_size,
            vector->item_size
        );
    }
    vector->length--;
    return 0;
}


int Vector_push_back(Vector *vector, const void *item){
    if(Vector_insert(vector, vector->length, item))
        return -1;
    return 0;
}


void Vector_pop_back(Vector *vector){
    Vector_delete(vector, vector->length - 1);
}


int Vector_swap(Vector *vector, size_t index1, size_t index2){
    if (vector == NULL){
        errno = EINVAL;
        return -1;
    }

    void *tmp = malloc(vector->item_size);
    if (tmp == NULL){
        errno = ENOMEM;
        return -1;
    }

    memcpy(
        tmp,
        Vector_get(vector, index2),
        vector->item_size
    );
    memcpy(
        Vector_get(vector, index2),
        Vector_get(vector, index1),
        vector->item_size
    );
    memcpy(
        Vector_get(vector, index1),
        tmp,
        vector->item_size
    );

    free(tmp);
    return 0;
}
