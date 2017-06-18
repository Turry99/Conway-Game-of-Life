#include <iostream>
#include <SFML/Graphics.hpp>
/**
    Author: Turry
    If you use the code please give credit.

0 White (Dead)
1 Black (Alive

Enter -->Generate random pattern
Space -->Start
Esc   -->Clear the screen

/**/

const int length = 10; //length of the square
const int w = length*90; //how many squares, 90x90
int grid[90][90];
int sgrid[90][90];

using namespace sf;

void generate();
void reset();
void randGen();

int main() {
    RenderWindow window(VideoMode(w,w), "Game Of Life");


    Texture t;
    t.loadFromFile("tiles.png");
    Sprite s(t);

    randGen(); //Make the grid random

    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);
        int x = pos.x/length;
        int y = pos.y/length;

        Event e;
        while (window.pollEvent(e))
        {

            if (e.type == Event::Closed) window.close();
            if (e.key.code == Keyboard::Space) generate();
            if (e.key.code == Keyboard::Escape) reset();
            if (e.key.code == Keyboard::Return) randGen();
        }

            if (Mouse::isButtonPressed(Mouse::Left)) grid[x][y] = 1; // Add
            if (Mouse::isButtonPressed(Mouse::Right)) grid[x][y] = 0; // Delete


        window.clear(Color::Green);


        /////Draw the squares////
        for ( int i=0; i< 90; i++)
            for (int j=0; j<90; j++)
            {
                s.setTextureRect(IntRect(grid[i][j]*length,0,length,length));
                s.setPosition(i*length, j*length);
                window.draw(s);
            }

        window.display();


    }

    return 0;
}



void reset()
///Reset the screen
{
for ( int i=0; i< 90; i++)
    for (int j=0; j<90; j++)
    {
        grid[i][j] = 0;
        sgrid[i][j] = 0;
    }
}
void randGen()
////Randomly generates a grid
{
for ( int i=0; i< 90; i++)
    for (int j=0; j<90; j++)
    {
        grid[i][j] = 0;
        if (rand()%10 == 0) grid[i][j] = 1;
    }
}



void generate()
/**
 * i-1 ==>Up
 * i+1 ==>Down
 * j-1 ==>Left
 * j+1 ==>Right
 */
{
    for ( int i=0; i< 90; i++)
        for (int j=0; j<90; j++)
        {
            int count = 0;

            if (i==0)//Row 1
            {
                if( j ==0 ) //First square
                {
                    if (grid[i][j+1] == 1) count++;
                    if (grid[i+1][j] == 1) count++;
                    if (grid[i+1][j+1] == 1) count++;
                }
                else if (j < 89)// Upper row
                {
                    if (grid[i][j-1] == 1) count++;
                    if (grid[i][j+1] == 1) count++;
                    if (grid[i+1][j+1] == 1) count++;
                    if (grid[i+1][j-1] == 1) count++;
                    if (grid[i+1][j] == 1) count++;
                }
                else if (j == 89)// Last square
                {
                    if (grid[i][j-1] == 1) count++;
                    if (grid[i+1][j] == 1) count++;
                    if (grid[i+1][j-1] == 1) count++;
                }
            }


            if (i == 89) //Last row
            {
                if( j ==0 ) //First square
                {
                    if (grid[i-1][j] == 1) count++;
                    if (grid[i][j+1] == 1) count++;
                    if (grid[i-1][j+1] == 1) count++;
                }
                else if (j < 89)//Lower row
                {
                    if (grid[i][j-1] == 1) count++;
                    if (grid[i][j+1] == 1) count++;
                    if (grid[i-1][j+1] == 1) count++;
                    if (grid[i-1][j-1] == 1) count++;
                    if (grid[i-1][j] == 1) count++;
                }
                else if (j == 89)//Last square
                {
                    if (grid[i-1][j] == 1) count++;
                    if (grid[i][j-1] == 1) count++;
                    if (grid[i-1][j-1] == 1) count++;
                }


            }


            if (j== 0)//First column
            {
                if( i>0 && i<89 )//Left column
                {
                    if (grid[i+1][j] == 1) count++;
                    if (grid[i-1][j] == 1) count++;
                    if (grid[i][j+1] == 1) count++;
                    if (grid[i+1][j+1] == 1) count++;
                    if (grid[i-1][j+1] == 1) count++;
                }
            }


            if (j == 89)//Last column
            {
                if( i>0 && i<89 )//Right column
                {
                    if (grid[i+1][j] == 1) count++;
                    if (grid[i-1][j] == 1) count++;
                    if (grid[i][j-1] == 1) count++;
                    if (grid[i+1][j-1] == 1) count++;
                    if (grid[i-1][j-1] == 1) count++;
                }
            }


            if ( (i >0) && (i < 89) && (j>0) && (j<89)) //It's in the middle, verify all
            {
                if (grid[i-1][j-1] == 1) count++;
                if (grid[i-1][j] == 1) count++;
                if (grid[i-1][j+1] == 1) count++;
                if (grid[i][j+1] == 1) count++;
                if (grid[i][j-1] == 1) count++;
                if (grid[i+1][j+1] == 1) count++;
                if (grid[i+1][j-1] == 1) count++;
                if (grid[i+1][j] == 1) count++;

            }

            if (grid[i][j] == 1) //Alive
            {
                if (count <2 || count >3) sgrid[i][j] =0;
                if (count == 3 || count==2) sgrid[i][j]=1;
            } else{ //Dead
                if (count == 3) sgrid[i][j] = 1;
            }

        }

    std::copy(&sgrid[0][0], &sgrid[0][0]+90*90, &grid[0][0]);
}


















