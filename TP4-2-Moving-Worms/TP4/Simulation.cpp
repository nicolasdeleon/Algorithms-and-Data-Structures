#include "Simulation.h"
#include <iostream>
#define P1_KEY_UP ALLEGRO_KEY_UP
#define P1_KEY_RIGHT ALLEGRO_KEY_RIGHT
#define P1_KEY_LEFT ALLEGRO_KEY_LEFT
#define P2_KEY_UP ALLEGRO_KEY_W
#define P2_KEY_RIGHT ALLEGRO_KEY_D
#define P2_KEY_LEFT ALLEGRO_KEY_A


using namespace std;



Simulation::Simulation()		//Constructor de Simulation.
{
	Graph * grapher = nullptr;
	wormNum = NWORMS;
	for (int i = 0; i < wormNum; i++)
		wormPtr[i] = nullptr;
}

Simulation::~Simulation()	//Destructor
{
	delete this->grapher;
}

bool Simulation::initSim(int width, int height)	//Inicializa a los worms y al objeto gr�fico.
{
	int res = true;
	for (int i = 0; i < wormNum; i++)
	{
		wormPtr[i] = new (nothrow) Worm();
		if (wormPtr[i] == nullptr)
			res = false;
	}

	grapher = new(nothrow) Graph(width, height);
	grapher->init();
	if (grapher == nullptr)
		res = false;
	if (grapher->getError())
		res = false;
	if (res)
		assignKeys();

	return res;
}

void Simulation::assignKeys(void)
{
	int walkKeys[] = { P1_KEY_RIGHT,P1_KEY_LEFT,P2_KEY_RIGHT,P2_KEY_LEFT };
	int jumpKeys[] = { P1_KEY_UP, NULL, P2_KEY_UP };

	wormPtr[0]->setWormKeys(P1_KEY_UP, P1_KEY_RIGHT, P1_KEY_LEFT);
	wormPtr[1]->setWormKeys(P2_KEY_UP, P2_KEY_RIGHT, P2_KEY_LEFT);
}

void Simulation::moveWorm(int keyCode_)
{
	for (int i = 0; i < wormNum; i++)
	{
		wormPtr[i]->wormFSM(keyCode_, KEY_DOWN);
	}
}

void Simulation::stopWorm(int keyCode_)
{
	for (int i = 0; i < wormNum; i++)
	{
		wormPtr[i]->wormFSM(keyCode_, KEY_UP);
	}
}

void Simulation::refresh_worm(int keyCode_)
{

	grapher->clearDisplay();

	for (int i = 0; i < wormNum; i++)
	{
		wormPtr[i]->updateWorm();
		wormPtr[i]->wormFSM(keyCode_, REFRESH);
	}

	for (int i = 0; i < wormNum; i++) {
		if (
			wormPtr[i]->getState() == BEGIN_MOVING ||
			wormPtr[i]->getState() == MOVING ||
			wormPtr[i]->getState() == IDLE
			)
			grapher->drawFrame(
				wormPtr[i]->getX(),
				wormPtr[i]->getY(),
				grapher->walkingFrames,
				wormPtr[i]->getFrameCounter(),
				wormPtr[i]->getDirection()
			);

		else if (
			wormPtr[i]->getState() == BEGIN_JUMPING ||
			wormPtr[i]->getState() == LANDING
			)
			grapher->drawFrame(
				wormPtr[i]->getX(),
				wormPtr[i]->getY(),
				grapher->jumpingFrames,
				wormPtr[i]->getFrameCounter() % 10,
				wormPtr[i]->getDirection()
			);

		else if (wormPtr[i]->getState() == JUMPING)
			grapher->drawFrame(
				wormPtr[i]->getX(),
				wormPtr[i]->getY(),
				grapher->jumpingFrames,
				5,
				wormPtr[i]->getDirection()
			);
	}
}




//Setters
void Simulation::setWormNum(int wormNum_)
{
	wormNum = wormNum_;
}

void Simulation::setWidth(int width_)
{
	width = width_;
}

void Simulation::setHeigth(int heigth_)
{
	heigth = heigth_;
}


//Getters
int Simulation::getWormNum(void)
{
	return wormNum;
}

int Simulation::getWidth(void)
{
	return width;
}

int Simulation::getHeight(void)
{
	return heigth;
}
