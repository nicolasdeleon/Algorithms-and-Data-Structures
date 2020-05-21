#pragma once
#include "Worm.h"
#include "Graph.h"
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

#define NWORMS 2
#define MAXWORMS 14

class Simulation
{
public:
	Simulation();
	~Simulation();

	bool initSim(int width, int height);
	void assignKeys(void);
	void moveWorm(int keyCode_);
	void stopWorm(int keyCode_);
	void refresh_worm(int keyCode_);

	//Setters
	void setWormNum(int wormNum_);
	void setWidth(int width_);
	void setHeigth(int heigth_);

	//Getters
	int getWormNum(void);
	int getWidth(void);
	int getHeight(void);

	//datos miembros.
	Worm *wormPtr[MAXWORMS];
	Graph *grapher;

private:
	int wormNum;
	int heigth;
	int width;

};

