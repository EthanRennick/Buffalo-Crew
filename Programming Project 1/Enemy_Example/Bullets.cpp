#include "Bullets.h"

#include"Player.h"
#include"Enemy Ship.h"
#include"EnemyTwo.h"

//represents several bullets
Bullet::Bullet()
{
	for (int i = 0; i < MAX_BULLETS; i++) //initialise bullets
	{
		bulletsScreen[i].setSize(sf::Vector2f(10, 10)); //size
		bulletsScreen[i].setPosition(-2000, -2000); //positions
		bulletsScreen[i].setFillColor(sf::Color::Yellow); //color
	}
	for (int i = 0; i < MAX_BULLETS; i++) //setup bullet velocities
	{
		bulletVelocities[i].x = 0;
		bulletVelocities[i].y = 0;
	}
	onScreenArea.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT)); //set the screen size of rectangle
	fireBuffer.loadFromFile("fire.wav"); //load
	fireSound.setBuffer(fireBuffer); //setup
}

void Bullet::shooting(PlayerShip &y_myPlayer) //if player shoots
{

	for (int i = 0; i < y_myPlayer.numOfBullets; i++) //for loop to check each bullet
	{
		if (bulletsScreen[i].getPosition().x != -2000) //if bullet is not at !2000
		{
			bulletsScreen[i].move(bulletVelocities[i]); //the bullets are on screen, so move them
			if (onScreenArea.getGlobalBounds().intersects(bulletsScreen[i].getGlobalBounds()) == 0) //if they go off the screen
			{
				bulletsScreen[i].setPosition(-2000, -2000); //go to -2000
				bulletVelocities[i].x = 0; //no more velocity
				bulletVelocities[i].y = 0;
			}
		}
	}
	if (readyToFire == true) //if bullets are ready to fire
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //if player presses space bar
		{
			for (int i = 0; i < y_myPlayer.numOfBullets; i++) //check each bullet
			{
				if (bulletsScreen[i].getPosition().x == -2000) //if bullet is at -2000
				{
					bulletsScreen[i].setPosition(y_myPlayer.bodySprite.getPosition()); //move bullet to the player
					bulletVelocities[i] = y_myPlayer.playerLookDirection; //bullet gets the direction of the player
					fireSound.play();
					
					//when the player shoots a bullet
					bulletVelocities[i].x *= 2; //increase velocity
					bulletVelocities[i].y *= 2;
					readyToFire = false; //cannot fire
					waitToFireCounter = 10; //wait ten clicks
					break; //leave for loop
				}

			}
		}
	}
	else {
		waitToFireCounter--; //decrease wait to fire
		if (waitToFireCounter <= 0) //if 0, then allow to fire again
		{
			readyToFire = true;
		}
	}
}

