#ifndef PARTICLECLUSTER_HPP
#define PARTICLECLUSTER_HPP

#include "particle.hpp"
#include <vector>

class ParticleCluster
{
public:
	ParticleCluster(sf::Vector2f origin = sf::Vector2f(0,0), int n = 10);
	virtual ~ParticleCluster();

private:
	sf::Vector2f _origin;
	std::vector<Particle> *_particles;
};

#endif