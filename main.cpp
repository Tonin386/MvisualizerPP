#include "dependencies/RtMidi.h"

#include <SFML/Graphics.hpp>

#include "classes/gnote.hpp"
#include "classes/particlecluster.hpp"

#include <iostream>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 1920
#define HEIGHT 1080
#define CREATION_PROTOCOL 1

using namespace std;
using namespace sf;

void findNoteIdx(int note, vector<GNote*> notes);
void clean(vector<GNote*> &notes, int processTimeSec);
void createParticles(int note, int r = -1, int g = -1, int b = -1, int x = 0, int y = 0);
void moveParticles(ParticleCluster &particles); //May undergo modifications


int main(int argc, char const *argv[])
{
	srand(time(NULL));

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "mvisualizerpp");

	RtMidiIn *inport = new RtMidiIn;
	inport->openPort(0);
	inport->ignoreTypes(0,0,0);
	bool done = false;

	Clock processClock

	while(window.isOpen())
	{
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

		window.clear();
		//window.draw(something;)
		window.display();
	}

	return 0;
}