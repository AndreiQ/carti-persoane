#ifndef MENIU_H
#define MENIU_H
#include<SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 9

class Meniu
{
    public:
        Meniu(float width, float height);
        int getPressedItem(){return selectedItemIndex;}
        bool isPlaying = false;
        void draw(sf::RenderWindow &window);
        void moveUp();
        void moveDown();
    private:
        int selectedItemIndex;
        sf::Font font;
        sf::Text meniu[MAX_NUMBER_OF_ITEMS];
};

#endif // MENIU_H
