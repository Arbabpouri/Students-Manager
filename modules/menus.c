#include <stdio.h>
#include <stdlib.h>
#include "./functions.c"

// start define functions prototypes

void students_menu(void);
void grades_menu(void);
void student_change_informations_menu(void);
void add_student_menu(void);
void student_change_informations_menu_gets(unsigned int select);
void remove_student_menu(void);
void add_student_grades_menu(const unsigned int stn);

// end define functions prototypes

// define functions

// ------------------------------------------------------ functions for all -----------------------------------------------------------

unsigned int get_stn(void)
{
    unsigned int stn;
    set_color(CYAN);
    printf("%s", "please enter stn code for search : ");
    set_color(BLUE);
    fscanf(stdin, "%10u", &stn);

    return stn;
}

// -------------------------------------------------------- students menus ------------------------------------------------------------

void main_menu(void)
{

    unsigned int select;
    unsigned char show = 1;

    while (!feof(stdin) /*ctrl + z in windows || ctrl + d in linux and mac*/ || select == 3 /*exit code*/)
    {

        if (show)
        {
            set_color(YELLOW);
            puts("⠀⠀⠀⠀⠀⠀⠀⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⠀");
            puts("⠀⠀⠀⠀⢀⣤⣀⠙⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀");
            puts("⠀⠀⠀⠀⣿⣿⣿⡆⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀");
            puts("⠀⠀⠀⠀⢻⣿⡿⠃⣸⣿⣿⠿⠿⠟⠛⠛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀");
            puts("⠀⠀⣀⣠⣤⣈⣠⣤⣠⣤⣤⡴⠶⠶⠛⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀");
            puts("⠀⣾⡿⣿⣿⣿⣿⣿⡏⢠⣤⣤⣶⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀");
            puts("⠀⣿⡇⢸⣿⣿⣿⣿⠇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀");
            puts("⠀⣿⡇⢸⣿⣿⣿⣿⠀⣈⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⠉⠀");
            puts("⠀⣿⡇⢸⣿⠟⣿⡏⠀⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠀⠀");
            puts("⠀⠀⠀⢸⣿⠀⣿⡇⠀⠀⢀⣾⣷⣆⠀⠀⠀⣰⣾⣶⡀⠀⠀⢀⣶⣿⣆⠀⠀⠀");
            puts("⠀⠀⠀⢸⣿⠀⣿⡇⠀⠀⢸⣿⣿⣿⠀⠀⠀⣿⣿⣿⡇⠀⠀⢸⣿⣿⣿⠀⠀⠀");
            puts("⠀⠀⠀⢸⣿⠀⣿⡇⠀⠀⠀⠙⠛⠁⠀⠀⠀⠈⠛⠋⠀⠀⠀⠀⠙⠛⠁⠀⠀⠀");
            puts("⠀⠀⠀⢸⣿⠀⣿⡇⠀⠀⢀⣾⣿⣦⠀⠀⠀⣰⣿⣷⣄⠀⠀⢀⣾⣿⣦⡀⠀⠀");
            puts("⠀⠀⠀⠘⠛⠀⠛⠃⠀⠀⠚⠛⠛⠛⠓⠀⠐⠛⠛⠛⠛⠂⠀⠚⠛⠛⠛⠓⠀⠀");
            puts("\n\n");
            set_color(PURPLE);
            puts("[1] - Students");
            puts("[2] - Grades");
            puts("[3] - Exit");
            set_color(WHITE);
        }
        set_color(BLUE);
        fprintf(stdout, "%s", "enter -> ");
        set_color(CYAN);
        fscanf(stdin, "%u", &select);
        set_color(WHITE);

        switch (select)
        {

        case 1: // Students menu
            students_menu();
            show = 1;
            break;

        case 2: // Grades menu
            grades_menu();
            show = 1;
            break;

        case 3:
            set_color(RED);
            puts("ok my friend, exited :)");
            set_color(WHITE);
            return;

        default: // else
            set_color(RED);
            puts("bad select, please try agein");
            set_color(WHITE);
            show = 0;
            break;
        }
    }

} // end main menu function

