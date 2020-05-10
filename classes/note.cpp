#include "note.hpp"
#include "particlecluster.hpp"

Note::Note(int note, int velocity, double time_on, double time_off) : _note(note), _velocity(velocity), _time_on(time_on), _time_off(time_off)
{
	_childCluster = nullptr;
}

void Note::setOff(double time_off)
{
	_time_off = time_off;
}

void Note::setChild(ParticleCluster* child)
{
	_childCluster = child;
}

int Note::getNote() const
{
	return _note;
}

int Note::getVelocity() const
{
	return _velocity;
}

double Note::getTimeOn() const
{
	return _time_on;
}

double Note::getTimeOff() const
{
	return _time_off;
}

ParticleCluster* Note::getChildCluster() const
{
	return _childCluster;
}

Note::~Note()
{
	
}