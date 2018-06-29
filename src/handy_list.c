#include "handy_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

handy_list create_handy_list()
{
    handy_list  temp_list = malloc( sizeof(*temp_list) );

    temp_list->size = 0;

    temp_list->contain       = handy_contain;
    temp_list->add_front     = handy_add_front;
    temp_list->add_back      = handy_add_back;
    temp_list->add_at        = handy_add_at;
    temp_list->push          = handy_push;
    temp_list->empty         = handy_empty;

    temp_list->get_front     = handy_get_front;
    temp_list->get_back      = handy_get_back;
    temp_list->get_at        = handy_get_at;
    temp_list->remove_front  = handy_remove_front;
    temp_list->remove_back   = handy_remove_back;
    temp_list->reverse       = handy_reverse;
    temp_list->remove_at     = handy_remove_at;
    temp_list->pop           = handy_pop;
    temp_list->free          = handy_free;

    return temp_list;
}

bool handy_contain        ( handy_list * l, void * item, size_t size )
{
    List_Obj iter = (*l)->first;
    for( int i = 0; i < (*l)->size; i++ )
    {
        if( memcmp( iter->data, item, size ) == 0 )
            return true;
        iter = iter->next;
    }
    return false;
}
bool handy_add_front      ( handy_list * l, void * item, size_t size )
{
    if( (*l)->size == 0 )
    {
        (*l)->first = malloc( size );
        (*l)->first->data = item;
        (*l)->first->size = size;

        (*l)->last  = (*l)->first;
        (*l)->size++;
        return true;
    }
    else if ( (*l)->size > 0 )
    {
        List_Obj temp = malloc( size );

        temp->size = size;
        temp->data = item;
        temp->next = (*l)->first;

        (*l)->first->prev = temp;
        (*l)->first = temp;
        (*l)->size++;

        return true;
    }
    return false;
}
bool handy_add_back       ( handy_list * l, void * item, size_t size )
{
    if( (*l)->size == 0 )
    {
        (*l)->first = malloc( size );

        (*l)->first->data = item;
        (*l)->first->size = size;

        (*l)->last  = (*l)->first;

        (*l)->size++;
        return true;
    }
    else if ( (*l)->size > 0 )
    {
        List_Obj temp = malloc( size );

        temp->size = size;
        temp->data = item;

        temp->prev = (*l)->last;
        (*l)->last->next = temp;

        (*l)->last = temp;
        (*l)->size++;

        return true;
    }
    return false;
}
bool handy_add_at         ( handy_list * l, void *item, int at, size_t  size )
{
    if( at < 0 || at > (*l)->size + 1 )
        return false;
    else if( at == 0 )
        return ((*l)->add_front(l, item, size));
    else if( at == (*l)->size )
        return ( (*l)->add_back(l, item, size ) );
    else if( at > 0 && at < (*l)->size )
    {
        List_Obj iter;
        iter = (*l)->first;

        List_Obj temp = malloc( size );
        temp->data = item;
        temp->size = size;

        for( int i = 1; i <= (*l)->size; i++ )
        {
            if( i == at )
            {
                List_Obj nodePrev = iter->prev;
                List_Obj nodeNext = iter->next;

                nodePrev->next = temp;
                nodeNext->prev = temp;

                temp->prev = nodePrev;
                temp->next = nodeNext;

                (*l)->size++;
                return true;
            }
            iter = iter->next;
        }
    }
    return false;
}
bool handy_push           ( handy_list * l, void * item, size_t size )
{
    return handy_add_back( l, item, size );
}
bool handy_empty          ( handy_list * l )
{
    return (*l)->size == 0 ? true : false;
}

void * handy_get_front    ( handy_list * l, size_t  size )
{
    if( (*l)->size == 0 )
    {
        return NULL;
    }
    else if( (*l)->size > 0 )
    {
        return  (*l)->first->data;
    }
    return NULL;
}
void * handy_get_back     ( handy_list * l, size_t  size )
{
    if( (*l)->size == 0 )
    {
        return NULL;
    }
    else if( (*l)->size > 0 )
    {
        return  (*l)->last->data;
    }
    return NULL;
}
void * handy_get_at       ( handy_list * l, int at, size_t size )
{
    if( at < 0 || at > (*l)->size )
        return NULL;
    else if( at >= 0 && at <= (*l)->size )
    {
        List_Obj iter;
        iter = (*l)->first;

        for( int i = 0; i < (*l)->size; i++ )
        {
            if( i == at )
            {
                return iter->data;
            }
            iter = iter->next;
        }
    }
    return NULL;
}
void * handy_remove_front ( handy_list * l, size_t size )
{
    if( (*l)->size == 0 )
    {
        return NULL;
    }
    else if( (*l)->size == 1 )
    {
        List_Obj  temp = (*l)->first;
        (*l)->first = (*l)->last = NULL;
        (*l)->size--;

        return temp->data;
    }
    else if( (*l)->size > 1 )
    {
        List_Obj temp = (*l)->first;
        (*l)->first = (*l)->first->next;

        (*l)->size--;
        return temp->data;
    }
    return NULL;

}
void * handy_remove_back  ( handy_list * l, size_t size )
{
    if( (*l)->size == 0 )
    {
        return NULL;
    }
    else if( (*l)->size == 1 )
    {
        List_Obj  temp = (*l)->last;
        (*l)->first = (*l)->last = NULL;
        (*l)->size--;

        return temp->data;
    }
    else if( (*l)->size > 1 )
    {
        List_Obj temp = (*l)->last;
        (*l)->last = (*l)->last->prev;

        (*l)->size--;
        return temp->data;
    }
    return NULL;
}
// surely need some fixing
void * handy_remove_at    ( handy_list * l, int at, size_t size )
{
    if( at < 0 || at > (*l)->size + 1 )
        return NULL;

    else if( at == 0 )
    {
        return ((*l)->remove_front(l, NULL) );
    }

    else if( at == (*l)->size )
    {
        return  ( (*l)->remove_back(l, NULL) );
    }

    else if( at > 0 && at < (*l)->size )
    {
        List_Obj iter;
        iter = (*l)->first;

        for( int i = 0; i < (*l)->size; i++ )
        {
            if( i == at )
            {
                iter->prev->next = iter->next;
                iter->next->prev = iter->prev;
                (*l)->size--;
                return iter->data;
            }
            iter = iter->next;
        }
    }
    return NULL;
}
// surely this is not not correct
void *handy_reverse       (handy_list *l)
{
    List_Obj temp = (*l)->first;

    (*l)->first = (*l)->last;
    (*l)->last = temp;
}
void * handy_pop          ( handy_list * l, size_t size )
{
    return handy_remove_front( l, size );
}
// need to handel this
void handy_free           ( handy_list * l )
{
    // handle l and free
}