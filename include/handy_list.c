#include "handy_list.h"

int    handy_list_contain       ( handy_list self, void * item );
bool   handy_list_add_front     ( handy_list self, void * item );
bool   handy_list_add_back      ( handy_list self, void * item );
bool   handy_list_add_at        ( handy_list self, void * item, int at );
bool   handy_list_empty         ( handy_list self );

void * handy_list_get_front     ( handy_list self );
void * handy_list_get_back      ( handy_list self );
void * handy_list_get_at        ( handy_list self, int at );
bool   handy_list_rem_front     ( handy_list self );
bool   handy_list_rem_back      ( handy_list self );
bool   handy_list_rem_at        ( handy_list self, int at );
void   handy_list_reverse       ( handy_list self );
void   handy_list_free          ( handy_list self );
int    handy_list_length        ( handy_list self );

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
int   handy_list_contain        ( handy_list self, void * item )
{
    _handy_list_obj iter = self->_first;
    for( int i = 0; i < self->_size; i++ )
    {
        if( memcmp( &(iter->_data), &item, sizeof(iter->_data) ) == 0 )
            return i;
        iter = iter->_next;
    }
    return -1;
}
bool   handy_list_add_front     ( handy_list self, void * item )
{
    if( self->_size == 0 )
    {
        _handy_list_obj temp = malloc( sizeof( *temp ) );

       	temp->_data = item;

        self->_last  = self->_first = temp;

        self->_size++;

        return true;
    }
    else if ( self->_size > 0 )
    {
        _handy_list_obj temp = malloc( sizeof( *temp ) );

        temp->_data = item;
        temp->_next = self->_first;

        self->_first->_prev = temp;
        self->_first = temp;
        self->_size++;

        return true;
    }
    return false;
}
bool   handy_list_add_back      ( handy_list self, void * item )
{
    if( self->_size == 0 )
    {
        _handy_list_obj temp = malloc( sizeof( * temp ) );

        temp->_data = item;

        self->_last  = self->_first = temp;

        self->_size++;

        return true;
    }
    else if ( self->_size > 0 )
    {
        _handy_list_obj temp = malloc( sizeof( * temp ) );

        temp->_data = item;

        temp->_prev = self->_last;
        self->_last->_next = temp;

        self->_last = temp;
        self->_size++;

        return true;
    }
    return false;
}
bool   handy_list_add_at        ( handy_list self, void *item, int at )
{
    if( at <= 0 )
        return (self->add_front(self, item));
    else if( at >= self->_size )
        return ( self->add_back(self, item) );
    else
    {
        _handy_list_obj iter;
        iter = self->_first;

        _handy_list_obj temp = malloc( sizeof( * temp ) );
        temp->_data = item;

        for( int i = 1; i < self->_size; i++ )
        {
            if( i == at )
            {
                // handy_obj nodePrev = iter->_prev;
                _handy_list_obj nextNode = iter->_next;

                iter->_next = temp;
                nextNode->_prev = temp;

                temp->_prev = iter;
                temp->_next = nextNode;

                self->_size++;
                return true;

            }
            iter = iter->_next;
        }
    }
    return false;
}
bool   handy_list_empty         ( handy_list self )
{
    return self->_size == 0 ? true : false;
}
void * handy_list_get_front     ( handy_list self )
{
    if( self->_size == 0 )
    {
        return NULL;
    }
    else if( self->_size > 0 )
    {
        return  self->_first->_data;
    }
    return NULL;
}
void * handy_list_get_back      ( handy_list self )
{
    if( self->_size == 0 )
    {
        return NULL;
    }
    else if( self->_size > 0 )
    {
        return  self->_last->_data;
    }
    return NULL;
}
void * handy_list_get_at        ( handy_list self, int at )
{
    if( at < 0 || at >= self->_size  )
        return NULL;
    else
    {
        _handy_list_obj iter;
        iter = self->_first;

        for( int i = 0; i < self->_size; i++ )
        {
            if( i == at )
            {
                if( i == 0 )
                    return (self->get_front(self) );
                else if( i == self->_size - 1 )
                    return (self->get_back(self) );
                else
                    return iter->_data;
            }
            iter = iter->_next;
        }
    }
    return NULL;
}
bool  handy_list_rem_front      ( handy_list self )
{
    if( self->_size == 1 )
    {
        self->_first = ( free( self->_first ), NULL );
        self->_first = self->_last = NULL;
        self->_size--;
        return true;
    }
    else if( self->_size > 1 )
    {
        self->_first = self->_first->_next;

        self->_first->_prev = ( free(self->_first->_prev), NULL );
        self->_size--;
        return true;
    }
    return false;
}
bool  handy_list_rem_back       ( handy_list self )
{

    if( self->_size == 1 )
    {
        self->_first = ( free(self->_first), NULL );
        self->_first = self->_last = NULL;
        self->_size--;

        return true;
    }
    else if( self->_size > 1 )
    {
        self->_last = self->_last->_prev;

        self->_size--;

        self->_last->_next = ( free(self->_last->_next), NULL );

        return true;
    }
    return false;
}
bool  handy_list_rem_at         ( handy_list self, int at )
{
    _handy_list_obj iter;
    iter = self->_first;

    if( at == 0 )
        return (self->rem_front(self) );
    else if( at == self->_size - 1 )
        return (self->rem_back(self) );
    else if( at > 0 || at < self->_size - 1 )
    {
        for( int i = 0; i < self->_size; i++ )
        {
            if( i == at )
            {

                iter->_prev->_next = iter->_next;
                iter->_next->_prev = iter->_prev;
                self->_size--;

                iter = ( free(iter), NULL );
                return true;
            }
            iter = iter->_next;
        }
    }

    return false;
}
void handy_list_reverse         ( handy_list self )
{
    // The front point the end, and _next and _prev of every node
    // reversed.

    _handy_list_obj hold_first = self->_first;
    _handy_list_obj hold_last = self->_last;

    void * temp_data;

    // exchange front and back till we reach middle
    for( int i = 0 ; i < (self->_size / 2); i++ )
    {
        temp_data = hold_first->_data;
        hold_first->_data = hold_last->_data;
        hold_last->_data = temp_data;

        hold_first = hold_first->_next;
        hold_last = hold_last->_prev;
    }
}
void   handy_list_free          ( handy_list self )
{
    // free every item in list and then remove them from the list
    while( self->_first != self->_last )
    {
        self->_first = self->_first->_next;

        self->_first->_prev = (free( self->_first->_prev ), NULL);
    }
    self->_first = (free( self->_first ), NULL);
    self->_size = 0;
}
int    handy_list_length        ( handy_list self )
{
    return self->_size;
}
