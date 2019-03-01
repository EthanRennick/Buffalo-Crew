// Name: Ethan Rennick
// Login: C00240102
// Date: 20/1/2019
// Approx hours of work : 26
//---------------------------------------------------------------------------
// This is my game created for Bernadette's Project 1
// It's a game where you play as a space ship, blowing up or dodging
// other space ships. Score is kept, damage is tracked, kills are counted
// and when you die, you have the option to restart
//
// ---------------------------------------------------------------------------
// Known Bugs:
// 

//////////////////////////////////////////////////////////// 
// include correct library file for release and debug versions
//////////////////////////////////////////////////////////// 

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "Game.h"   // include Game header file

int main()
{
	Game myGame; //run game
	myGame.loadContent();
	myGame.run();
	return 0;
}

Game::Game() :window(sf::VideoMode(static_cast<int>(SCREEN_WIDTH), static_cast<int>(SCREEN_HEIGHT)), "The Buffalo Crew", sf::Style::Default) //window
//  default constructor function
{
	if (!backgroundTexture.loadFromFile("ASSETS/IMAGES/Space-PNG-Pic.png")) //load background
	{
		std::cout << "error with background texture file"; //error
	}
	backgroundSprite.setTexture(backgroundTexture); //set sprite to tecture
	backgroundSprite.setPosition(0, 0); //set position

	if (!menuTexture.loadFromFile("ASSETS/IMAGES/bamquet.png")) //load menu
	{
		std::cout << "error with menu texture file"; //error
	}
	menuSprite.setTexture(menuTexture); //set sprite to texture
	menuSprite.setScale(2, 2);
	menuSprite.setPosition(230, 200); //set position

	musicBuffer.loadFromFile("music.ogg"); //load game music
	musicSound.setBuffer(musicBuffer); //setup
	//musicSound.play(); //play upon setup
	explosionBuffer.loadFromFile("explosion.wav"); //load explosions
	explodeSound.setBuffer(explosionBuffer);//setup
}


void Game::loadContent()
// load the font file & set the message string
{
	if (!m_font.loadFromFile("ASSETS/FONTS/BebasNeue.otf")) //load font
	{
		std::cout << "error with font file file"; //error
	}

	// set up the message string 
	m_message.setFont(m_font);  // set the font for the text
	m_message.setCharacterSize(24); // set the text size
	m_message.setFillColor(sf::Color::White); // set the text colour
	m_message.setPosition(10, 10);  // its position on the screen

}