void students_menu(void)
{

    unsigned int select;
    unsigned char show = 1;

    while (!feof(stdin))
    {

        if (show)
        {
            set_color(CYAN);
            puts("      _ _");
            puts(" .-. | | |");
            puts(" |M|_|A|N|");
            puts(" |A|a|.|.|<\\");
            puts(" |T|r| | | \\\\");
            puts(" |H|t|M|Z|  \\\\");
            puts(" | |!| | |   \\>  ");
            puts("................");

            set_color(BLUE);

            puts("students menu\t\t");
            puts("\n\n");
            puts("[1] - Add student");
            puts("[2] - Remove student");
            puts("[3] - Change informations");
            puts("[4] - back to main menu");
            puts("\n");
        }
        set_color(YELLOW);
        fprintf(stdout, "%s", "enter code -> ");
        set_color(GREEN);
        fscanf(stdin, "%u", &select);

        switch (select)
        {
        case 1:
            add_student_menu();
            break;

        case 2:
            remove_student_menu();
            break;

        case 3:
            student_change_informations_menu();
            break;

        case 4:
            return;

        default:
            set_color(RED);
            puts("bad command");
            break;
        }
    }
}

void add_student_menu(void)
{
    // this function for get information for pas to add_student function to add to students.txt
    student student;

    set_color(GREEN);
    printf("%s", "enter first name -> ");
    set_color(RED);
    fscanf(stdin, "%25s", student.first_name); // get first name
    set_color(GREEN);
    printf("%s", "enter last name -> ");
    set_color(RED);
    fscanf(stdin, "%25s", student.last_name); // get last name
    set_color(GREEN);
    printf("%s", "enter stn -> ");
    set_color(RED);
    fscanf(stdin, "%d", &student.stn); // get student code : stn
    set_color(GREEN);
    printf("%s", "enter age -> ");
    set_color(RED);
    fscanf(stdin, "%u", &student.age); // get student age
    set_color(WHITE);
    unsigned int result = add_student(student); // add to students.txt with call this function

    switch (result) // check returned result
    {
    case OK:
        set_color(GREEN);
        fprintf(stdout, "%s,%s,%u,%u - %s", student.first_name, student.last_name, student.stn, student.age, "add to students.txt");
        break;

    default:
        set_color(RED);
        puts("error in add student, please try agein");
        break;
    }

    return;

} // end add_student_menu function

void remove_student_menu(void)
{
    unsigned int stn = get_stn();

    unsigned int result = remove_student(stn);

    switch (result)
    {
    case OK:
        set_color(GREEN);
        fprintf(stdout, "%s %d %s", "student with stn code:", stn, "was removed\n");
        break;

    case STUDENT_NOT_FOUND:
        set_color(YELLOW);
        puts("student with this stn not found");
        break;

    default:
        set_color(RED);
        puts("bad command");
        break;
    }
}

void student_change_informations_menu(void)
{
    unsigned int select;

    while (!feof(stdin))
    {
        set_color(PURPLE);
        puts("\t\tStudent Change Informations Menu .");
        puts("[1] - First Name");
        puts("[2] - Last Name");
        puts("[3] - Stn");
        puts("[4] - Age");
        puts("[5] - Back to student menu");
        set_color(RED);
        printf("%s", "enter -> ");
        set_color(GREEN);
        fscanf(stdin, "%d", &select);

        switch (select)
        {
        case 1:
        case 2:
        case 3:
        case 4:
            student_change_informations_menu_gets(select);
            break;
        case 5:
            return;
            break;

        default:
            set_color(RED);
            puts("Bad command");
            break;
        }
    }

    return;
}

void student_change_informations_menu_gets(unsigned int select)
{

    unsigned int stn = get_stn();

    if (search_student_in_students_with_stn(stn) != STUDENT_ALREADY_EXIST)
    {
        fprintf(stdout, "%s %u %s", "student with stn :", stn, "not found\n");
        return;
    } // end if

    while (!feof(stdin))
    {

        switch (select)
        {

        case FIRST_NAME:
        case LAST_NAME:

            char *name;
            fprintf(stdout, "%s", "please enter new name: ");
            fscanf(stdin, "%s", name);

            if (select == FIRST_NAME)
            {
                change_first_name(stn, name);
            }
            else
            {
                change_last_name(stn, name);
            }

            return;

        case STN:

            unsigned int new_stn;
            printf("%s", "please enter new stn : ");
            fscanf(stdin, "%u", &new_stn);
            unsigned int status = change_stn(stn, new_stn);

            if (status == STUDENT_ALREADY_EXIST)
            {
                puts("this stn is already exist, please try agein");
            }
            else
            {

                return;
            }
            break;

        case AGE:

            unsigned int new_age;
            printf("%s", "please enter new age : ");
            fscanf(stdin, "%u", &new_age);
            change_age(stn, new_age);
            return;

        default:
            puts("bad select");
            return;
        } // end switch
    }     // end while

    return;
}

