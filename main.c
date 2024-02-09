#include <stdio.h>
#include "modules/menus.c"

int main(void)
{
    // create files;

    FILE * grades_file = fopen(GRADES_FILE, "a");
    FILE * students_file = fopen(GRADES_FILE, "a");
    fclose(grades_file);
    fclose(students_file);
    
    // call menus
    main_menu();

    return 0; // end

} // end main function
