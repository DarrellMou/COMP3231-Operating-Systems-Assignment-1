/* This file will contain your solution. Modify it as you wish. */
#include <types.h>
#include <lib.h>
#include <synch.h>
#include "cafe.h"

/* Some variables shared between threads */

static unsigned int ticket_counter; /* the next customer's ticket */
static unsigned int next_serving;   /* the barista's next ticket to serve */
static unsigned current_customers;  /* customers remaining in cafe */


/*
 * get_ticket: generates an ticket number for a customers next order.
 */

unsigned int get_ticket(void)
{
        unsigned int t;

        ticket_counter = ticket_counter + 1;
        t = ticket_counter;

        return t;
}

/*
 * next_ticket_to_serve: generates the next ticket number for a
 * barista for that barista to serve next.
 */

unsigned int next_ticket_to_serve(void)
{

        unsigned int t;

        next_serving = next_serving + 1;
        t = next_serving;

        return t;
}

/*
 * leave_cafe: a function called by a customer thread when the
 * specific thread leaves the cafe.
 */

void leave_cafe(unsigned long customer_num)
{
        (void)customer_num;

        current_customers = current_customers - 1;

}


/*
 * wait_to_order() and announce_serving_ticket() work together to
 * achieve the following:
 *
 * A customer thread calling wait_to_order will block on a synch primitive
 * until announce_serving_ticket is called with the matching ticket.
 *
 * A barista thread calling announce_serving_ticket will block on a synch
 * primitive until the corresponding ticket is waited on, OR there are
 * no customers left in the cafe.
 *
 * wait_to_order returns the number of the barista that will serve
 * the calling customer thread.
 *
 * announce_serving_ticket returns the number of the customer that the
 * calling barista thread will serve.
 */

unsigned long wait_to_order(unsigned long customer_number, unsigned int ticket)
{
        unsigned long barista_number = 0;

        (void) customer_number;
        (void) ticket;
      
        return barista_number;
}

unsigned long announce_serving_ticket(unsigned long barista_number, unsigned int serving)
{
        unsigned long cust = 0;

        (void) barista_number;
        (void) serving;

        return cust;
}

/* 
 * cafe_startup: A function to allocate and/or intitialise any memory
 * or synchronisation primitives that are needed prior to the
 * customers and baristas arriving in the cafe.
 */
void cafe_startup(void)
{

        ticket_counter = 0;
        next_serving = 0;
        current_customers = NUM_CUSTOMERS;

}   

/*
 * cafe_shutdown: A function called after baristas and customers have
 * exited to de-allocate any memory or synchronisation
 * primitives. Anything allocated during startup should be
 * de-allocated after calling this function.
 */

void cafe_shutdown(void)
{
}
                              
