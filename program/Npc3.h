#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	‚m‚o‚bƒNƒ‰ƒX
//---------------------------------------------------------------------------------
class Npc3
{
public:
	int pos_x;
	int pos_y;
	int speed;
	int image[12];
	int mode;
	int spawn_posX;
	int spawn_posY;
	int time_spawn;
	int warning;
	int warning_time;
	int warning_mode;
	int image_index;
	int time_switch_image;
	void Init();		//	‰Šú‰»ˆ—
	void Update();	//	XVˆ—
	void Render();		//	•`‰æˆ—
	void Exit();		//	I—¹ˆ—
};
