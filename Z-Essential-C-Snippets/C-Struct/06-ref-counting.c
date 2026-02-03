// #include "04-vehicle.h"

typedef struct {
    int model;
    char *brand;
    int refcount;
} vehicle;

/* API Prototypes using Ref-Count concept.
    - No function calls free() anymore.
    - They only call retain() and release().
*/
vehicle *vehicle_create(void);
void vehicle_retain(vehicle *v);
void vehicle_release(vehicle *v);




// Modification of Create Heap-API Function to use Ref-Count.
vehicle *vehicle_create(void) {
    vehicle *v = malloc(sizeof *v);
    if (!v) return NULL;

    v->brand = NULL;
    v->model = 0;
    v->refcount = 1;
    return v;
}

// Retain Function.
void vehicle_retain(vehicle *v) {
    if(v) v->refcount++;
}

// Release Function.
void vehicle_release(vehicle *v) {
    if(!v) return;

    --(v->refcount);
    if( v->refcount == 0) {
        free(v->brand);
        free(v);
    }
}