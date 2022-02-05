//"bloons" style game, part 2
//coded by Dr. Mo, Feb 2022
//dynamicsofanasteroid.com

// in this part, we add class "bloon" and instantiate a bunch of bloons for the game.

#include <SFML/Graphics.hpp>
#include <vector>
#include<iostream>
using namespace std;

//note: because class bloon uses this struct, you need to have this *above* the class def in the code!
struct point {
    int x;
    int y;
};


class bloon {
private:
    int xpos;
    int ypos;
    int currPath;
public:
    bloon(int x, int y);
    void move(vector<point>myPath);
    void draw(sf::RenderWindow& window);
};


int main()//start of main=============================================================================
{
    //set up path points using the struct we made
    struct point p1;
    p1.x = 100;
    p1.y = 400;
    struct point p2;
    p2.x = 200;
    p2.y = 200;
    struct point p3;
    p3.x = 800;
    p3.y = 400;


    //set up vector to hold path points, push path points into it
    vector <point> pathPoints;
    pathPoints.push_back(p1);
    pathPoints.push_back(p2);
    pathPoints.push_back(p3);


    // create game window
    sf::RenderWindow window(sf::VideoMode(800, 800), "bloons");

    //game variables
    int ticker = 0;

    bloon b1(-50, 400);
    //instantiate more here

    // GAME LOOP----------------------------------------------------------------------------------------
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ticker++; //slow dem bloons down
        if (ticker % 30 == 0) { //make 30 bigger to slow down baloon more

            b1.move(pathPoints);
            //move more here
        }

        // Render section----------------------------------------------------------------
        window.clear(sf::Color::Black);
        b1.draw(window);
        //draw more here
        window.display();
    }

    return 0;//buh bye
}//end of main===========================================================================================

//class function definitions=============================================================================

bloon::bloon(int x, int y){
    xpos = x;
    ypos = y;
    currPath = 0;
}


//note for part 2: I called my vector by a different name here to show this could work with any vector of points
void bloon::move(vector<point>myPath ){
    if ((xpos == myPath[currPath].x) && (ypos == myPath[currPath].y))
        if (currPath < myPath.size() - 1) //don't walk off end of vector!
            currPath++; //iterate to next point

    //if not there yet, move our x towards x position of next junction
    if (xpos < myPath[currPath].x)
        xpos += 1;
    if (xpos > myPath[currPath].x)
        xpos -= 1;
    //and move our y towards y position of next junction
    if (ypos < myPath[currPath].y)
        ypos += 1;
    if (ypos > myPath[currPath].y)
        ypos -= 1;

}


void bloon::draw(sf::RenderWindow& window){ //passes a POINTER to the gamescreen
    sf::CircleShape baloon(25);
    baloon.setFillColor(sf::Color(250, 0, 0));
    baloon.setPosition(xpos, ypos);
    window.draw(baloon);//draw to gamescreen
}
