#include <stdlib.h>
#include <stdbool.h>

#ifndef HANDY_HANDY_TREE_H
#define HANDY_HANDY_TREE_H

typedef struct _handy_tree * handy_tree;

#ifndef HANDY_HANDY_TREE_ITER_H
#define HANDY_HANDY_TREE_ITER_H
typedef struct _handy_tree_iter * handy_tree_iter;
struct _handy_tree_iter
{
    int _capacity;
    int _count;
    int _current_pos;
    bool (*isEnd)   ( handy_tree_iter self );
    void * (*next)  ( handy_tree_iter self );
    void   (*restart)( handy_tree_iter self );
    int    (*count) ( handy_tree_iter self );
    void ** _bucket;
};
#endif //HANDY_HANDY_BTREE_ITER_H

struct _handy_tree
{
    handy_tree_iter (*traverse_in_order)   ( handy_tree self );
    handy_tree_iter (*traverse_pre_order)  ( handy_tree self );
    handy_tree_iter (*traverse_post_order) ( handy_tree self );

    void * _data;
    handy_tree _left;
    handy_tree _right;

};

handy_tree handy_create_tree( void * data, handy_tree left, handy_tree right );
handy_tree_iter  _handy_create_tree_iter();

#endif //HANDY_HANDY_TREE_H
