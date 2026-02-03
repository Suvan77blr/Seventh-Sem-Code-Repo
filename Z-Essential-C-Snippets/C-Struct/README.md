
## -> Core API Functions :-
    * type_init(type*)                  -> Valid Empty State.
    * type_destroy(type*)               -> Frees owned memory.
    * type_set_*()                      -> Controlled mutation.
    * type_copy(type*, const type*)     -> Deep Copy.

If any one of these is missing → bug waiting to happen.

## -> Recommended Extended Functions :-

| Function        | Purpose            |
| --------------- | ------------------ |
| `type_move`     | Transfer ownership |
| `type_clear`    | Reset without free |
| `type_is_valid` | Invariant check    |
| `type_swap`     | Exception-safe ops |

## -> Optional but Powerful :-

| Function      | Purpose              |
| ------------- | -------------------- |
| `type_create` | Heap-allocate struct |
| `type_free`   | Destroy + free       |
| `type_equals` | Value comparison     |
| `type_print`  | Debug output         |

## -> Naming Conventions :-

| Verb      | Meaning               |
| --------- | --------------------- |
| `init`    | No allocation         |
| `create`  | Allocates             |
| `destroy` | Frees internals       |
| `free`    | Frees object          |
| `set`     | Copies input          |
| `take`    | Steals ownership      |
| `get`     | No ownership transfer |
| `retain`  | +1 refcount           |
| `release` | -1 refcount           |

---
---
---

# `.h` vs `.c`

* Core rule: Headers describe contracts, Source files implement behavior.

