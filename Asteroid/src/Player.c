
#include "include.h"

Player* initPlayer(
	float x, 
	float y, 
	float r,
	float l, 
	float w){

	Player* a = malloc(sizeof(Player));

	a->x = x;
	a->y = y;
	a->xspd = 0;
	a->yspd = 0;
	a->render = renderPlayer;
	a->update = updatePlayer;
	a->radius = r;

	a->length = l;
	a->width = w;
	a->c = randomColor();
	a->angle = 90;
	a->angleAccel = 3;
	a->accel = 1;
	a->maxSpeed = 5;

	return a;
}

void renderPlayer(Player* p) {

	float a0 = DEG2RAD * p->angle;
	float a1 = DEG2RAD * (p->angle - 120);
	float a2 = DEG2RAD * (p->angle + 120);

	Vector2 tip;
	tip.x = (p->length * cos(a0)) + p->x;
	tip.y = -(p->length * sin(a0)) + p->y;

	Vector2 rside;
	rside.x = (p->width * cos(a1)) + p->x;
	rside.y = -(p->width * sin(a1)) + p->y;

	Vector2 lside;
	lside.x = (p->width * cos(a2)) + p->x;
	lside.y = -(p->width * sin(a2)) + p->y;

	DrawTriangleLines(tip, rside, lside, p->c);
}

void updatePlayer(Player* p) {
	bool d = IsKeyDown(KEY_D);
	bool a = IsKeyDown(KEY_A);

	if (a) {
		p->angle += p->angleAccel; 
	}
	if (d) {
		p->angle -= p->angleAccel; 
	}

	p->angle %= 360;

	if(IsKeyDown(KEY_SPACE)) {

		float a0 = DEG2RAD * p->angle;
		float xspd = p->accel * cos(a0);
		float yspd = p->accel * sin(a0);

		float velAngle = atan(-p->yspd / p->xspd);
		float angleDiff = velAngle - p->angle;

		if (abs(angleDiff) < 90) {
			if (sqrt( pow(p->xspd + xspd, 2) + pow(p->yspd + yspd, 2)) > p->maxSpeed) {	// if the next speed is going faster than max
				float magnitude = p->accel * (1 - cos(a0));	// the magnitude not associated with the current speed direction

				float refAngle;
				if (velAngle > p->angle) {

				}
				else {
					
				}
				p->xspd += xspd;
				p->yspd -= yspd;
			}
			else {
				p->xspd += xspd;
				p->yspd -= yspd;
			}
		}
		else {			// angleDiff >= 90
			p->xspd += xspd;
			p->yspd -= yspd;
		}
	}

	// Xcollision
	if(p->x + p->xspd > *(getWindowWidth())) {
		p->x = 0;
	}
	else if (p->x + p->xspd < 0) {
		p->x = *(getWindowWidth());
	}

	// Ycollision
	if(p->y + p->yspd > *(getWindowHeight())) {
		p->y = 0;
	}
	else if (p->y + p->yspd < 0) {
		p->y = *(getWindowHeight());
	}

	p->x += p->xspd;
	p->y += p->yspd;
}



