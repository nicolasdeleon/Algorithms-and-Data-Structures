#pragma once
#include <allegro5/allegro.h>
#include "Worm.h"
#include <allegro5/keyboard.h>
#define BACKGROUND "Scenario.png"
#define WALKINGFRAMES 15
#define JUMPINGFRAMES 10
#define DEFAULT_DISPLAY_WIDTH 1920
#define DEFAULT_DISPLAY_HEIGHT 696


class Graph
{
public:
	Graph();
	Graph(
		int width = DEFAULT_DISPLAY_WIDTH,
		int height = DEFAULT_DISPLAY_HEIGHT,
		ALLEGRO_DISPLAY* display = nullptr,
		ALLEGRO_BITMAP* background = nullptr
	);
	~Graph();

	void init(void);

	void update(Worm **wormPtr, int wormNum);	//Actualiza el display.

	void clearDisplay(void);
	//Getters
	bool getError(void);

	ALLEGRO_DISPLAY* getDisplay(void);

	void drawFrame(unsigned int posX, unsigned int posY, ALLEGRO_BITMAP** frames, unsigned int frame, int dir);

	ALLEGRO_BITMAP* getBackground(void);

	ALLEGRO_BITMAP* walkingFrames[WALKINGFRAMES];		//Im�genes de 'worm walk'.
	ALLEGRO_BITMAP* jumpingFrames[JUMPINGFRAMES];		//Im�genes de 'worm jump'.

private:
	ALLEGRO_DISPLAY * display;							//Display.
	ALLEGRO_BITMAP  * background;						//Imagen de fondo.


	bool setAllegro(int width, int height, ALLEGRO_DISPLAY*& display);
	bool setImages();

	unsigned int width;
	unsigned int height;

	bool error;		//vale 1 si hubo error de Allegro, en caso contrario cero.

};

