#include "EventGen.h"

using namespace std;


EventGen::EventGen(Graph*graph) {

	/* Creo e inicializo el timer */
	if (!(timer = al_create_timer(1.0 / FPS)))
		cout << "Error al inicializar timer de allegro" << endl;
	else
		al_start_timer(timer);

	/* Creo cola de eventos de Allegro */
	if (!(eventQueue = al_create_event_queue()))
		cout << "Error al inicializar la cola de eventos de Alegro" << endl;

	/* Instalo el teclado */
	if (!al_install_keyboard())
		cout << "Error al inicializar el teclado" << endl;

	/* Registro en cola de eventos */
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_display_event_source(graph->getDisplay()));

}

EventGen::~EventGen()
{
	if (eventQueue)
		al_destroy_event_queue(eventQueue);
	if (timer)
		al_destroy_timer(timer);
	al_uninstall_keyboard();	
}

ALLEGRO_EVENT EventGen::getAllegroEvent(void) {
	return alEvent;
}

int EventGen::nextEvent(void) {
	return al_get_next_event(eventQueue, &alEvent);
}


ALLEGRO_EVENT_QUEUE* EventGen::getQueue(void)
{
	return eventQueue;
}

void EventGen::dispatch(Simulation* simPtr) {
	switch (alEvent.type) {
	case ALLEGRO_EVENT_KEY_UP:
		simPtr->stopWorm(alEvent.keyboard.keycode);
		break;
	case ALLEGRO_EVENT_KEY_DOWN:
		simPtr->moveWorm(alEvent.keyboard.keycode);
		break;
	case ALLEGRO_EVENT_TIMER:
		simPtr->refresh_worm(alEvent.keyboard.keycode);
		break;
	default:
		break;
	}
}