#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "./structs.c"
#include "./colors.c"

#define STUDENTS_FILE "students.txt"
#define GRADES_FILE "grades.txt"
#define UPDATE_FILE "update_file.txt"
#define MAX_LESSON 10000

// ------------------------------------------------------------ functions for all -------------------------------------------------------

unsigned int delete_student_grades(const unsigned int stn);


void next_line(FILE *file)
{
    int ch = '-';
    while (!feof(file))
    {
        ch = fgetc(file);
        if (feof(file) || ch == '\n')
        {
            break;
        } // end if
    }     // end while
}

// ------------------------------------------------------------ students functions -------------------------------------------------------

//  ----------------------- reads

void read_students_string(FILE *file, char *temp)
{
    int ch = '.';
    int i = 0;
    while (ch != ',')
    {
        ch = fgetc(file);
        if (feof(file))
        {
            break;
        }
        temp[i] = ch;
        i++;
    }
    temp[i - 1] = '\0';
}

void read_students_number(FILE *file, unsigned int *num_ptr)
{
    int ch = '.';
    unsigned int i;
    *num_ptr = 0;
    while (ch != ',' || ch == '\n')
    {
        ch = fgetc(file);
        if (feof(file) || ch == '\n' || ch == ',')
        {
            break;
        }
        *num_ptr = (*num_ptr * 10) + (unsigned int)(ch - 48); // ch - 48 -> convert char '1' to int 1 from ascii
    }
}

//  ----------------------- searchs

unsigned int search_student_in_students_with_stn(const unsigned int stn)
{

    // this function for search student

    FILE *stu_file = fopen(STUDENTS_FILE, "r");
    student stu;

    if (stu_file == NULL)
    {
        set_color(RED);
        printf("%s %s", "Error in open file", STUDENTS_FILE);
        return ERROR;
    }

    while (!feof(stu_file))
    {
        read_students_string(stu_file, stu.first_name);
        read_students_string(stu_file, stu.last_name);
        read_students_number(stu_file, &(stu.stn));
        read_students_number(stu_file, &(stu.age));
        if (feof(stu_file))
        {
            fclose(stu_file);
            return STUDENT_NOT_FOUND;
        }
        else if (stu.stn == stn)
        {
            fclose(stu_file);
            return STUDENT_ALREADY_EXIST;
        }
    }

} // end search_student_in_students_with_stn function

//  ----------------------- adds

unsigned int add_student(student student)
{
    // for appedn new student to STUDENTS_FILE

    FILE *student_file = fopen(STUDENTS_FILE, "a");

    if (student_file == NULL)
    {
        set_color(RED);
        fprintf(stderr, "%s %s", "error in open file", STUDENTS_FILE);
        return ERROR;
    } // end if

    unsigned int status = search_student_in_students_with_stn(student.stn);

    switch (status)
    {
    case STUDENT_NOT_FOUND:

        fprintf(student_file, "%s,%s,%u,%u\n", student.first_name, student.last_name, student.stn, student.age);
        fclose(student_file);
        return OK;

    case STUDENT_ALREADY_EXIST:

        puts("student with this stn code is in database");
        fclose(student_file);
        return STUDENT_ALREADY_EXIST;

    default:
        return ERROR;
    }

} // end add_student function

//  ----------------------- removes

unsigned int remove_student(unsigned int stn)
{

    FILE *stu_file = fopen(STUDENTS_FILE, "r");
    FILE *update_file = fopen(UPDATE_FILE, "w");
    student stu;
    bool is_removed = false;
    unsigned int result = search_student_in_students_with_stn(stn);

    if (stu_file == NULL)
    {
        set_color(RED);
        fprintf(stderr, "error in open file %s", STUDENTS_FILE);
        return ERROR;
    } // end if
    else if (update_file == NULL)
    {
        set_color(RED);
        fprintf(stderr, "error in open file %s", UPDATE_FILE);
        return ERROR;
    } // end else if

    if (result == STUDENT_NOT_FOUND)
    {
        return STUDENT_NOT_FOUND;
    } // end if

    while (!feof(stu_file))
    {
        read_students_string(stu_file, stu.first_name);
        read_students_string(stu_file, stu.last_name);
        read_students_number(stu_file, &stu.stn);
        read_students_number(stu_file, &stu.age);

        if (feof(stu_file))
        {
            break;
        } // end if
        else if (stu.stn == stn && !is_removed)
        {
            continue;
        }

        fprintf(update_file, "%s,%s,%u,%u\n", stu.first_name, stu.last_name, stu.stn, stu.age);

    } // end while


    fclose(stu_file);
    fclose(update_file);
    remove(STUDENTS_FILE);
    rename(UPDATE_FILE, STUDENTS_FILE);

    delete_student_grades(stn);


    return OK;
} // end remove_student function

