## handy_hashtbl

A key-value pair data structure. Reading and writing to and from `handy_hashtbl` is of order *O(1)*.

##### Usage

NOTE: `handy_hashtbl` requires `handy_list` to work, hence include `handy_list` if you intend to use this.

Start by creating a `handy_hashtbl` object:

```c
    handy_hashtbl my_hashtbl;
```

Initialize `handy_hashtbl` object:

```c
    my_hashtbl = handy_create_hashtbl();
```

A `handy_hashtbl` object has fields that affords hash table, dictionary, map,  operation, they are listed below.

**For best performance and for predictable behavior, fields whose name
begins with underscore(_) should not be use**.

| Fields            | Signature                                     | Description                          |
|:------------------|:----------------------------------------------|:------------------------------------|
| `contain`         | `int ( handy_hashtbl t, char * key)`        | Check in hash location of key if an item with key matches, `contains` return true if found or false is not found.|
| `add`             | `bool ( handy_hashtbl t, char * key, void * i)`| Attempts to add an item to to location of the hash of key, returns true if successful or false if not successful.|
| `get`             | `void * ( handy_hashtbl t, char * key )`    | Returns the item in the hashtbl at the hash position of key. `get_at` will return `NULL` if item at position is not found.
| `remove`          | `void  ( handy_hashtbl t, char * key )`     | Remove key-value pair at position of hash of key.
| `free`            | `void ( handy_hashtbl t )`                  | Free all memory allocated to hold items in hashtbl. This should be call whenever the container is no longer need.
| `_size`           | `int`                                         | Keep count of number of items added to hashtbl.
| `_bucket`         | `handy_list *`                                | Any array of handy_list, holds key-value pairs in handy_list at position of hash of key.


Checkout an implemented example at [examples/example_handy_hashtbl.c](../examples/example_handy_hashtbl.c).