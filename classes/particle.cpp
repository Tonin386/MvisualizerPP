#include "particle.hpp"

using namespace sf;
using namespace std;

Particle::Particle(double acceleration, double accelerationDecay, Color color, double radiants, Vector2f position) : _acceleration(acceleration), _accelerationDecay(accelerationDecay), _color(color), _radiants(radiants), _position(position)
{
	_active = true;
}

void Particle::setOff()
{
	_active = false;
}

void Particle::move(int protocol)
{
	//work to do
}

Particle::~Particle()
{
	
}