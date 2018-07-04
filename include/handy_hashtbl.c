
#include "handy_hashtbl.h"

/*bool   handy_hashtbl_contain  ( handy_hashtbl * l, void * key, size_t size );
bool   handy_hashtbl_add_front( handy_hashtbl * l, void * item, void * key, size_t size );
bool   handy_hashtbl_add_back ( handy_hashtbl * l, void * item, void * key, size_t size );
bool   handy_hashtbl_add_at   ( handy_hashtbl * l, void * item, void * key, size_t size );
bool   handy_hashtbl_push     ( handy_hashtbl * l, void * item, void * key, size_t size );
bool   handy_hashtbl_empty    ( handy_hashtbl * l );
void * handy_hashtbl_get_front( handy_hashtbl * l, size_t size );
void * handy_hashtbl_get_back ( handy_hashtbl * l, size_t size );
void * handy_hashtbl_get_at   ( handy_hashtbl * l, int at, size_t size );
void * handy_hashtbl_remove_front( handy_hashtbl * l, size_t size );
void * handy_hashtbl_remove_back( handy_hashtbl * l, size_t size );
void * handy_hashtbl_reverse  ( handy_hashtbl * l );
void * handy_hashtbl_remove_at( handy_hashtbl * l, void * key, size_t size );
void * handy_hashtbl_pop      ( handy_hashtbl * l, size_t size );
void   handy_hashtbl_free     ( handy_hashtbl * l );
void * handy_hashtbl_top      ( handy_hashtbl * l, size_t size );*/


handy_hashtbl handy_create_hashtbl()
{
    handy_hashtbl  temp_list = malloc( sizeof(*temp_list) );

    temp_list->size = 0;

    temp_list->contain       = handy_hashtbl_contain;
    temp_list->add_front     = handy_hashtbl_add_front;
    temp_list->add_back      = handy_hashtbl_add_back;
    temp_list->add_at        = handy_hashtbl_add_at;
    temp_list->push          = handy_hashtbl_push;
    temp_list->empty         = handy_hashtbl_empty;

    temp_list->get_front     = handy_hashtbl_get_front;
    temp_list->get_back      = handy_hashtbl_get_back;
    temp_list->get_at        = handy_hashtbl_get_at;
    temp_list->remove_front  = handy_hashtbl_remove_front;
    temp_list->remove_back   = handy_hashtbl_remove_back;
    temp_list->reverse       = handy_hashtbl_reverse;
    temp_list->remove_at     = handy_hashtbl_remove_at;
    temp_list->pop           = handy_hashtbl_pop;
    temp_list->free          = handy_hashtbl_free;
    temp_list->top           = handy_hashtbl_top;

    return temp_list;
}
bool handy_hashtbl_contain    ( handy_hashtbl * l, void * key, size_t size )
{}
bool handy_hashtbl_add_front  ( handy_hashtbl * l, void * item, void * key, size_t size )
{}
bool handy_hashtbl_add_back   ( handy_hashtbl * l, void * item, void * key, size_t size )
{}
bool handy_hashtbl_add_at     ( handy_hashtbl * l, void * item, void * key, size_t size )
{}
bool handy_hashtbl_push       ( handy_hashtbl * l, void * item, void * key, size_t size )
{}
bool handy_hashtbl_empty      ( handy_hashtbl * l )
{}
void * handy_hashtbl_get_front( handy_hashtbl * l, size_t size )
{}
void * handy_hashtbl_get_back ( handy_hashtbl * l, size_t size )
{}
void * handy_hashtbl_get_at   ( handy_hashtbl * l, int at, size_t size )
{}
void * handy_hashtbl_remove_front( handy_hashtbl * l, size_t size )
{}
void * handy_hashtbl_remove_back( handy_hashtbl * l, size_t size )
{}
void * handy_hashtbl_reverse  ( handy_hashtbl * l )
{}
void * handy_hashtbl_remove_at( handy_hashtbl * l, void * key, size_t size )
{}
void * handy_hashtbl_pop      ( handy_hashtbl * l, size_t size )
{}
void   handy_hashtbl_free     ( handy_hashtbl * l )
{}
void * handy_hashtbl_top      ( handy_hashtbl * l, size_t size )
{}