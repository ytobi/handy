// TODO: Document code
#include "handy_tree.h"

void _handy_btree_in_order  ( handy_tree self, handy_tree_iter iter )
{
    if( iter->_count == iter->_capacity )
    {
        void ** new_bucket = realloc( iter->_bucket, iter->_capacity + (iter->_capacity / 4) );

        if( new_bucket )
        {
            iter->_bucket = new_bucket;
            iter->_capacity = iter->_capacity + (iter->_capacity / 4);
        }
    }

    if( self == NULL )
        return;
    _handy_btree_in_order( self->_left, iter );
    iter->_bucket[iter->_count++] = self->_data;
    _handy_btree_in_order( self->_right, iter );
}
void _handy_btree_pre_order ( handy_tree self, handy_tree_iter iter )
{
    if( iter->_count == iter->_capacity )
    {
        void ** new_bucket = realloc( iter->_bucket, iter->_capacity + (iter->_capacity / 4) );

        if( new_bucket )
        {
            iter->_bucket = new_bucket;
            iter->_capacity = iter->_capacity + (iter->_capacity / 4);
        }
    }

    if( self == NULL )
        return;
    iter->_bucket[iter->_count++] = self->_data;
    _handy_btree_in_order( self->_left, iter );
    _handy_btree_in_order( self->_right, iter );
}
void _handy_btree_post_order( handy_tree self, handy_tree_iter iter )
{
    if( iter->_count == iter->_capacity )
    {
        void ** new_bucket = realloc( iter->_bucket, iter->_capacity + (iter->_capacity / 4) );

        if( new_bucket )
        {
            iter->_bucket = new_bucket;
            iter->_capacity = iter->_capacity + (iter->_capacity / 4);
        }
    }

    if( self == NULL )
        return;
    _handy_btree_in_order( self->_left, iter );
    _handy_btree_in_order( self->_right, iter );
    iter->_bucket[iter->_count++] = self->_data;
}


handy_tree_iter handy_btree_traverse_in_order  ( handy_tree self )
{
    handy_tree_iter temp_iter;
    temp_iter = _handy_create_tree_iter();

    _handy_btree_in_order( self, temp_iter );

    return temp_iter;
}
handy_tree_iter handy_btree_traverse_pre_order ( handy_tree self )
{
    handy_tree_iter temp_iter = _handy_create_tree_iter();

    _handy_btree_pre_order( self, temp_iter );

    return temp_iter;
}
handy_tree_iter handy_btree_traverse_post_order( handy_tree self )
{
    handy_tree_iter temp_iter = _handy_create_tree_iter();

    _handy_btree_post_order( self, temp_iter );

    return temp_iter;
}

void  _handy_start_btree_iter   ( handy_tree_iter self )
{
    self->_current_pos = 0;
}
void * _handy_btree_iter_next   ( handy_tree_iter self )
{
    if( self->_current_pos >= self->_count )
        return NULL;
    if( self->_bucket == NULL )
        return NULL;
    return self->_bucket[self->_current_pos++];
}
int _handy_btree_iter_count     ( handy_tree_iter self )
{
    return self->_count;
}
bool _hand_tree_iter_isEnd      ( handy_tree_iter self )
{
    if( self->_current_pos >= self->_count )
        return true;
    return false;
}

handy_tree_iter  _handy_create_tree_iter()
{
    handy_tree_iter self = malloc( sizeof(*self) );

    self->_count = 0;
    self->_capacity = 1024;
    self->_current_pos = 0;

    self->restart= _handy_start_btree_iter;
    self->next  = _handy_btree_iter_next;
    self->count = _handy_btree_iter_count;
    self->isEnd = _hand_tree_iter_isEnd;

    self->_bucket = malloc( sizeof(void *) * self->_capacity );

    return self;
}
handy_tree handy_create_tree( void * data, handy_tree left, handy_tree right )
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
