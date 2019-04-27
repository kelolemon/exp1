#ifndef PROJECT_EXP1_H
#define PROJECT_EXP1_H

#endif //PROJECT_EXP1_H

# include <cstdio>
# include <iostream>
# include <cmath>
# include <cstring>
# include <algorithm>

using namespace std;
// students info & I/O models

struct student {
    int number;
    char name[100];
    int sex;
    char major[100];

    inline void print() {
        printf("%d %s %d %s\n", number, name, sex, major);
    }

    inline void scan() {
        scanf("%d%s%d%s", &number, name, &sex, major);
    }

    inline void file_print(FILE *output) {
        fprintf(output, "%d %s %d %s\n", number, name, sex, major);
    }

    inline void file_scan(FILE *input) {
        fscanf(input, "%d%s%d%s", &number, name, &sex, major);
    }

    bool operator<(const student &x) const {
        return number < x.number;
    }
};
// course info & I/O models

struct course {
    int number;
    char name[100];
    int class_hour;

    inline void print() {
        printf("%d %s %d\n", number, name, class_hour);
    }

    inline void scan() {
        scanf("%d%s%d", &number, name, &class_hour);
    }

    inline void file_print(FILE *output) {
        fprintf(output, "%d %s %d\n", number, name, class_hour);
    }

    inline void file_scan(FILE *input) {
        fscanf(input, "%d%s%d", &number, name, &class_hour);
    }

    bool operator<(const course &x) const {
        return number < x.number;
    }
};
// grade info & I/O models;

struct grade {
    int student_number;
    int course_number;
    int grades;

    inline void print() {
        printf("%d %d %d\n", student_number, course_number, grades);
    }

    inline void scan() {
        scanf("%d%d%d", &student_number, &course_number, &grades);
    }

    inline void file_print(FILE *output) {
        fprintf(output, "%d %d %d\n", student_number, course_number, grades);
    }

    inline void file_scan(FILE *input) {
        fscanf(input, "%d%d%d", &student_number, &course_number, &grades);
    }

    bool operator<(const grade &x) const {
        if (student_number == x.student_number) return course_number < x.course_number;
        return student_number < x.student_number;
    }
};

// opt 1-3 create the .dat file

struct create_file {
    student stu[100];
    course cou[100];
    grade gra[100];

    inline void read_student() {
        FILE *output;
        puts("plz input 10 students' info(number, name, sex(0/1) & major)");
        for (int i = 1; i <= 10; i++) stu[i].scan();
        output = fopen("student.dat", "w");
        for (int i = 1; i <= 10; i++) stu[i].file_print(output);
        puts("the info have saved in the file student.dat");
        fclose(output);
    }

    inline void read_course() {
        FILE *output;
        puts("plz input 3 courses' info(number, name & class_hour)");
        for (int i = 1; i <= 3; i++) cou[i].scan();
        output = fopen("course.dat", "w");
        for (int i = 1; i <= 3; i++) cou[i].file_print(output);
        puts("the info have saved in the file course.dat");
        fclose(output);
    }

    inline void read_grade() {
        FILE *output;
        puts("plz input 10 students' 3 courses' grade (student_number, course_number & grades)");
        for (int i = 1; i <= 30; i++) gra[i].scan();
        output = fopen("courseGrade.dat", "w");
        for (int i = 1; i <= 30; i++) gra[i].file_print(output);
        fclose(output);
    }
} write_data;

// process the .dat file in the screen

struct process_file {
    struct student_list {
        student data;
        student_list *next;
    };
    student_list *stu_head;

    struct course_list {
        course data;
        course_list *next;
    };
    course_list *cou_head;

    struct grade_list {
        grade data;
        grade_list *next;
    };
    grade_list *grade_head;
    int have_existed_list;

    inline void init() {
        have_existed_list = 0;
    }

