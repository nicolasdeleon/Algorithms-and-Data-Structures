#include "Evento.h"



Evento::Evento()
{
}

Evento::Evento(int type_)
{
	type = type_;
}


Evento::~Evento()
{
}

void Evento::setType(int type_)
{
	type = type_;
}

void Evento::setKeycode(int keyCode_)
{
	keycode = keyCode_;
}

int Evento::getType(void)
{
	return type;
}

int Evento::getKeycode(void)
{
	return keycode;
}
