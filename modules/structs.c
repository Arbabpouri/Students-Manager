typedef struct
{
    char first_name[25];
    char last_name[25];
    unsigned int stn;
    unsigned int age;
} student;

typedef struct
{
    char name[25];
    unsigned int unit;
    float score;
} grade;

typedef struct
{
    unsigned int stn;
    grade grade;
} stn_grade;

typedef struct
{
    char name[25];
    unsigned int unit;
    unsigned int passed;
    unsigned int failed;
    float avarage;
} lesson;

typedef struct
{
    student *info;
    float avarage;
} student_avrage;

typedef union
{
    char first_name[25];
    char last_name[25];
    unsigned int stn;
    unsigned int age;
} new_item;