// -------------------------------------------------------- grades menus ------------------------------------------------------------

void remove_student_grade_menu(const unsigned int stn);
void change_student_grades_menu(const unsigned int stn);
void print_grades_with_name(void);
void print_faild_grades_with_name(void);
void print_avarage_grades_student_with_name(void);
void print_students_who_faild_grades_lesson_with_name(void);
void print_students_who_passed_lesson_z_with_score_x_menu(void);
void print_avarage_lesson_x_in_college(void);
void print_conditionalـstudents(void);
void print_name_and_avarage_all_students(void);
void print_lesson_which_not_have_faild_grades(void);
void print_lesson_and_avarage_students(void);

void grades_menu(void)
{

    unsigned int select;
    unsigned int show = 1;
    unsigned int stn;
    while (!feof(stdin))
    {

        if (show)
        {
            set_color(RED);

            puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
            puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣶⡿⠿⠛⣳⡶⢷⡞⣾⠛⠋⢒⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
            puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠤⣾⡿⢟⠁⠶⡆⠒⢲⠾⢀⣴⣿⠙⣲⣶⣶⠍⢀⠻⢦⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
            puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠚⣡⠄⢩⡽⢃⣐⣯⣧⣤⣞⣤⣿⣿⣿⣶⣿⣿⣇⡄⠀⢀⠾⣿⣷⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
            puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠻⢡⡖⠃⠀⣼⣏⣾⣿⣿⣿⣿⣿⣿⣟⣛⢿⣿⣿⣿⣿⣿⣇⡀⠀⠚⠚⢿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
            puts("⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⠉⠉⠀⠙⣧⢲⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⡀⠙⢿⣿⣿⣿⣶⣦⣤⣤⡹⣿⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀");
            puts("⠀⠀⠀⢀⣀⣤⠤⠺⠛⠁⠀⠀⣴⣿⣿⠟⠋⣵⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠀⠉⠻⢿⣿⣿⣿⣿⣷⣿⣿⡟⢦⠀⠀⠀⠀⠀⠀⠀");
            puts("⢀⣤⠶⠏⠈⠈⠀⠁⢀⣤⣾⣾⢿⠟⠁⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀⠀⠀⠀⠙⠛⠻⣿⣿⣿⣿⣷⠈⢣⡀⠀⠀⠀⠀⠀");
            puts("⣿⡯⠻⠆⠀⠀⢀⣴⣿⠟⠋⠀⠁⠀⠀⠀⣿⣿⣿⣿⣿⣿⠿⣿⡿⢿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠛⢻⣿⣿⣿⣦⠀⠙⢦⡀⠀⠀⠀");
            puts("⡏⠈⣠⣤⣤⣶⠟⠉⢻⡆⠀⠀⠀⠀⠀⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣷⣤⣀⠙⢦⡀⠀");
            puts("⣇⠀⠙⠛⠻⣿⣧⣤⣤⣿⣶⣤⣄⠀⠀⠀⠀⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣽⣿⣿⣿⣿⣿⠇⠀⠙⢆");
            puts("⠈⠲⢄⡀⠀⠈⠉⠙⠛⢻⣿⣿⣿⣿⣷⣶⣤⣄⡙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⣿⣿⣿⣿⣿⣶⣦⣄⠀");
            puts("⠀⠀⠀⠉⠑⠲⠤⣴⣃⠀⡘⠃⠀⡀⢨⢴⢛⢻⣿⣿⣭⣿⣿⣿⣿⠿⣛⣉⣀⣀⣀⡠⢤⠤⢤⣖⠉⢀⣤⣾⣿⣿⣿⣿⣿⣿⣿⠿⠿⠛⠋⡰");
            puts("⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠒⠦⣄⠆⠀⠁⢼⠟⠉⣬⢻⠦⣤⣹⣟⠿⣟⢿⣟⠛⢿⣿⣶⡶⢾⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⠁⢀⠀⣀⠤⠚⠁");
            puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠺⣜⡠⠞⡳⣄⡀⠀⠘⠁⢙⠠⠟⠀⡿⣷⠺⣌⢻⣿⠺⣿⣿⣿⣿⣿⣿⡿⢃⣀⣠⠖⠚⠉⠀⠀⠀⠀");
            puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠓⠦⣄⡉⠃⠀⠀⠀⠀⠀⠀⠀⠸⡆⠹⢆⣿⢠⠘⣿⢿⣿⠿⠛⣠⠜⠋⠀⠀⠀⠀⠀⠀⠀⠀");
            puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠒⠢⠤⠤⣀⣠⣄⣀⠙⠀⠀⣡⣈⣀⣉⠤⠽⠓⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
            puts("\n");
            puts("[1] - add student grades");
            puts("[2] - delete student grade");
            puts("[3] - delete student grades");
            puts("[4] - change grades");
            puts("[5] - print grades for student with name : Z");
            puts("[6] - print faild grades student with name : Z");
            puts("[7] - print avarage grades student with name : Z");
            puts("[8] - print stundets which faild grades lesson with name : Z");
            puts("[9] - print students which passed grades [Z] lesson with grade [x]");
            puts("[10] - print avarage college with lesson name [X]");
            puts("[11] - print name faild grades students"); // mashruti ha
            puts("[12] - print name and avarage students");
            puts("[13] - print lesson which not have faild grades");
            puts("[14] - print lesson name and avarage students on lesson");
            puts("[15] - back to main menu");
        } // end if

        // pink color
        set_color(GREEN);
        fprintf(stdout, "%s", "enter -> ");
        set_color(CYAN);
        fscanf(stdin, "%u", &select);

        if (select >= 1 && select <= 4)
        {
            stn = get_stn();

            unsigned int result = search_student_in_students_with_stn(stn);

            

            if (result == STUDENT_NOT_FOUND)
            {
                puts("* - this stn not found in students list, in first section add new student with this stn so back to this part");
                return;
            } // end if

            result = search_student_in_grades_with_stn(stn);
            if (result == STUDENT_NOT_FOUND && select != 1)
            {
                puts("* - this stn not found in students list, in first section add grade student with this stn so back to this part");
                return;
            }
        } // end if

        switch (select)
        {
        case 1:
            add_student_grades_menu(stn);
            show = 1;
            break;

        case 2:
        case 3:
            remove_student_grade_menu(stn);
            show = 1;
            break;
        case 4:
            change_student_grades_menu(stn);
            show = 1;
            break;
        case 5:
            print_grades_with_name();
            show = 0;
            break;

        case 6:
            print_faild_grades_with_name();
            show = 0;
            break;
        case 7:
            print_avarage_grades_student_with_name();
            show = 0;
            break;
        case 8:
            print_students_who_faild_grades_lesson_with_name();
            show = 0;
            break;
        case 9:
            print_students_who_passed_lesson_z_with_score_x_menu();
            show = 0;
            break;
        case 10:
            print_avarage_lesson_x_in_college();
            show = 0;
            break;
        case 11:
            print_conditionalـstudents();
            show = 1;
            break;
        case 12:
            print_students_with_avarage();
            show = 1;
            break;
        case 13:
            print_subject_without_failed();
            show = 0;
            break;
        case 14:
            print_subject_name_and_students_avarage_score();
            show = 0;
            break;

        case 15:
            return;

        default:
            set_color(RED);
            puts("* - bad select, please try agein - *");
            show = 0;
            break;
        } // end switch

    } // end while
} // end grades_menu function

