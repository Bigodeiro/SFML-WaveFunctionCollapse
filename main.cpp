#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <math.h>

#define WIDTH 1280
#define HEIGTH 960


int main()
{
    //*tela e view
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "SFML!", sf::Style::Close | sf::Style::Titlebar);
    sf::View view(sf::Vector2f(0,0), sf::Vector2f(WIDTH, HEIGTH));
    window.setView(view);
    // store a jpg file in a sfml


    while (window.isOpen())//! cada iteração aqui é um frame
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                
                window.close();

                break;
            }
        }

    //!codigo a ser executado todo frame
    window.clear();

    //? renderiza algo para a tela, modificando-a

    //window.draw()

    //? recarrega a tela, fazendo com que as mudanças sejam efetivadas
    window.display();

    }

    return 0;
}