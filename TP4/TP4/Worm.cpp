#include "Worm.h"



Worm::Worm()	//Se inicializa el worm en reposo y mirando a la derecha por defecto. Aparecen en posiciones aleatorias. 
{
	currentState = IDLE;
	angle = ANGLE;
	g = G;
	x = randBetweenReal((double)LEFT_EDGE, (double)RIGHT_EDGE);
	y = FLOOR;
	walkFrameCounter = 0;
	jumpFrameCounter = 0;
	preWalkFrameCounter = 0;
	preJumpFrameCounter = 0;
	frameCounter = 0;
	direction = RIGHT;
	rightKey = NULL;
	leftKey = NULL;
	jumpKey = NULL;
	jumpingSpeed = JUMPINGSPEED;
	isRightKeyPressed = 0;
	isLeftKeyPressed = 0;
	isJumpKeyPressed = 0;
}


Worm::~Worm()
{
}

void Worm::increaseWalkFrameCounter(void)
{
	walkFrameCounter++;
}

void Worm::increaseJumpFrameCounter(void)
{
	jumpFrameCounter++;
}

void Worm::wormWalk(void)
{
		if (frameCounter >= MOVINGFRAMES)
		{
			frameCounter = 0;
		}

		if ((x + ONESTEP * direction) < RIGHT_EDGE && (x + ONESTEP * direction) > LEFT_EDGE)
		{
			x += ONESTEP * direction;
		}

		walkFrameCounter++;
}

void Worm::wormJump(void)
{
	x += (direction*jumpingSpeed*cos(angle));
	if (x > RIGHT_EDGE)
	{
		direction=LEFT;
	}
	if (x < LEFT_EDGE)
	{
		direction=RIGHT;
	}
	
	y = FLOOR - jumpingSpeed*sin(angle)*jumpFrameCounter + 0.5*g*pow(jumpFrameCounter,2);
}


void Worm::setWormKeys(int jumpKey_, int rightKey_, int leftKey_)
{
	jumpKey = jumpKey_;
	rightKey = rightKey_;
	leftKey = leftKey_;
}



