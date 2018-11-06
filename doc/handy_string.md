## handy_string

An object for string manipulation.

##### Usage

Start by creating a `handy_string` object:

```c
    handy_string my_string;
```

Initialize `handy_string` object:

```c
    my_string = handy_create_string();
```

A handy_string object has fields that affords string operation, they are listed below.

**For best performance and for predictable behavior, fields whose name
begins with underscore(_) should not be use**.

| Fields            | Signature                             | Description                          |
|:------------------|:--------------------------------------|:------------------------------------|
| `append`          | `int ( handy_string *, char * )`      |  Append a string, appended at the back.|
| `equel`           | `bool ( handy_string *, handy_string *)`| Checks if the content of two handy_string are equal .|
| `equal_str`       | `bool ( handy_string *, char * )`     |  Checks if the content of a handy_string and a char * a the same. |
| `contain_char`    | `int ( handy_string *, char )`        | Checks if a char is in string, return the position of first occurrence. |
| `contain_str`     | `int ( handy_string *, char * )`      | Checks if string is in handy_string, returns the position of the first occurrence. |
| `add_char_front`  | `bool ( handy_string *, char )`       | Attempts to add a char at the front of handy_string. |  
| `add_char_back`   | `bool ( handy_string *, char )`       | Attempts to add a char at the back of handy_string. |  
| `add_char_at`     | `bool ( handy_string *, char, int )`  | Attempts to add a char at a specified position in handy_string. |  
| `is_null`         | `bool ( handy_string * )`             | Check if handy_string contains no string, return true if handy_string is empty or false if it contains at least a char. |
| `copy`            | `bool ( handy_string *, handy_string * )`| Attempts to copy the content of one handy_string( second parameter) to another( first parameter ).|
| `to_upper`        | `void ( handy_string * )`             | Convert handy_string to all upper case letters. |
| `to_lower`        | `void ( handy_string * )`             | Convert handy_string to all lower case letters. |
| `string`          | `char * ( handy_string * )`           | Return the string representation of handy_string. |
| `get_front_char`  | `char ( handy_string * )`             | Return the first letter in handy_string, but does not remove the letter.|
| `get_back_char`   | `char ( handy_string * )`             | Return the last letter in handy_string, but does not remove the letter.|
| `get_at_char`     | `char ( handy_string * )`             | Return the letter at specified position in handy_string, but does not remove the letter.|
| `del_front_char`  | `bool ( handy_string * )`             | Attempts to delete the first char in handy_string.|
| `del_back_char`   | `bool ( handy_string * )`             | Attempts to delete the last char in handy_string.|
| `del_at_char`     | `bool ( handy_string * )`             | Attempts to delete the char at specified position in handy_string.|
| `reverse`         | `void ( handy_string * )`             | Reverse position all chars in handy_string.|
| `word_count`      | `int ( handy_string *, char * )`      | Counts the number of words separated by delimiter( second argument ). |
| `free`            | `void ( handy_string * )`             | Free memory allocated by handy_string. |
| `length`          | `int ( handy_string * )`              | Counts and return the number of char in handy_string. |
| `_data`           | `char *`                              | Bucket to hold chars in handy_string. |
| `_size`           | `int`                                 | Keeps count of number of chars in handy_string. |
||
| `TODO get_front_str`| `char * ( handy_string * , char *)` | Splits handy_string at delimiter and return the first string in the resulting split. This does not modify the handy_string. |
| `TODO get_back_str`| `char * ( handy_string * , char *)`  | Splits handy_string at delimiter and return the last string in the resulting split. This does not modify the handy_string. |
| `TODO get_at_str` | `char * ( handy_string * , char *, int )` | Splits handy_string at delimiter and return the string at specified position. This does not modify the handy_string. |
This does not modify the handy_string.

Checkout an implemented example at [examples/example_handy_string.c](../examples/example_handy_string.c).