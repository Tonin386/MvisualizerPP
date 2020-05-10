#include "particle.hpp"
#include "particlecluster.hpp"
#include "note.hpp"

#include "../constants.hpp"

#include <random>
#include <cmath>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>

using namespace sf;
using namespace std;

ParticleCluster::ParticleCluster(Note* parentNote, int protocol, Color color) : _parentNote(parentNote), _protocol(protocol), _color(color)
{
	//Need to figure out how to create the particles of a cluster

	extern Clock PROCESS_TIME;

	default_random_engine gen;
	int n = 0;

	parentNote->setChild(this);

	switch(_protocol)
	{
		case 0: //Not full circle
		{
			n = _parentNote->getVelocity() / 3;
			break;
		}

		case 1: //Full circle
		{
			n = 36;
			break;
		}

		case 2:
		{
			n = _parentNote->getVelocity() / 3;
			break;
		}

		case 3:
		{
			n = _parentNote->getVelocity() / 3;
			_origin.x = ((int)(_parentNote->getTimeOn()*1511453)) % WIDTH;
			break;
		}

		default:
		{
			n = 7;
			break;
		}
	}

	for(int i = 0; i < n; i++)
	{
		double deg = 0;
		double acceleration = 0;
		double accelerationDecay = 0;

		switch(_protocol)
		{
			case 0:
			{
				deg = rand() % 361;

				// acceleration = _parentNote->getVelocity() / 32 + (double)rand() / RAND_MAX * (_parentNote->getVelocity()/4 - _parentNote->getVelocity()/4);
				acceleration = 1 + (rand() % 10000) / 1000;

				_origin.x = (int)(PROCESS_TIME.getElapsedTime().asSeconds()*50) % WIDTH;
				_origin.y = HEIGHT - (int)((_parentNote->getNote() - 21) * (HEIGHT/87));
				break;
			}

			case 1:
			{
				deg = (double)i * 10;
				acceleration  = _parentNote->getVelocity() / 16;
				_origin.x = (int)(PROCESS_TIME.getElapsedTime().asSeconds()*50) % WIDTH;
				_origin.y = HEIGHT - (int)((_parentNote->getNote() - 21) * (HEIGHT/87));
				break;
			}

			case 2:
			{
				deg = rand() % 361;

				// acceleration = _parentNote->getVelocity() / 32 + (double)rand() / RAND_MAX * (_parentNote->getVelocity()/4 - _parentNote->getVelocity()/4);
				acceleration = 1 + (rand() % 10000) / 1000;

				_origin.x = rand() % WIDTH;
				_origin.y = HEIGHT - (int)((_parentNote->getNote() - 21) * (HEIGHT/87));
				break;
			}

			case 3:
			{
				deg = rand() % 361;

				// acceleration = _parentNote->getVelocity() / 32 + (double)rand() / RAND_MAX * (_parentNote->getVelocity()/4 - _parentNote->getVelocity()/4);
				acceleration = 1 + (rand() % 10000) / 1000;

				_origin.y = HEIGHT - (int)((_parentNote->getNote() - 21) * (HEIGHT/87));
				break;
			}

			default:
			{
				deg = rand() % 361;

				acceleration = _parentNote->getVelocity() / 64 + (double)rand() / RAND_MAX * (_parentNote->getVelocity()/6 - _parentNote->getVelocity()/6);

				_origin.x = (int)(PROCESS_TIME.getElapsedTime().asSeconds()*50) % WIDTH;
				_origin.y = HEIGHT - (int)((_parentNote->getNote() - 21) * (HEIGHT/87));
				break;
			}
		}

		if(acceleration < 1)
			acceleration = 1;

		accelerationDecay = acceleration/1600;
		Color pColor = _color;

		int intensity = 1 + rand() % 8;
		pColor.r /= intensity;
		pColor.g /= intensity;
		pColor.b /= intensity;

		Particle *p = new Particle(this, acceleration, accelerationDecay, pColor, deg, _origin);
		_particles.push_back(p);
	}
}

void ParticleCluster::moveParticles()
{
	for(int i = 0; i < _particles.size(); i++)
	{
		if(_particles[i]->isActive())
		{
			_particles[i]->move();	
		}
		else
		{
			Particle* particle = _particles[i];
			_particles.erase(_particles.begin() + i);
			i--;

			delete particle;
		}
	}
}

void ParticleCluster::addParticle(Particle* p)
{
	_particles.push_back(p);
}

Note* ParticleCluster::getParentNote() const
{
	return _parentNote;
}

Vector2f ParticleCluster::getOrigin() const
{
	return _origin;
}

vector<Particle*> ParticleCluster::getParticles() const
{
	return _particles;
}

int ParticleCluster::getProtocol()const
{
	return _protocol;
}

Color ParticleCluster::getColor() const
{
	return _color;
}

ParticleCluster::~ParticleCluster()
{
	
}