//  ----------------------- changes

unsigned int change_students(const unsigned int stn, enum student_change_informations changing_mode, new_item new_item)
{

    // this function for change student informations

    FILE *stu_file = fopen(STUDENTS_FILE, "r");
    FILE *update_file = fopen(UPDATE_FILE, "w");
    student stu;
    bool is_changed = false;
    unsigned int result = search_student_in_students_with_stn(stn);

    if (result == STUDENT_NOT_FOUND)
    {
        return result;
    } // end if

    if (stu_file == NULL)
    {
        set_color(RED);
        fprintf(stderr, "error in open file %s", STUDENTS_FILE);
        return ERROR;
    } // end if
    else if (update_file == NULL)
    {
        set_color(RED);
        fprintf(stderr, "error in open file %s", UPDATE_FILE);
        return ERROR;
    } // end else if

    while (!feof(stu_file))
    {
        read_students_string(stu_file, stu.first_name);
        read_students_string(stu_file, stu.last_name);
        read_students_number(stu_file, &stu.stn);
        read_students_number(stu_file, &stu.age);

        if (feof(stu_file))
        {
            break;
        }

        if (stu.stn == stn)
        {
            switch (changing_mode)
            {
            case FIRST_NAME:
                sscanf(new_item.first_name, "%s", stu.first_name);
                is_changed = true;
                break;

            case LAST_NAME:
                sscanf(new_item.last_name, "%s", stu.last_name);
                is_changed = true;
                break;

            case STN:
                stu.stn = new_item.stn;
                is_changed = true;
                break;

            case AGE:
                stu.age = new_item.age;
                is_changed = true;
                break;
            } // end switch
        }     // end if
        set_color(GREEN);
        fprintf(update_file, "%s,%s,%u,%u\n", stu.first_name, stu.last_name, stu.stn, stu.age);

        if (is_changed)
        {
            break;
        } // end if

    } // end while

    while (!feof(stu_file))
    {
        read_students_string(stu_file, stu.first_name);
        read_students_string(stu_file, stu.last_name);
        read_students_number(stu_file, &stu.stn);
        read_students_number(stu_file, &stu.age);

        if (feof(stu_file))
        {
            break;
        } // end if
        fprintf(update_file, "%s,%s,%u,%u\n", stu.first_name, stu.last_name, stu.stn, stu.age);
    } // end while

    fclose(stu_file);
    fclose(update_file);

    remove(STUDENTS_FILE);
    rename(UPDATE_FILE, STUDENTS_FILE);

    return OK;

} // end change_students fucntion

unsigned int change_first_name(const unsigned int stn, const char name[25])
{
    // this is function for change student first name

    new_item new_first_name;
    sscanf(name, "%s", new_first_name.first_name);
    unsigned int result = change_students(stn, FIRST_NAME, new_first_name);

    return result;

} // end change_first_name function

unsigned int change_last_name(const unsigned int stn, const char *name)
{
    // this is function for change student last name

    new_item new_last_name;
    sscanf(name, "%s", new_last_name.last_name);
    unsigned int result = change_students(stn, LAST_NAME, new_last_name);

    return result;

} // end change_last_name function

unsigned int change_stn(const unsigned int stn, const unsigned int new_stn)
{

    // this is function for change student stn code

    if (search_student_in_students_with_stn(new_stn) == STUDENT_ALREADY_EXIST)
    {
        return STUDENT_ALREADY_EXIST;
    } // end if

    new_item new_stn_code;
    new_stn_code.stn = new_stn;
    unsigned int result = change_students(stn, STN, new_stn_code);

    return result;

} // end change_stn function

unsigned int change_age(const unsigned int stn, const unsigned int new_age)
{
    // this is function for change student age

    new_item age;
    age.age = new_age;
    unsigned int result = change_students(stn, AGE, age);

    return result;

} // end change_age function

//  ----------------------- gets

