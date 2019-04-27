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

struct create_file{
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
    }

    inline void read_course() {
        FILE *output;
        puts("plz input 3 courses' info(number, name & class_hour)");
        for (int i = 1; i <= 3; i++) cou[i].scan();
        output = fopen("course.dat", "w");
        for (int i = 1; i <= 3; i++) cou[i].file_print(output);
        puts("the info have saved in the file course.dat");
    }

    inline void read_grade() {
        FILE *output;
        puts("plz input 10 students' 3 courses' grade (student_number, course_number & grades)");
        for (int i = 1; i <= 30; i++) gra[i].scan();
        output = fopen("courseGrade.dat", "w");
        for (int i = 1; i <= 30; i++) gra[i].file_print(output);
    }
} write_data;

// process the .dat file in the screen

struct process_file{
    struct student_list {
        student data;
        student_list *next;
    };
    student_list *stu_head;

    struct course_list{
        course data;
        course_list *next;
    };
    course_list *cou_head;

    struct grade_list{
        grade data;
        grade_list *next;
    };
    grade_list *grade_head;
    int have_existed_list;
    inline void put_student(){
        stu_head = (student_list *) malloc(sizeof(student_list));
        stu_head->next=NULL;
        student_list * tmp=stu_head;
        FILE *input;
        input = fopen("student.dat","r");
        puts("the 10 students' info read from student.dat are as follows");
        for (int i=1;i<=10;i++){
            student_list * p=(student_list *) malloc(sizeof(student_list));
            p->data.file_scan(input);
            p->next=NULL;
            tmp->next=p;
            tmp=p;
        }
        for (student_list *p = stu_head->next; p; p = p->next)
            for (student_list *q = p->next; q; q = q->next) {
                if (q->data< p->data) {
                    student tmp = p->data;
                    p->data = q->data;
                    q->data = tmp;
                }
            }
        for (student_list *p=stu_head->next;p;p=p->next) p->data.print();
        have_existed_list = 1;
    }

    inline void put_course(){
        cou_head = (course_list *) malloc(sizeof(course_list));
        cou_head->next=NULL;
        course_list * tmp=cou_head;
        FILE *input;
        input = fopen("course.dat","r");
        puts("the 3 courses' info read from course.dat are as follows");
        for (int i=1;i<=3;i++){
            course_list * p=(course_list *) malloc(sizeof(course_list));
            p->data.file_scan(input);
            p->next=NULL;
            tmp->next=p;
            tmp=p;
        }
        for (course_list *p = cou_head->next; p; p = p->next)
            for (course_list *q = p->next; q; q = q->next) {
                if (q->data< p->data) {
                    course tmp = p->data;
                    p->data = q->data;
                    q->data = tmp;
                }
            }
        for (course_list *p=cou_head->next;p;p=p->next) p->data.print();
    }
    inline void put_grade(){
        grade_head = (grade_list *) malloc(sizeof(grade_list));
        grade_head->next=NULL;
        grade_list * tmp=grade_head;
        FILE *input;
        input = fopen("courseGrade.dat","r");
        puts("the 10 students' 3 courses' grade info read from courseGrade.dat are as follows");
        for (int i=1;i<=30;i++){
            grade_list * p=(grade_list *) malloc(sizeof(grade_list));
            p->data.file_scan(input);
            p->next=NULL;
            tmp->next=p;
            tmp=p;
        }
        for (grade_list *p = grade_head->next; p; p = p->next)
            for (grade_list *q = p->next; q; q = q->next) {
                if (q->data< p->data) {
                    grade tmp = p->data;
                    p->data = q->data;
                    q->data = tmp;
                }
            }
        for (grade_list *p=grade_head->next;p;p=p->next) p->data.print();
    }

    student_list *re_stu_head;
    // 栈
    student st[100];
    int top;
    //栈+栈顶指针
    inline void reserve_stu_info(){
        if (!have_existed_list) {
            puts("the students' list have not been built. plz built it first");
            return;
        }
        memset(st,0, sizeof(st)); top=0;
        for (student_list *p=stu_head->next;p;p=p->next) st[++top]=p->data;
        re_stu_head=(student_list *)malloc(sizeof(student_list));
        re_stu_head->next=NULL;
        student_list * tmp=re_stu_head;
        puts("the new reserved list have built and put as follows");
        for (int i=top;i;i--){
            student_list *p=(student_list *) malloc(sizeof(student_list));
            p->data=st[i];
            p->next=NULL;
            tmp->next=p;
            tmp=p;
        }
        for (student_list *p=re_stu_head->next;p;p=p->next) p->data.print();
    }
} get_data;

// union the info ..
struct record{
    struct student_grade{
        int student_number;
        int course_number;
        int sex;
        int class_hours;
        char student_name[50];
        char course_name[50];
        int grades;
        char major[50];
        inline void file_print(FILE *input){
            fprintf(input,"%d %s %d %s %d %s %d %d\n",student_number,student_name,sex,major,course_number,course_name,class_hours,grades);
        }
        inline void print(){
            printf("%d %s %d %s %d %s %d %d\n",student_number,student_name,sex,major,course_number,course_name,class_hours,grades);
        }
    }info[100];
    static int cmp(student_grade a,student_grade b){
        return a.grades>b.grades;
    }
    student stu[100];
    course cou[100];
    inline void get_info(){
        FILE *input=fopen("student.dat","r");
        for (int i=1;i<=10;i++) stu[i].file_scan(input);
        fclose(input);
        input=fopen("course.dat","r");
        for (int i=1;i<=3;i++) cou[i].file_scan(input);
        fclose(input);
        input=fopen("courseGrade.dat","r");
        for (int j=1;j<=30;j++){
            grade tmp;tmp.file_scan(input);
            for (int i=1;i<=10;i++)
                if (stu[i].number==tmp.student_number) {
                    info[j].student_number = stu[i].number;
                    strcpy(info[j].major, stu[i].major);
                    info[j].sex=stu[i].sex;
                    strcpy(info[j].student_name, stu[i].name);
                    info[j].grades=tmp.grades;
                }
            for (int i=1;i<=3;i++)
                if (cou[i].number==tmp.course_number){
                    info[j].course_number=cou[i].number;
                    info[j].class_hours=cou[i].class_hour;
                    strcpy(info[j].course_name,cou[i].name);
                }
        }
        fclose(input);
        sort(info+1,info+31,cmp);
        puts("the students' grade info have been built saved in the studentGrade.dat");
        for (int i=1;i<=30;i++) info[i].print();
        FILE *output=fopen("studentGrade.dat","w");
        for (int i=1;i<=30;i++) info[i].file_print(output);
    }
    inline void check_course(int number){
        printf("the number %d course' grade are as follows\n",number);
        for (int i=1;i<=30;i++)
            if (info[i].course_number == number) info[i].print();
    }
    inline void check_course_failed(int number){
        printf("the number %d course' grade which are below 60 are as follows\n",number);
        for (int i=1;i<=30;i++)
            if (info[i].course_number == number && info[i].grades<60) info[i].print();
    }
} process;

inline void init(){
    get_data.have_existed_list=0;
}

int main() {
    init();

    //write_data.read_student();
    //write_data.read_course();
    //write_data.read_grade();
    //get_data.put_student();
    //get_data.put_course();
    //get_data.put_grade();
    //get_data.reserve_stu_info();
    process.get_info();
    //process.check_course(1);
    //process.check_course_failed(1);
}