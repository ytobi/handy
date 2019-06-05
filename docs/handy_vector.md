## handy_vector

An  array-like generic container. Reading and writing to and from `handy_vector` is of order *O(1)*.

##### Usage

Start by creating a `handy_vector` object:

```c
    handy_vector my_vector;
```

Initialize `handy_vector` object:

```c
    my_vector = handy_create_vector();
```

A handy_vector object has fields that affords array operation, they are listed below. When number
of item in vector has reach capacity, `handy_vector` will resize to +(1/4) of original capacity.

**For best performance and for predictable behavior, fields whose name
begins with underscore(_) should not be use**.

| Fields            | Signature                             | Description                         |
|:------------------|:--------------------------------------|:------------------------------------|
| `contain`         | `int ( handy_vector, void * )`      | Checks if an item is in the vector, returns position of item if found or -1 if item is not found.|
| `set_at`          | `bool ( handy_vector, void *, int )`| Attempts to add an item to specified position of the vector, returns true if successful or false if not successful.|
| `get_at`          | `void * ( handy_vector )`           | Read and return item at specified position, will return null if position is empty.
| `rm_at`           | `void * ( handy_vector, int )`      | Erase the item at position.
| `capacity`        | `int ( handy_vector )`              | The current number of item the vector can hold before a need/resize for more space. |
| `free`            | `void ( handy_vector )`             | Free all memory allocated to hold items in the vector. This should be call whenever the container is no longer need.
| `free`            | `void ( handy_vector )`             | Free all memory allocated to hold items in the vector. This should be call whenever the container is no longer need.
| `_bucket`         | `void **`                             | Dynamically resizable container where items are store.
| `_capacity`       | `int`                                 | The current number of item the vector can hold before a need/resize for more space.
| `_size`           | `int`                                 | Holds the number of items in vector.


Checkout an implemented example at [examples/example_handy_vector.c](../examples/example_handy_vector.c).