unsigned int get_student_with_stn(const unsigned int stn, student *stu)
{

    FILE *stu_file = fopen(STUDENTS_FILE, "r");

    if (stu_file == NULL)
    {
        set_color(RED);
        printf("%s %s", "Erro in open file", STUDENTS_FILE);
        return ERROR;
    } // end if

    while (!feof(stu_file))
    {
        read_students_string(stu_file, stu->first_name);
        read_students_string(stu_file, stu->last_name);
        read_students_number(stu_file, &stu->stn);
        read_students_number(stu_file, &stu->age);
        if (feof(stu_file))
        {
            stu->first_name[0] = '\0';
            stu->last_name[0] = '\0';
            stu->stn = 0;
            stu->age = 0;
            fclose(stu_file);
            return STUDENT_NOT_FOUND;
        } // end if
        else if (stu->stn == stn)
        {
            fclose(stu_file);
            return STUDENT_ALREADY_EXIST;
        } // end else if

    } // end while

} // end get_student_with_stn function

unsigned int get_student_with_first_name(const char *first_name, student *stu)
{
    FILE *stu_file = fopen(STUDENTS_FILE, "r");

    if (stu_file == NULL)
    {
        set_color(RED);
        printf("%s %s", "Erro in open file", STUDENTS_FILE);
        return ERROR;
    } // end if

    while (!feof(stu_file))
    {
        read_students_string(stu_file, stu->first_name);
        read_students_string(stu_file, stu->last_name);
        read_students_number(stu_file, &stu->stn);
        read_students_number(stu_file, &stu->age);
        if (feof(stu_file))
        {
            stu->first_name[0] = '\0';
            stu->last_name[0] = '\0';
            stu->stn = 0;
            stu->age = 0;
            fclose(stu_file);
            return STUDENT_NOT_FOUND;
        }
        else if (!strcmp(stu->first_name, first_name))
        {
            fclose(stu_file);
            return STUDENT_ALREADY_EXIST;
        }
    }

    fclose(stu_file);
    return STUDENT_NOT_FOUND;
}

// ------------------------------------------------------------- grades functions ---------------------------------------------------------

grade *get_grades_with_stn(const unsigned int stn, unsigned int *const size);
unsigned int get_lesson_name_in_grades(const unsigned int stn, const char *name, grade *get_grade);

//  ----------------------- tools

float get_avarage(grade *grades, const unsigned int len)
{
    grade grade;
    float scores = 0.0;
    float avarage = 0.0;
    unsigned int units = 0;

    if (len <= 0)
    {
        return 0.0;
    } // end if

    for (int i = 0, number = 1; i < len; i++)
    {
        grade = grades[i];
        scores += grade.score * (float)grade.unit;
        units += grade.unit;
    } // end for

    avarage = scores / (float)units;
    return avarage;

} // end avarage function

//  ----------------------- reads

unsigned int read_stn_from_grades_file(FILE *grades_file)
{
    unsigned int stn = 0;
    int ch = '.';

    while (ch != ',')
    {
        ch = fgetc(grades_file);

        if (feof(grades_file) || ch == ',')
        {
            break;
        } // end if

        stn = (stn * 10) + (unsigned int)(ch - 48); // ch - 48 -> convert char '1' to int 1 from ascii
    }                                               // end while

    return stn;

} // end read_stn_from_grades_file

unsigned int read_grade_name(FILE *grades_file, grade *grade)
{

    // this funtcion for get grade name

    int ch = '*';
    int i = 0;
    grade->name[0] = '\0';
    while (ch != ':')
    {
        ch = fgetc(grades_file);
        if (ch == ':')
        {
            break;
        }
        grade->name[i] = ch;
        i++;
    }
    grade->name[i] = '\0';
} // end read_grade_name function

unsigned int read_grade_unit(FILE *grades_file, grade *grade)
{
    int ch = '*';
    grade->unit = 0;
    while (ch != ':')
    {
        ch = fgetc(grades_file);
        if (ch == ':')
        {
            break;
        }
        grade->unit = (grade->unit * 10) + (unsigned int)(ch - 48); // ch - 48 -> convert char '1' to int 1 from ascii
    }
} // end read_grade_unit function

