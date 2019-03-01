// Game class declaration
#pragma once

#include "Player.h"   // include Player header file
#include "particles.h"
#include "Enemy Ship.h"
#include "EnemyTwo.h"
#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function
#include"Bullets.h"
#include "HealthPackage.h"

#include "Globals.h"   // include Global header file
#include <SFML/Audio/SoundBuffer.hpp>
#include<SFML/Audio/Sound.hpp>

class Game
{
	// data members
	PlayerShip myPlayer;  // creates an object of type Player using the default constructor
	EnemyShip myEnemy; //one enemy object
	EnemyShipTwo enemyTwo[MAX_ENEMY]; //array of followers
	sf::RenderWindow window;  // main game window
	Bullet bullets; //bullet class for player
	healthPackage healthBox; //health crate


public:
	sf::Font m_font;  // font for writing text
	sf::Text m_message;  // text to write on the screen
	sf::SoundBuffer explosionBuffer; //explosion buffer
	sf::Sound explodeSound; //explosion sound
	sf::Sprite backgroundSprite; //background texture + sprite
	sf::Texture backgroundTexture;
	sf::Sprite menuSprite; //menu texture + sprite
	sf::Texture menuTexture;
	sf::SoundBuffer musicBuffer; //music
	sf::Sound musicSound; //music sounds

public:	  // declaration of function members
	Game();  //  default constructor function
	void	loadContent();
	void	run();

private:
	void update();  // handles input in the game
	void draw();  // draws/renders the game world
};



