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
	_dummy = 0;
	// cout << "Particle created | Acceleration = " << _acceleration << " | Acceleration Decay = " << _accelerationDecay << " | degrees = " << _degrees << " | (x,y) = (" << _position.x << ";" << _position.y << ")" <<endl;
}

void Particle::setOff()
{
	_active = false;
}

void Particle::move()
{
	switch(_parent->getProtocol())
	{
		case 4:
		{
			if(_acceleration < 0.1) _active = false;
			_position.x += _acceleration * cos((_degrees + 30 * sin(_dummy*PI/180))*PI/180);
			_position.y += _acceleration * sin((_degrees + 30 * sin(_dummy*PI/180))*PI/180);
			_dummy += 10;
			_dummy = (int)_dummy % 360;
			_acceleration -= _accelerationDecay;
			break;
		}
		case 0:
		case 1:
		case 2:
		case 3:
		default:
		{
			if(_acceleration < 0.05) _active = false;
			_position.x += _acceleration * cos(_degrees*PI/180);
			_position.y += _acceleration * sin(_degrees*PI/180);

			_acceleration -= _accelerationDecay;
			break;	
		}
	}
	// cout << "Particle moved | Acceleration = " << _acceleration << " | Acceleration Decay = " << _accelerationDecay << " | degrees = " << _degrees << " | (x,y) = (" << _position.x << ";" << _position.y << ")" <<endl;

	if(_position.x > WIDTH || _position.x < 0 || _position.y > HEIGHT || _position.y < 0) _active = false;
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