void add_student_grades_menu(const unsigned int stn)
{

    // this function for get grades from admin and save to file

    unsigned int cancel = 1;
    grade new_grade;
    new_grade.unit = 0;
    new_grade.score = 21;

    while (!feof(stdin) && cancel)
    {
        new_grade.unit = 0;
        new_grade.score = 21.0;

        while (1)
        {
            set_color(PURPLE);
            printf("%s", "* - enter lesson name : ");
            fscanf(stdin, "%25s", new_grade.name);

            if (search_grade_name_in_grades(stn, new_grade.name) == LESSON_NOT_FOUND)
            {
                break;
            }
            else
            {
                set_color(RED);
                puts("* - lesson with this name in already exist - *");
            }
        }
        // 0 < x <= 4
        while (!(new_grade.unit > 0 && new_grade.unit <= 4))
        {
            set_color(BLUE);
            printf("%s", "* - unit : ");
            fscanf(stdin, "%u", &new_grade.unit);
        }

        while (!(new_grade.score >= 0.0 && new_grade.score <= 20.0))
        {
            set_color(CYAN);
            printf("%s", "* - score : ");
            fscanf(stdin, "%f", &new_grade.score);
        }

        unsigned int result = add_grade(stn, new_grade);
        set_color(YELLOW);
        printf("%s", " * - if ended send 0 else 1 -> ");
        fscanf(stdin, "%u", &cancel);
    }

} // end add_student_grades function