unsigned int read_grade_score(FILE *grades_file, grade *grade)
{
    int ch = '*';
    bool ashar = false;
    float ragham = 1.0;
    float ragham_ashar = 0.0;
    grade->score = 0.0;
    while (ch != ';')
    {
        ch = fgetc(grades_file);
        if (ch == ';')
        {
            break;
        } // end if
        else if (ch == '.')
        {
            ashar = true;
            continue;
        } // end else if

        if (ashar)
        {

            ragham_ashar = (ragham_ashar * 10.0) + (float)((float)(ch - 48.0)); // ch - 48 -> convert char '1' to int 1 from ascii
            ragham *= 10.0;

        } // end if
        else
        {
            grade->score = (grade->score * 10.0) + (float)(ch - 48.0); // ch - 48 -> convert char '1' to int 1 from ascii
        }                                                              // end else if
    }                                                                  // end while

    ragham_ashar /= ragham;
    grade->score += ragham_ashar;
} // end read_grade_score function

unsigned int go_to_line_with_stn(FILE *file, const unsigned int stn)
{

    unsigned int get_stn;

    while (!feof(file))
    {

        get_stn = read_stn_from_grades_file(file);

        if (feof(file))
        {
            return STUDENT_NOT_FOUND;
        } // end if
        else if (stn == get_stn)
        {
            return OK;
        } // end else if
        else
        {
            next_line(file);
        } // end else

    } // end while

    return STUDENT_NOT_FOUND;

} // end go_to_line_with_stn function

unsigned int number_of_grades(unsigned int stn, unsigned int *number)
{
    // this function
    FILE *grades_file = fopen(GRADES_FILE, "r");
    int ch = '*';
    unsigned int get_stn;
    unsigned int result;
    *number = 0;

    result = go_to_line_with_stn(grades_file, stn);

    if (result != OK)
    {
        fclose(grades_file);
        return result;
    } // end if

    while (!feof(grades_file) || ch != '\n') // number
    {
        ch = fgetc(grades_file);
        if (feof(grades_file) || ch == '\n')
        {
            break;
        } // end if
        else if (ch == ';')
        {
            (*number)++;
        } // end else if

    } // end while
    fclose(grades_file);
    return OK;

} // end function number_of_grades

//  ----------------------- searchs

unsigned int search_grade_name_in_grades(const unsigned int stn, const char *name)
{
    grade grade;
    return get_lesson_name_in_grades(stn, name, &grade);
}

unsigned int search_student_in_grades_with_stn(const unsigned int stn)
{

    // this function for search stn in grades.txt

    FILE *grades_file = fopen(GRADES_FILE, "r");
    unsigned int result;

    if (grades_file == NULL)
    {
        printf("%s %s", "error in open file", GRADES_FILE);
        return ERROR;
    } // end if

    result = go_to_line_with_stn(grades_file, stn);
    fclose(grades_file);

    if (result == OK)
    {
        return STUDENT_ALREADY_EXIST;
    } // end if

    return STUDENT_NOT_FOUND;

} // end search_student_in_grades_with_stn function

//  ----------------------- adds

unsigned int add_new_stu_grade(const unsigned int stn, const grade grade)
{
    // this ins function for add new stn_grades

    FILE *grades_file = fopen(GRADES_FILE, "a");

    if (grades_file == NULL)
    {
        printf("%s %s", "error in open file", GRADES_FILE);
        return ERROR;
    } // end if

    fprintf(grades_file, "%u,%s:%u:%f;\n", stn, grade.name, grade.unit, grade.score);

    fclose(grades_file);

    return OK;

} // end add_new_stu_grade function

unsigned int add_new_grade(const unsigned int stn, const grade new_grade)
{
    // thisfis function for add only grade without stn

    FILE *grades_file = fopen(GRADES_FILE, "r");
    FILE *update_file = fopen(UPDATE_FILE, "w");
    unsigned int len;
    unsigned int get_stn;
    unsigned int i;
    bool is_added = false;
    grade grade_inf;

    while (!feof(grades_file))
    {
        len = 0;
        get_stn = read_stn_from_grades_file(grades_file);

        if (feof(grades_file))
        {
            break;
        } // end if

        fprintf(update_file, "%u,", get_stn);
        grade *grades = get_grades_with_stn(get_stn, &len);
        for (i = 0; i < len; i++)
        {
            grade_inf = grades[i];
            fprintf(update_file, "%s:%u:%f;", grade_inf.name, grade_inf.unit, grade_inf.score);
        } // end for

        if (get_stn == stn && !is_added)
        {
            fprintf(update_file, "%s:%u:%f;", new_grade.name, new_grade.unit, new_grade.score);
            is_added = true;
        } // end else if

        fprintf(update_file, "\n");
        next_line(grades_file);

    } // end while

    fclose(grades_file);
    fclose(update_file);
    remove(GRADES_FILE);
    rename(UPDATE_FILE, GRADES_FILE);

    return OK;

} // end add_new_grade function

