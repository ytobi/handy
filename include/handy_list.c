#include "handy_list.h"

int    handy_list_contain       ( handy_list l, void * item );
bool   handy_list_add_front     ( handy_list l, void * item );
bool   handy_list_add_back      ( handy_list l, void * item );
bool   handy_list_add_at        ( handy_list l, void * item, int at );
bool   handy_list_empty         ( handy_list l );

void * handy_list_get_front     ( handy_list l );
void * handy_list_get_back      ( handy_list l );
void * handy_list_get_at        ( handy_list l, int at );
bool   handy_list_rem_front     ( handy_list l );
bool   handy_list_rem_back      ( handy_list l );
bool   handy_list_rem_at        ( handy_list l, int at );
void   handy_list_reverse       ( handy_list l );
void   handy_list_free          ( handy_list l );
int    handy_list_length        ( handy_list l );

handy_list handy_create_list    ()
{
    handy_list  temp_list = malloc( sizeof(*temp_list) );

    temp_list->_first = temp_list->_last = NULL;
    temp_list->_size = 0;

    temp_list->contain       = handy_list_contain;
    temp_list->add_front     = handy_list_add_front;
    temp_list->add_back      = handy_list_add_back;
    temp_list->add_at        = handy_list_add_at;
    temp_list->empty         = handy_list_empty;
    temp_list->get_front     = handy_list_get_front;
    temp_list->get_back      = handy_list_get_back;
    temp_list->get_at        = handy_list_get_at;
    temp_list->rem_front     = handy_list_rem_front;
    temp_list->rem_back      = handy_list_rem_back;
    temp_list->reverse       = handy_list_reverse;
    temp_list->rem_at        = handy_list_rem_at;
    temp_list->free          = handy_list_free;
    temp_list->length        = handy_list_length;

    return temp_list;
}
int   handy_list_contain        ( handy_list l, void * item )
{
    _handy_list_obj iter = l->_first;
    for( int i = 0; i < l->_size; i++ )
    {
        if( memcmp( &(iter->_data), &item, sizeof(iter->_data) ) == 0 )
            return i;
        iter = iter->_next;
    }
    return -1;
}
bool   handy_list_add_front     ( handy_list l, void * item )
{
    if( l->_size == 0 )
    {
        _handy_list_obj temp = malloc( sizeof( *temp ) );

       	temp->_data = item;

        l->_last  = l->_first = temp;

        l->_size++;

        return true;
    }
    else if ( l->_size > 0 )
    {
        _handy_list_obj temp = malloc( sizeof( *temp ) );

        temp->_data = item;
        temp->_next = l->_first;

        l->_first->_prev = temp;
        l->_first = temp;
        l->_size++;

        return true;
    }
    return false;
}
bool   handy_list_add_back      ( handy_list l, void * item )
{
    if( l->_size == 0 )
    {
        _handy_list_obj temp = malloc( sizeof( * temp ) );

        temp->_data = item;

        l->_last  = l->_first = temp;

        l->_size++;

        return true;
    }
    else if ( l->_size > 0 )
    {
        _handy_list_obj temp = malloc( sizeof( * temp ) );

        temp->_data = item;

        temp->_prev = l->_last;
        l->_last->_next = temp;

        l->_last = temp;
        l->_size++;

        return true;
    }
    return false;
}
bool   handy_list_add_at        ( handy_list l, void *item, int at )
{
    if( at <= 0 )
        return (l->add_front(l, item));
    else if( at >= l->_size )
        return ( l->add_back(l, item) );
    else
    {
        _handy_list_obj iter;
        iter = l->_first;

        _handy_list_obj temp = malloc( sizeof( * temp ) );
        temp->_data = item;

        for( int i = 1; i < l->_size; i++ )
        {
            if( i == at )
            {
                // handy_obj nodePrev = iter->_prev;
                _handy_list_obj nextNode = iter->_next;

                iter->_next = temp;
                nextNode->_prev = temp;

                temp->_prev = iter;
                temp->_next = nextNode;

                l->_size++;
                return true;

            }
            iter = iter->_next;
        }
    }
    return false;
}
bool   handy_list_empty         ( handy_list l )
{
    return l->_size == 0 ? true : false;
}
void * handy_list_get_front     ( handy_list l )
{
    if( l->_size == 0 )
    {
        return NULL;
    }
    else if( l->_size > 0 )
    {
        return  l->_first->_data;
    }
    return NULL;
}
void * handy_list_get_back      ( handy_list l )
{
    if( l->_size == 0 )
    {
        return NULL;
    }
    else if( l->_size > 0 )
    {
        return  l->_last->_data;
    }
    return NULL;
}
void * handy_list_get_at        ( handy_list l, int at )
{
    if( at < 0 || at >= l->_size  )
        return NULL;
    else
    {
        _handy_list_obj iter;
        iter = l->_first;

        for( int i = 0; i < l->_size; i++ )
        {
            if( i == at )
            {
                if( i == 0 )
                    return (l->get_front(l) );
                else if( i == l->_size - 1 )
                    return (l->get_back(l) );
                else
                    return iter->_data;
            }
            iter = iter->_next;
        }
    }
    return NULL;
}
bool  handy_list_rem_front      ( handy_list l )
{
    if( l->_size == 1 )
    {
        l->_first = ( free( l->_first ), NULL );
        l->_first = l->_last = NULL;
        l->_size--;
        return true;
    }
    else if( l->_size > 1 )
    {
        l->_first = l->_first->_next;

        l->_first->_prev = ( free(l->_first->_prev), NULL );
        l->_size--;
        return true;
    }
    return false;
}
bool  handy_list_rem_back       ( handy_list l )
{

    if( l->_size == 1 )
    {
        l->_first = ( free(l->_first), NULL );
        l->_first = l->_last = NULL;
        l->_size--;

        return true;
    }
    else if( l->_size > 1 )
    {
        l->_last = l->_last->_prev;

        l->_size--;

        l->_last->_next = ( free(l->_last->_next), NULL );

        return true;
    }
    return false;
}
bool  handy_list_rem_at         ( handy_list l, int at )
{
    _handy_list_obj iter;
    iter = l->_first;

    if( at == 0 )
        return (l->rem_front(l) );
    else if( at == l->_size - 1 )
        return (l->rem_back(l) );
    else if( at > 0 || at < l->_size - 1 )
    {
        for( int i = 0; i < l->_size; i++ )
        {
            if( i == at )
            {

                iter->_prev->_next = iter->_next;
                iter->_next->_prev = iter->_prev;
                l->_size--;

                iter = ( free(iter), NULL );
                return true;
            }
            iter = iter->_next;
        }
    }

    return false;
}
void handy_list_reverse         ( handy_list l )
{
    // The front point the end, and _next and _prev of every node
    // reversed.

    _handy_list_obj hold_first = l->_first;
    _handy_list_obj hold_last = l->_last;

    void * temp_data;

    // exchange front and back till we reach middle
    for( int i = 0 ; i < (l->_size / 2); i++ )
    {
        temp_data = hold_first->_data;
        hold_first->_data = hold_last->_data;
        hold_last->_data = temp_data;

        hold_first = hold_first->_next;
        hold_last = hold_last->_prev;
    }
}
void   handy_list_free          ( handy_list l )
{
    // free every item in list and then remove them from the list
    while( l->_first != l->_last )
    {
        l->_first = l->_first->_next;

        l->_first->_prev = (free( l->_first->_prev ), NULL);
    }
    l->_first = (free( l->_first ), NULL);
    l->_size = 0;
}
int    handy_list_length        ( handy_list l )
{
    return l->_size;
}
