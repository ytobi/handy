## handy_list

A doubly linked list container. Good to hold data of 
unknown size. Reading and writing to and from list is of order *O(n)*.

##### Usage

**For best performance and for predictable behavior, fields whose name
begins with underscore(_) should not be use**


* `contain`: sig: `int ( handy_list *, void * )`: returns the location of
the item if found in in the list, or -1 if item is not found.

* `add_front`: sig: `bool ( handy_list *, void * )`: attempts to add an item to
 first position in the list, returns true if successful or false if not successful.
 
* `add_back`: sig: `bool ( handy_list *, void * )`: attempts to add an item to
last position in the list, returns true if successful or false if not successful.

* `add_at`: sig: `bool ( handy_list *, void *, int )`: attempts to add an item to a specified
position in the list, returns true if successful or false if not successful.

* `empty`: sig: `bool ( handy_list * )`: return true if the list is empty and length == 0
or empty will return false is list is not empty and length > 0.

* `get_front`: sig: `void * ( handy_list * )`: returns the first item in the list, at position 0.
`get_front` will return `NULL` if list is empty.

* `get_back`: sig: `void * ( handy_list * )`: returns the last item in the list, at position length - 1.
`get_back` will return `NULL` if list is empty.

* `rem_back`: sig: `bool ( handy_list * )`: attempts to remove the last item in the list, at position length - 1.
`rem_back` will return true is successful or false if unsuccessful.

* `reverse`: sig: `void ( handy_list * )`: reverse the item in the list.

* `rem_at`: sig: `bool ( handy_list * )`: attempts to remove the last item in the list, at specified position.
`rem_back` will return true is successful or false if unsuccessful.

* `free`: sig: `void ( handy_list * )`: free all memory allocated to hold items in list. This should be call when ever
the container is no longer need.

* `length`: sig: `int ( handy_list * )`: return the number of item in list.


* `_first`: sig: `handy_list_object`: points to the first item in list.
* `_last`: sig: `handy_list_object`: points to the last item in list.
* `_size`: sig: `int`: holds the number of items in list.
