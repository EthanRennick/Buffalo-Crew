#include "HealthPackage.h"

//health package
healthPackage::healthPackage()
{
	speed = 2; //speed
	loadImage(); //load image
	setPosition(); //set position
}

//load his files
void healthPackage::loadImage()
{

	if (!healthTexture.loadFromFile("Assets/Images/lifesaver.png")) //load
	{
		std::cout << "error with player image file"; //error
	}
	healthSprite.setTexture(healthTexture);//set sprite to texture
}

//return sprite body
sf::Sprite healthPackage::getBody()
{
	return sf::Sprite();
}

//set his position
void healthPackage::setPosition()
{
	healthSprite.setPosition(rand() % 900 + 50, -100); //random point above screen
}

//move down always
void healthPackage::moveDown()
{
	healthSprite.move(0, speed); //move down
	if (healthSprite.getPosition().y > SCREEN_HEIGHT - 10) //if offscreen, respawn
	{
		healthSprite.setPosition(rand() % 900 + 50, -1000); //random point above screen
	}
}


