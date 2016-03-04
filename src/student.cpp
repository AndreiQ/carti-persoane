#include "student.h"
#include<iostream>
using namespace std;
student::student()
{
    //ctor
}
void student::create_student()
{
    cout<<"Numele persoanei: ";
    cin.get(studentName,30);cin.get();
}
void student::show_student()

{
    cout<<studentName<<endl;
}
