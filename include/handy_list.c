#include "handy_list.h"

bool   handy_list_contain     ( handy_list * l, void * item );
bool   handy_list_add_front   ( handy_list * l, void * item );
bool   handy_list_add_back    ( handy_list * l, void * item );
bool   handy_list_add_at      ( handy_list * l, void * item, int at );
bool   handy_list_push        ( handy_list * l, void * item );
bool   handy_list_empty       ( handy_list * l );
void * handy_list_get_front   ( handy_list * l );
void * handy_list_get_back    ( handy_list * l );
void * handy_list_get_at      ( handy_list * l, int at );
void * handy_list_remove_front( handy_list * l );
void * handy_list_remove_back ( handy_list * l );
void * handy_list_remove_at   ( handy_list * l, int at );
void * handy_list_reverse     ( handy_list * l );
void * handy_list_pop         ( handy_list * l );
void * handy_list_top         ( handy_list * l );
void   handy_list_free        ( handy_list * l );

handy_list handy_create_list   ()
{
    handy_list  temp_list = malloc( sizeof(*temp_list) );

    temp_list->size = 0;

    temp_list->contain       = handy_list_contain;
    temp_list->add_front     = handy_list_add_front;
    temp_list->add_back      = handy_list_add_back;
    temp_list->add_at        = handy_list_add_at;
    temp_list->push          = handy_list_push;
    temp_list->empty         = handy_list_empty;

    temp_list->get_front     = handy_list_get_front;
    temp_list->get_back      = handy_list_get_back;
    temp_list->get_at        = handy_list_get_at;
    temp_list->remove_front  = handy_list_remove_front;
    temp_list->remove_back   = handy_list_remove_back;
    temp_list->reverse       = handy_list_reverse;
    temp_list->remove_at     = handy_list_remove_at;
    temp_list->pop           = handy_list_pop;
    temp_list->free          = handy_list_free;
    temp_list->top           = handy_list_top;

    return temp_list;
}
bool   handy_list_contain      ( handy_list * l, void * item ) // TODO
{
    handy_Obj iter = (*l)->first;
    for( int i = 1; i <= (*l)->size; i++ )
    {
        printf( "sizeof : %d \n", iter->size );
        if( memcmp( iter->data, item, iter->size ) == 0 )
            return true;
        iter = iter->next;
    }
    return false;
}
bool   handy_list_add_front    ( handy_list * l, void * item )
{
    if( (*l)->size == 0 )
    {
        (*l)->first = malloc( sizeof( handy_Obj * ) );
        (*l)->first->data = item;
        (*l)->first->size = sizeof( item );

        (*l)->last  = (*l)->first;
        (*l)->size++;

        return true;
    }
    else if ( (*l)->size > 0 )
    {
        handy_Obj temp = malloc( sizeof( * temp ) );

        temp->size = sizeof( item );;
        temp->data = item;
        temp->next = (*l)->first;

        (*l)->first->prev = temp;
        (*l)->first = temp;
        (*l)->size++;

        return true;
    }
    return false;
}
bool   handy_list_add_back     ( handy_list * l, void * item )
{
    if( (*l)->size == 0 )
    {
        (*l)->first = malloc( sizeof( handy_Obj * ) );

        (*l)->first->data = item;
        (*l)->first->size = sizeof( item );

        (*l)->last  = (*l)->first;

        (*l)->size++;
        return true;
    }
    else if ( (*l)->size > 0 )
    {
        handy_Obj temp = malloc( sizeof( * temp ) );

        temp->size = sizeof( item );
        temp->data = item;

        temp->prev = (*l)->last;
        (*l)->last->next = temp;

        (*l)->last = temp;
        (*l)->size++;

        return true;
    }
    return false;
}
bool   handy_list_add_at       ( handy_list * l, void *item, int at )
{
    if( at < 0 || at > (*l)->size + 1 )
        return false;
    else if( at == 0 )
        return ((*l)->add_front(l, item));
    else if( at == (*l)->size )
        return ( (*l)->add_back(l, item) );
    else if( at > 0 && at < (*l)->size )
    {
        handy_Obj iter;
        iter = (*l)->first;

        handy_Obj temp = malloc( sizeof( * temp ) );
        temp->data = item;
        temp->size = sizeof( item );

        for( int i = 1; i <= (*l)->size; i++ )
        {
            if( i == at )
            {
                handy_Obj nodePrev = iter->prev;
                handy_Obj nodeNext = iter->next;

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
bool   handy_list_push         ( handy_list * l, void * item )
{
    return handy_list_add_front( l, item );
}
bool   handy_list_empty        ( handy_list * l )
{
    return (*l)->size == 0 ? true : false;
}
void * handy_list_get_front    ( handy_list * l )
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
void * handy_list_get_back     ( handy_list * l )
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
void * handy_list_get_at       ( handy_list * l, int at )
{
    if( at < 0 || at > (*l)->size )
        return NULL;
    else if( at >= 0 && at <= (*l)->size )
    {
        handy_Obj iter;
        iter = (*l)->first;

        for( int i = 1; i <= (*l)->size; i++ )
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
void * handy_list_remove_front ( handy_list * l )
{
    if( (*l)->size == 0 )
    {
        return NULL;
    }
    else if( (*l)->size == 1 )
    {
        handy_Obj  temp = (*l)->first;
        (*l)->first = (*l)->last = NULL;
        (*l)->size--;

        return temp->data;
    }
    else if( (*l)->size > 1 )
    {
        handy_Obj temp = (*l)->first;
        (*l)->first = (*l)->first->next;

        (*l)->size--;
        return temp->data;
    }
    return NULL;

}
void * handy_list_remove_back  ( handy_list * l )
{
    if( (*l)->size == 0 )
    {
        return NULL;
    }
    else if( (*l)->size == 1 )
    {
        handy_Obj  temp = (*l)->last;
        (*l)->first = (*l)->last = NULL;
        (*l)->size--;

        return temp->data;
    }
    else if( (*l)->size > 1 )
    {
        handy_Obj temp = (*l)->last;
        (*l)->last = (*l)->last->prev;

        (*l)->size--;
        return temp->data;
    }
    return NULL;
}
void * handy_list_remove_at    ( handy_list * l, int at )   // surely need some fixing
{
    if( at < 0 || at > (*l)->size + 1 )
        return NULL;

    else if( at == 0 )
    {
        return ((*l)->remove_front(l) );
    }

    else if( at == (*l)->size )
    {
        return  ( (*l)->remove_back(l) );
    }

    else if( at > 0 && at < (*l)->size )
    {
        handy_Obj iter;
        iter = (*l)->first;

        for( int i = 1; i <= (*l)->size; i++ )
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
void * handy_list_reverse      (handy_list  * l)       // surely this is not correct
{
    handy_Obj temp = (*l)->first;

    (*l)->first = (*l)->last;
    (*l)->last = temp;

    handy_Obj iter = (*l)->first->next;

    // here were are simply re-nameing the next and prev
    // node of thge structure.
    for( int i = 0; i < (*l)->size; i++ )
    {
        // looks not write!!!
        // need recchecking
        iter->next = iter->prev;
        iter->prev = iter->next;

        iter = iter->prev;
    }
}
void * handy_list_pop          ( handy_list * l )
{
    return handy_list_remove_front( l );
}
void   handy_list_free         ( handy_list * l )    // need to handel this
{
    // handle l and free
}
void * handy_list_top          ( handy_list * l )
{
    return handy_list_get_front( l );
}