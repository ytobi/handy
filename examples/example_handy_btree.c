#include <stdio.h>
#include "../include/handy_btree.h"


int main()
{
    // create a tree with left and right nodes
    handy_tree tree = handy_create_btree( "root",
                                          handy_create_btree("left", NULL, NULL),
                                          handy_create_btree("right", NULL, NULL) );


    // traverse tree and print out order visited nodes
    handy_btree_iter iter = tree->traverse_post_order(tree);

    for( int i = 0; i < iter->count( iter ); iter->start(iter), i++ )
        printf( " -%s- ", iter->next(iter) );
}