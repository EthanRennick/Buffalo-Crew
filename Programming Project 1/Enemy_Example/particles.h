#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include <SFML/Audio/SoundBuffer.hpp>
#include<SFML/Audio/Sound.hpp>

//particles
class Particle
{
public:
	sf::RectangleShape shape; //body
	sf::Vector2f velocity; //speed
	int framesToLive; //time on screen


};

//system
class ParticleSystem
{
public:
	static const int numParticles = 20; //amount of particles to make
	Particle particles[numParticles]; //declare array of particles
	float maxSpeed = 6; //speed maximum
	sf::Vector2f center; //center of the particles


	ParticleSystem()
	{
		srand(static_cast<unsigned int>(time(nullptr)));
	}
	void Initialise(sf::Vector2f position) //initialise all the particles
	{
		center = position; //set center
		//for loop to initialise all the particles

		for (int i = 0; i < numParticles; i++)
		{
			particles[i].shape.setSize(sf::Vector2f{ 10.0f,10.0f }); //set size
			particles[i].shape.setPosition(center); //set centre
			particles[i].shape.setFillColor(sf::Color(static_cast<unsigned int>(rand() % 255 + 1), static_cast<unsigned int>(rand() % 255 + 1), static_cast<unsigned int>(rand() % 255 + 1))); //random colors
			particles[i].velocity.x = rand() / double(RAND_MAX) * maxSpeed * 2 - maxSpeed; //random velocity
			particles[i].velocity.y = rand() / double(RAND_MAX) * maxSpeed * 2 - maxSpeed; //rand velocity
			particles[i].framesToLive = rand() % 40 + 2; //time on screen
			
		}


	}
	void Update()
	{
		//for loop to move all the particles
		for (int i = 0; i < numParticles; i++)
		{
			if (particles[i].framesToLive > 0) //if they're alive, move them
			{
				particles[i].shape.move(particles[i].velocity);

			}

		}
	}
	void Draw(sf::RenderWindow &window) //draw to screen
	{
		//for loop to draw all the particles
		for (int i = 0; i < numParticles; i++)
		{
			if (particles[i].framesToLive > 0) //only draw if alive
			{
				window.draw(particles[i].shape); //draw
				particles[i].framesToLive--; //life goes down
			}

		}
	}
};