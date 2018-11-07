## handy_stack

A last-in first-out generic container. Reading and writing to and from `handy_stack` is of order *O(1)*.

##### Usage

Start by creating a `handy_stack` object:

```c
    handy_stack my_stack;
```

Initialize `handy_stack` object:

```c
    my_stack = handy_create_stack();
```

A handy_stack object has fields that affords stack operation, they are listed below.

**For best performance and for predictable behavior, fields whose name
begins with underscore(_) should not be use**.

| Fields            | Signature                             | Description                          |
|:------------------|:--------------------------------------|:------------------------------------|
| `contain`         | `int ( handy_stack, void * )`       | Checks if an item is in the stack from the top, returns position of item if found or -1 if item is not found.|
| `push`            | `bool ( handy_stack, void * )`      | Attempts to add an item to top of the stack, returns true if successful or false if not successful.|
| `empty`           | `bool ( handy_stack )`              | Check if the stack is empty, returns true if empty or false if not empty.
| `reverse`         | `void ( handy_stack )`              | Reverse the position of all items in the stack, of order O(n).
| `pop`             | `void * ( handy_stack )`            | Remove and return the item at top of the stack. |
| `free`            | `void ( handy_stack )`              | Free all memory allocated to hold items in the stack. This should be call whenever the container is no longer need.
| `top`             | `void * ( handy_stack )`            | Return the item at the top of the stack but does not remove it. `top` will return `NULL` if stack is empty.
| `bottom`          | `void * ( handy_stack )`            | Return the item at bottom of the stack but does not remove it.`bottom` will return `NULL` if stack is empty.
| `length`          | `int ( handy_stack )`               | Return a count of all items in the stack.
| `_handy_poped`    | `void **`                             | Holds temporarily the most recent item poped from stack.
| `_first`          | `handy_stack_obj`                     | Points to the item at top in stack.
| `_last`           | `handy_stack_obj`                     | Points to the item at bottom in stack.
| `_size`           | `int`                                 | Holds the number of items in stack.


Checkout an implemented example at [examples/example_handy_stack.c](../examples/example_handy_stack.c).