## handy_string

An object for string manipulation.

##### Usage

Start by creating a `handy_string` object:

```c
    handy_string my_string;
```

initialize handy_string object:

```c
    my_string = handy_create_string();
```

A handy_string object has fields that affords string operation, they are listed below.

**For best performance and for predictable behavior, fields whose name
begins with underscore(_) should not be use**.

| Fields            | Signature                             | Description                          |
|:------------------|:--------------------------------------|:------------------------------------|
| `append`          | `int ( handy_string *, char * )`      |  Append a string, appended at the back.|
| `equel`           | `bool ( handy_string *, handy_string *)`| Check if the content of two handy_string are equal .|
| `equal_str`       | `bool ( handy_string *, char * )`     |  Checks if the content of a handy_string and a char * a the same /

###### // TODO

Checkout an implemented example at [examples/example_handy_string.c](../examples/example_handy_string.c).