#include "m_events.h"
#include "stddef.h"
#include <stdarg.h>
#include <stdlib.h>

struct handler_list **list_h;

void attach_handler(int ev_num,handler_t func){
    struct handler_list *new_handler_list;
    	
	if(ev_num > EV_LAST){

		printf("MOD LOADING ERROR: mod tried attaching handler to invalid ev_num %d!!\n", ev_num);
		return;
	}


    if( list_h[ev_num] == 0){
        new_handler_list = list_h[ev_num] = malloc(sizeof(struct handler_list));
    }
    else {
        struct handler_list *it = list_h[ev_num];
        while(it->next){
            it = it->next;
        }
        new_handler_list = it->next = malloc(sizeof(struct handler_list));
    }

    new_handler_list->handler = func;
    new_handler_list->next = 0;
}

void signal_ev(int ev_num, int numargs, ...){
    struct handler_list *it = list_h[ev_num];
    va_list vl;
    va_start(vl, numargs);
    if(it && it->handler){
        while(it){
            it->handler(numargs, vl);
            it = it->next;
        }
    }

    va_end(vl);
}

void init_ev(){
    list_h = calloc(1,sizeof(struct handler_list*) * EV_LAST);


}
