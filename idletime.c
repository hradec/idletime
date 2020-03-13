#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/scrnsaver.h>

float GetIdleTime () {
        float idle_time;
        static XScreenSaverInfo *mit_info;
        Display *display;
        int screen;
        mit_info = XScreenSaverAllocInfo();
        if((display=XOpenDisplay(NULL)) == NULL) { return(-1); }
        screen = DefaultScreen(display);
        XScreenSaverQueryInfo(display, RootWindow(display,screen), mit_info);
        idle_time = (mit_info->idle) / 1000.0;
        XFree(mit_info);
        XCloseDisplay(display); 
        return (float)idle_time;
}

int main(int argc, char *argv[]) {

    int opt;
    char *ctype="%d\n";
    // put ':' in the starting of the 
    // string so that program can  
    //distinguish between '?' and ':'  
    while((opt = getopt(argc, argv, "fh:")) != -1){
        switch(opt){
            case 'f':
                ctype="%f\n";
                break;
        }
    }
    printf(ctype, GetIdleTime());
}
