# include "exp1.h"


inline int read() {
    int x;
    scanf("%d", &x);
    return x;
}

int main() {
    get_data.init();
    process.init();
    for (;;) {
        int flag = 0;
        puts("Welcome to the grade query system");
        puts("1. write the student.dat");
        puts("2. write the course.dat");
        puts("3. write the courseGrade.dat");
        puts("4. output the students' info");
        puts("5. output the courses' info");
        puts("6. output the courseGrade.dat");
        puts("7. create query the all grades");
        puts("8. check the number x' course's grades");
        puts("9. show the number x' course's grades which are below 60");
        puts("10. reserve the students; info");
        puts("-1. exit");
        puts("=================================================================");
        puts("plz input the opt you want to process");
        int opt = read();
        switch (opt) {
            case 1: {
                write_data.read_student();
                break;
            }
            case 2: {
                write_data.read_course();
                break;
            }
            case 3: {
                write_data.read_grade();
                break;
            }
            case 4: {
                get_data.put_student();
                break;
            }
            case 5: {
                get_data.put_course();
                break;
            }
            case 6: {
                get_data.put_grade();
                break;
            }
            case 7: {
                process.get_info();
                break;
            }
            case 8: {
                puts("plz input the course's number you want to check");
                process.check_course(read());
                break;
            }
            case 9: {
                puts("plz input the course's number you want to check");
                process.check_course_failed(read());
                break;
            }
            case 10: {
                get_data.reserve_stu_info();
                break;
            }
            case -1: {
                flag = 1;
                break;
            }
        }
        if (flag) break;
        puts("the option have done successfully. plz press y to continue or n to exit");
        char ch = getchar();
        for (; ch != 'y' && ch != 'n';) ch = getchar();
        if (ch == 'n') break;
    }
}