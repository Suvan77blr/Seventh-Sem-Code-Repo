
// Example struct:
typedef struct {
    int model;
    char* brand;    // owned memory.
} vehicle;

// API Function Prototypes.
void vehicle_init(vehicle*);
void vehicle_destory(vehicle*);
void vehicle_set_brand(vehicle*, int);
int vehicle_set_brand(vehicle*, const char*);
int vehicle_copy(vehicle*, const vehicle*);

/*
Initialization.
    - Safe default state.
    - Can be destroyed immediately.
*/
void vehicle_init(vehicle *v) {
    if(!v) return;
    v->model = 0;
    v->brand = NULL;
}

/*
Simple Setter.
*/
void vehicle_set_model(vehicle *v, int model) {
    if(!v) return;
    v->model = model;
}

/* 
Setter -> deep copy + safe overwriting.
    - Prevents leaks.
    - Handles reassignment.
    - Returns success/failure.

#include <string.h>
#include <stdlib.h>
*/
int vehicle_set_brand(vehicle *v, const char *brand) {
    if(!v || !brand) return 0;

    char *tmp;
    tmp = (char*)malloc( strlen(brand)+1 );
    if(!tmp) 
        return 0;

    strcpy(tmp, brand);

    free(v->brand);     // Safe freeing, even for NULL.
    v->brand = tmp;

    return 1;
}

/*
Destructor
    - Idempotent.
    - Safe to call multiple times.
*/
void vehicle_destory(vehicle *v) {
    if(!v) return;
    free(v->brand);
    v->brand = NULL;
}

/*
Copy Function => deep copy.
    - No shallow copies
    - No double free
    - Explicit ownership
*/
int vehicle_copy(vehicle *dest, const vehicle *src) {
    if(!dest || !src) return 0;

    vehicle_init(dest);
    dest->model = src->model;

    if(src->brand) {
        if( !vehicle_set_brand(dest, src->brand) ) {
            vehicle_destory(dest);
            return 0;
        }
    }

    return 1;
}



