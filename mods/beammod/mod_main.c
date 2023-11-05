#include "m_events.h"
#include <stdio.h>
#include <dlfcn.h>

//void(*attach_handler)(int, handler_t);


void confmod(int sz, va_list args){

        printf("%s\n", "conf handler");

}
void mod_init(){
    printf("%s\n", "helo world");

    attach_handler(EV_GUI_CONF_INIT_POST, confmod);
}