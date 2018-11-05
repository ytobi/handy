## handy_queue

A first-in first-out generic container. Reading and writing to and from `handy_queue` is of order *O(1)*.

##### Usage

Start by creating a `handy_queue` object:

```c
    handy_queue my_queue;
```

Initialize handy_queue object:

```c
    my_queue = handy_create_queue();
```

A handy_queue object has fields that affords queue operation, they are listed below.

**For best performance and for predictable behavior, fields whose name
begins with underscore(_) should not be use**.

| Fields            | Signature                             | Description                          |
|:------------------|:--------------------------------------|:------------------------------------|
| `contain`         | `int ( handy_queue *, void * )`       | Checks if an item is in the queue from the front, returns position of item if found or -1 if item is not found.|
| `enqueue`         | `bool ( handy_queue *, void * )`      | Attempts to add an item to back of the queue, returns true if successful or false if not successful.|
| `empty`           | `bool ( handy_queue * )`              | Check if the queue is empty, returns true if empty or false if not empty.
| `reverse`         | `void ( handy_queue * )`              | reverse the position of all items in the queue, of order O(n).
| `dequeue`         | `void * ( handy_queue * )`            | Remove and return the item at front of the queue. |
| `free`            | `void ( handy_queue * )`              | free all memory allocated to hold items in the queue. This should be call whenever the container is no longer need.
| `front`           | `void * ( handy_queue * )`            | Return the item at the front of the queue. `front` will return `NULL` if queue is empty.
| `back`            | `void * ( handy_queue * )`            | Return the item at back of the queue.`back` will return `NULL` if queue is empty.
| `length`          | `int ( handy_queue * )`               | Return a count of all items in the queue.
| `_handy_dequeued` | `void **`                             | holds temporarily the most recent item remove from queue
| `_first`          | `handy_queue_obj`                     | points to the item at front in queue.
| `_last`           | `handy_queue_obj`                     | points to the item at back in queue.
| `_size`           | `int`                                 | holds the number of items in queue.


Checkout an implemented example at [examples/example_handy_queue.c](../examples/example_handy_queue.c).