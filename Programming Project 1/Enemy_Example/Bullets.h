#pragma once

#include "SFML/Graphics.hpp" 
#include "Globals.h"   // include Global header file
#include <iostream>
#include "Player.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include<SFML/Audio/Sound.hpp>


//inappropriately named - should be plural as it represents several 'bullets'
class Bullet
{
public:
	sf::RectangleShape bulletsScreen[MAX_BULLETS]; //bullets that are displayed to screen
	sf::Vector2f bulletVelocities[MAX_BULLETS]; //bullet velocity - speed they move at
	sf::RectangleShape onScreenArea; //area of the screen
	int waitToFireCounter = 40; //time between bullets
	bool readyToFire = true; //bool to control bursts
	sf::SoundBuffer fireBuffer; //fire buffer
	sf::Sound fireSound; //fire sound

public:	Bullet();

	void shooting(PlayerShip &y_myPlayer); //the player shoots function
};