#pragma once
class Evento
{
public:
	Evento();
	Evento(int type_);
	~Evento();


	//Setters
	void setType(int type_);
	void setKeycode(int keyCode_);


	//Getters
	int getType(void);
	int getKeycode(void);



private:
	int type;	//Tipo de evento.
	int keycode;	
};

