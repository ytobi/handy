#include <stdlib.h>

#ifndef HANDY_HANDY_BTREE_H
#define HANDY_HANDY_BTREE_H

typedef struct _handy_btree * handy_tree;

#ifndef HANDY_HANDY_BTREE_ITER_H
#define HANDY_HANDY_BTREE_ITER_H
typedef struct _handy_btree_iter * handy_btree_iter;
struct _handy_btree_iter
{
    int _capacity;
    int _count;
    int _current_pos;
    void * (*next)  ( handy_btree_iter );
    void   (*start) ( handy_btree_iter );
    int    (*count) ( handy_btree_iter );
    void ** _bucket;
};
#endif //HANDY_HANDY_BTREE_ITER_H

struct _handy_btree
{
    handy_btree_iter (*traverse_in_order)   ( handy_tree );
    handy_btree_iter (*traverse_pre_order)  ( handy_tree );
    handy_btree_iter (*traverse_post_order) ( handy_tree );

    void * _data;
    handy_tree _left;
    handy_tree _right;

};

handy_tree handy_create_btree( void * data, handy_tree left, handy_tree right );
handy_btree_iter  _handy_create_btree_iter();

#endif //HANDY_HANDY_BTREE_H
