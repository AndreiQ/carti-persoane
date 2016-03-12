#ifndef MENIU_H
#define MENIU_H
#include<SFML/Graphics.hpp>
#define maximElementeMeniu 100
class Meniu
{
    public:
        Meniu(float w, float h);
        int elementulSelectat;
        void afiseazaMeniul(sf::RenderWindow &window,int key);
        void afiseazaMeniulPrincipal(sf::RenderWindow &window);
        void afiseazaMeniulCartilor(sf::RenderWindow &window);
        void afiseazaMeniulPersoanelor(sf::RenderWindow &window);
        void afiseazaMeniulImprumuturilor(sf::RenderWindow &window);
        void moveUp();
        void moveDown();
        void seteazaPozitieDeInitiala();
    private:
        sf::Font font;
        sf::Text meniu[maximElementeMeniu];
        int numarulDeElementeDinMeniulActual;
        float width;
        float height;

};

#endif // MENIU_H
