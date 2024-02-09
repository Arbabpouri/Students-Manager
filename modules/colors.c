#include <stdio.h>
#include "./enums.c"


void set_color(enum colors color)
{
    switch(color)
    {
        case WHITE:
        
            printf("%s", "\033[1;37m");
            break;
        
        case RED:
        
            printf("%s", "\033[1;31m");
            break;
        
        case GREEN:
        
            printf("%s", "\033[1;32m");
            break;
        
        case YELLOW:
        
            printf("%s", "\033[1;33m");
            break;
        
        case BLUE:
        
            printf("%s", "\033[1;34m");
            break;
        
        case PURPLE:
        
            printf("%s", "\033[1;35m");
            break;
        
        case CYAN:
        
            printf("%s", "\033[1;36m");
            break;
        
    } // end switch
} // end set_color function
