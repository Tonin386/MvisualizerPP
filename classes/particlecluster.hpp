#ifndef PARTICLECLUSTER_HPP
#define PARTICLECLUSTER_HPP

#include "note.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Particle;

class ParticleCluster
{
public:
	ParticleCluster(Note* parentNote, int protocol = 0, sf::Color color = sf::Color(255,255,255));

	virtual void 					moveParticles();
	virtual void 					addParticle(Particle* p);

	virtual Note*					getParentNote() const;
	virtual sf::Vector2f 			getOrigin() 	const;
	virtual std::vector<Particle*> 	getParticles() 	const;
	virtual int						getProtocol() 	const;
	virtual sf::Color 				getColor() 		const;

	virtual ~ParticleCluster();

private:
	Note* 					_parentNote;
	sf::Vector2f 			_origin;
	std::vector<Particle*> 	_particles;
	int 					_protocol;
	sf::Color 				_color;
};

#endif