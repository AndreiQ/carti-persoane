#include <iostream>
#include<fstream>
#include<String.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sstream>
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
string IntToString ( int number ){
ostringstream oss;
oss<< number;
return oss.str();
}
bool existaNumelePersoanei(char studentName[30]){
    pers.open("bazaDeDate/persoane.bin",ios::in|ios::binary);
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
void creeazaEcranCu(string totTextul,string titlu){

    sf::RenderWindow ecran(sf::VideoMode(400,500),titlu);

    sf:: Texture imagine;
    imagine.loadFromFile("ListaCarti.jpg");

    sf::Sprite imagineFundal(imagine);
    imagineFundal.setScale(1.5,3);

    sf::Font font;
    font.loadFromFile("fondul.ttf");

    sf::Text text(totTextul, font, 20);
    text.setPosition(1,1);
    text.setColor(sf::Color::Red);

    sf::Event event;
    while(ecran.isOpen())
    {
        while(ecran.pollEvent(event))
            switch(event.type)
        {
        case sf::Event::Closed:
            ecran.close();
            break;
        case sf::Event::KeyReleased:
            if(event.key.code==sf::Keyboard::Return)
            ecran.close();
            break;
        }
        ecran.clear();
        ecran.draw(imagineFundal);
        ecran.draw(text);
        ecran.display();
    }
}
void introduEroare(string textEroare){
sf::RenderWindow ecran(sf::VideoMode(400,200),"Eroare");

    sf:: Texture imagine;
    imagine.loadFromFile("eroare.jpg");

    sf::Sprite imagineFundal(imagine);
    imagineFundal.setScale(2,1.3);

    sf::Font font;
    font.loadFromFile("fondul.ttf");

    sf::Text text(textEroare, font, 30);
    text.setPosition(1,1);
    text.setColor(sf::Color::White);

    sf::Event event;

    while(ecran.isOpen())
    {
        while(ecran.pollEvent(event))
            switch(event.type)
        {
        case sf::Event::Closed:
            ecran.close();
            break;
        case sf::Event::KeyPressed:
            ecran.close();
        }
        ecran.clear();
        ecran.draw(imagineFundal);
        ecran.draw(text);
        ecran.display();
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
void afisare_carti(){
    int ID=1;
    books.open("bazaDeDate/carti.bin",ios::in|ios::binary);
    books.clear();
    books.seekg(0);
    string totTextul="";
    while(books.read((char*)&bk,sizeof(book)))
        totTextul +=IntToString(ID++)+". "+string(bk.bName)+" - "+string(bk.aName)+"\n";
    books.close();
    creeazaEcranCu(totTextul,"Lista Cartii");
}
void afisare_pers(){
    int ID=1;
    pers.open("bazaDeDate/persoane.bin",ios::in|ios::binary);
    pers.clear();
    pers.seekg(0);
    string totTextul="";
    while(pers.read((char*)&st,sizeof(student)))
    {
        totTextul+=IntToString(ID)+". "+string(st.studentName)+"\n";
        ID++;
    }
    pers.close();
    creeazaEcranCu(totTextul,"Lista Persoane");
}
void afisare_imprum(){
    impr.open("bazaDeDate/imprumut.bin",ios::in|ios::binary);
    impr.clear();
    impr.seekg(0);
    int ID=1;
    string totTextul;
    while(impr.read((char*)&imprum,sizeof(imprumut)))
        totTextul +=IntToString(ID++)+". "+string(imprum.bookName)+" - "+string(imprum.studentName)+"\n";
    impr.close();
    creeazaEcranCu(totTextul,"Imprumuturi");
}
void adaugaImprumutNou(){
    impr.open("bazaDeDate/imprumut.bin",ios::out|ios::app|ios::binary);
    string totTextul = "Nume persoana:\n";
    string inputText="";
    int numarInputuri = 2;
    char numePersoana[30];
    char numeCarte[30];
    bool carte = false,persoana=false;
    sf::RenderWindow ecran(sf::VideoMode(500,300),"adauga Cartea");

    sf:: Texture imagine;
    imagine.loadFromFile("inputuri.jpg");

    sf::Sprite imagineFundal(imagine);
    imagineFundal.setScale(0.35,0.4);

    sf::Font font;
    font.loadFromFile("fondul.ttf");

    sf::Text text(totTextul, font, 20);
    text.setPosition(1,1);
    text.setColor(sf::Color::Red);

    sf::Event event;

    while(ecran.isOpen())
    {
        while(ecran.pollEvent(event))
            switch(event.type)
        {
        case sf::Event::Closed:
            ecran.close();
            break;
        case sf::Event::KeyReleased:
            if(event.key.code==sf::Keyboard::Return)
            {
                numarInputuri--;
                if(numarInputuri)
                    {
                    strcpy(numePersoana,inputText.c_str());
                    if(existaNumelePersoanei(numePersoana))
                        {
                        totTextul+=inputText+"\nNume Carte:\n";
                        persoana =true;
                        }
                    else
                        {
                         numarInputuri++;
                         introduEroare("Aceasta persoana nu exista");
                        }
                    inputText ="";
                    }
                else
                    {
                    strcpy(numeCarte,inputText.c_str());
                    if(existaNumeleCartii(numeCarte))
                        {
                        carte =true;
                        ecran.close();
                        }
                    else
                        {
                        numarInputuri++;
                        inputText="";
                        introduEroare("Aceasta carte nu exista");
                        }
                    }
            }
            break;
        case sf::Event::KeyPressed:
            if(event.key.code==sf::Keyboard::BackSpace)
                inputText = inputText.substr(0,inputText.size()-1);
            break;
        case sf::Event::TextEntered:
            if((event.text.unicode>=65&&event.text.unicode<=90)||(event.text.unicode>=97&&event.text.unicode<=122)||(event.text.unicode==32))
                inputText += event.text.unicode;
            break;
        }
        text.setString(totTextul+inputText);
        ecran.clear();
        ecran.draw(imagineFundal);
        ecran.draw(text);
        ecran.display();
    }
    if(carte&&persoana)
    {
    imprum.creazaImprumut(numePersoana,numeCarte);
    impr.write((char*)&imprum,sizeof(imprum));
    }
    impr.close();
}
void adaugaPersoana(){

    pers.open("bazaDeDate/persoane.bin",ios::out|ios::app|ios::binary);
    string totTextul = "Nume persoana :\n";
    string inputText="";
    char numePersoana[30];

    sf::RenderWindow ecran(sf::VideoMode(500,300),"adauga Cartea");

    sf:: Texture imagine;
    imagine.loadFromFile("inputuri.jpg");

    sf::Sprite imagineFundal(imagine);
    imagineFundal.setScale(0.35,0.4);

    sf::Font font;
    font.loadFromFile("fondul.ttf");

    sf::Text text(totTextul, font, 20);
    text.setPosition(1,1);
    text.setColor(sf::Color::Red);

    sf::Event event;

    while(ecran.isOpen())
    {
        while(ecran.pollEvent(event))
            switch(event.type)
        {
        case sf::Event::Closed:
            ecran.close();
            break;
        case sf::Event::KeyReleased:
            if(event.key.code==sf::Keyboard::Return)
            {
                strcpy(numePersoana,inputText.c_str());
                ecran.close();
            }
            break;
        case sf::Event::KeyPressed:
            if(event.key.code==sf::Keyboard::BackSpace)
                inputText = inputText.substr(0,inputText.size()-1);
        case sf::Event::TextEntered:
            if((event.text.unicode>=65&&event.text.unicode<=90)||(event.text.unicode>=97&&event.text.unicode<=122)||(event.text.unicode==32))
                inputText += event.text.unicode;
            break;
        }
        text.setString(totTextul+inputText);
        ecran.clear();
        ecran.draw(imagineFundal);
        ecran.draw(text);
        ecran.display();
    }
    st.create_student(numePersoana);
    pers.write((char*)&st,sizeof(student));
    pers.close();
}
void adaugaCarte(){
    books.open("bazaDeDate/carti.bin",ios::out|ios::app|ios::binary);
    string totTextul = "Nume carte :\n";
    string inputText="";
    int numarInputuri = 2;
    char numeAutor[30];
    char numeCarte[30];
    bool carte=false,autor=false;
    sf::RenderWindow ecran(sf::VideoMode(500,300),"adauga Cartea");

    sf:: Texture imagine;
    imagine.loadFromFile("inputuri.jpg");

    sf::Sprite imagineFundal(imagine);
    imagineFundal.setScale(0.35,0.4);

    sf::Font font;
    font.loadFromFile("fondul.ttf");

    sf::Text text(totTextul, font, 20);
    text.setPosition(1,1);
    text.setColor(sf::Color::Red);

    sf::Event event;

    while(ecran.isOpen())
    {
        while(ecran.pollEvent(event))
            switch(event.type)
        {
        case sf::Event::Closed:
            ecran.close();
            break;
        case sf::Event::KeyReleased:
            if(event.key.code==sf::Keyboard::Return)
            {
                numarInputuri--;
                if(numarInputuri)
                    {
                    carte = true;
                    totTextul+=inputText+"\nNume Autor:\n";
                    strcpy(numeCarte,inputText.c_str());
                    inputText = "";
                    }
                else
                    {
                    autor = true;
                    inputText+=" ";
                    strcpy(numeAutor,inputText.c_str());
                    ecran.close();
                    }
            }
            break;
        case sf::Event::KeyPressed:
            if(event.key.code==sf::Keyboard::BackSpace)
                inputText = inputText.substr(0,inputText.size()-1);
            break;
        case sf::Event::TextEntered:
            if((event.text.unicode>=65&&event.text.unicode<=90)||(event.text.unicode>=97&&event.text.unicode<=122)||(event.text.unicode==32))
                inputText += event.text.unicode;
            break;
        }
        text.setString(totTextul+inputText);
        ecran.clear();
        ecran.draw(imagineFundal);
        ecran.draw(text);
        ecran.display();
    }
    if(carte&&autor)
    {
        bk.create_book(numeAutor,numeCarte);
        books.write((char*)&bk,sizeof(book));
    }
    books.close();
}

int main(){
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
                        case 0:adaugaCarte();
                                break;
                        case 1:afisare_carti();
                                break;
                        }
                        break;
                    case 2:
                        switch(meniu.elementulSelectat)
                        {
                        case 0:adaugaPersoana();
                                break;
                        case 1:afisare_pers();
                                break;
                        }
                        break;
                    case 3:
                        switch(meniu.elementulSelectat)
                        {
                        case 0:adaugaImprumutNou();
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
