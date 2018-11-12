# handy

A generic header-only data structure library for C.

This library of common data structure, functions, services and more, is meant to serve and fill the immediate need of programs that require them. It is often common to be in need of a simple data structure to serve an immediate need without the need to expand, compile or build external code and programs in your code. Handy will come in "handy" during those times.

Handy has a simple and straightforward object-oriented API, this means objects have functions which are the property of the object and operates on them.

Handy is modular, i.e can be copied and used on the go.

## Instalations

All you need to do is copy the header and implementation file for the container or services from the include directory to your project directory.

## Usage

First thing first, create an object of the container to be used.

Here is a simple usage of **handy_list**: list container:


NOTE. Always call the property free on the object to clean up some memory and finally free the object itself.

```C
    handy_list my_list = handy_create_list();                       // create a handy_list
    
    
    my_list->add_front( my_list, "Hello, world" );                 // add first item at front of list
    my_list->add_front( my_list, 'A' );                            // add another item at front of list
   

    printf( "Item at front: %c\n", my_list->get_front(my_list) );  // expect a char, prints 'A' 
    
    printf( "Item at back: %s\n", my_list->get_back(my_list) );    // expect char *, prints "Hello, world"
    
    my_list.free( my_list );                                       // free item(s) in list
    free( my_list );                                                // free my_list itself

```

##### Here is a list of already implemented(ticked) or to be implemented feature:


- [x] **[handy_list](doc/handy_list.md) ( list ):** Dynamically sized list of generic items.
- [x] **[handy_hashtbl](doc/handy_hashtbl.md) ( hashtable ):** A dictionary, map: a collection of key-value pairs.
- [x] **[handy_stack](doc/handy_stack.md)  ( stack ):** Dynamically sized, odered collection of generic items that afford stack operations.
- [x] **[handy_queue](doc/handy_queue.md)  ( queue ):** Dynamically sized, odered collection of generic items that afford queue operations.
- [x] **[handy_string](doc/handy_string.md) ( string ):** A stucture for string maninipulations.
- [x] **[handy_vector](doc/handy_vector.md) ( vector ):** Dynamically sized collection of generic items with constant insertion and  deletion.
- [ ] **handy_time ( time ):** A structure for time keeping.
- [ ] **handy_serialize ( serialize ):** Reading and writing generic data to disk.
- [ ] **handy_numeric ( numeric ):** For working with all types of numeric data eg decimal, binary, hexadecimal, octal etc.
- [ ] **handy_sick ( sockets ):** sick - Socket Interface Communication Kit.

## Contributions

I commit to handy as a hobby, if you like to see a feature or you found a defect, feel free to raise an issue for them and if you feel further motivated submit a pull request for them. Contributions are highly welcome.


[![](https://sourcerer.io/fame/ytobi/ytobi/handy/images/0)](https://sourcerer.io/fame/ytobi/ytobi/handy/links/0)[![](https://sourcerer.io/fame/ytobi/ytobi/handy/images/1)](https://sourcerer.io/fame/ytobi/ytobi/handy/links/1)[![](https://sourcerer.io/fame/ytobi/ytobi/handy/images/2)](https://sourcerer.io/fame/ytobi/ytobi/handy/links/2)[![](https://sourcerer.io/fame/ytobi/ytobi/handy/images/3)](https://sourcerer.io/fame/ytobi/ytobi/handy/links/3)[![](https://sourcerer.io/fame/ytobi/ytobi/handy/images/4)](https://sourcerer.io/fame/ytobi/ytobi/handy/links/4)[![](https://sourcerer.io/fame/ytobi/ytobi/handy/images/5)](https://sourcerer.io/fame/ytobi/ytobi/handy/links/5)[![](https://sourcerer.io/fame/ytobi/ytobi/handy/images/6)](https://sourcerer.io/fame/ytobi/ytobi/handy/links/6)[![](https://sourcerer.io/fame/ytobi/ytobi/handy/images/7)](https://sourcerer.io/fame/ytobi/ytobi/handy/links/7)

