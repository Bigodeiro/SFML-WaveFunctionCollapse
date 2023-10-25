#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <math.h>

#define WIDTH 900
#define HEIGTH 900
#define GRIDSIZE 9
#define CELLSIZE 9

int random(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

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
        nPossib = 16;

        imgPath = "img/16.png";
    };
};

void drawGrid(sf::RenderWindow &window, cell grid[GRIDSIZE][GRIDSIZE])
{
    for (int i = 0; i < GRIDSIZE; i++)
    {
        for (int j = 0; j < GRIDSIZE; j++)
        {
            //display img
            sf::Sprite sprite;
            sf::Texture texture;
            texture.loadFromFile(grid[i][j].imgPath);
            sprite.setTexture(texture);
            sprite.setPosition(grid[i][j].pos);

            window.draw(sprite);

            //print npossib of each cell

            //std::cout << std::setw(2) << grid[i][j].nPossib << " ";
        }
        //std::cout << std::endl;
    }
    //std::cout << std::endl;
}

int lowestNPossib (cell grid[GRIDSIZE][GRIDSIZE])
{
    int min = 16;

    for (int i = 0; i < GRIDSIZE; i++)
    {
        for (int j = 0; j < GRIDSIZE; j++)
        {
            if (grid[i][j].nPossib < min && grid[i][j].nPossib != 0)
            {
                min = grid[i][j].nPossib;
            }
        }
    }

    return min;
}

sf::Vector2i randomCell (cell grid[GRIDSIZE][GRIDSIZE])
{
    sf::Vector2i pos;
    int min = lowestNPossib(grid);
    int n = 0;


    //*Aleatoriza uma celula qualquer, mas se ela não for uma das com menor nPossib, ele aleatoriza de novo
    while (n != min)
    {
        pos.x = random(0, GRIDSIZE - 1);
        pos.y = random(0, GRIDSIZE - 1);

        n = grid[pos.x][pos.y].nPossib;
    }

    return pos;
}

int main()
{
    //*tela e view
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "SFML!", sf::Style::Close | sf::Style::Titlebar);
    sf::View view(sf::Vector2f(GRIDSIZE * CELLSIZE / 2, GRIDSIZE * CELLSIZE / 2), sf::Vector2f(GRIDSIZE * CELLSIZE + 100, GRIDSIZE * CELLSIZE + 100));
    window.setView(view);

    cell grid[GRIDSIZE][GRIDSIZE];
    for (int i = 0; i < GRIDSIZE; i++)
    {
        for (int j = 0; j < GRIDSIZE; j++)
        {
            grid[i][j].pos.x = i * (CELLSIZE + 1);//? 0 é o espaçamento entre as celulas
            grid[i][j].pos.y = j * (CELLSIZE + 1);

        }
    }




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