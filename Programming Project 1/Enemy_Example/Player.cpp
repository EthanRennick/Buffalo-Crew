// Player class

#include "Player.h"   // include Player header file



// Definition of member functions of the Player class

PlayerShip::PlayerShip() //Default constructor
{
	loadImage(); //load player image
	setPosition(); //set player position
	shields = 100; //starting shield
	shipSpeed = 14; //starting pseed
	numOfBullets = 5; //amount of bullets
	score = 0; //initial score
	hull = 100; //initial hull
	bodySprite.setOrigin(50, 50); //origin of sprite
	killCounter = 0; //kills you have
}

//load images to player
void PlayerShip::loadImage()
{
	if (!spaceShipTexture.loadFromFile("Assets/Images/player.png")) //load
	{
		std::cout << "error with player image file"; //error
	}
	bodySprite.setTexture(spaceShipTexture); //set texture to sprite
}

//return player sprite 
sf::Sprite PlayerShip::getBody()
{
	return bodySprite;
}

//set player's position to bottom of screen
void PlayerShip::setPosition()
{
	bodySprite.setPosition(475, 700);
}

//get the player's position on screen
sf::Vector2f PlayerShip::getPlayerPosition()
{
	playerPosition = bodySprite.getPosition(); //position is the position of sprite
	return playerPosition;
}

//reset his velocity to 0,0   -> for gun
void PlayerShip::resetVelocity()
{
	playerVelocity.x = 0;
	playerVelocity.y = 0;
}

//player's go left movement
void PlayerShip::goLeft()
{
	playerVelocity.x = -5; //move this way
	if (playerVelocity.x != 0 || playerVelocity.y != 0)
	{
		playerLookDirection = playerVelocity; //look direction is the velocity (way he's looking)
	}
	bodySprite.move(-shipSpeed, 0); //move his sprite
	//screen wrap
	if (bodySprite.getPosition().x < 0) ///if his x is less than 0
	{
		bodySprite.setPosition(SCREEN_WIDTH - bodySprite.getGlobalBounds().width, bodySprite.getPosition().y); //go to right side of screen
	}
}

//go right movement     same as code before
void PlayerShip::goRight()
{
	playerVelocity.x = 5;
	if (playerVelocity.x != 0 || playerVelocity.y != 0)
	{
		playerLookDirection = playerVelocity;
	}
	
	bodySprite.move(shipSpeed, 0);
	//screen wrap
	if (bodySprite.getPosition().x > SCREEN_WIDTH - bodySprite.getGlobalBounds().width + 50) //if he goes right
	{
		bodySprite.setPosition(0, bodySprite.getPosition().y); //appear on the left
	}
	
}

//upwards movement - same as before
void PlayerShip::moveUp()
{
	playerVelocity.y = -5;
	if (playerVelocity.x != 0 || playerVelocity.y != 0)
	{
		playerLookDirection = playerVelocity;
	}
	bodySprite.move(0, -shipSpeed);
	if (bodySprite.getPosition().y < 0) //if y < 0
	{
		bodySprite.setPosition(bodySprite.getPosition().x, SCREEN_HEIGHT - bodySprite.getGlobalBounds().height); //appear on bottom
	}
}

//downward movement
void PlayerShip::moveDown()
{
	playerVelocity.y = 5;
	if (playerVelocity.x != 0 || playerVelocity.y != 0)
	{
		playerLookDirection = playerVelocity;
	}
	bodySprite.move(0, +shipSpeed);
	if (bodySprite.getPosition().y > SCREEN_HEIGHT - bodySprite.getGlobalBounds().height + 50) //if go too low
	{
		bodySprite.setPosition(bodySprite.getPosition().x, 0); //appear on top
	}
}

//collision with health
void PlayerShip::collision(healthPackage &t_healthBox) 
{
	if (bodySprite.getGlobalBounds().intersects(t_healthBox.healthSprite.getGlobalBounds())) //if they touch
	{
		shields += 60; //shields go up 
		t_healthBox.healthSprite.setPosition(rand() % 500 + 100, -4000); //respawn health box
	}
}

//reset player if he dies
void PlayerShip::resetPlayer()
{
	//reset all
	setPosition();
	shields = 100;
	shipSpeed = 14;
	numOfBullets = 5;
	score = 0;
	hull = 100;
	killCounter = 0;
}


