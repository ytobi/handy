#include <stdio.h>
#include "../include/handy_tree.h"


int main()
{
    // create a tree with left and right nodes
    handy_tree tree = handy_create_tree( "root",
                                          handy_create_tree("left", NULL, NULL),
                                          handy_create_tree("right", NULL, NULL) );


    // traverse tree and print out order visited nodes
    handy_tree_iter iter = tree->traverse_in_order(tree);

    int i = 0;
    for( ; iter->isEnd(iter) == false; )
        printf( " -%s- \n", iter->next(iter) );
}