void remove_student_grade_menu(const unsigned int stn)
{

    // this function for delete

    int i;
    unsigned int select;
    unsigned int len = 0;
    unsigned int delete_all = 0;
    unsigned int cancel = 0;
    unsigned int result;

    grade *grades = get_grades_with_stn(stn, &len);

    if (len <= 0)
    {
        set_color(RED);
        puts("* - grades not found - *");
        return;
    } // end if

    for (i = 0; i < len; i++)
    {
        set_color(GREEN);
        printf("* - [%d] - name : [%s] - unit : [%d] - score : [%f] . - *\n", i + 1, grades[i].name, grades[i].unit, grades[i].score);
    } // end for

    set_color(RED);
    printf("[%d] - %s\n", ++i, "delete all");
    delete_all = i;
    set_color(GREEN);
    printf("[%d] - %s\n", ++i, "cancel and back to grades menu");
    cancel = i;

    while (!feof(stdin))
    {
        set_color(BLUE);
        printf("%s", "select number -> ");
        fscanf(stdin, "%d", &select);

        if (select > 0 && select <= delete_all)
        {

            if (select == delete_all)
            {
                result = delete_student_grades(stn);
            } // end if
            else
            {
                result = delete_student_grade(stn, grades[select - 1].name);
            } // end else

            if (result == ERROR)
            {
                set_color(RED);
                puts("Error :/");
            } // end if
            else
            {
                set_color(GREEN);
                puts("removed");
            } // end else

            return;

        } // end if

        else if (select == cancel)
        {
            break;
        }
        set_color(RED);
        puts("bad select, try agien");

    } // end while

} // end ... function

void change_student_grades_menu(const unsigned int stn)
{
    int i;
    unsigned int select;
    unsigned int len = 0;
    unsigned int cancel = 0;
    float new_score;

    grade *grades = get_grades_with_stn(stn, &len);

    if (len <= 0)
    {
        set_color(RED);
        puts("grades not found");
        return;
    } // end if

    for (i = 0; i < len; i++)
    {
        set_color(GREEN);
        printf("* - [%d] - name : [%s] - unit : [%d] - score : [%f] . - *\n", i + 1, grades[i].name, grades[i].unit, grades[i].score);
    } // end for

    set_color(BLUE);
    printf("[%d] - %s\n", ++i, "cancel and back to grades menu");

    cancel = i;

    while (!feof(stdin) || select == cancel)
    {
        set_color(YELLOW);
        printf("%s", "select number -> ");
        fscanf(stdin, "%d", &select);

        if (select > 0 && select <= cancel - 1)
        {

            while (!feof(stdin))
            {
                set_color(PURPLE);
                printf("%s", "New score : ");
                fscanf(stdin, "%f", &new_score);

                if (new_score >= 0.0 && new_score <= 20.0)
                {
                    unsigned int result = change_student_score(stn, grades[select - 1].name, new_score);

                    if (result == OK)
                    {
                        set_color(GREEN);
                        puts("* score was changed *");
                        return;
                    } // end if
                    set_color(RED);
                    puts("error, try agien");

                    return;

                } // end if
                else
                {
                    set_color(RED);
                    puts("[score >= 0 and score <= 20]");
                } // end else
            }     // end while
            set_color(RED);
            puts(":/, try agien");
            return;

        } // end if
        set_color(RED);
        puts("bad select, try agien");

    } // end while

} // end ... function

