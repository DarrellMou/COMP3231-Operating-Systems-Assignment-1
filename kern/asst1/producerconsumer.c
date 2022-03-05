/* This file will contain your solution. Modify it as you wish. */
#include <types.h>
#include <lib.h>
#include <synch.h>
#include "producerconsumer.h"

/* The bounded buffer uses an extra free slot to distinguish between
   empty and full. See
   http://www.mathcs.emory.edu/~cheung/Courses/171/Syllabus/8-List/array-queue2.html
   for details if needed. 
*/

#define BUFFER_SIZE (BUFFER_ITEMS + 1)

/* Declare any variables you need here to keep track of and
   synchronise the bounded buffer. The declaration of a buffer is
   shown below. It is an array of pointers to data_items.
*/


data_item_t * item_buffer[BUFFER_SIZE];

volatile int write_head, read_tail;

struct cv *empty;
struct cv *full;
struct lock *l;

/* The following functions test if the buffer is full or empty. They
   are obviously not synchronised in any way */

static bool is_full() {
        return (write_head + 1) % BUFFER_SIZE == read_tail;
}

static bool is_empty() {
        return write_head == read_tail;
}

/* consumer_receive() is called by a consumer to request more data. It
   should block on a sync primitive if no data is available in your
   buffer. It should not busy wait! Any concurrency issues involving
   shared state should also be handled. 
*/

data_item_t * consumer_receive(void)
{
        data_item_t * item;

        lock_acquire(l);
        while(is_empty()) {
                cv_wait(empty, l);
        }
        
        item = item_buffer[read_tail];
        read_tail = (read_tail + 1) % BUFFER_SIZE;

        cv_signal(full, l);
        lock_release(l);

        return item;
}

/* producer_send() is called by a producer to store data in the
   bounded buffer.  It should block on a sync primitive if no space is
   available in the buffer. It should not busy wait! Any concurrency
   issues involving shared state should also be handled.
*/

void producer_send(data_item_t *item)
{
        lock_acquire(l);
        while(is_full()) {
                cv_wait(full, l);
        }

        item_buffer[write_head] = item;
        write_head = (write_head + 1) % BUFFER_SIZE;

        cv_signal(empty, l);
        lock_release(l);
}

/* Perform any initialisation (e.g. of global data or synchronisation
   variables) you need here. Note: You can panic if any allocation
   fails during setup
*/

void producerconsumer_startup(void)
{
        write_head = read_tail = 0;
        empty = cv_create("empty");
        full = cv_create("full");
        l = lock_create("lock");
}

/* Perform your clean-up here */
void producerconsumer_shutdown(void)
{
        cv_destroy(empty);
        cv_destroy(full);
        lock_destroy(l);
}

