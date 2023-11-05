#include <stdarg.h>

enum events{
    EV_NULL, EV_GUI_TITLE_INIT_PRE, EV_GUI_TITLE_INIT_POST, EV_GUI_CONF_INIT_POST, EV_LAST

};

typedef void(*handler_t)(int,va_list);

struct handler_list{
    handler_t handler;
    struct handler_list *next;
};

void signal_ev(int ev_num, int numargs, ...);

void init_ev();

void attach_handler(int ev_num,handler_t func);