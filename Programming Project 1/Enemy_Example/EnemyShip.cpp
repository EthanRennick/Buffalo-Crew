#include "Enemy Ship.h"
#include "Bullets.h"
#include"Player.h"


//default constructor
EnemyShip::EnemyShip() 
{
	//setup base of enemy ship
	enemyloadImage();
	enemysetPosition();
	enemyshipSpeed = 8; //speed
	enemySprite.setOrigin(60, 20); //origin of the sprite
}

//load enemy image
void EnemyShip::enemyloadImage()
{
	if (!enemyShipTexture.loadFromFile("Assets/Images/enemyDefault.png")) //load
	{
		std::cout << "error with enemy default image file"; //error
	}
	enemySprite.setTexture(enemyShipTexture); //set sprite to enemy texture
}

//get me the enemy's sprite
sf::Sprite EnemyShip::enemygetBody()
{
	return enemySprite;
}

//set the enemy's position
void EnemyShip::enemysetPosition()
{
	enemySprite.setPosition(rand() % 900 + 100 , -100); 
}

//enemy movement
void EnemyShip::enemygoDown(PlayerShip &t_myPlayer)
{
		enemySprite.move(0, enemyshipSpeed); //always move down

		if (enemySprite.getPosition().y > SCREEN_HEIGHT - 10) //if he goes off screen
		{
			enemySprite.setPosition(rand() % 700 + 150 , -200); //reset to this random position north of map
			t_myPlayer.score += 4; //player's score increases for dodging the enemy
		}
}

//enemy collision with player
void EnemyShip::enemyCollision(PlayerShip &t_myPlayer) //
{
	if (t_myPlayer.bodySprite.getGlobalBounds().intersects(enemySprite.getGlobalBounds())) //if they touch
	{
		explosionEnemy.Initialise(sf::Vector2f{ enemygetBody().getPosition() });  //explosion initialises
		enemySprite.setPosition(rand() % 700 + 150, -200); //enemy position resets
		t_myPlayer.playerExplosion.Initialise(sf::Vector2f{ t_myPlayer.getBody().getPosition() }); //the player also explodes
		if (t_myPlayer.shields < 0) //if shields is zero, basically ignore
		{
			t_myPlayer.shields = 0;
		}

		if (t_myPlayer.shields > 0) //if he has shields, damage the shields
		{
			t_myPlayer.shields--;
		}
		else //if no shields, hit the hull
		{
			t_myPlayer.hull--;
		}

		//if hull is less than 50, player's bullets are reduced
		if (t_myPlayer.hull <= 50)
		{
			t_myPlayer.numOfBullets = 3;
		}//if less than 75, player's spped is reduced
		else if (t_myPlayer.hull <= 75)
		{
			t_myPlayer.shipSpeed = 10;
		}
	}
}

//enemy collision with bullets
void EnemyShip::bulletCollision(Bullet &t_bullet, PlayerShip &t_player)
{
	for (int i = 0; i < MAX_BULLETS; i++) //check each bullet
	{
		if (t_bullet.bulletsScreen[i].getGlobalBounds().intersects(enemySprite.getGlobalBounds())) //if any bullets touch enemy
		{
			t_bullet.bulletsScreen[i].setPosition(-2000, -2000); //reset bullets
			explosionEnemy.Initialise(sf::Vector2f{enemygetBody().getPosition()}); //explosion occurs
			enemySprite.setPosition(rand() % 700 + 150, -200); //enemy position resets
			t_player.score += 10; //player's score goes up
			t_player.killCounter += 1; //one kill

		}
	}
}

//reset enemy when player dies
void EnemyShip::resetEnemy()
{
	enemysetPosition();
	enemyshipSpeed = 8;
}
