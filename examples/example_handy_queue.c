#include "../include/handy_queue.h"


int main()
{
    handy_queue queue;                                      // declear handy_queue object queue

    queue = handy_create_queue();                           // initialize queue


    for( int i = 0 ; i < 10; i++ )                          // add, aka enqueue 10 item in queue
    {
        queue->enqueue( &queue, i );
    }

    queue->contain( &queue, 7 );                            // if find '7' return 1, else 0

    int zero = queue->front( &queue );                      // get item at front aka '0'

    queue->reverse( &queue );                               // reverse queue

    int nine = queue->dequeue( &queue );                    // remove item in front queue


    queue->free( &queue );                                  // free memory allocated in queue

    free( queue );                                          // finally cleanup, free queue itself

    return 0;
}
