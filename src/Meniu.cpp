#include "Meniu.h"

Meniu::Meniu(float width, float height)
{
    if(!font.loadFromFile("orange juice 2.0.ttf"))
    {
        //handle error
    }
    for(int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
        {   meniu[i].setCharacterSize(30);
            meniu[i].setFont(font);
            meniu[i].setColor(sf::Color::White);
            meniu[i].setPosition(sf::Vector2f(width/10, height/(MAX_NUMBER_OF_ITEMS + 1) * (i+1)));
        }
    meniu[0].setColor(sf::Color::Red);
    meniu[0].setString("0. Iesire");
    meniu[1].setString("1. Adauga carte noua");
    meniu[2].setString("2. Adauga persoana noua");
    meniu[3].setString("3. Afisare lista imprumuturi");
    meniu[4].setString("4. Vezi date persoana");
    meniu[5].setString("5. Vezi date carte");
    meniu[6].setString("6. Adauga imprumut nou");
    meniu[7].setString("7. Afiseaza toate cartile");
    meniu[8].setString("8. Afiseaza toate persoanele");

    selectedItemIndex = 0;
}
void Meniu::draw(sf::RenderWindow &window)
{
    for(int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        window.draw(meniu[i]);
    }
}
void Meniu::moveUp()
{
    if(selectedItemIndex - 1 >= 0)
    {
        meniu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex--;
        meniu[selectedItemIndex].setColor(sf::Color::Red);
    }
}
void Meniu::moveDown()
{
    if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
    {
        meniu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex++;
        meniu[selectedItemIndex].setColor(sf::Color::Red);
    }
}