unsigned int add_grade(unsigned int stn, grade new_grade)
{

    unsigned int result;

    if (search_student_in_grades_with_stn(stn) == STUDENT_ALREADY_EXIST)
    {
        return add_new_grade(stn, new_grade);
    } // end if

    return add_new_stu_grade(stn, new_grade);

} // end add_grade function

//  ----------------------- deletes

unsigned int delete_student_grade(const unsigned int stn, const char *lesson_name)
{

    // this function for remove lesson with name lesson_name from GRADES_FILE with stn

    FILE *grades_file = fopen(GRADES_FILE, "r");
    FILE *update_file = fopen(UPDATE_FILE, "w");

    if (grades_file == NULL)
    {

        printf("%s %s", "error in open file", GRADES_FILE);
        return ERROR;
    } // end if
    else if (update_file == NULL)
    {

        printf("%s %s", "error in open file", UPDATE_FILE);
        return ERROR;
    } // end else if

    unsigned int len;
    unsigned int result;
    unsigned int i;
    unsigned int get_stn = 0;

    bool is_deleted = false;

    grade get_grade;

    while (!feof(grades_file))
    {

        get_stn = read_stn_from_grades_file(grades_file);

        if (feof(grades_file))
        {
            break;
        } // end if

        next_line(grades_file);
        fprintf(update_file, "%u,", get_stn);

        grade *grades = get_grades_with_stn(get_stn, &len);

        if (stn == get_stn && !is_deleted)
        {
            if (len > 0)
            {
                for (i = 0; i < len; i++)
                {
                    get_grade = grades[i];
                    if (strcmp(get_grade.name, lesson_name))
                    {
                        fprintf(update_file, "%s:%u:%f;", get_grade.name, get_grade.unit, get_grade.score);
                    } // end if

                } // end for

            } // end if

            is_deleted = true;

        } // end if
        else
        {

            if (len > 0)
            {
                for (i = 0; i < len; i++)
                {
                    get_grade = grades[i];
                    fprintf(update_file, "%s:%u:%f;", get_grade.name, get_grade.unit, get_grade.score);

                } // end for

            } // end if

        } // end else

        fprintf(update_file, "\n");

    } // end while

    fclose(grades_file);
    fclose(update_file);

    remove(GRADES_FILE);
    rename(UPDATE_FILE, GRADES_FILE);

    return OK;

} // end delete_student_grade function

unsigned int delete_student_grades(const unsigned int stn)
{

    // this function for remove all lesson from GRADES_FILE with stn

    FILE *grades_file = fopen(GRADES_FILE, "r");
    FILE *update_file = fopen(UPDATE_FILE, "w");

    if (grades_file == NULL)
    {

        printf("%s %s", "error in open file", GRADES_FILE);
        return ERROR;
    } // end if
    else if (update_file == NULL)
    {

        printf("%s %s", "error in open file", UPDATE_FILE);
        return ERROR;
    } // end else if

    unsigned int len;
    unsigned int result;
    unsigned int i;
    unsigned int get_stn;

    bool is_deleted = false;

    grade get_grade;

    while (!feof(grades_file))
    {
        get_stn = read_stn_from_grades_file(grades_file);

        if (feof(grades_file))
        {
            break;
        } // end if

        next_line(grades_file);

        if (stn == get_stn && !is_deleted)
        {
            is_deleted = true;
        } // end if
        else
        {
            grade *grades = get_grades_with_stn(get_stn, &len);

            fprintf(update_file, "%u,", get_stn);

            if (len > 0)
            {
                for (i = 0; i < len; i++)
                {
                    get_grade = grades[i];
                    fprintf(update_file, "%s:%u:%f;", get_grade.name, get_grade.unit, get_grade.score);
                } // end for

            } // end if
            fprintf(update_file, "\n");
        } // end else
    }     // end while

    fclose(grades_file);
    fclose(update_file);

    remove(GRADES_FILE);
    rename(UPDATE_FILE, GRADES_FILE);

    return OK;

} // end delete_student_grades function

//  ----------------------- changes

