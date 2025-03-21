## Vectors
A vector can be thought of as a dynamically allocated array that automagically changes its size on use. Items are stored in a single block of memory, just like a regular array; but you can add/remove items and it will take care of all the book keeping. It's by far the most common kind of collection in mainstream programming languages.

Rather than storing pointers to values, we'll expose the memory directly to allow copying values in place. This means that the vector needs to know the size of its items.

```C
struct hc_vector v;
hc_vector_init(&v, sizeof(int));
hc_vector_grow(&v, 10);
  
const int n = 10;
    
for (int i = 0; i < n; i++) {
  *(int *)hc_vector_push(&v) = i;
}
```

The `hc_vector_grow()` call in the preceding example is not strictly needed, but helps reduce allocations; without it the vector would need to duble the size of its memory block 3 times (allocating 2, 4, 8 and finally 16*32 bytes) to store 10 integers.

```C
void hc_vector_grow(struct hc_vector *v, int capacity) {
  v->capacity = capacity;

  v->items = realloc(v->items,
		     hc_align(v->item_size*(v->capacity+1), v->item_size));

  v->start = hc_align(v->items, v->item_size);
  v->end = v->start + v->item_size*v->length;
}
```

A macro is provided to simplify looping.

```C
hc_vector_do(&v, it) {
  int v = *(int *)it;
  ...
}
```

Alternatively you could use `hc_vector_get()` with a manual loop, which is slightly slower since it needs to call a function and calculate the pointer for every iteration.

```C
for (int i = 0; i < n; i++) {
  int v = *(int *)hc_vector_get(&v, i);
  ...
}  
```

While not the primary use case for vectors, it's sometimes useful to be able to insert/delete blocks of items. `hc_vector_insert()` returns a pointer to the start of the inserted block.

```C
void *hc_vector_insert(struct hc_vector *v, int i, int n) {
  const int m = v->length+n;
  if (m > v->capacity) { hc_vector_grow(v, m); } 
  uint8_t *const p = hc_vector_get(v, i);

  if (i < v->length) {
    memmove(p + v->item_size*n, p, (v->length - i) * v->item_size);
  }
  
  v->length += n;
  v->end += n*v->item_size;
  return p;
}
```

While `hc_vector_delete()` simply returns a boolean signalling if the deletion was successful or not.

```
bool hc_vector_delete(struct hc_vector *v, int i, int n) {
  const int m = i+n;
  if (v->length < m) { return false; }

  if (m < v->length) {
    uint8_t *const p = hc_vector_get(v, i);
    memmove(p, p + n*v->item_size, i + (v->length-n) * v->item_size);
  }

  v->length -= n;
  v->end -= n*v->item_size;
  return true;
}
```