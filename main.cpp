#include <iostream>
#include<fstream>
#include <stdlib.h>
#include <string.h>
//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/System.hpp>
#include "book.h"
#include "student.h"
#include "imprumut.h"
using namespace std;

fstream books,pers,impr;
book bk;
student st;
imprumut imprum;
inline bool checkIfFileExists(const std::string& fileName){
    ifstream file(fileName.c_str());
    if (file.good()) {
        file.close();
        return true;
    } else {
        file.close();
        return false;
    }
}
void initializare()
{
    if(!checkIfFileExists("persoane.bin"))
    {
    ofstream auxiliarFile;
    auxiliarFile.open("persoane.bin");
    auxiliarFile.close();
    }
    if(!checkIfFileExists("carti.bin"))
    {
    ofstream auxiliarFile;
    auxiliarFile.open("carti.bin");
    auxiliarFile.close();
    }
    if(!checkIfFileExists("imprumut.bin"))
    {
    ofstream auxiliarFile;
    auxiliarFile.open("imprumut.bin");
    auxiliarFile.close();
    }
}
void TITLU()
{
    cout<<"\t\t\t\t\t\t--------------\n";
    cout<<"\t\t\t\t\t\t| Biblioteca |\n";
    cout<<"\t\t\t\t\t\t--------------\n\n";
}
void add_book()
{
    char ch;
    books.open("carti.bin",ios::out|ios::app|ios::binary);
    do
    {
        system("cls");
        TITLU();
        bk.create_book();
        books.write((char*)&bk,sizeof(book));
        cout<<"\nVrei sa mai adaugi carti?(y/n?)";
        cin>>ch;
        cin.get();
    }
    while(ch=='y'||ch=='Y');
    books.close();
}
void afisare_carti()
{
    books.open("carti.bin",ios::in|ios::binary);
    books.clear();
    books.seekg(0);  //set pozitie la inceputul fisierului
    while(books.read((char*)&bk,sizeof(book)))
        bk.show_book();
    books.close();
}
void add_pers()
{
    char ch;
    pers.open("persoane.bin",ios::out|ios::app|ios::binary);
    do
    {
        system("cls");
        TITLU();
        st.create_student();
        pers.write((char*)&st,sizeof(student));
        cout<<"\nVrei sa mai adaugi persoane?(y/n?)";
        cin>>ch;
        cin.get();
    }
    while(ch=='y'||ch=='Y');
    pers.close();
}
void afisare_pers()
{
    pers.open("persoane.bin",ios::in|ios::binary);
    pers.clear();
    pers.seekg(0);  //set pozitie la inceputul fisierului
    while(pers.read((char*)&st,sizeof(student)))
        st.show_student();
    pers.close();
}
bool existaNumelePersoanei(char studentName[30])
{
    pers.open("persoane.bin",ios::in|ios::binary);
    pers.clear();
    pers.seekg(0);
    while(pers.read((char*)&st,sizeof(student)))
    {
        if(strcmp(st.studentName,studentName)==0)
        {
            pers.close();
            return true;
        }
    }
    pers.close();
    return false;
}

bool existaNumeleCartii(char bookName[30])
{
    books.open("carti.bin",ios::in|ios::binary);
    books.clear();
    books.seekg(0);
    while(books.read((char*)&bk,sizeof(book)))
    {
        if(strcmp(bk.bName,bookName)==0)
        {
            books.close();
            return true;
        }
    }
    books.close();
    return false;
}

int imprumut_nou()
{
    char studentName[30],bookName[30];
    impr.open("imprumut.bin",ios::out|ios::binary);
    cout<<"Introdu numele persoanei care imprumuta :";
    cin.get(studentName,30);
    cin.get();
    if(!existaNumelePersoanei(studentName))
    {
        cout<<"Aceasta persoana nu exista\n";
        return 0;
    }
    cout<<"Introdu numele cartii :";
    cin.get(bookName,30);
    cin.get();
    if(!existaNumeleCartii(bookName))
    {
        cout<<"Aceasta carte nu exista\n";
        return 0;
    }
    imprum.creazaImprumut(studentName,bookName);
    impr.write((char*)&imprum,sizeof(imprumut));
    impr.close();
    return 1;
}
void afisare_imprum()
{
    impr.open("imprumut.bin",ios::in|ios::binary);
    impr.clear();
    impr.seekg(0);  //set pozitie la inceputul fisierului
    while(impr.read((char*)&imprum,sizeof(imprumut)))
        imprum.show_imprumut();
    impr.close();
}
void afisare_meniu()
{
    cout<<"Ce doriti sa faceti?"<<endl;
    cout<<"\n0 Iesire"<<endl;
    cout<<"1 Adauga carte noua"<<endl;
    cout<<"2 Adauga persoana noua"<<endl;
    cout<<"3 Vezi cine a imprumutat cartea"<<endl;
    cout<<"4 Vezi date persoana"<<endl;
    cout<<"5 Adauga imprumut nou"<<endl;
    cout<<"6 Afiseaza toate cartile"<<endl;
    cout<<"7 Afiseaza toate persoanele"<<endl;
}

void meniu()
{
    TITLU();
    int rasp;
    do
    {
        afisare_meniu();
        cin>>rasp; cin.get();
        system("cls");
        TITLU();
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
        /*case 3: list_imprumut();
         break;
         case 4: data_pers();
         break;*/
         case 5: imprumut_nou();
         break;
        case 6:
            afisare_carti();
            break;
        case 7:
            afisare_pers();
            break;
        default:
            cout<<"Optiune gresita.";
            break;
        };
    }
    while(true);
}
int main()
{
    initializare();
    meniu();
    return 0;
}
