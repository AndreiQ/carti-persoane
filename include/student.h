#ifndef STUDENT_H
#define STUDENT_H


class student
{
private:
    char studentName[30];
    //char studentNr[3];
//    std::vector<std::string> borrowedBooks;
public:
    student();
    void create_student();
    void show_student();
};

#endif // STUDENT_H
