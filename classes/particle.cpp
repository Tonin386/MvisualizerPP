#include "particle.hpp"
#include "particlecluster.hpp"

#include "../constants.hpp"

#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

Particle::Particle(ParticleCluster* parent, double acceleration, double accelerationDecay, Color color, double degrees, Vector2f position) : _parent(parent), _acceleration(acceleration), _accelerationDecay(accelerationDecay), _color(color), _degrees(degrees), _position(position)
{
	_active = true;
	// cout << "Particle created | Acceleration = " << _acceleration << " | Acceleration Decay = " << _accelerationDecay << " | degrees = " << _degrees << endl;
}

void Particle::setOff()
{
	_active = false;
}

void Particle::move()
{
	switch(_parent->getProtocol())
	{
		default:
		{
			if(_acceleration < 0.05) _active = false;
			_position.x += _acceleration * cos(_degrees*PI/180);
			_position.y += _acceleration * sin(_degrees*PI/180);

			_acceleration -= _accelerationDecay;
			break;	
		}
	}

	if(_position.x > WIDTH || _position.x < 0)
		_active = false;
	if(_position.y > HEIGHT || _position.y < 0)
		_active = false;
}

double Particle::getAcceleration() const
{
	return _acceleration;
}

double Particle::getAccelerationDecay() const
{
	return _accelerationDecay;
}

Color Particle::getColor() const
{
	return _color;
}

double Particle::getDegrees() const
{
	return _degrees;
}

Vector2f Particle::getPosition() const
{
	return _position;
}

bool Particle::isActive() const
{
	return _active;
}

Particle::~Particle()
{
	
}