#ifndef STUDENT_H
#define STUDENT_H


class student
{
private:

    //char studentNr[3];
//    std::vector<std::string> borrowedBooks;
public:
    char studentName[30];
    student();
    void create_student();
    void show_student();
};

#endif // STUDENT_H