    inline void put_student() {
        stu_head = (student_list *) malloc(sizeof(student_list));
        stu_head->next = NULL;
        student_list *tmp = stu_head;
        FILE *input;
        input = fopen("student.dat", "r");
        puts("the 10 students' info read from student.dat are as follows");
        for (int i = 1; i <= 10; i++) {
            student_list *p = (student_list *) malloc(sizeof(student_list));
            p->data.file_scan(input);
            p->next = NULL;
            tmp->next = p;
            tmp = p;
        }
        for (student_list *p = stu_head->next; p; p = p->next)
            for (student_list *q = p->next; q; q = q->next) {
                if (q->data < p->data) {
                    student tmp = p->data;
                    p->data = q->data;
                    q->data = tmp;
                }
            }
        puts("from left to right are students' number, students' name, students' sex, students' major");
        for (student_list *p = stu_head->next; p; p = p->next) p->data.print();
        have_existed_list = 1;
        fclose(input);
    }

    inline void put_course() {
        cou_head = (course_list *) malloc(sizeof(course_list));
        cou_head->next = NULL;
        course_list *tmp = cou_head;
        FILE *input;
        input = fopen("course.dat", "r");
        puts("the 3 courses' info read from course.dat are as follows");
        for (int i = 1; i <= 3; i++) {
            course_list *p = (course_list *) malloc(sizeof(course_list));
            p->data.file_scan(input);
            p->next = NULL;
            tmp->next = p;
            tmp = p;
        }
        for (course_list *p = cou_head->next; p; p = p->next)
            for (course_list *q = p->next; q; q = q->next) {
                if (q->data < p->data) {
                    course tmp = p->data;
                    p->data = q->data;
                    q->data = tmp;
                }
            }
        puts("from left to right are courses' number, courses' name, courses' class_hours");
        for (course_list *p = cou_head->next; p; p = p->next) p->data.print();
        fclose(input);
    }

    inline void put_grade() {
        grade_head = (grade_list *) malloc(sizeof(grade_list));
        grade_head->next = NULL;
        grade_list *tmp = grade_head;
        FILE *input;
        input = fopen("courseGrade.dat", "r");
        puts("the 10 students' 3 courses' grade info read from courseGrade.dat are as follows");
        for (int i = 1; i <= 30; i++) {
            grade_list *p = (grade_list *) malloc(sizeof(grade_list));
            p->data.file_scan(input);
            p->next = NULL;
            tmp->next = p;
            tmp = p;
        }
        for (grade_list *p = grade_head->next; p; p = p->next)
            for (grade_list *q = p->next; q; q = q->next) {
                if (q->data < p->data) {
                    grade tmp = p->data;
                    p->data = q->data;
                    q->data = tmp;
                }
            }
        puts("from left to right are students' number, courses' number and grades");
        for (grade_list *p = grade_head->next; p; p = p->next) p->data.print();
    }

    student_list *re_stu_head;
    // 栈
    student st[100];
    int top;

    //栈+栈顶指针
    inline void reserve_stu_info() {
        if (!have_existed_list) put_student();
        memset(st, 0, sizeof(st));
        top = 0;
        for (student_list *p = stu_head->next; p; p = p->next) st[++top] = p->data;
        re_stu_head = (student_list *) malloc(sizeof(student_list));
        re_stu_head->next = NULL;
        student_list *tmp = re_stu_head;
        puts("the new reserved list have built and put as follows");
        for (int i = top; i; i--) {
            student_list *p = (student_list *) malloc(sizeof(student_list));
            p->data = st[i];
            p->next = NULL;
            tmp->next = p;
            tmp = p;
        }
        puts("from left to right are students' number, students' name, students' sex, students' major");
        for (student_list *p = re_stu_head->next; p; p = p->next) p->data.print();
    }
} get_data;

// union and process the info ..
struct record {
    struct student_grade {
        int student_number;
        int course_number;
        int sex;
        int class_hours;
        char student_name[50];
        char course_name[50];
        int grades;
        char major[50];

        inline void file_print(FILE *input) {
            fprintf(input, "%d %s %d %s %d %s %d %d\n", student_number, student_name, sex, major, course_number,
                    course_name, class_hours, grades);
        }

        inline void print() {
            printf("%d %s %d %s %d %s %d %d\n", student_number, student_name, sex, major, course_number, course_name,
                   class_hours, grades);
        }

