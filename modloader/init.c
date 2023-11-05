#include "m_events.h"
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>
#include <linux/limits.h>

#include "gui.h" 

void title_text(int numargs, va_list vl){
  //  va_start(vl, numargs);

    int *gui_id = va_arg(vl,int*);
    int label = gui_label(*gui_id,"modloader 0.1", GUI_SML, 0,0 );
    gui_layout(label,8,-8);
   // va_end(vl);

}

void modl_init(){
    
    init_ev();

    struct stat s;
    int err = stat("./mods", &s);
    if(err == -1 || !S_ISDIR(s.st_mode)) {
        if(errno == ENOENT) {
            mkdir("mods", 0777);   
        }
    }

    DIR *d;
    struct dirent *dir;
    chdir("./mods");
    d = opendir(".");
    if(d){
        while((dir = readdir(d)) != NULL){

            if(!strcmp(dir->d_name, "..") || !strcmp(dir->d_name, ".")){
                continue;
            }
            struct stat s2;
            int err = stat(dir->d_name, &s2);

            if(S_ISDIR(s2.st_mode)) {
               continue;
            }
            printf("%s%s\n", "Loading mod ", dir->d_name);

            char actualpath [PATH_MAX+1];
            realpath(dir->d_name, actualpath);
            void *mod;
            mod=dlopen(actualpath,RTLD_NOW);
            
            void (*initfunc)() = (dlsym(mod, "mod_init"));
            initfunc();
            
        }
        closedir(d);
    }
    chdir("..");

    attach_handler(EV_GUI_TITLE_INIT_POST, title_text);

}