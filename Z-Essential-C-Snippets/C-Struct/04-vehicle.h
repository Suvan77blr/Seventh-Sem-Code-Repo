/* vehicle.h => PUBLIC API (contract)
Contains :-
    - Types,
    - Function declarations.
    - Ownership rules ( via naming + comments ).
    - NO implementation.
    - NO private helpers.
*/

#ifndef VEHICLE_H
#define VEHICLE_H

typedef struct {
    int model;
    char *brand;
    // int refcount;    // => Object tracking.
} vehicle;

/* Lifecycle Functions */
void vehicle_init(vehicle *v);
void vehicle_destroy(vehicle *v);

/* Mutation Functions */
void vehicle_set_model(vehicle *v, int model);
int  vehicle_set_brand(vehicle *v, const char *brand);

/* Copy / Move Functions */
int  vehicle_copy(vehicle *dest, const vehicle *src);
void vehicle_move(vehicle *dest, vehicle *src);
void vehicle_swap(vehicle *a, vehicle *b);

/* Utility Functions */
int  vehicle_equals(const vehicle *a, const vehicle *b);
int  vehicle_is_valid(const vehicle *v);
void vehicle_print(const vehicle *v);

/* Heap API Functions */
vehicle *vehicle_create(void);
void     vehicle_free(vehicle *v);

#endif /* VEHICLE_H*/