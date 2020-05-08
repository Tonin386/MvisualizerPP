#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

class Particle
{
public:
	Particle(double acceleration = 10, double accelerationDecay = 0.001, sf::Color color = sf::Color(255,255,255), double radiants = 0, sf::Vector2f position = sf::Vector2f(0,0));
	virtual void setOff();
	virtual void move(int protocol);
	virtual ~Particle();

private:
	double _acceleration;
	double _accelerationDecay;
	sf::Color _color;
	double _radiants;
	sf::Vector2f _position;
	bool _active;
	
};

#endif