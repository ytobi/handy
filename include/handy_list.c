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
    handy_Obj iter = (*l)->first;
    for( int i = 0; i < (*l)->size; i++ )
    {
        if( memcmp( &(iter->data), &item, iter->size ) == 0 )
            return i;
        iter = iter->next;
    }
    return -1;
}
bool   handy_list_add_front    ( handy_list * l, void * item )
{
    if( (*l)->size == 0 )
    {
        handy_Obj temp = malloc( sizeof( *temp ) );

       	temp->data = item;
        temp->size = sizeof( item );

        (*l)->last  = (*l)->first = temp;

        (*l)->size++;

        return true;
    }
    else if ( (*l)->size > 0 )
    {
        handy_Obj temp = malloc( sizeof( *temp ) );

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
        handy_Obj temp = malloc( sizeof( * temp ) );

        temp->data = item;
        temp->size = sizeof( item );

        (*l)->last  = (*l)->first = temp;

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
    else
    {
        handy_Obj iter;
        iter = (*l)->first;

        handy_Obj temp = malloc( sizeof( * temp ) );
        temp->data = item;
        temp->size = sizeof( item );

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
                    handy_Obj nodePrev = iter->prev;
                    handy_Obj nodeNext = iter->next;

                    nodePrev->next = temp;
                    nodeNext->prev = temp;

                    temp->prev = nodePrev;
                    temp->next = nodeNext;

                    (*l)->size++;
                    return true;
                }
            }
            iter = iter->next;
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
    char * handy_str_return = malloc( ((*l)->size + 3) * (*l)->first->size );

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
    if( at < 0 || at >= (*l)->size  )
        return NULL;
    else
    {
        handy_Obj iter;
        iter = (*l)->first;

        for( int i = 0; i < (*l)->size; i++ )
        {
            if( i == at )
            {
                if( i == 0 )
                    return ((*l)->get_front(l) );
                else if( i == (*l)->size - 1 )
                    return ((*l)->get_back(l) );
                else
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
        return NULL;
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
void * handy_list_remove_at    ( handy_list * l, int at )
{
    handy_Obj iter;
    iter = (*l)->first;

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
void * handy_list_reverse      (handy_list  * l)
{
    // The front point the end, and next and prev of every node
    // reversed.

    handy_Obj hold_first = (*l)->first;
    handy_Obj hold_last = (*l)->last;

    void * temp_data;

    // exchange front and back till we reach middle
    for( int i = 0 ; i < ((*l)->size / 2); i++ )
    {
        temp_data = hold_first->data;
        hold_first->data = hold_last->data;
        hold_last->data = temp_data;

        hold_first = hold_first->next;
        hold_last = hold_last->prev;
    }
}
void   handy_list_free         ( handy_list * l )
{
    // free every item in list and then remove them from the list
    while( (*l)->size > 0 )
    {
        free( (*l)->first );
        (*l)->remove_front(l);
    }
}
