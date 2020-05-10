#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

class ParticleCluster;

class Particle
{
public:
	Particle(ParticleCluster* parent, double acceleration = 10, double accelerationDecay = 0.001, sf::Color color = sf::Color(255,255,255), double degrees = 0, sf::Vector2f position = sf::Vector2f(0,0));

	virtual void 			setOff();
	virtual void 			move();

	virtual double 			getAcceleration() 		const;
	virtual double 			getAccelerationDecay() 	const;
	virtual sf::Color 		getColor() 				const;
	virtual double 			getDegrees() 			const;
	virtual sf::Vector2f 	getPosition() 			const;
	virtual bool 			isActive() 				const;

	virtual ~Particle();

private:
	double	 			_acceleration;
	double	 			_accelerationDecay;
	sf::Color 			_color;
	double 				_degrees;
	sf::Vector2f 		_position;
	bool 				_active;
	ParticleCluster* 	_parent;

	double _dummy;
};

#endif