unsigned int change_student_score(const unsigned int stn, char *lesson_name, const float new_score)
{

    FILE *grades_file = fopen(GRADES_FILE, "r");
    FILE *update_file = fopen(UPDATE_FILE, "w");

    if (grades_file == NULL)
    {

        printf("%s %s", "error in open file", GRADES_FILE);
        return ERROR;
    } // end if
    else if (update_file == NULL)
    {

        printf("%s %s", "error in open file", UPDATE_FILE);
        return ERROR;
    } // end else if

    unsigned int len;
    unsigned int result;
    unsigned int i;
    unsigned int get_stn;

    bool is_deleted = false;

    grade get_grade;

    while (!feof(grades_file))
    {
        get_stn = read_stn_from_grades_file(grades_file);

        if (feof(grades_file))
        {
            break;
        } // end if

        next_line(grades_file);

        grade *grades = get_grades_with_stn(get_stn, &len);
        fprintf(update_file, "%u,", get_stn);

        if (stn == get_stn && !is_deleted)
        {

            if (len > 0)
            {

                for (i = 0; i < len; i++)
                {

                    get_grade = grades[i];

                    if (!strcmp(lesson_name, get_grade.name))
                    {
                        get_grade.score = new_score;

                    } // end if

                    fprintf(update_file, "%s:%u:%f;", get_grade.name, get_grade.unit, get_grade.score);

                } // end for

            } // end if

            fprintf(update_file, "\n");

            is_deleted = true;

        } // end if
        else
        {

            if (len > 0)
            {

                for (i = 0; i < len; i++)
                {

                    get_grade = grades[i];
                    fprintf(update_file, "%s:%u:%f;", get_grade.name, get_grade.unit, get_grade.score);

                } // end for

            } // end if

            fprintf(update_file, "\n");

        } // end else

    } // end while

    fclose(grades_file);
    fclose(update_file);

    remove(GRADES_FILE);
    rename(UPDATE_FILE, GRADES_FILE);

    return OK;

} // end change_student_score function

//  ----------------------- gets

unsigned int get_all_lessons(lesson lessons[MAX_LESSON])
{

    FILE *grades_file = fopen(GRADES_FILE, "r");

    unsigned int number = 0;
    unsigned int stn;
    unsigned int len;
    unsigned int k = 0;
    bool founded = false;
    lesson lesson_inf;

    // lesson lesson_inf;

    grade *grades;
    grade grade_inf;

    if (grades_file == NULL)
    {
        printf("%s %s", "error in open file", GRADES_FILE);
        return 0;
    } // end if

    while (!feof(grades_file))
    {

        stn = read_stn_from_grades_file(grades_file);
        if (feof(grades_file))
        {
            break;
        } // end if

        grades = get_grades_with_stn(stn, &len);
        next_line(grades_file);

        if (len > 0)
        {
            for (unsigned int i = 0; i < len; i++)
            {
                grade_inf = grades[i];

                k = number;

                for (unsigned int j = 0; j <= k; j++)
                {
                    lesson_inf = lessons[j];
                    founded = false;

                    if (number > 1 && !strcmp(grade_inf.name, lesson_inf.name) && grade_inf.unit == lesson_inf.unit)
                    {
                        if (grade_inf.score >= 10.0)
                        {
                            lesson_inf.passed++;
                        } // end if
                        else
                        {
                            lesson_inf.failed++;
                        } // end else

                        founded = true;
                        lesson_inf.avarage += grade_inf.score;
                        lessons[j] = lesson_inf;
                        break;
                    } // end if

                } // end for

                if (!founded)
                {
                    sscanf(grade_inf.name, "%s", lesson_inf.name);
                    lesson_inf.unit = grade_inf.unit;
                    lesson_inf.avarage = grade_inf.score;
                    lesson_inf.passed = 0;
                    lesson_inf.failed = 0;

                    if (grade_inf.score >= 10.0)
                    {
                        lesson_inf.passed++;
                    } // end if
                    else
                    {
                        lesson_inf.failed++;
                    } // end else
                    lessons[number] = lesson_inf;
                    number++;

                } // end if

            } // end for

        } // end if

    } // end while

    for (unsigned int i = 0; i < number; i++) // avarage
    {
        lesson_inf = lessons[i];
        lessons[i].avarage = lesson_inf.avarage / (lesson_inf.passed + lesson_inf.failed);
    } // end for

    fclose(grades_file);

    return number;

} // end number_of_lessons

