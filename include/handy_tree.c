// TODO: Document code
#include "handy_btree.h"


handy_btree_iter handy_btree_traverse_in_order  ( handy_tree );
handy_btree_iter handy_btree_traverse_pre_order ( handy_tree );
handy_btree_iter handy_btree_traverse_post_order( handy_tree );


void  _handy_start_btree_iter   ( handy_btree_iter );
void * _handy_btree_iter_next   ( handy_btree_iter );
int _handy_btree_iter_count     ( handy_btree_iter );

void _handy_btree_in_order  ( handy_tree t, handy_btree_iter i )
{
    if( i->_count == i->_capacity )
    {
        void ** new_bucket = realloc( i->_bucket, i->_capacity + (i->_capacity / 4) );

        if( new_bucket )
        {
            i->_bucket = new_bucket;
            i->_capacity = i->_capacity + (i->_capacity / 4);
        }
    }

    if( t == NULL )
        return;
    _handy_btree_in_order( t->_left, i );
    i->_bucket[i->_count++] = t->_data;
    _handy_btree_in_order( t->_right, i );
}
void _handy_btree_pre_order ( handy_tree t, handy_btree_iter i )
{
    if( i->_count == i->_capacity )
    {
        void ** new_bucket = realloc( i->_bucket, i->_capacity + (i->_capacity / 4) );

        if( new_bucket )
        {
            i->_bucket = new_bucket;
            i->_capacity = i->_capacity + (i->_capacity / 4);
        }
    }

    if( t == NULL )
        return;
    i->_bucket[i->_count++] = t->_data;
    _handy_btree_in_order( t->_left, i );
    _handy_btree_in_order( t->_right, i );
}
void _handy_btree_post_order( handy_tree t, handy_btree_iter i )
{
    if( i->_count == i->_capacity )
    {
        void ** new_bucket = realloc( i->_bucket, i->_capacity + (i->_capacity / 4) );

        if( new_bucket )
        {
            i->_bucket = new_bucket;
            i->_capacity = i->_capacity + (i->_capacity / 4);
        }
    }

    if( t == NULL )
        return;
    _handy_btree_in_order( t->_left, i );
    _handy_btree_in_order( t->_right, i );
    i->_bucket[i->_count++] = t->_data;
}


handy_btree_iter  _handy_create_btree_iter()
{
    handy_btree_iter temp_iter = malloc( sizeof(*temp_iter) );

    temp_iter->_count = 0;
    temp_iter->_capacity = 1024;
    temp_iter->_current_pos = 0;

    temp_iter->start= _handy_start_btree_iter;
    temp_iter->next = _handy_btree_iter_next;
    temp_iter->count= _handy_btree_iter_count;

    temp_iter->_bucket = malloc( sizeof(void *) * temp_iter->_capacity );
}

handy_tree handy_create_btree( void * data, handy_tree left, handy_tree right )
{
    handy_tree temp_tree = malloc( sizeof(*temp_tree) );

    temp_tree->_data = data;
    temp_tree->_right = right;
    temp_tree->_left = left;

    temp_tree->traverse_in_order = handy_btree_traverse_in_order;
    temp_tree->traverse_pre_order= handy_btree_traverse_pre_order;
    temp_tree->traverse_post_order= handy_btree_traverse_post_order;

    return temp_tree;
}

handy_btree_iter handy_btree_traverse_in_order  ( handy_tree t )
{
    handy_btree_iter temp_iter = _handy_create_btree_iter();

    _handy_btree_in_order( t, temp_iter );

    return temp_iter;
}
handy_btree_iter handy_btree_traverse_pre_order ( handy_tree t )
{
    handy_btree_iter temp_iter = _handy_create_btree_iter();

    _handy_btree_pre_order( t, temp_iter );

    return temp_iter;
}
handy_btree_iter handy_btree_traverse_post_order( handy_tree t )
{
    handy_btree_iter temp_iter = _handy_create_btree_iter();

    _handy_btree_post_order( t, temp_iter );

    return temp_iter;
}

void  _handy_start_btree_iter   ( handy_btree_iter i )
{
    i->_current_pos = 0;
}
void * _handy_btree_iter_next   ( handy_btree_iter i )
{
    if( i->_current_pos >= i->_count )
        return NULL;
    if( i->_bucket == NULL )
        return NULL;
    return i->_bucket[i->_current_pos++];
}
int _handy_btree_iter_count     ( handy_btree_iter i )
{
    return i->_count;
}