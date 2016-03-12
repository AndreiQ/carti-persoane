#include "Meniu.h"

Meniu::Meniu(float w,float h)
{
width = w;
height = h;
font.loadFromFile("fondul.ttf");
numarulDeElementeDinMeniulActual = 4;
for(int i = 0;i < numarulDeElementeDinMeniulActual;i++)
    {
        meniu[i].setCharacterSize(40);
        meniu[i].setFont(font);
        meniu[i].setColor(sf::Color::White);
        meniu[i].setPosition(sf::Vector2f(width/10, height/(numarulDeElementeDinMeniulActual + 1) *(i+1)));
    }
elementulSelectat = 0;
meniu[elementulSelectat].setColor(sf::Color::Red);
}
void Meniu::moveUp()
{
    if(elementulSelectat - 1 >= 0)
    {
        meniu[elementulSelectat].setColor(sf::Color::White);
        elementulSelectat--;
        meniu[elementulSelectat].setColor(sf::Color::Red);
    }
    else
    {
        meniu[elementulSelectat].setColor(sf::Color::White);
        elementulSelectat = numarulDeElementeDinMeniulActual-1;
        meniu[elementulSelectat].setColor(sf::Color::Red);
    }
}
void Meniu::moveDown()
{
    if(elementulSelectat + 1 < numarulDeElementeDinMeniulActual)
    {
        meniu[elementulSelectat].setColor(sf::Color::White);
        elementulSelectat++;
        meniu[elementulSelectat].setColor(sf::Color::Red);
    }
    else
    {
        meniu[elementulSelectat].setColor(sf::Color::White);
        elementulSelectat = 0;
        meniu[elementulSelectat].setColor(sf::Color::Red);
    }
}
void Meniu::seteazaPozitieDeInitiala()
{
    elementulSelectat = 0;
    meniu[elementulSelectat].setColor(sf::Color::Red);
    for(int i=1;i<maximElementeMeniu;i++)
        meniu[i].setColor(sf::Color::White);
}
void Meniu::afiseazaMeniul(sf::RenderWindow &window,int key)
{
    if(key==0)
        afiseazaMeniulPrincipal(window);
    if(key==1)
        afiseazaMeniulCartilor(window);
    if(key==2)
        afiseazaMeniulPersoanelor(window);
    if(key==3)
        afiseazaMeniulImprumuturilor(window);
}
void Meniu::afiseazaMeniulPrincipal(sf::RenderWindow &window)
{
    numarulDeElementeDinMeniulActual = 4;
    for(int i = 0; i < numarulDeElementeDinMeniulActual; i++)
        window.draw(meniu[i]);
    meniu[0].setString("0. Iesire");
    meniu[1].setString("1. Operatii Carti");
    meniu[2].setString("2. Operatii Persoane");
    meniu[3].setString("3. Operatii Imprumuturi");
}
void Meniu::afiseazaMeniulCartilor(sf::RenderWindow &window)
{
numarulDeElementeDinMeniulActual = 3;
int numarulDeOperatiiPentruCarti=3;
for(int i = 0; i < numarulDeOperatiiPentruCarti; i++)
        window.draw(meniu[i]);
meniu[0].setString("0. Carte noua");
meniu[1].setString("1. Lista carti");
meniu[2].setString("2. Date despre carte");
}

void Meniu::afiseazaMeniulPersoanelor(sf::RenderWindow &window)
{
numarulDeElementeDinMeniulActual = 3;
int numarulDeOperatiiPentruPersoane=3;
for(int i = 0; i < numarulDeOperatiiPentruPersoane; i++)
        window.draw(meniu[i]);
meniu[0].setString("0. Persoana noua");
meniu[1].setString("1. Lista persoane");
meniu[2].setString("2. Date despre persoane");

}
void Meniu::afiseazaMeniulImprumuturilor(sf::RenderWindow &window)
{
numarulDeElementeDinMeniulActual = 2;
int numarulDeOperatiiPentruImprumuturi=2;
for(int i = 0; i < numarulDeOperatiiPentruImprumuturi; i++)
        window.draw(meniu[i]);
meniu[0].setString("0. Imprumut nou");
meniu[1].setString("1. Lista imprumut");
}







