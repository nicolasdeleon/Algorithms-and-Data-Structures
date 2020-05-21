#pragma once
#include "Simulation.h"
#include <iostream>
#include <allegro5/allegro.h>

#define FPS 50.0

class EventGen
{
public:
	EventGen();
	
	EventGen(Graph* graph = nullptr);

	int nextEvent(void);	// Regresa si hay evento o no

	ALLEGRO_EVENT_QUEUE* getQueue(void);

	ALLEGRO_EVENT getAllegroEvent(void);

	void dispatch(Simulation* simPtr);

	~EventGen();

private:
	ALLEGRO_EVENT_QUEUE * eventQueue;
	ALLEGRO_TIMER * timer;
	ALLEGRO_EVENT alEvent;
};

