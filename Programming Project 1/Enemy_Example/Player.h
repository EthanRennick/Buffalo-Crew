// Player class declaration
#pragma once


#include "SFML/Graphics.hpp" 
#include "Globals.h"   // include Global header file
#include <iostream>
#include "particles.h"
#include "healthPackage.h"

//player class -> you play as this
class PlayerShip
{
public:
	sf::Sprite bodySprite; //player sprite
	sf::Texture spaceShipTexture; //player texture
	int shields; //player's shields - damage this before hull
	int score; //player's score - increase by killing / dodging ships
	int shipSpeed; //speed you travel at
	int numOfBullets; //amount of bullets you have
	int hull; //strength of your hull - keep above 0 to survive
	int killCounter; //enemies you kill
	sf::Vector2f playerPosition; //your position

	//look direction - used with regards to bullets
	sf::Vector2f playerVelocity{ 0,0 };
	sf::Vector2f playerVelocityTwo{ 0,0 };
	sf::Vector2f playerLookDirection{ 0,-1 };
	sf::Vector2f playerLookDirectionTwo{ 0,-1 };

	bool playerAlive = false; //is player alive?
	bool reset = false; //has or hasnt reset game
	bool displayMessage = false; //if dead - display 'restart?'
	bool menu = true;

	//various checkpoints at every thousand up to 6000 - increases enemy speed
	bool checkpoint1 = false;
	bool checkpoint2 = false;
	bool checkpoint3 = false;
	bool checkpoint4 = false;
	bool checkpoint5 = false;
	bool checkpoint6 = false;

public:	  // declaration of member functions
	ParticleSystem playerExplosion; //player explosion
	PlayerShip(); //constructor
	void loadImage(); //load images
	sf::Sprite getBody(); //get player sprite
	void setPosition(); //set position
	sf::Vector2f getPlayerPosition(); //get the player position
	void resetVelocity(); //reset his velocity - used with guns
	void goLeft(); //various movements
	void goRight();
	void moveUp();
	void moveDown();
	void collision(healthPackage &t_healthBox); //collision with healthcrate
	void resetPlayer(); //reset him if he dies
};
