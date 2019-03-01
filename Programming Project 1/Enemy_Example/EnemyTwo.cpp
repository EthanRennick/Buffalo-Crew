#include "EnemyTwo.h"
#include "Bullets.h"
#include "Player.h"



//enemy two, follower
EnemyShipTwo::EnemyShipTwo()
{
	//default constructor
	enemyloadImageTwo();
	enemysetPositionTwo();
	enemyshipSpeedTwo = 3; //speed
	enemySpriteTwo.setOrigin(55, 100); //origin of sprite
}

//load images
void EnemyShipTwo::enemyloadImageTwo()
{
	if (!enemyShipTextureTwo.loadFromFile("Assets/Images/enemyFollower.png")) //load
	{
		std::cout << "error with player image file"; //error
	}
	enemySpriteTwo.setTexture(enemyShipTextureTwo); //set sprite to texture
}

//return follower sprite
sf::Sprite EnemyShipTwo::enemygetBodyTwo()
{
	return enemySpriteTwo;
}

//set his initial position
void EnemyShipTwo::enemysetPositionTwo()
{
	enemySpriteTwo.setPosition(rand() % 1000 + 100, -300); //position above screen
	
}

//enemy movement
void EnemyShipTwo::enemygoDownTwo(PlayerShip &t_myPlayer)
{
	sf::Vector2f distance = t_myPlayer.getPlayerPosition() - enemySpriteTwo.getPosition(); //get the distance between the two sprites (follower - player)
	float magnitudeOfDistance = sqrt(distance.x * distance.x + distance.y * distance.y); //magnitude of distance 
	sf::Vector2f moveDirection = distance / magnitudeOfDistance; //move the follower in the direction of player

	if (magnitudeOfDistance > 90) //if more than 90 away, move to player
	{
		enemySpriteTwo.move(moveDirection * static_cast<float>(enemyshipSpeedTwo));
	}

	if (enemySpriteTwo.getPosition().y > SCREEN_HEIGHT - 10) //if he goes off bottom of screen, reset
	{
		enemySpriteTwo.setPosition(rand() % 700 + 150, -200);
	}
}

//follower collisions
void EnemyShipTwo::collision(PlayerShip &t_myPlayer)
{
	if (t_myPlayer.bodySprite.getGlobalBounds().intersects(enemySpriteTwo.getGlobalBounds())) //if they touch
	{
		explosionEnemyTwo.Initialise(sf::Vector2f{ enemySpriteTwo.getPosition() }); //explode
		enemySpriteTwo.setPosition(rand() % 700 + 150, -200);		//position reset


		if (t_myPlayer.shields < 0) //ignore shields if at 0
		{
			t_myPlayer.shields = 0;
		}

		if (t_myPlayer.shields > 0) //if he has shields, hurt them
		{
			t_myPlayer.shields -= 10;
			
		}
		else //if he has no shields, hit the hull
		{
			t_myPlayer.hull-=10;
			if (t_myPlayer.shields < 0) //if shield damaged below 0, it is 0
			{
				t_myPlayer.shields == 0;
			}
		}

	}
}

//contact with bullets
void EnemyShipTwo::bulletCollision(Bullet & t_bullet, PlayerShip & t_player)
{
	for (int i = 0; i < MAX_BULLETS; i++) //check each bullet
	{
		if (t_bullet.bulletsScreen[i].getGlobalBounds().intersects(enemySpriteTwo.getGlobalBounds())) //if they touch
		{
			t_bullet.bulletsScreen[i].setPosition(-2000, -2000); //reset position of bullet
			explosionEnemyTwo.Initialise(sf::Vector2f{ enemygetBodyTwo().getPosition() }); //explosion
			enemySpriteTwo.setPosition(rand() % 700 + 150, -200); //enemy position reset
			t_player.score += 20; //score
			t_player.killCounter += 1; //kill + 1
		}
	}
}

//reset if player restarts
void EnemyShipTwo::resetEnemyTwo()
{
	enemysetPositionTwo();
	enemyshipSpeedTwo = 3;
}