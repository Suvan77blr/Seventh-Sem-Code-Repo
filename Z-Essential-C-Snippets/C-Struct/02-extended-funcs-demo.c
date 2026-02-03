/*
Extended, strongly recommened API functions.

Here, defined wrt;
typedef struct {
    int model;
    char* brand;    // owned memory.
} vehicle;
*/

// Extended-API functions' prototypes.
void vehicle_move(vehicle*, vehicle*);
void vehicle_clear(vehicle*);
int vehicle_is_valid(const vehicle*);
void vehicle_swap(vehicle*, vehicle*);

/*
Move
    - Ownership transfer.
    - Used to avoid extra allocations.
*/
void vehicle_move(vehicle *dest, vehicle *src) {
    if(!dest || !src) return;
    *dest = *src;
    src->brand = NULL;
}

/*
Clear
    - Object reuse.
*/
void vehicle_clear(vehicle *v) {
    if (!v) return;
    free(v->brand);
    v->brand = NULL;
    v->model = 0;
}

/*
Invariant checking.
*/
int vehicle_is_valid(const vehicle *v) {
    return v && (!v->brand || strlen(v->brand) > 0);
}

/*
Swap => for swapping allocation w/o allocation.
    - Shallow copy is OK here.
    - Ownership moves atomically.
*/
void vehicle_swap(vehicle *a, vehicle *b) {
    if(!a || !b) return;

    vehicle tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}