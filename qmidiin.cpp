//*****************************************//
//  qmidiin.cpp
//  by Gary Scavone, 2003-2004.
//
//  Simple program to test MIDI input and
//  retrieval from the queue.
//
//*****************************************//

#include <iostream>
#include <cstdlib>
#include <signal.h>
#include "dependencies/RtMidi.h"

// Platform-dependent sleep routines.
#if defined(WIN32)
  #include <windows.h>
  #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds ) 
#else // Unix variants
  #include <unistd.h>
  #define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif

bool done;
static void finish( int /*ignore*/ ){ done = true; }

void usage( void ) {
  // Error function in case of incorrect command-line
  // argument specifications.
	std::cout << "\nusage: qmidiin <port>\n";
	std::cout << "    where port = the device to use (first / default = 0).\n\n";
	exit( 0 );
}

int main( int argc, char *argv[] )
{
	RtMidiIn *midiin = 0;
	std::vector<unsigned char> message;
	int nBytes, i;
	double stamp;

  // Minimal command-line check.
	if ( argc > 2 ) usage();

  // RtMidiIn constructor
	try {
		midiin = new RtMidiIn();
	}
	catch ( RtMidiError &error ) {
		error.printMessage();
		exit( EXIT_FAILURE );
	}

  // Check available ports vs. specified.
	unsigned int port = 0;
	unsigned int nPorts = midiin->getPortCount();
	if ( argc == 2 ) port = (unsigned int) atoi( argv[1] );
	if ( port >= nPorts ) {
		delete midiin;
		std::cout << "Invalid port specifier!\n";
		usage();
	}

	try {
		midiin->openPort( port );
	}
	catch ( RtMidiError &error ) {
		error.printMessage();
		goto cleanup;
	}

  // Don't ignore sysex, timing, or active sensing messages.
	midiin->ignoreTypes( false, false, false );

  // Install an interrupt handler function.
	done = false;
	(void) signal(SIGINT, finish);

  // Periodically check input queue.
	std::cout << "Reading MIDI from port " << midiin->getPortName() << " ... quit with Ctrl-C.\n";
	while ( !done ) {
		stamp = midiin->getMessage( &message );
		nBytes = message.size();
		bool something = false;
		for ( i=0; i<nBytes; i++ )
			if(message[0] != 254)
			{
				std::cout << "Byte " << i << " = " << (int)message[i] << ", ";
				something = true;
			}

		if (something)
			//std::cout << "stamp = " << stamp << std::endl;
			std::cout << std::endl;

	// Sleep for 10 milliseconds.
		SLEEP( 10 );
	}

  // Clean up
	cleanup:
	delete midiin;

	return 0;
}
