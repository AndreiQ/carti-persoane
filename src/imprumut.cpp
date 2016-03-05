#include "imprumut.h"
#include <iostream>
#include <string.h>
using namespace std;
void imprumut::creazaImprumut(char nume[],char carte[])
{
    strcpy(studentName,nume);
    strcpy(bookName,carte);
}
void imprumut::show_imprumut()
{
    cout<<studentName<<" - "<<bookName<<endl;
}

