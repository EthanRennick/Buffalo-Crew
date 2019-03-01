
#pragma once
// health package class declaration

#include "SFML/Graphics.hpp" 
#include "Globals.h"   // include Global header file
#include <iostream>

class healthPackage
{
public:
	sf::Sprite healthSprite; //health sprite
	sf::Texture healthTexture; //health texture
	int speed; //speed of floating crate


public:
	healthPackage(); //default construct
	void loadImage(); //get images
	sf::Sprite getBody(); //get sprite body
	void setPosition(); //get position
	void moveDown(); //repeated vertical movement
};