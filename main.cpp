#include <iostream>
#include<fstream>
#include <stdlib.h>
#include "book.h"
#include "student.h"
using namespace std;

fstream books,pers;
book bk;
student st;
void add_book()
{
    char ch;
    books.open("carti.bin",ios::out|ios::app|ios::binary);
    do
    {
        system("cls");
        bk.create_book();
        books.write((char*)&bk,sizeof(book));
        cout<<"\nVrei sa mai adaugi carti?(y/n?)";
        cin>>ch;
        cin.get();
    }
    while(ch=='y'||ch=='Y');
}
void add_pers()
{
    char ch;
    pers.open("persoane.bin",ios::out|ios::app|ios::binary);
    do
    {
        system("cls");
        st.create_student();
        pers.write((char*)&st,sizeof(student));
        cout<<"\nVrei sa mai adaugi persoane?(y/n?)";
        cin>>ch;cin.get();
    }
    while(ch=='y'||ch=='Y');
}

void meniu()
{
    int rasp;
    do
    {
        cout<<"\t\t\t\t\t Biblioteca\n\n";
        cout<<"Ce doriti sa faceti?"<<endl;

        cout<<"\n0 Iesire"<<endl;
        cout<<"1 Adauga carte noua"<<endl;
        cout<<"2 Adauga persoana noua"<<endl;
        cout<<"3 Vezi cine a imprumutat cartea"<<endl;
        cout<<"4 Vezi date persoana"<<endl;
        cout<<"5 Adauga imprumut nou"<<endl;
        cout<<"6 Afiseaza toate cartile"<<endl;
        cout<<"7 Afiseaza toate persoanele"<<endl;
        cin>>rasp;cin.get();
        switch(rasp)
        {
        case 0:
            exit(0);
            break;
        case 1:
            add_book();
            break;
        case 2:
            add_pers();
            break;
        /* case 3: list_imprumut();
         break;
         case 4: data_pers();
         break;
         case 5: imprumut_nou();
         break;
         case 6: afisare_carti();
         break;
         case 7: afisare_pers();
         break;*/
        default:
            cout<<"Optiune gresita";
            break;
        };
        system("cls");
    }
    while(true);
}
int main()
{

    meniu();
    return 0;
}












/*write string in binary files
------------------------------------------------------
  string ReadString(istream& file)
{
u32 len = ReadU32(file);

char* buffer = new char[len];
file.read(buffer, len);

string str( buffer, len );
delete[] buffer;

return str;
}

void WriteString(istream& file, string str)
{
u32 len = str.length();

WriteU32(file, len);
file.write( str.c_str(), len );
}
-----------------------------------------------------------------

*/

