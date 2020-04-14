#include <iostream>
#include "EventGen.h"
#include "Simulation.h"
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) {

	bool res = true;

	srand(time(NULL));

	/* Simulation is initialized. */
	Simulation* simPtr = new (nothrow) Simulation();
	if (simPtr == nullptr)
		res = false;
	else 
		/* Graphing requirements are initialized and worms are assigned their game keys. */
		res = simPtr->initSim(X_DISPLAY, Y_DISPLAY);
	
	/* Event generator is created. */
	EventGen* generator = new (nothrow) EventGen(simPtr->grapher);		
	
	if (generator == nullptr)
		res = false;
															
	if (res)
	{
		/* Checks whether the user wants to close the display or not. */
		while (generator->getAllegroEvent().type != ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			/* Checks if there are events in the queue */
			if (generator->getAllegroEvent().type != ALLEGRO_EVENT_DISPLAY_CLOSE && generator->nextEvent())
			{
				generator->dispatch(simPtr);
				al_flip_display();
			}
		}
	}
	else
		cout << "No se pudo asignar memoria." << endl;
	
	delete generator;
	delete simPtr;

	return 0;
}
