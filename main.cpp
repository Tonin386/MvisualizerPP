#include "dependencies/RtMidi.h"

#include "classes/note.hpp"
#include "classes/particle.hpp"
#include "classes/particlecluster.hpp"

#include <iostream>
#include <cstdlib>
#include <cmath>

#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "constants.hpp"

using namespace std;
using namespace sf;

int fetchMidiInput(vector<Note*> &notes, RtMidiIn *midiin);
int findNoteIdx(int note, vector<Note*> notes);
void clean(vector<Note*> &notes);
void createClusters(vector<ParticleCluster*> &pClusters, vector<Note*> notes);
void tickClusters(vector<ParticleCluster*> &pClusters);
Color drawParticles(RenderWindow &window, vector<ParticleCluster*> pClusters);


Clock PROCESS_TIME;

int main(int argc, char const *argv[])
{
	srand(time(NULL));

	Clock tick;
	Clock debug;

	RtMidiIn *midiin = 0;
	try {
		midiin = new RtMidiIn();
	}
	catch (RtMidiError &error) {
		error.printMessage();
		return 0;
	}

	unsigned int port = 0;
	unsigned int nPorts = midiin->getPortCount();
	if (port >= nPorts) {
		delete midiin;
		cout << "Invalid port specifier!\n";
	}

	try {
		midiin->openPort(0);
	}
	catch (RtMidiError &error) {
		error.printMessage();
		delete midiin;
		return 0;
	}

	midiin->ignoreTypes(false, false, false);
	cout << "Reading MIDI from port " << midiin->getPortName() << "\n";

	RenderWindow window(VideoMode(WIDTH, HEIGHT, BITS), "MVisualizerPP", Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	Color bg(rand() % 11, rand() % 11, 200 + rand() % 25);

	vector<Note*> notes;
	vector<ParticleCluster*> pClusters;

	while(window.isOpen())
	{
		// cout << debug.restart().asMilliseconds() << endl;
		Event e;
		while(window.pollEvent(e))
		{
			switch(e.type)
			{
				case Event::Closed:
				window.close();
				break;

				case Event::KeyPressed:
				if(e.key.code == Keyboard::Escape)
				{
					window.close();
				}
				break;
			}
		}

		fetchMidiInput(notes, midiin);
		clean(notes);

		tick.restart();
		tickClusters(pClusters);
		createClusters(pClusters, notes);

		window.clear();
		drawParticles(window, pClusters);
		window.display();

		bg = Color(rand() % 11, rand() % 11, 200 + rand() % 25);
	}

	delete midiin;

	return 0;
}

int fetchMidiInput(vector<Note*> &notes, RtMidiIn *midiin)
{
	vector<unsigned char> message;
	int nBytes(1), i, n(0);
	double stamp;
	// Periodically check input queue.
	while (nBytes > 0) 
	{
		stamp = midiin->getMessage(&message);
		nBytes = message.size();

		if(nBytes > 0 && (int)message[0] != 254) //254 is "nothing happened" basically
		{
			if((int)message[0] == 144) //Key pressed
			{
				n++;
				Note *note = new Note((int)message[1], (int)message[2], PROCESS_TIME.getElapsedTime().asSeconds());
				// cout << "Key pressed | note = " << note->getNote() << " | velocity = " << note->getVelocity() << " | time_on = " << note->getTimeOn() << endl;
				notes.push_back(note);
			}
			else if((int)message[0] == 128) //Key released
			{
				// cout << "Key released | note = " << (int)message[1] << endl;
				int idx = findNoteIdx((int)message[1], notes);
				if(idx != -1)
				{
					notes[idx]->setOff(PROCESS_TIME.getElapsedTime().asSeconds());
				}
				else
				{
					cout << "Error while trying to find the note." << endl;
				}
			}
		}
	}

	return n;
}

int findNoteIdx(int note, vector<Note*> notes)
{
	for(int i = 0; i<notes.size(); i++)
	{
		if(notes[i]->getNote() == note && notes[i]->getTimeOff() == -1)
		{
			return i;
		}
	}

	return -1;
}

void clean(vector<Note*> &notes)
{
	for(int i = 0; i < notes.size(); i++)
	{
		if(PROCESS_TIME.getElapsedTime().asSeconds() - notes[i]->getTimeOff() > 10 && notes[i]->getTimeOff() != -1) 
		{
			// cout << "Deleted note" << endl;
			Note* note = notes[i];
			notes.erase(notes.begin() + i);
			i--;

			delete note;
		}
	}
}

void createClusters(vector<ParticleCluster*> &pClusters, vector<Note*> notes)
{
	for(int i = 0; i < notes.size(); i++)
	{
		// if(notes[i]->getChildCluster() == nullptr)
		// {
		// 	ParticleCluster *cluster = new ParticleCluster(notes[i], 4, Color(rand() % 10, 10 + rand() % 10, 190 + rand() % 20 - rand() % 20));
		// 	pClusters.push_back(cluster);
		// }
		if(notes[i]->getTimeOff() == -1)
		{
			ParticleCluster *clusterA = new ParticleCluster(notes[i], 3, Color(100 + rand() % 10, 100 + rand() % 10, 220 + rand() % 20 - rand() % 20));
			ParticleCluster *clusterB = new ParticleCluster(notes[i], 4, Color(190 + rand() % 10, 100 + rand() % 10, 190 + rand() % 20 - rand() % 20));
			pClusters.push_back(clusterA);
			pClusters.push_back(clusterB);
		}
	}
}

void tickClusters(vector<ParticleCluster*> &pClusters)
{
	for(int i = 0; i < pClusters.size(); i++)
	{
		pClusters[i]->moveParticles();
		if(pClusters[i]->getParticles().size() == 0)
		{
			ParticleCluster* p = pClusters[i];
			pClusters.erase(pClusters.begin() + i);
			i--;

			delete p;
		}
	}
}

Color drawParticles(RenderWindow &window, vector<ParticleCluster*> pClusters)
{
	VertexArray dots(Quads, 0);
	int totalDotsCount = 0;
	int dotsCount = 0;
	double r(0), g(0), b(0);
	for(int i = 0; i < pClusters.size(); i++) //each cluster
	{
		vector<Particle*> clusterParticles = pClusters[i]->getParticles();
		totalDotsCount += clusterParticles.size()*4; //We add the number of particles in the cluster to the total count of dots in order to resize our vertexarray
		dots.resize(totalDotsCount);
		for(int j = 0; j < clusterParticles.size(); j++) //each particle
		{	
			Vector2f center = clusterParticles[j]->getPosition();
			Color pColor = clusterParticles[j]->getColor();

			r += pColor.r;
			g += pColor.g;
			b += pColor.b;

			dots[dotsCount].position = Vector2f(center.x-1, center.y-2);
			dots[dotsCount + 1].position = Vector2f(center.x+2, center.y-1);
			dots[dotsCount + 2].position =  Vector2f(center.x+2, center.y+1);
			dots[dotsCount + 3].position =  Vector2f(center.x-1, center.y+2);

			dots[dotsCount].color = pColor;
			dots[dotsCount + 1].color = pColor;
			dots[dotsCount + 2].color = pColor;
			dots[dotsCount + 3].color = pColor;

			dotsCount += 4;
		}

		dotsCount = totalDotsCount;
	}

	window.draw(dots);

	r /= totalDotsCount/4;
	g /= totalDotsCount/4;
	b /= totalDotsCount/4;

	return Color(r,g,b);
}