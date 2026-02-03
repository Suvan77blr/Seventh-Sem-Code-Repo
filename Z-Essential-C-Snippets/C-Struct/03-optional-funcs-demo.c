/*
Optional, but powerful API functions.

Here, defined wrt;
typedef struct {
    int model;
    char* brand;    // owned memory.
} vehicle;
*/

// Powerful-API functions' prototypes.
vehicle* vehicle_create(void);
void vehicle_free(vehicle*);
int vehicle_equals(const vehicle*, const vehicle*);
void vehicle_print(const vehicle*);

/*
Create Function => Heap API
*/
vehicle* vehicle_create(void) {
    vehicle *v = (vehicle*)malloc(sizeof *v);
    if(!v) 
        return NULL;
    vehicle_init(v);
    return v;
}

/*
Free Function => Heap API
*/
void vehicle_free(vehicle *v) {
    if (!v) return;
    vehicle_destory(v);
    free(v);
}

/*
Value Check => if two objects reprs the same value.
    - Pointer equality is wrong here.
    - strcmp, not ==.
    - NULL-safe.
*/
int vehicle_equals(const vehicle *a, const vehicle *b) {
    if(!a || !b) return 0;

    if(a->model != b->model) 
        return 0;

    if(a->brand == NULL && b->brand == NULL) 
        return 1;

    if(a->brand ==NULL || b->brand == NULL)
        return 0;

    return strcmp( a->brand, b->brand) == 0;
}

/*
Debug => Human-readable diagnostics
*/
void vehicle_print(const vehicle *v) {
    if(!v) {
        printf("vehicle(NULL)\n");
        return;
    }

    printf("vehicle { brand: \"%s\", model: %d }",
        v->brand ? v->brand : "(null)",
        v->model
    );
}