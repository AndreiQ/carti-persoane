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
inline bool checkIfFileExists(const string& fileName)
{
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
    int ID=1;
    books.open("carti.bin",ios::in|ios::binary);
    books.clear();
    books.seekg(0);  //set pozitie la inceputul fisierului
    while(books.read((char*)&bk,sizeof(book)))
    {
        cout<<ID++<<". " ;
        bk.show_book();
    }
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
    impr.open("imprumut.bin",ios::out|ios::app|ios::binary);
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
int data_pers()
{
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
int data_carte()
{
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
void afisare_meniu()
{
    cout<<"Ce doriti sa faceti?"<<endl;
    cout<<"\n0 Iesire"<<endl;
    cout<<"1 Adauga carte noua"<<endl;
    cout<<"2 Adauga persoana noua"<<endl;
    cout<<"3 Afiseaza lista imprumuturilor"<<endl;
    cout<<"4 Vezi date persoana"<<endl;
    cout<<"5 Vezi date carte"<<endl;
    cout<<"6 Adauga imprumut nou"<<endl;
    cout<<"7 Afiseaza toate cartile"<<endl;
    cout<<"8 Afiseaza toate persoanele"<<endl;
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
        case 0: exit(0);
            break;
        case 1: add_book();
            break;
        case 2: add_pers();
            break;
        case 3: afisare_imprum();
            break;
        case 4: data_pers();
            break;
        case 5: data_carte();
            break;
        case 6: imprumut_nou();
            break;
        case 7: afisare_carti();
            break;
        case 8: afisare_pers();
            break;
        default: cout<<"Optiune gresita.";
            break;
        };
    }
    while(true);
}
int main()
{
    initializare();
   int textFont=28;
    std::vector<sf::Text> op;
    sf::Font font;
    if (!font.loadFromFile("orange juice 2.0.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Biblioteca", font, 45);
   /* sf::Text op0("0. Iesire",font,textFont);
    sf::Text op1("1. Adauga carte noua",font,textFont);
    sf::Text op2("2. Adauga persoana noua",font,textFont);
    sf::Text op3("3. Afisare lista imprumuturi",font,textFont);
    sf::Text op4("4. Vezi date persoana",font,textFont);
    sf::Text op5("5. Vezi date carte",font,textFont);
    sf::Text op6("6. Adauga imprumut nou",font,textFont);
    sf::Text op7("7. Afiseaza toate cartile",font,textFont);
    sf::Text op8("8. Afiseaza toate persoanele",font,textFont);
    op.push_back(op0);op.push_back(op1);op.push_back(op2);op.push_back(op3);op.push_back(op4);op.push_back(op5);op.push_back(op6);op.push_back(op7);op.push_back(op8);
   */ sf::RenderWindow window(sf::VideoMode(640,640),"Library");
    text.setPosition(window.getSize().y/3,2);
    text.setColor(sf::Color::Red);
    sf::Thread meniu_consola(&meniu);
     // run it
    meniu_consola.launch();

    //DEFINE MENU
    class Meniu menu(window.getSize().x, window.getSize().y);

    // run the program as long as the window is open
    while(window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    menu.moveUp();
                    break;
                case sf::Keyboard::Down:
                    menu.moveDown();
                    break;
                case sf::Keyboard::Return:
                    switch(menu.getPressedItem())
                    {// aici facem ca optiunile alese sa fie afisate in consola******************
                    case 0:
                        return 0;
                        break;
                    //case 1:

                    case 2:
                        window.close();
                        break;
                    }
                    break;
                    }
                break;
                }
        }
        window.clear();
        window.draw(text);
        menu.draw(window);
        window.display();
    }
    return 0;
}
