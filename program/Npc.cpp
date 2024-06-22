#include "Main.h"
#include "Game.h"
#include "Npc.h"
#include "Hit.h"



//---------------------------------------------------------------------------------
//	èâä˙âªèàóù
//---------------------------------------------------------------------------------
void Npc::Init()
{
	pos_x = -30;
	pos_y = -30;
	mode = 0;
	speed = 2;
	time_s = 60;
	time_warp = 20;
	image_index = 4;
	time_switch_image = 60;
	LoadDivGraph("data/flying_dragon-red.png", 12, 3, 4, 432 / 3, 512 / 4, image);
}
//---------------------------------------------------------------------------------
//	çXêVèàóù
//---------------------------------------------------------------------------------
void Npc::Update(int mouseX, int mouseY)
{

SettingMode:
	{

		//Reset
		if (mode == 0) {
			pos_x = -130;
			pos_y = -30;
			time_s = 60;
		}
		//RandomSpawn
		if (mode == 1) {
			spawn_pos = GetRand(1);
			mode = 2;
		}
		//SettingSpawn
		if (mode == 2) {
			switch (spawn_pos) {
			case 0:
				pos_x = -130;
				pos_y = 500;
				break;
			case 1:
				pos_x = SCREEN_W + 30;
				pos_y = 500;
				break;
			}
			mode = 3;
		}
		//Moving
		{
			if (mode == 3 && pos_y >=449) {
				switch (spawn_pos) {
				case 0:
					pos_x += speed;
					break;
				case 1:
					pos_x -= speed;
					break;
				}
			}
			//Gravity
			{
				pos_y += speed ;
				if (pos_y >= 450) {
					pos_y = 450;
				}
			}
		}
		//Damaged
		if (mode == 4) {
			time_s--;
			if (time_s <= 0) {
				mode = 0;

			}
		}
		//Warp
		if (mode == 5) {
			time_warp--;
			if (time_warp <= 0) {
				time_warp = 20;
				mode = 7;
			}
		}
		//FallingDown
		if (mode == 6) {
			pos_y += speed+2;
			if (pos_y >= 450) {
				mode = 4;
			}
		}
		if (mode == 7) {
			pos_x = mouseX - 50;
			pos_y = mouseY - 60;
		}
	}

SettingHitBox:
	{
		//TowerHit and Mouse Hit
		if (mode == 3)
		{
		
			if (PushMouseInput(MOUSE_INPUT_LEFT))
			{
				if (CheckBoxHit(mouseX, mouseY, 1, 1, pos_x + 10, pos_y + 20, 110, 90)) {
					mode = 5;
				}
			}
		}
		//Check Mouse Warp Position
		if (mode == 7)
		{
			if (PushMouseInput(MOUSE_INPUT_RIGHT)) {
				if (((mouseX >= SCREEN_W / 2 - 130 && mouseX <= SCREEN_W / 2 + 90) || mouseY >= 500)) {
					return;
				}
				if (mouseY <= SCREEN_H / 2 + 50 && (mouseX < SCREEN_W / 2)) {
					spawn_pos = 0;
					mode = 6;

				}
				else if (mouseY <= SCREEN_H / 2 + 50 && (mouseX > SCREEN_W / 2)) {
					spawn_pos = 1;
					mode = 6;

				}
				else
				{
					if (mouseX < SCREEN_W / 2) {
						spawn_pos = 0;
						mode = 3;
					}
					if (mouseX > SCREEN_W / 2) {
						spawn_pos = 1;
						mode = 3;
					}
				}
			}
		}
	}
SettingAnimation: {
	if ((mode <= 3 && mode > 0) && spawn_pos == 0  || mode == 5 && spawn_pos == 0)
	{
		time_switch_image--;
		if (time_switch_image < 0) {
			time_switch_image = 59;
		}
		if (time_switch_image % 10 == 0) {
			image_index++;
			if (image_index > 5) {
				image_index = 3;
			}
		}
	}
	if ((mode <= 3 && mode > 0) && spawn_pos == 1 || mode == 5 && spawn_pos == 1)
	{
		time_switch_image--;
		if (time_switch_image < 0) {
			time_switch_image = 59;
		}
		if (time_switch_image % 10 == 0) {
			image_index++;
			if (image_index > 11) {
				image_index = 9;
			}
		}
	}
	}
}
//---------------------------------------------------------------------------------
//	ï`âÊèàóù
//---------------------------------------------------------------------------------
void Npc::Render()
{
	if (time_s % 20 >= 0 && time_s % 20 < 10)
	{
		if ((mode <= 4 && mode > 0) && spawn_pos == 0 || mode == 6 && spawn_pos == 0 || mode == 5 && spawn_pos == 0)
		{
		
			DrawGraph(pos_x, pos_y, image[image_index], TRUE);
		}
		if ((mode <= 4 && mode > 0) && spawn_pos == 1 || mode == 6 && spawn_pos == 1 || mode == 5 && spawn_pos == 1)
		{
			DrawGraph(pos_x, pos_y, image[image_index], TRUE);
		}
	}
}
//---------------------------------------------------------------------------------
//	èIóπèàóù
//---------------------------------------------------------------------------------
void Npc::Exit()
{
	for (int i = 0; i < 12; i++)DeleteGraph(image[i]);
}
