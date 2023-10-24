#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <math.h>

#define WIDTH 900
#define HEIGTH 900
#define GRIDSIZE 9

class cell 
{
  public:
    sf::Vector2f pos;
    int nPossib;

    int possibleCellsUp[16] = {0};
    int possibleCellsDown[16] = {0};
    int possibleCellsLeft[16] = {0};
    int possibleCellsRight[16] = {0};

    //variable to store path to image
    std::string imgPath;
    

    cell()
    {
        pos.x = 0;
        pos.y = 0;

        imgPath = "img/0.png";
    };
};

void drawGrid(sf::RenderWindow &window, cell grid[GRIDSIZE][GRIDSIZE])
{
    for (int i = 0; i < GRIDSIZE; i++)
    {
        for (int j = 0; j < GRIDSIZE; j++)
        {
            sf::Sprite sprite;
            sf::Texture texture;
            texture.loadFromFile(grid[i][j].imgPath);
            sprite.setTexture(texture);
            sprite.setPosition(grid[i][j].pos);

            window.draw(sprite);
        }
    }
}

int main()
{
    //*tela e view
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "SFML!", sf::Style::Close | sf::Style::Titlebar);
    sf::View view(sf::Vector2f(GRIDSIZE * 9 / 2, GRIDSIZE * 9 / 2), sf::Vector2f(GRIDSIZE * 10, GRIDSIZE * 10));
    window.setView(view);

    //declare the map grid
    cell grid[GRIDSIZE][GRIDSIZE];
    for (int i = 0; i < GRIDSIZE; i++)
    {
        for (int j = 0; j < GRIDSIZE; j++)
        {
            grid[i][j].pos.x = i * 9;//multiplique por 10 para separar as celulas
            grid[i][j].pos.y = j * 9;
        }
    }

    grid[0][0].imgPath = "img/2.png";
    grid[1][0].imgPath = "img/9.png";
    grid[2][0].imgPath = "img/9.png";
    grid[3][0].imgPath = "img/9.png";
    grid[4][0].imgPath = "img/4.png";



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

    //!code that will be executed every frame
    window.clear();

    //? render something on the screen

    //*draw the grid
    drawGrid(window, grid);


    //? refresh the screen applying the changes
    window.display();

    }

    return 0;
}