#include <iostream>
#include<fstream>
#include<String.h>
#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "book.h"
#include "student.h"
#include "imprumut.h"
#include "Meniu.h"
using namespace std;
fstream books,pers,impr;
book bk;
student st;
imprumut imprum;
inline bool checkIfFileExists(const string& fileName){
    ifstream file(fileName.c_str());
    if (file.good())
    {
        file.close();
        return true;
    }
    else
    {
        file.close();
        return false;
    }
}
void initializare(){
    if(!checkIfFileExists("bazaDeDate/persoane.bin"))
    {
        ofstream auxiliarFile;
        auxiliarFile.open("bazaDeDate/persoane.bin");
        auxiliarFile.close();
    }
    if(!checkIfFileExists("bazaDeDate/carti.bin"))
    {
        ofstream auxiliarFile;
        auxiliarFile.open("bazaDeDate/carti.bin");
        auxiliarFile.close();
    }
    if(!checkIfFileExists("bazaDeDate/imprumut.bin"))
    {
        ofstream auxiliarFile;
        auxiliarFile.open("bazaDeDate/imprumut.bin");
        auxiliarFile.close();
    }
}
void add_book(){
    char ch;
    books.open("carti.bin",ios::out|ios::app|ios::binary);
    system("cls");
    do
    {
        bk.create_book();
        books.write((char*)&bk,sizeof(book));
        cout<<"\nVrei sa mai adaugi carti?(y/n?)";
        cin>>ch;
        cin.get();
        system("cls");
    }
    while(ch=='y'||ch=='Y');
    books.close();
}
void afisare_carti(){
    int ID=1;
    books.open("carti.bin",ios::in|ios::binary);
    books.clear();
    books.seekg(0);
    system("cls");
    while(books.read((char*)&bk,sizeof(book)))
    {
        cout<<ID++<<". " ;
        bk.show_book();
    }
    books.close();
}
void add_pers(){
    char ch;
    pers.open("persoane.bin",ios::out|ios::app|ios::binary);
    system("cls");
    do
    {
        st.create_student();
        pers.write((char*)&st,sizeof(student));
        cout<<"\nVrei sa mai adaugi persoane?(y/n?)";
        cin>>ch;
        cin.get();
        system("cls");
    }
    while(ch=='y'||ch=='Y');
    pers.close();
}
void afisare_pers(){
    int ID=1;
    pers.open("persoane.bin",ios::in|ios::binary);
    pers.clear();
    pers.seekg(0);  //set pozitie la inceputul fisierului
    while(pers.read((char*)&st,sizeof(student)))
    {
        cout<<ID++<<". " ;
        st.show_student();
    }
    pers.close();
}
bool existaNumelePersoanei(char studentName[30]){
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
bool existaNumeleCartii(char bookName[30]){
    books.open("bazaDeDate/carti.bin",ios::in|ios::binary);
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
int imprumut_nou(){
    char studentName[30],bookName[30];
    impr.open("bazaDeDate/imprumut.bin",ios::out|ios::app|ios::binary);
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
void afisare_imprum(){
    impr.open("bazaDeDate/imprumut.bin",ios::in|ios::binary);
    impr.clear();
    impr.seekg(0);  //set pozitie la inceputul fisierului
    while(impr.read((char*)&imprum,sizeof(imprumut)))
        imprum.show_imprumut();
    impr.close();
}
int data_pers(){
    char studentName[30];
    cout<<"Introdu numele persoanei :";
    cin.get(studentName,30);
    cin.get();
    if(!existaNumelePersoanei(studentName))
    {
        cout<<"Aceasta persoana nu exista\n";
        return 0;
    }
    cout<<"Carti imprumutate:\n";
    impr.open("imprumut.bin",ios::in|ios::binary);
    while(impr.read((char*)&imprum,sizeof(imprumut)))
        if(strcmp(imprum.studentName,studentName)==0)
            cout<<imprum.bookName<<endl;
    impr.close();
    return 1;
}
int data_carte(){
    char bookName[30];
    cout<<"Introdu numele cartii :";
    cin.get(bookName,30);
    cin.get();
    if(!existaNumeleCartii(bookName))
    {
        cout<<"Aceasta carte nu exista\n";
        return 0;
    }
    cout<<"Persoane care au imprumutat cartea:\n";
    impr.open("imprumut.bin",ios::in|ios::binary);
    while(impr.read((char*)&imprum,sizeof(imprumut)))
        if(strcmp(imprum.bookName,bookName)==0)
            cout<<imprum.studentName<<endl;
    impr.close();
    return 1;
}

int main()
{
    initializare();
    sf::Font font;
    font.loadFromFile("fondul.ttf");

    sf::RenderWindow ecran(sf::VideoMode(1000,600),"Biblioteca");
    sf::Text titlu("Biblioteca", font, 70);

    titlu.setPosition(ecran.getSize().x/3,2);
    titlu.setColor(sf::Color::Red);

    class Meniu meniu(ecran.getSize().x, ecran.getSize().y);

    sf:: Texture imagine;
    imagine.loadFromFile("download.jpg");
    sf::Sprite imagineFundal(imagine);
    imagineFundal.setScale(0.27,0.25);

    sf::Event event;
    unsigned key =0;
    while(ecran.isOpen())
    {
        while (ecran.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                ecran.close();
                break;
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    meniu.moveUp();
                    break;
                case sf::Keyboard::Down:
                    meniu.moveDown();
                    break;
                case sf::Keyboard::Return:
                    switch(key)
                    {
                    case 0:
                        if(key = meniu.elementulSelectat);
                        else return 0;
                        meniu.seteazaPozitieDeInitiala();
                        break;
                    case 1:
                        switch(meniu.elementulSelectat)
                        {
                        case 0:add_book();
                                break;
                        case 1:afisare_carti();
                                break;
                        case 2:data_carte();
                                break;
                        }
                        break;
                    case 2:
                        switch(meniu.elementulSelectat)
                        {
                        case 0:add_pers();
                                break;
                        case 1:afisare_pers();
                                break;
                        case 2:data_pers();
                                break;
                        }
                        break;
                    case 3:
                        switch(meniu.elementulSelectat)
                        {
                        case 0:imprumut_nou();
                               break;
                        case 1:afisare_imprum();
                                break;
                        }
                        break;
                    }
                    break;
                case sf::Keyboard::BackSpace:
                    key = 0;
                    meniu.seteazaPozitieDeInitiala();
                    break;
                }
                break;
            }
        }
    ecran.clear();
    ecran.draw(imagineFundal);
    ecran.draw(titlu);
    meniu.afiseazaMeniul(ecran,key);
    ecran.display();
    }
    return 0;
}
