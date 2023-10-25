#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <math.h>

#define WIDTH 900
#define HEIGTH 900
#define GRIDSIZE 16
#define CELLSIZE 9

int random(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

class cell 
{
  public:
    sf::Vector2f pos;
    int nPossib = 16;
    int id;

    std::array<int, 16> possibId = {1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15, -1};

    std::array<int, 16> possibleCellsUp;
    std::array<int, 16> possibleCellsDown;
    std::array<int, 16> possibleCellsLeft;
    std::array<int, 16> possibleCellsRight;

    //variable to store path to image
    std::string imgPath;
    

    cell()
    {
        pos.x = 0;
        pos.y = 0;
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

void printGridId(cell grid[GRIDSIZE][GRIDSIZE])
{
    for (int i = 0; i < GRIDSIZE; i++)
    {
        for (int j = 0; j < GRIDSIZE; j++)
        {
            std::cout << std::setw(2) << grid[i][j].id << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void printGridNpossib(cell grid[GRIDSIZE][GRIDSIZE])
{
    for (int i = 0; i < GRIDSIZE; i++)
    {
        for (int j = 0; j < GRIDSIZE; j++)
        {
            std::cout << std::setw(2) << grid[j][i].nPossib << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
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

sf::Vector2i randomLowestCell (cell grid[GRIDSIZE][GRIDSIZE])
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

void changeCellId(cell grid[GRIDSIZE][GRIDSIZE], sf::Vector2i pos, int id)
{
    grid[pos.x][pos.y].id = id;
    grid[pos.x][pos.y].imgPath = "img/" + std::to_string(id) + ".png";


    /*baixo vazio =       0, 2, 3, 4, 8, 9, 10,14,-1,-1,-1,-1,-1,-1,-1,-1
    esquerda vazio =      0, 1, 3, 4, 6, 7, 10,13,-1,-1,-1,-1,-1,-1,-1,-1
    direita vazio =       0, 1, 2, 3, 5, 6, 8, 11,-1,-1,-1,-1,-1,-1,-1,-1
    cima vazio =          0, 1, 2, 4, 5, 7, 9, 12,-1,-1,-1,-1,-1,-1,-1,-1

    baixo preenchido =    1, 5, 6, 7, 11,12,13,15,-1,-1,-1,-1,-1,-1,-1,-1
    esquerda preenchido = 2, 5, 8, 9, 11,12,14,15,-1,-1,-1,-1,-1,-1,-1,-1
    direita preenchido =  4, 7, 9, 10,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1
    cima preenchido =     3, 6, 8, 10,11,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1
    */
   

    switch (id)
    {
    case 0:
        grid[pos.x][pos.y].nPossib = 0;
        grid[pos.x][pos.y].possibleCellsDown =  {0,2,3,4,8,9,10,14,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsLeft =  {0,1,3,4,6,7,10,13,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsRight = {0,1,2,3,5,6,8,11,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsUp =    {0,1,2,4,5,7,9,12,-1,-1,-1,-1,-1,-1,-1,-1};
        break;
    case 1:
        grid[pos.x][pos.y].nPossib = 0;
        grid[pos.x][pos.y].possibleCellsDown =  {0,2,3,4,8,9,10,14,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsLeft =  {0,1,3,4,6,7,10,13,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsRight = {0,1,2,3,5,6,8,11,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsUp =    {3,6,8,10,11,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        break;
    case 2:
        grid[pos.x][pos.y].nPossib = 0;
        grid[pos.x][pos.y].possibleCellsDown =  {0, 2, 3, 4, 8, 9, 10,14,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsLeft =  {0, 1, 3, 4, 6, 7, 10,13,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsRight = {4, 7, 9, 10,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsUp =    {0, 1, 2, 4, 5, 7, 9, 12,-1,-1,-1,-1,-1,-1,-1,-1};
        break;
    case 3:
        grid[pos.x][pos.y].nPossib = 0;
        grid[pos.x][pos.y].possibleCellsDown =  {1, 5, 6, 7, 11,12,13,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsLeft =  {0, 1, 3, 4, 6, 7, 10,13,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsRight = {0, 1, 2, 3, 5, 6, 8, 11,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsUp =    {0, 1, 2, 4, 5, 7, 9, 12,-1,-1,-1,-1,-1,-1,-1,-1};
        break;
    case 4:
        grid[pos.x][pos.y].nPossib = 0;
        grid[pos.x][pos.y].possibleCellsDown =  {0, 2, 3, 4, 8, 9, 10,14,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsLeft =  {2, 5, 8, 9, 11,12,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsRight = {0, 1, 2, 3, 5, 6, 8, 11,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsUp =    {0, 1, 2, 4, 5, 7, 9, 12,-1,-1,-1,-1,-1,-1,-1,-1};
        break;
    case 5:
        grid[pos.x][pos.y].nPossib = 0;
        grid[pos.x][pos.y].possibleCellsDown =  {0, 2, 3, 4, 8, 9, 10,14,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsLeft =  {0, 1, 3, 4, 6, 7, 10,13,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsRight = {4, 7, 9, 10,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsUp =    {3, 6, 8, 10,11,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        break;
    case 6:
        grid[pos.x][pos.y].nPossib = 0;
        grid[pos.x][pos.y].possibleCellsDown =  {1, 5, 6, 7, 11,12,13,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsLeft =  {0, 1, 3, 4, 6, 7, 10,13,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsRight = {0, 1, 2, 3, 5, 6, 8, 11,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsUp =    {3, 6, 8, 10,11,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        break;
    case 7:
        grid[pos.x][pos.y].nPossib = 0;
        grid[pos.x][pos.y].possibleCellsDown =  {0, 2, 3, 4, 8, 9, 10,14,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsLeft =  {2, 5, 8, 9, 11,12,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsRight = {0, 1, 2, 3, 5, 6, 8, 11,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsUp =    {3, 6, 8, 10,11,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        break;
    case 8:
        grid[pos.x][pos.y].nPossib = 0;
        grid[pos.x][pos.y].possibleCellsDown =  {1, 5, 6, 7, 11,12,13,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsLeft =  {0, 1, 3, 4, 6, 7, 10,13,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsRight = {4, 7, 9, 10,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsUp =    {0, 1, 2, 4, 5, 7, 9, 12,-1,-1,-1,-1,-1,-1,-1,-1};
        break;
    case 9:
        grid[pos.x][pos.y].nPossib = 0;
        grid[pos.x][pos.y].possibleCellsDown =  {0, 2, 3, 4, 8, 9, 10,14,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsLeft =  {2, 5, 8, 9, 11,12,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsRight = {4, 7, 9, 10,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsUp =    {0, 1, 2, 4, 5, 7, 9, 12,-1,-1,-1,-1,-1,-1,-1,-1};
        break;
    case 10:
        grid[pos.x][pos.y].nPossib = 0;
        grid[pos.x][pos.y].possibleCellsDown =  {1, 5, 6, 7, 11,12,13,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsLeft =  {2, 5, 8, 9, 11,12,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsRight = {0, 1, 2, 3, 5, 6, 8, 11,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsUp =    {0, 1, 2, 4, 5, 7, 9, 12,-1,-1,-1,-1,-1,-1,-1,-1};
        break;
    case 11:
        grid[pos.x][pos.y].nPossib = 0;
        grid[pos.x][pos.y].possibleCellsDown =  {1, 5, 6, 7, 11,12,13,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsLeft =  {0, 1, 3, 4, 6, 7, 10,13,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsRight = {4, 7, 9, 10,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsUp =    {3, 6, 8, 10,11,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        break;
    case 12:
        grid[pos.x][pos.y].nPossib = 0;
        grid[pos.x][pos.y].possibleCellsDown =  {0, 2, 3, 4, 8, 9, 10,14,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsLeft =  {2, 5, 8, 9, 11,12,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsRight = {4, 7, 9, 10,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsUp =    {3, 6, 8, 10,11,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        break;
    case 13:
        grid[pos.x][pos.y].nPossib = 0;
        grid[pos.x][pos.y].possibleCellsDown =  {1, 5, 6, 7, 11,12,13,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsLeft =  {2, 5, 8, 9, 11,12,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsRight = {0, 1, 2, 3, 5, 6, 8, 11,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsUp =    {3, 6, 8, 10,11,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        break;
    case 14:
        grid[pos.x][pos.y].nPossib = 0;
        grid[pos.x][pos.y].possibleCellsDown =  {1, 5, 6, 7, 11,12,13,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsLeft =  {2, 5, 8, 9, 11,12,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsRight = {4, 7, 9, 10,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsUp =    {0, 1, 2, 4, 5, 7, 9, 12,-1,-1,-1,-1,-1,-1,-1,-1};
        break;
    case 15:
        grid[pos.x][pos.y].nPossib = 0;
        grid[pos.x][pos.y].possibleCellsDown =  {1, 5, 6, 7, 11,12,13,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsLeft =  {2, 5, 8, 9, 11,12,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsRight = {4, 7, 9, 10,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        grid[pos.x][pos.y].possibleCellsUp =    {3, 6, 8, 10,11,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1};
        break;
    case 16:
        grid[pos.x][pos.y].possibleCellsDown =  {1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15, -1};
        grid[pos.x][pos.y].possibleCellsLeft =  {1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15, -1};
        grid[pos.x][pos.y].possibleCellsRight = {1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15, -1};
        grid[pos.x][pos.y].possibleCellsUp =    {1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15, -1};
        break;
    }

}

void atualizaNPossib(cell grid[GRIDSIZE][GRIDSIZE])
{
    for (int x = 0; x < GRIDSIZE; x++)
    {
        for (int y = 0; y < GRIDSIZE; y++)
        {
            //*checa se a celula de CIMA existe
            if (y - 1 >= 0 && grid[x][y].id == 16)
            {
                for (int i = 0; i < 16; i++)
                {
                    int existe = 0;
                    for (int j = 0; j < 16; j++)
                    {
                        if (grid[x][y - 1].possibleCellsDown[j] == grid[x][y].possibId[i])
                        {
                            existe = 1;
                        }
                    }
                    if (existe == 0)
                    {
                        grid[x][y].possibId[i] = -1;
                    }
                }
            }

            //*checa se a celula de BAIXO existe
            if (y + 1 < GRIDSIZE && grid[x][y].id == 16)
            {
                for (int i = 0; i < 16; i++)
                {
                    int existe = 0;
                    for (int j = 0; j < 16; j++)
                    {
                        if (grid[x][y + 1].possibleCellsUp[j] == grid[x][y].possibId[i])
                        {
                            existe = 1;
                        }
                    }
                    if (existe == 0)
                    {
                        grid[x][y].possibId[i] = -1;
                    }
                }
            }

            //*checa se a celula da ESQUERDA existe
            if (x - 1 >= 0 && grid[x][y].id == 16)
            {
                for (int i = 0; i < 16; i++)
                {
                    int existe = 0;
                    for (int j = 0; j < 16; j++)
                    {
                        if (grid[x - 1][y].possibleCellsRight[j] == grid[x][y].possibId[i])
                        {
                            existe = 1;
                        }
                    }
                    if (existe == 0)
                    {
                        grid[x][y].possibId[i] = -1;
                    }
                }
            }

            //*checa se a celula da DIREITA existe
            if (x + 1 < GRIDSIZE && grid[x][y].id == 16)
            {
                for (int i = 0; i < 16; i++)
                {
                    int existe = 0;
                    for (int j = 0; j < 16; j++)
                    {
                        if (grid[x + 1][y].possibleCellsLeft[j] == grid[x][y].possibId[i])
                        {
                            existe = 1;
                        }
                    }
                    if (existe == 0)
                    {
                        grid[x][y].possibId[i] = -1;
                    }
                }
            }


            //! atualiza o nPossib
            int difID = 0;
            for (int ID = 0; ID < 16; ID++)
            {
                if (grid[x][y].possibId[ID] != -1 && grid[x][y].id == 16)
                {
                    difID++;
                }
                
            }
            grid[x][y].nPossib = difID;
        }
    } 
}

int main()
{
    //*tela e view
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "SFML!", sf::Style::Close | sf::Style::Titlebar);
    sf::View view(sf::Vector2f(GRIDSIZE * CELLSIZE / 2, GRIDSIZE * CELLSIZE / 2), sf::Vector2f(GRIDSIZE * CELLSIZE, GRIDSIZE * CELLSIZE));
    window.setView(view);

    //*cria a grid e aleatoriza uma celula para começar o algoritmo
    cell grid[GRIDSIZE][GRIDSIZE];
    for (int i = 0; i < GRIDSIZE; i++)
    {
        for (int j = 0; j < GRIDSIZE; j++)
        {
            grid[i][j].pos.x = i * (CELLSIZE + 0);//? 0 é o espaçamento entre as celulas
            grid[i][j].pos.y = j * (CELLSIZE + 0);

            changeCellId(grid, sf::Vector2i(i, j), 16);

        }
    }
    // sf::Vector2i pos = randomLowestCell(grid);
    sf::Vector2i pos = sf::Vector2i(4, 5);
    changeCellId(grid, pos, random(1, 15));

    atualizaNPossib(grid);

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
    //* appl 500ms delay

    //checks if there is any cell with id == 16
    int n16 = 0;
    for (int i = 0; i < GRIDSIZE; i++)
    {
        for (int j = 0; j < GRIDSIZE; j++)
        {
            if (grid[i][j].id == 16)
            {
                n16++;
                i = GRIDSIZE;
                j = GRIDSIZE;
            }
        }
    }
    if (n16 == 1)
    {
        sf::sleep(sf::milliseconds(125));

            sf::Vector2i posLowest = randomLowestCell(grid);

        //changes the lowest cell to a random id in its possibId
        int changed = 0;
        while(changed == 0)
        {
            int id = random(0, 15);
            if (grid[posLowest.x][posLowest.y].possibId[id] != -1)
            {
                changeCellId(grid, posLowest, grid[posLowest.x][posLowest.y].possibId[id]);
                changed = 1;
            }
        }
        atualizaNPossib(grid);
    }


    //*clear the screen
    window.clear();

    //? render something on the screen

    //*draw the grid
    drawGrid(window, grid);


    //? refresh the screen applying the changes
    window.display();

    }

    return 0;
}