grade *get_grades_with_stn(const unsigned int stn, unsigned int *const size)
{

    FILE *grades_file = fopen(GRADES_FILE, "r");
    grade *grades;
    grade new_grade;
    unsigned int result;
    unsigned int get_stn;
    *size = 0;

    if (grades_file == NULL)
    {
        printf("%s %s", "erro in open file", GRADES_FILE);
        exit(1);
    } // end if

    if (feof(grades_file))
    {
        fclose(grades_file);
        return grades;
    } // end if

    result = go_to_line_with_stn(grades_file, stn);

    if (result == OK)
    {
        number_of_grades(stn, size);
        grades = (grade *)malloc((*size) * sizeof(grade));
        for (unsigned int i = 0; i < (*size); i++)
        {
            read_grade_name(grades_file, &new_grade);
            read_grade_unit(grades_file, &new_grade);
            read_grade_score(grades_file, &new_grade);
            grades[i] = new_grade;
        } // end for

    } // end if

    fclose(grades_file);
    return grades;
}

grade *get_grades_with_name(const char *const name, unsigned int *const size)
{

    grade *grades;
    student stu;
    unsigned int result;
    *size = 0;

    result = get_student_with_first_name(name, &stu);

    if (result != STUDENT_ALREADY_EXIST)
    {
        return grades;
    } // end if

    grades = get_grades_with_stn(stu.stn, size);

    return grades;

} // end get_grades_with_name functiom

unsigned int get_lesson_name_in_grades(const unsigned int stn, const char *name, grade *get_grade)
{

    unsigned int get_stn;
    unsigned int len;
    grade *grades;
    grade grade_inf;
    unsigned int result;

    grades = get_grades_with_stn(stn, &len);

    if (len <= 0)
    {
        return LESSON_NOT_FOUND;
    } // end if

    for (unsigned int i = 0; i < len; i++)
    {
        grade_inf = grades[i];
        if (!strcmp(grade_inf.name, name))
        {
            *get_grade = grade_inf;
            return LESSON_ALREADY_EXIST;
        } // end if

    } // end for

    return LESSON_NOT_FOUND;
}

stn_grade *get_students_lesson_with_name(const char *const lesson_name, unsigned int *size)
{
    // this function for get all students be have lesson_name

    FILE *grades_file = fopen(GRADES_FILE, "r");
    stn_grade *all_stn_grade;
    unsigned int stn;
    unsigned int result;
    unsigned int i = 0;
    *size = 0;

    while (!feof(grades_file))
    {

        stn = read_stn_from_grades_file(grades_file);
        if (feof(grades_file))
        {
            break;
        } // end if
        result = search_grade_name_in_grades(stn, lesson_name);
        if (result == LESSON_ALREADY_EXIST)
        {
            i++;
        } // end if
        next_line(grades_file);

    } // end while

    rewind(grades_file);

    all_stn_grade = (stn_grade *)malloc(i * sizeof(stn_grade));

    while (!feof(grades_file) && i > (*size))
    {

        stn = read_stn_from_grades_file(grades_file);

        if (feof(grades_file))
        {
            break;
        } // end if

        grade get_grade;

        result = get_lesson_name_in_grades(stn, lesson_name, &get_grade);

        next_line(grades_file);

        if (result == LESSON_ALREADY_EXIST)
        {
            stn_grade get_stn_grade;

            get_stn_grade.stn = stn;
            get_stn_grade.grade = get_grade;

            all_stn_grade[(*size)] = get_stn_grade;

            (*size)++;
        } // end if

    } // end while

    return all_stn_grade;

} // end get_students_lesson_with_name function

bool is_conditional(const unsigned int stn)
{
    FILE *grades_file = fopen(GRADES_FILE, "r");
    unsigned int result;
    unsigned int len;
    float avarage;
    grade *grades;
    result = go_to_line_with_stn(grades_file, stn);

    if (grades_file == NULL)
    {
        printf("%s %s", "error in open file", GRADES_FILE);
        return false;
    }

    if (result != OK)
    {
        fclose(grades_file);
        return false;
    } // end if

    grades = get_grades_with_stn(stn, &len);
    avarage = get_avarage(grades, len);

    fclose(grades_file);

    if (avarage < 12.0)
    {
        return true;
    } // end if

    return false;

} // end  is_conditional function

unsigned int avarage_lesson_x_in_college(float *avarage, const char *lesson_name)
{
    lesson lessons[MAX_LESSON];
    lesson lesson_inf;
    unsigned int len;

    len = get_all_lessons(lessons);

    if (len <= 0)
    {
        puts("not found");
        return LESSON_NOT_FOUND;
    } // end if

    for (unsigned int i = 0; i < len; i++)
    {

        lesson_inf = lessons[i];

        if (!strcmp(lesson_name, lesson_inf.name))
        {
            *avarage = lesson_inf.avarage;
            return OK;
        } // end if

    } // end for

    return LESSON_NOT_FOUND;

} //