void Worm::wormFSM(int keyCode_, wormEvents_n eventType_)		//Recibe un evento y según el estado actual y el evento recibido procede acorde.
{
	if (eventType_ == KEY_DOWN) {

		if (keyCode_ == rightKey)
			isRightKeyPressed = true;
		else if (keyCode_ == leftKey)
			isLeftKeyPressed = true;
		else if (keyCode_ == jumpKey)
			isJumpKeyPressed = true;

		switch (currentState)
		{
		case IDLE:
			if (keyCode_ == jumpKey)		
			{
				currentState = BEGIN_JUMPING;
				frameCounter = 0;
				jumpWarmUp();
			}
			else if (keyCode_ == rightKey || keyCode_ == leftKey)
			{
				currentState = BEGIN_MOVING;
				if (keyCode_ == rightKey)
				{
					direction = RIGHT;
				}
				else if(keyCode_==leftKey)
				{
					direction = LEFT;
				}
				preWalkFrameCounter = 0;
				frameCounter = 0;
			}
			break;

		case BEGIN_MOVING:
			if (keyCode_ == jumpKey)
			{
				frameCounter = 0;
				currentState = BEGIN_JUMPING;
				jumpWarmUp();
			}
			else if (keyCode_ == rightKey || keyCode_ == leftKey)
			{
				if (preWalkFrameCounter >= IDLEFRAMES)
				{
					currentState = MOVING;
					preWalkFrameCounter = 0;
					frameCounter = 0;
				}
			}
			break;

		case MOVING:
			if (keyCode_ == jumpKey)
			{
				currentState = BEGIN_JUMPING;
				frameCounter = 0;
				jumpWarmUp();
			}
			else if (keyCode_ == rightKey || keyCode_ == leftKey)
			{
				wormWalk();
				if (walkFrameCounter >= FULLMOVEFRAME)
				{
					preWalkFrameCounter++;
				}
				if (walkFrameCounter >= CYCLEFRAMES)
				{
					walkFrameCounter = 0;
				}
			}
			break;

		case BEGIN_JUMPING:
			jumpWarmUp();
			break;

		case JUMPING:
			if (y <= FLOOR)		//Si toadavía no aterrizo actualiza la posición y los contadores.
				wormJump();
			else {
				frameCounter = FIRSTFALLFRAME;		//Una vez que aterriza se pasa a dibujar los frames de aterrizaje.
				jumpFrameCounter = 0;
				currentState = LANDING;
				y = FLOOR;
			}
			break;

		case LANDING:
			wormLanding();
			break;

		default:
			break;
		}
	}

	if (eventType_ == KEY_UP) {

		if (keyCode_ == rightKey)
			isRightKeyPressed = false;
		else if (keyCode_ == leftKey)
			isLeftKeyPressed = false;
		else if (keyCode_ == jumpKey)
			isJumpKeyPressed = false;

		switch (currentState)
		{
		case MOVING:
			if (keyCode_ == rightKey || keyCode_ == leftKey)		//El worm no debe detenerse si la tecla que se suelta no corresponde a la que indica su movimiento.
			{
				if(direction==RIGHT && isRightKeyPressed==false || direction==LEFT && isLeftKeyPressed==false)
				{
					if (!isRightKeyPressed && !isLeftKeyPressed)	//Sólo se detiene si se dejan de apretar las dos teclas de movimiento horizontal
					{
						currentState = IDLE;
						frameCounter = 0;
					}
					else if(isLeftKeyPressed)
					{
						currentState = BEGIN_MOVING;
						direction = LEFT;
						frameCounter = 0;
						preWalkFrameCounter = 0;
						walkFrameCounter = 0;
					}
					else if (isRightKeyPressed)
					{
						currentState = BEGIN_MOVING;
						direction = RIGHT;
						frameCounter = 0;
						preWalkFrameCounter = 0;
						walkFrameCounter = 0;
					}
				}
				else
				{

					if (walkFrameCounter <= FULLMOVEFRAME)		//Si está en la sección de warm up deja de moverse inmediatamente.
					{
						if (!isRightKeyPressed && !isLeftKeyPressed)
							currentState = IDLE;
					}
					if (walkFrameCounter >= FULLMOVEFRAME)		//si pasaron los 100 ms completa el ciclo y luego se detiene.
					{
						{
							currentState = BEGIN_MOVING;
							frameCounter = 0;
							preWalkFrameCounter = 0;
						}
					}
					walkFrameCounter = 0;
				}
			}
			break;

		case BEGIN_MOVING:
			if (keyCode_ == rightKey || keyCode_ == leftKey)		//Como no pasaron los primeros 100ms y no está en estado moving, se quedará quieto o cambiará de dirección.
			{
				preWalkFrameCounter = 0;
				currentState = IDLE;
				turnWorm(keyCode_);				//Revisa si es necesario cambiar la dirección de worm.
			}
			break;

		default:
			break;
		}
	}

	if (eventType_ == REFRESH) {
		switch (currentState)
		{
		case IDLE:
			frameCounter = 0;
			break;
		case BEGIN_MOVING:
			if (preWalkFrameCounter >= IDLEFRAMES)
			{
				currentState = MOVING;
				preWalkFrameCounter = 0;
				frameCounter = 0;
			}
			break;

		case MOVING:
			wormWalk();
			if (walkFrameCounter >= FULLMOVEFRAME)
			{
				preWalkFrameCounter++;
			}
			if (walkFrameCounter >= CYCLEFRAMES)
			{
				walkFrameCounter = 0;
			}
			break;

		case BEGIN_JUMPING:
			jumpWarmUp();
			break;
		case JUMPING:
			if (y <= FLOOR)		//Si toadavía no aterrizo actualiza la posición y los contadores.
				wormJump();
			else {
				frameCounter = FIRSTFALLFRAME;		//Una vez que aterriza se pasa a dibujar los frames de aterrizaje.
				jumpFrameCounter = 0;
				currentState = LANDING;
				y = FLOOR;
			}
			break;

		case LANDING:
			wormLanding();
			break;

		default:
			break;
		}
	}
}


	void Worm::jumpWarmUp(void)		//Lleva a cabo el las animaciones de warm up antes del salto.
	{

		if (frameCounter >= 0 && frameCounter <= IDLEFRAMES)	//Warmup.
		{
		}

		else
		{
			jumpFrameCounter = 0;
			currentState = JUMPING;		//Una vez que finalizó el warm up comienza a moverse.
		}
	}

	void Worm::wormLanding()
	{

		if (frameCounter >= FIRSTFALLFRAME && frameCounter <= LASTFALLFRAME) //Mientras está descendiendo no se modifica el estado.
		{
		}
		else
		{
			if (isJumpKeyPressed)
			{
				currentState = BEGIN_JUMPING;
				frameCounter = 0;
				jumpWarmUp();
			}

			else if (isRightKeyPressed)
			{
				currentState = BEGIN_MOVING;
				direction = RIGHT;
				preWalkFrameCounter = 0;
				frameCounter = 0;
			}
			else if (isLeftKeyPressed)
			{
				currentState = BEGIN_MOVING;
				direction = LEFT;
				preJumpFrameCounter = 0;
				frameCounter = 0;
			}
			else
			{
				currentState = IDLE;		//Worm has landed.
				frameCounter = 0;
				isJumpKeyPressed = 0;
				isLeftKeyPressed = 0;
				isJumpKeyPressed = 0;
			}
		}
	}



	void Worm::turnWorm(int keyCode_)
	{
		if ((keyCode_ == leftKey && direction == RIGHT) || (keyCode_ == rightKey && direction == LEFT))	//Se debe invertir
		{
			direction = ((direction == RIGHT) ? LEFT : RIGHT);
		}
	}

	void Worm::updateWorm(void)		//Incrementa el contador de la acción que corresponda.
	{
		switch (currentState)
		{
		case BEGIN_MOVING:			//Si todavía está en la etapa de warm up, actualiza sólo el contador temporario. (no el de frames de la caminata)
			preWalkFrameCounter++;
			break;

		case BEGIN_JUMPING:
		case JUMPING:
			jumpFrameCounter++;
			break;

		default:
			break;
		}
		frameCounter++;
	}





