#pragma once
// enemy ship class declaration
#include "Player.h"
#include "Bullets.h"
#include "SFML/Graphics.hpp" 
#include "Globals.h"   // include Global header file
#include <iostream>
#include "particles.h"

//enemy with vertical movement only
class EnemyShip 
{
public:
	sf::Sprite enemySprite; //enemy sprite
	sf::Texture enemyShipTexture; //enemy texture for sprite
	int enemyshipSpeed; //enemy speed

public: ParticleSystem explosionEnemy; //enemy particle system
public:	  // declaration of member functions	

	EnemyShip(); //constructor
	void enemyloadImage(); //load images
	sf::Sprite enemygetBody(); //find enemy sprite
	void enemysetPosition(); //set his position
	void enemygoDown(PlayerShip &t_myPlayer); //down movement
	void enemyCollision(PlayerShip &t_myPlayer); //collision with player
	void bulletCollision(Bullet &t_bullet, PlayerShip &t_player); //collision with player's bullets
	void resetEnemy(); //reset when player dies and plays again

};