void Game::run()
//This function is the most important function in the project. 
// This function contains the main game loop which controls the game. 
{
	srand(time(nullptr)); // set the seed once

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;


	clock.restart();

	while (window.isOpen())
	{
		// check if the close window button is clicked on
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.
		if (timeSinceLastUpdate > timePerFrame)
		{
			update();
			draw();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}  // end while loop

} // end main

void Game::update()
// handles input in the game
{
	if (myPlayer.menu == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) //if enter is pressed
		{
			myPlayer.displayMessage = false; //dont display 'reset'
			myPlayer.playerAlive = true; //the player is alive
			myPlayer.menu = false; //turn menu off
			enemyTwo->resetEnemyTwo(); //reset follower
			myEnemy.resetEnemy(); //reset enemy
			myPlayer.resetPlayer(); //reset player
		}
	}
	// checks what  keys have been pressed  
	if (myPlayer.menu == false)
	{
		//left ward movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			myPlayer.goLeft(); //go left
			myPlayer.bodySprite.setRotation(-90); //rotate left

		}//right ward movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			myPlayer.goRight(); //go right
			myPlayer.bodySprite.setRotation(90); //rotate right
		}
		//upward movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			myPlayer.moveUp(); //move north
			myPlayer.bodySprite.setRotation(0); //look ahead

		}//south movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			myPlayer.moveDown(); //move south
			myPlayer.bodySprite.setRotation(-180); //look down
		}

		//ONLY RUN WHEN PLAYER IS ALIVE
		if (myPlayer.displayMessage == false)
		{
			//enemy movement
			myEnemy.enemygoDown(myPlayer); //pass myPlayer as an arguement 
			for (int i = 0; i < MAX_ENEMY; i++) //look at both enemies
			{
				enemyTwo[i].enemygoDownTwo(myPlayer); //both enemies should follow player
			}

			//enemy collisions
			myEnemy.enemyCollision(myPlayer);
			for (int i = 0; i < MAX_ENEMY; i++) //check both enemies
			{
				enemyTwo[i].collision(myPlayer); //both collide with player
			}

			//particles Update
			myPlayer.playerExplosion.Update(); //update player particles
			for (int i = 0; i < MAX_ENEMY; i++)
			{
				enemyTwo[i].explosionEnemyTwo.Update(); //both follower particles
			}
			myEnemy.explosionEnemy.Update(); //enemy particles

			//bullets and their collisions
			bullets.shooting(myPlayer); //player's shooting function
			myEnemy.bulletCollision(bullets, myPlayer); //if they hit the enemy
			for (int i = 0; i < MAX_ENEMY; i++)
			{
				enemyTwo[i].bulletCollision(bullets, myPlayer); //if they hit any followers
			}

			//player direction - linked to gun
			myPlayer.resetVelocity(); //reset velocity

			//health
			healthBox.moveDown(); //box movement
			myPlayer.collision(healthBox); //player hitting the box
		}

		//do this all the time

			//if player is alive, check if he dies
		if (myPlayer.playerAlive == true)
		{
			if (myPlayer.hull < 1) //if hull is less than 1, the ship is dead
			{
				myPlayer.displayMessage = true; //display 'reset'
				myPlayer.playerAlive = false; //he's dead
			}
		} //if player is dead, display dead message
		
		if (myPlayer.playerAlive == false)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) //if enter is pressed
			{
				myPlayer.displayMessage = false; //dont display 'reset'
				myPlayer.playerAlive = true; //the player is alive
				enemyTwo->resetEnemyTwo(); //reset follower
				myEnemy.resetEnemy(); //reset enemy
				myPlayer.resetPlayer(); //reset player
			}
		} //score over 1000
		if (myPlayer.checkpoint1 == false) //checkpoint 1
		{
			if (myPlayer.score > 1000)
			{
				//speed increase
				enemyTwo->enemyshipSpeedTwo += 1;
				myEnemy.enemyshipSpeed += 1;
				myPlayer.checkpoint1 = true;
			}
		} //score over 2000
		if (myPlayer.checkpoint2 == false)
		{
			if (myPlayer.score > 2000)
			{
				//speed increase
				enemyTwo->enemyshipSpeedTwo += 1;
				myEnemy.enemyshipSpeed += 1;
				myPlayer.checkpoint2 = true;
			}
		} //score over 3000
		if (myPlayer.checkpoint3 == false)
		{
			if (myPlayer.score > 3000)
			{
				//speed increase
				enemyTwo->enemyshipSpeedTwo += 1;
				myEnemy.enemyshipSpeed += 1;
				myPlayer.checkpoint3 = true;
			}
		}
		if (myPlayer.checkpoint4 == false)
		{
			if (myPlayer.score > 4000)
			{
				//speed increase
				enemyTwo->enemyshipSpeedTwo += 1;
				myEnemy.enemyshipSpeed += 1;
				myPlayer.checkpoint4 = true;
			}
		}
		if (myPlayer.checkpoint5 == false)
		{
			if (myPlayer.score > 5000)
			{
				//speed increase
				enemyTwo->enemyshipSpeedTwo += 1;
				myEnemy.enemyshipSpeed += 1;
				myPlayer.checkpoint5 = true;
			}
		}
	}
}

void Game::draw()
// draws/renders the game world
{
	window.clear(); // clear the screen 
	if (myPlayer.playerAlive == true) //if the player is alive, display his stats
	{
		window.draw(backgroundSprite); //draw background
		m_message.setString("Score: " + std::to_string(myPlayer.score) + "\n" + "Shields: " + std::to_string(myPlayer.shields) 
		+ "\n" + "Hull: " + std::to_string(myPlayer.hull) + "\n" + "Shot Down: " + std::to_string(myPlayer.killCounter)); //stats
		window.draw(m_message);  // write the message on the screen
	}
	if (myPlayer.displayMessage == true) //if he's dead, display the 'reset' screen
	{
		m_message.setString("\n \n \n \n \n \n \n \n \n \n \n                                                                                   	You have lost. Press Enter to restart. \n \n \n \n"); //you've lost
		window.draw(m_message);  // write the message on the screen
		m_message.setString("\n \n \n \n \n \n \n \n \n \n \n \n \n \n                                                                                                                     Score: " + std::to_string(myPlayer.score)); //display score
		window.draw(m_message);  // write the message on the screen
		m_message.setString("\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n                                                                                                          Enemies Destroyed: " + std::to_string(myPlayer.killCounter)); //display kills
		window.draw(m_message);  // write the message on the screen
	}
	if (myPlayer.menu == true) //if the menu is up
	{
		window.draw(menuSprite); //display menu
		m_message.setString("\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n                                                 	Welcome, Captain of the Buffalo crew. Press Enter to begin the battle. \n \n \n \n"); //welcome
		window.draw(m_message);  // write the message on the screen
	}
	if (myPlayer.playerAlive == true) //if he's alive
	{
		window.draw(myPlayer.getBody());  // draw the player object
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			window.draw(bullets.bulletsScreen[i]); //draw all bullets
		}
	}
	window.draw(myEnemy.enemygetBody()); //draw the basic enemy
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		window.draw(enemyTwo[i].enemygetBodyTwo()); //draw both followers
	}
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		enemyTwo[i].explosionEnemyTwo.Draw(window); //draw both follower explosions
	}
	myEnemy.explosionEnemy.Draw(window); //draw enemy explosion
	myPlayer.playerExplosion.Draw(window); //draw player explosion
	window.draw(healthBox.healthSprite); //draw health box
	window.display(); //display all
}



