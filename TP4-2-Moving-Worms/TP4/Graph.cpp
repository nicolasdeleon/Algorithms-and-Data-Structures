#include "Graph.h"
#include <iostream>
#include <string>
#include <allegro5/allegro_image.h>


using namespace std;

Graph::Graph()
{
}

Graph::Graph(int width, int height, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* background)
{
	this->display = display;
	this->background = background;
	this->width = width;
	this->height = height;
}

void Graph::init(void) {
	this->error = !setAllegro(this->width, this->height, display);
	this->error = !setImages();
	al_flip_display();
}


Graph::~Graph()
{
	if (display)
		al_destroy_display(display);
	if (background)
		al_destroy_bitmap(background);

	al_shutdown_image_addon();
	
	for(int i=0; i < WALKINGFRAMES; i++) {
		if (walkingFrames[i]) {
			al_destroy_bitmap(walkingFrames[i]);
		}
	}
	for (int i = 0; i < JUMPINGFRAMES; i++) {
		if (jumpingFrames[i]) {
			al_destroy_bitmap(jumpingFrames[i]);
		}
	}
}


bool Graph::getError(void)
{
	return error;
}



/* Inicializa Allegro, el display, y el complemento de im�genes. */
bool Graph::setAllegro(int width, int height, ALLEGRO_DISPLAY*& display)
{
	/* Intenta inicializar Allegro */
	if (!al_init())
	{
		cout << "No es posible inicializar Allegro." << endl;
		return false;
	}

	display = al_create_display(width, height);
	if (!display)
	{
		cout << "No es posible inicializar el display." << endl;
		return false;
	}

	if (!(al_init_image_addon()))
	{
		cout << "No es posible inicializar el complemento de im�genes" << endl;
		return false;
	}

	return true;
}

bool Graph::setImages()
{
	bool res = true;
	string walkingFile = "wwalking/wwalk-F";
	string jumpingFile = "wjump/wjump-F";
	string png = ".png";
	string image;

	for (int i = 1; i <= WALKINGFRAMES; i++)
	{
		/* Formo path correspondiente a cada img */
		image = walkingFile + to_string(i) + png;
		/* Cargo img */
		walkingFrames[i - 1] = al_load_bitmap(image.c_str());
		if (!walkingFrames[i - 1])
			return false;
	}

	for (int j = 1; j <= JUMPINGFRAMES; j++)
	{
		/* Formo path correspondiente a cada img */
		image = jumpingFile + to_string(j) + png;
		/* Cargo img */
		jumpingFrames[j - 1] = al_load_bitmap(image.c_str());
		if (!jumpingFrames[j - 1])
			return false;
	}

	/* Cargo el fondo */
	background = al_load_bitmap("Scenario.png");
	if (!background)
		return false;

	/* Dibujo el fondo */
	al_draw_bitmap(background, 0, 0, 0);

	return true;
}

ALLEGRO_DISPLAY* Graph::getDisplay(void) {
	return this->display;
}

void Graph::drawFrame(unsigned int posX, unsigned int posY, ALLEGRO_BITMAP** frames, unsigned int frame, int dir) {
	int flag = 0;
	if (dir == 1)
		flag = ALLEGRO_FLIP_HORIZONTAL;

	al_draw_bitmap(frames[frame], posX, posY, flag);
}

ALLEGRO_BITMAP* Graph::getBackground(void) {
	return background;
}

void Graph::clearDisplay(void) {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_set_target_backbuffer(display);
	al_draw_bitmap(background, 0, 0, 0);
}