        bool operator<(const student_grade &x) const {
            return grades < x.grades;
        }
    };

    struct stu_gra_list{
        student_grade data;
        stu_gra_list *next;
    };

    stu_gra_list *stu_gra_head; // queue list head
    stu_gra_list *stu_gra_tail; // queue list tail
    int have_existed;

    inline void init() {
        have_existed = 0;
    }

    static int cmp(student_grade a, student_grade b) {
        return a.grades > b.grades;
    }

    student stu[100];
    course cou[100];

    inline void get_info() {
        stu_gra_head = (stu_gra_list *) malloc(sizeof(stu_gra_list)); // create queue head
        stu_gra_tail = (stu_gra_list *) malloc(sizeof(stu_gra_list)); //create queue tail
        stu_gra_list *transient=stu_gra_head;
        transient->next=NULL;
        stu_gra_tail->next=NULL;
        FILE *input = fopen("student.dat", "r");
        for (int i = 1; i <= 10; i++) stu[i].file_scan(input);
        fclose(input);
        input = fopen("course.dat", "r");
        for (int i = 1; i <= 3; i++) cou[i].file_scan(input);
        fclose(input);
        input = fopen("courseGrade.dat", "r");
        for (int j = 1; j <= 30; j++) {
            grade tmp;
            tmp.file_scan(input);
            stu_gra_list *p = (stu_gra_list *) malloc(sizeof(stu_gra_list));
            for (int i = 1; i <= 10; i++)
                if (stu[i].number == tmp.student_number) {
                    p->data.student_number = stu[i].number;
                    strcpy(p->data.major, stu[i].major);
                    p->data.sex = stu[i].sex;
                    strcpy(p->data.student_name, stu[i].name);
                    p->data.grades = tmp.grades;
                }
            for (int i = 1; i <= 3; i++)
                if (cou[i].number == tmp.course_number) {
                    p->data.course_number = cou[i].number;
                    p->data.class_hours = cou[i].class_hour;
                    strcpy(p->data.course_name, cou[i].name);
                }
            // tail insert to create the queue list
            transient ->next = p;
            p->next=stu_gra_tail;
            transient = p;
        }
        fclose(input);
        for (stu_gra_list *p = stu_gra_head->next; p!=stu_gra_tail; p = p->next)
            for (stu_gra_list *q = p->next; q!=stu_gra_tail; q = q->next) {
                if (p->data< q->data) {
                    student_grade tmp = p->data;
                    p->data = q->data;
                    q->data = tmp;
                }
            }
        puts("the students' grade info have been built saved in the studentGrade.dat");
        puts("from left to right are students' number, students' name, students' sex, students' major, "
             "courses' number, courses' name, courses' class_hours and grades");
        for (stu_gra_list *p=stu_gra_head->next;p!=stu_gra_tail;p=p->next) p->data.print();
        FILE *output = fopen("studentGrade.dat", "w");
        for (stu_gra_list *p=stu_gra_head->next;p!=stu_gra_tail;p=p->next) p->data.file_print(output);
        have_existed = 1;
        fclose(output);
    }

    inline void check_course(int number) {
        if (!have_existed) get_info();
        printf("the number %d course' grade are as follows\n", number);
        puts("from left to right are students' number, students' name, students' sex, students' major, "
             "courses' number, courses' name, courses' class_hours and grades");
        for (stu_gra_list *p=stu_gra_head->next;p!=stu_gra_tail;p=p->next)
            if (p->data.course_number == number) p->data.print();
    }

    inline void check_course_failed(int number) {
        if (!have_existed) get_info();
        printf("the number %d course' grade which are below 60 are as follows\n", number);
        puts("from left to right are students' number, students' name, students' sex, students' major, "
             "courses' number, courses' name, courses' class_hours and grades");
        for (stu_gra_list *p=stu_gra_head->next;p!=stu_gra_tail;p=p->next)
            if (p->data.course_number == number && p->data.grades < 60) p->data.print();
    }

} process;
