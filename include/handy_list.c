#include "handy_list.h"

int   handy_list_contain     ( handy_list * l, void * item );
bool   handy_list_add_front   ( handy_list * l, void * item );
bool   handy_list_add_back    ( handy_list * l, void * item );
bool   handy_list_add_at      ( handy_list * l, void * item, int at );
bool   handy_list_empty       ( handy_list * l );

char * handy_list_to_string   ( handy_list * l );

void * handy_list_get_front   ( handy_list * l );
void * handy_list_get_back    ( handy_list * l );
void * handy_list_get_at      ( handy_list * l, int at );
void * handy_list_remove_front( handy_list * l );
void * handy_list_remove_back ( handy_list * l );
void * handy_list_remove_at   ( handy_list * l, int at );
void * handy_list_reverse     ( handy_list * l );
void   handy_list_free        ( handy_list * l );

handy_list handy_create_list   ()
{
    handy_list  temp_list = malloc( sizeof(*temp_list) );

    temp_list->size = 0;

    temp_list->contain       = handy_list_contain;
    temp_list->add_front     = handy_list_add_front;
    temp_list->add_back      = handy_list_add_back;
    temp_list->add_at        = handy_list_add_at;
    temp_list->empty         = handy_list_empty;

    temp_list->to_string     = handy_list_to_string;

    temp_list->get_front     = handy_list_get_front;
    temp_list->get_back      = handy_list_get_back;
    temp_list->get_at        = handy_list_get_at;
    temp_list->remove_front  = handy_list_remove_front;
    temp_list->remove_back   = handy_list_remove_back;
    temp_list->reverse       = handy_list_reverse;
    temp_list->remove_at     = handy_list_remove_at;
    temp_list->free          = handy_list_free;

    return temp_list;
}
int   handy_list_contain      ( handy_list * l, void * item )
{
    handy_obj iter = (*l)->_first;
    for( int i = 0; i < (*l)->size; i++ )
    {
        if( memcmp( &(iter->_data), &item, sizeof(iter->_data) ) == 0 )
            return i;
        iter = iter->_next;
    }
    return -1;
}
bool   handy_list_add_front    ( handy_list * l, void * item )
{
    if( (*l)->size == 0 )
    {
        handy_obj temp = malloc( sizeof( *temp ) );

       	temp->_data = item;

        (*l)->_last  = (*l)->_first = temp;

        (*l)->size++;

        return true;
    }
    else if ( (*l)->size > 0 )
    {
        handy_obj temp = malloc( sizeof( *temp ) );

        temp->_data = item;
        temp->_next = (*l)->_first;

        (*l)->_first->_prev = temp;
        (*l)->_first = temp;
        (*l)->size++;

        return true;
    }
    return false;
}
bool   handy_list_add_back     ( handy_list * l, void * item )
{
    if( (*l)->size == 0 )
    {
        handy_obj temp = malloc( sizeof( * temp ) );

        temp->_data = item;

        (*l)->_last  = (*l)->_first = temp;

        (*l)->size++;

        return true;
    }
    else if ( (*l)->size > 0 )
    {
        handy_obj temp = malloc( sizeof( * temp ) );

        temp->_data = item;

        temp->_prev = (*l)->_last;
        (*l)->_last->_next = temp;

        (*l)->_last = temp;
        (*l)->size++;

        return true;
    }
    return false;
}
bool   handy_list_add_at       ( handy_list * l, void *item, int at )
{
    if( at < 0 || at > (*l)->size + 1 )
        return false;
    else
    {
        handy_obj iter;
        iter = (*l)->_first;

        handy_obj temp = malloc( sizeof( * temp ) );
        temp->_data = item;

        for( int i = 0; i < (*l)->size; i++ )
        {
            if( i == at )
            {
                if( at == 0 )
                    return ((*l)->add_front(l, item));
                else if( at == (*l)->size )
                    return ( (*l)->add_back(l, item) );
                else
                {
                    handy_obj nodePrev = iter->_prev;
                    handy_obj nodeNext = iter->_next;

                    nodePrev->_next = temp;
                    nodeNext->_prev = temp;

                    temp->_prev = nodePrev;
                    temp->_next = nodeNext;

                    (*l)->size++;
                    return true;
                }
            }
            iter = iter->_next;
        }
    }
    return false;
}
bool   handy_list_empty        ( handy_list * l )
{
    return (*l)->size == 0 ? true : false;
}
char * handy_list_to_string   ( handy_list * l )    // TODO
{
    if( (*l)->size <= 0 )
    {
        return "[]";
    }
    char * handy_str_return = malloc( ((*l)->size + 3) * sizeof((*l)->_first->_data) );

    handy_str_return[0] = '[';

    for( int i = 0; i <= (*l)->size; i++ )
    {
        handy_str_return[i + 1] = (*l)->get_at(l,  i ) + ' ' - ' ';
    }
    handy_str_return[(*l)->size + 1] = ']';
    handy_str_return[(*l)->size + 2] = '\0';

    return handy_str_return;
}
void * handy_list_get_front    ( handy_list * l )
{
    if( (*l)->size == 0 )
    {
        return NULL;
    }
    else if( (*l)->size > 0 )
    {
        return  (*l)->_first->_data;
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
        return  (*l)->_last->_data;
    }
    return NULL;
}
void * handy_list_get_at       ( handy_list * l, int at )
{
    if( at < 0 || at >= (*l)->size  )
        return NULL;
    else
    {
        handy_obj iter;
        iter = (*l)->_first;

        for( int i = 0; i < (*l)->size; i++ )
        {
            if( i == at )
            {
                if( i == 0 )
                    return ((*l)->get_front(l) );
                else if( i == (*l)->size - 1 )
                    return ((*l)->get_back(l) );
                else
                    return iter->_data;
            }
            iter = iter->_next;
        }
    }
    return NULL;
}
void * handy_list_remove_front ( handy_list * l )
{
    if( (*l)->size == 0 )
        return NULL;
    else if( (*l)->size == 1 )
    {
        handy_obj  temp = (*l)->_first;
        (*l)->_first = (*l)->_last = NULL;
        (*l)->size--;

        return temp->_data;
    }
    else if( (*l)->size > 1 )
    {
        handy_obj temp = (*l)->_first;
        (*l)->_first = (*l)->_first->_next;

        (*l)->size--;
        return temp->_data;
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
        handy_obj  temp = (*l)->_last;
        (*l)->_first = (*l)->_last = NULL;
        (*l)->size--;

        return temp->_data;
    }
    else if( (*l)->size > 1 )
    {
        handy_obj temp = (*l)->_last;
        (*l)->_last = (*l)->_last->_prev;

        (*l)->size--;
        return temp->_data;
    }
    return NULL;
}
void * handy_list_remove_at    ( handy_list * l, int at )
{
    handy_obj iter;
    iter = (*l)->_first;

    if( at == 0 )
        return ((*l)->remove_front(l) );
    else if( at == (*l)->size - 1 )
        return ((*l)->remove_back(l) );
    else if( at < 0 || at >= (*l)->size  )
        return NULL;
    else if( at > 0 || at < (*l)->size - 1 )
    {
        for( int i = 0; i < (*l)->size; i++ )
        {
            if( i == at )
            {
                iter->_prev->_next = iter->_next;
                iter->_next->_prev = iter->_prev;
                (*l)->size--;
                return iter->_data;
            }
            iter = iter->_next;
        }
    }

    return NULL;
}
void * handy_list_reverse      (handy_list  * l)
{
    // The front point the end, and _next and _prev of every node
    // reversed.

    handy_obj hold_first = (*l)->_first;
    handy_obj hold_last = (*l)->_last;

    void * temp_data;

    // exchange front and back till we reach middle
    for( int i = 0 ; i < ((*l)->size / 2); i++ )
    {
        temp_data = hold_first->_data;
        hold_first->_data = hold_last->_data;
        hold_last->_data = temp_data;

        hold_first = hold_first->_next;
        hold_last = hold_last->_prev;
    }
}
void   handy_list_free         ( handy_list * l )
{
    // free every item in list and then remove them from the list
    while( (*l)->size > 0 )
    {
        free( (*l)->_first );
        (*l)->remove_front(l);
    }
}