//  ----------------------- prints

void print_conditionalـstudents(void)
{

    FILE *students_file = fopen(STUDENTS_FILE, "r");
    student stu;

    bool result;

    while (!feof(students_file))
    {
        read_students_string(students_file, stu.first_name);
        read_students_string(students_file, stu.last_name);
        read_students_number(students_file, &(stu.stn));
        read_students_number(students_file, &(stu.age));

        if (feof(students_file))
        {
            break;
        }

        result = is_conditional(stu.stn);

        if (result)
        {
            printf("* - student with stn : [%u] - first name : [%s] - last name : [%s] - age : [%u], * mashrut ast * - *\n", stu.stn, stu.first_name, stu.last_name, stu.age);
        } // end if

    } // end while
}

void print_students_with_avarage(void)
{
    FILE *students_file = fopen(STUDENTS_FILE, "r");
    grade *grades;
    float avarage;

    student stu;

    unsigned int result;
    unsigned int len;

    while (!feof(students_file))
    {
        read_students_string(students_file, stu.first_name);
        read_students_string(students_file, stu.last_name);
        read_students_number(students_file, &(stu.stn));
        read_students_number(students_file, &(stu.age));

        if (feof(students_file))
        {
            break;
        } // end if

        grades = get_grades_with_stn(stu.stn, &len);

        avarage = get_avarage(grades, len);

        printf("first name : [%s] - last name : [%s] - stn : [%u] - age : [%u] - avarage : [%f] - *\n", stu.first_name, stu.last_name, stu.stn, stu.age, avarage);

    } // end while
}

void print_subject_without_failed(void)
{

    lesson lessons[MAX_LESSON];
    lesson lesson_inf;
    unsigned int len;

    len = get_all_lessons(lessons);

    if (len <= 0)
    {
        set_color(RED);
        puts("lessons not found");
        return;
    } // end if

    for (unsigned int i = 0; i < len; i++)
    {

        lesson_inf = lessons[i];

        if (lesson_inf.failed == 0)
        {
            set_color(YELLOW);
            printf("* - lesson : [%s] without failed - *\n", lesson_inf.name);
        } // end if

    } // end for
}

void print_subject_name_and_students_avarage_score(void)
{

    lesson lessons[MAX_LESSON];
    lesson lesson_inf;
    unsigned int len;

    len = get_all_lessons(lessons);

    if (len <= 0)
    {
        set_color(RED);
        puts("* lessons not found *");
        return;
    } // end if

    for (unsigned int i = 0; i < len; i++)
    {

        lesson_inf = lessons[i];
        set_color(PURPLE);
        printf("* - lesson name : [%s] - avarage score : [%f] - *\n", lesson_inf.name, lesson_inf.avarage);

    } // end for
}

void print_students_which_passed_lesson_z_with_score_x(char *lesson_name, float score)
{

    FILE *grades_file = fopen(GRADES_FILE, "r");
    grade get_grade;
    student stu;
    unsigned int stn;
    unsigned int result;
    bool is_printed = false;

    if (grades_file == NULL)
    {
        set_color(RED);
        printf("%s %s\n", "error in open file", GRADES_FILE);
        return;
    }

    while (!feof(grades_file))
    {

        stn = read_stn_from_grades_file(grades_file);

        if (feof(grades_file))
        {
            break;
        } // end if

        next_line(grades_file);

        result = get_lesson_name_in_grades(stn, lesson_name, &get_grade);

        if (result == LESSON_ALREADY_EXIST && !strcmp(get_grade.name, lesson_name) && get_grade.score == score)
        {

            result = get_student_with_stn(stn, &stu);

            if (result == STUDENT_ALREADY_EXIST)
            {
                set_color(CYAN);
                printf("* - first name : [%s] - last name : [%s] - stn : [%u] - age : [%u] - *\n", stu.first_name, stu.last_name, stu.stn, stu.age);
                is_printed = true;
            } // end if

        } // end if

    } // end while

    if (!is_printed)
    {
        set_color(YELLOW);
        puts("not found");
    }

    fclose(grades_file);

} // end function get_students_which_passed_lesson_z_with_score_x

// end
