#pragma once
#include "Player.h"
// enemy ship class declaration
#include "Bullets.h"
#include "SFML/Graphics.hpp" 
#include "Globals.h"   // include Global header file
#include"particles.h"
#include <iostream>

//the follower enemy
class EnemyShipTwo
{
public:
	sf::Sprite enemySpriteTwo; //enemy two sprite
	sf::Texture enemyShipTextureTwo;	//texture
	int enemyshipSpeedTwo; //speed he moves at

public: ParticleSystem explosionEnemyTwo; //follower explosion particles

public:	  // declaration of member functions	

	EnemyShipTwo(); //constructor
	void enemyloadImageTwo(); //images
	sf::Sprite enemygetBodyTwo(); //get sprite
	void enemysetPositionTwo(); //set his position
	void enemygoDownTwo(PlayerShip &t_myPlayer); //enemy movement to follow player
	void collision(PlayerShip &t_myPlayer); //collision with player
	void bulletCollision(Bullet &t_bullet, PlayerShip &t_player); //collision with bullets
	void resetEnemyTwo(); //reset when player restarts


};