void print_grades_with_name(void)
{
    char name[25];
    set_color(GREEN);
    fprintf(stdout, "%s: ", " * - please enter first name");
    set_color(YELLOW);
    fscanf(stdin, "%s", name);
    name[25] = '\0';
    unsigned int len;
    grade *grades = get_grades_with_name(name, &len);

    if (len <= 0)
    {
        set_color(RED);
        puts("* - grades not found - *");
        return;
    } // end if

    for (int i = 0; i < len; i++)
    {
        set_color(GREEN);
        printf("* - [%d] - name : [%s] - unit : [%d] - score : [%f] . - *\n", i + 1, grades[i].name, grades[i].unit, grades[i].score);
    } // end for

    return;

} // end print_grades_with_name function

void print_faild_grades_with_name(void)
{

    char name[25];
    set_color(BLUE);
    fprintf(stdout, "%s : ", "please enter first name");
    set_color(CYAN);
    fscanf(stdin, "%s", name);
    name[25] = '\0';
    unsigned int len;
    unsigned int number = 1;

    grade *grades = get_grades_with_name(name, &len);

    if (len <= 0)
    {
        set_color(RED);
        puts("* - grades not found - *");
        return;
    } // end if

    for (int i = 0; i < len; i++)
    {
        if (grades[i].score < 10)
        {
            set_color(RED);
            printf("* - [%u] - name : [%s] - unit : [%d] - score : [%f] . - *\n", number, grades[i].name, grades[i].unit, grades[i].score);
            number++;
        } // end if

    } // end for

    if (number == 1)
    {
        set_color(RED);
        puts("faild grade not found");
    } // end if

    return;
}

void print_avarage_grades_student_with_name(void)
{
    char name[25];
    set_color(BLUE);
    fprintf(stdout, "%s : ", "please enter first name");
    set_color(CYAN);
    fscanf(stdin, "%s", name);
    name[25] = '\0';

    unsigned int len;
    grade *grades = get_grades_with_name(name, &len);

    unsigned int units = 0;
    float scores = 0;
    float avarage = 0.0;
    grade informations;

    if (len <= 0)
    {
        set_color(RED);
        puts("* - grades not found - *");
        return;
    } // end if

    for (int i = 0, number = 1; i < len; i++)
    {
        informations = grades[i];
        scores += informations.score * (float)informations.unit;
        units += informations.unit;
    } // end for

    avarage = scores / (float)units;
    set_color(GREEN);
    printf("%s %s %s %d %s %f\n", "student with first name :", name, ", units : ", units, "avarage", avarage);

    return;
} // end print_avarage_grades_student_with_name function

void print_students_who_faild_grades_lesson_with_name(void)
{
    char name[25];
    fprintf(stdout, "%s : ", "please enter lesson name");
    fscanf(stdin, "%s", name);
    name[25] = '\0';

    unsigned int len;
    stn_grade *grades = get_students_lesson_with_name(name, &len);
    stn_grade informations;
    bool is_printed = false;

    if (len <= 0)
    {
        puts("not found.");
        return;
    } // end if

    for (int i = 0; i < len; i++)
    {
        informations = grades[i];
        if (informations.grade.score < 10.0)
        {
            printf("* - student with stn : [%u] - score : [%f] - *\n", informations.stn, informations.grade.score);
            is_printed = true;
        } // end if

    } // end for

    if (!is_printed)
    {
        puts("not found");
    } // end if

    return;
}

void print_students_who_passed_lesson_z_with_score_x_menu(void)
{

    char lesson_name[25];
    fprintf(stdout, "%s : ", "please enter lesson name");
    fscanf(stdin, "%s", lesson_name);
    lesson_name[25] = '\0';

    float score;
    while (score < 10.0)
    {

        printf("%s", "please enter score [+10.0]: ");
        fscanf(stdin, "%f", &score);
    } // end while

    print_students_which_passed_lesson_z_with_score_x(lesson_name, score);
}

void print_avarage_lesson_x_in_college(void)
{
    char lesson_name[25];
    fprintf(stdout, "%s : ", "please enter lesson name");
    fscanf(stdin, "%s", lesson_name);
    lesson_name[25] = '\0';
    float avarage;

    unsigned int result = avarage_lesson_x_in_college(&avarage, lesson_name);

    if (result == OK)
    {
        printf("%s %f\n", "* - avarage :", avarage);
        return;
    } // end if

    puts("Error");
    return;
} // end print_avarage_lesson_x_in_college function

// end