void Worm::setX(double x_)
{
	x = x_;
}

void Worm::setY(double y_)
{
	y = y_;
}

void Worm::set_keys(char ku, char kl, char kr)
{
}

void Worm::setDirection(dir_n d)
{
	direction = d;
}

void Worm::setState(wormStates_n nextState)
{
	currentState = nextState;
}

void Worm::setJumpKey(int jumpKey_)
{
	jumpKey = jumpKey_;
}

void Worm::setRightKey(int rightKey_)
{
	rightKey = rightKey_;
}

void Worm::setLeftKey(int leftKey_)
{
	leftKey = leftKey_;
}

void Worm::setWalkFrameCounter(int walkFrame)
{
	walkFrameCounter = walkFrame;
}

void Worm::setJumpFrameCounter(int jumpFrame)
{
	jumpFrameCounter = jumpFrame;
}

double Worm::getX(void)
{
	return x;
}

double Worm::getY(void)
{
	return y;
}

dir_n Worm::getDirection(void)
{
	return direction;
}

wormStates_n Worm::getState(void)
{
	return currentState;
}

double Worm::getJumpingSpeed(void)
{
	return jumpingSpeed;
}

double Worm::getGravity(void)
{
	return g;
}

double Worm::getAngle(void)
{
	return angle;
}


int Worm::getJumpKey(void)
{
	return jumpKey;
}

int Worm::getLeftKey(void)
{
	return leftKey;
}

int Worm::getRightKey(void)
{
	return rightKey;
}

int Worm::getWalkFrameCounter(void)
{
	return walkFrameCounter;
}

int Worm::getJumpFrameCounter(void)
{
	return jumpFrameCounter;
}

int Worm::getFrameCounter(void)
{
	return frameCounter;
}
