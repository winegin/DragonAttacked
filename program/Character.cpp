#include "Main.h"
#include "Game.h"
#include "Character.h"
#include "Hit.h"


//---------------------------------------------------------------------------------
//	‰Šú‰»ˆ—
//---------------------------------------------------------------------------------
void Character::Init()
{
	pos_x = SCREEN_W / 2;
	pos_y = 100;
	LoadDivGraph("data/character.png", 3, 3, 1, 505 / 3, 212, image);
	LoadDivGraph("data/character2.png", 3, 3, 1, 505 / 3, 212, image2);
	portal_image = LoadGraph("data/portal1.png");
	index = 0;
	time = 59;
	face = 0;
	warpX = 0;
	warpY = 0;
	portal_size = 0;
	portal_change = 0;
}
//---------------------------------------------------------------------------------
//	XVˆ—
//---------------------------------------------------------------------------------
void Character::Update(int mouseX, int mouseY)
{
Character_Animation:
	{
		if (mouseX > SCREEN_W / 2) {
			face = 0;
		}
		else face = 1;
		time--;
		if (time < 0) {
			time = 59;
		}
		if (time % 10 == 0) {
			index++;
			if (index > 2) {
				index = 0;
			}

		}
	}
Character_Skill_Effect:
	{
		//Portal Set Position
		if (portal_change == 0&& portal_size == 0)
		{
			if (PushMouseInput(MOUSE_INPUT_LEFT)||( PushMouseInput(MOUSE_INPUT_RIGHT)))
			{
					warpX = mouseX;
					warpY = mouseY;
					portal_change = 1;
			}
			
		}
		//Open Portal
		if (portal_change == 1) {
			portal_size += 5;
			if (portal_size >= 60) {
				portal_size = 60;
				portal_change = 2;
			}
		}
		//Close Portal
		if (portal_change == 2) {
			portal_size-=5;
			if (portal_size <= 0) {
				portal_size = 0;
				portal_change = 0;
			}
		}
	}
}
//---------------------------------------------------------------------------------
//	•`‰æˆ—
//---------------------------------------------------------------------------------
void Character::Render()
{	
	DrawExtendGraph(warpX - portal_size*3, warpY - portal_size, warpX + portal_size*3, warpY + portal_size, portal_image, TRUE);
	if (face == 0)
		DrawExtendGraph(pos_x - 40, pos_y - 40, pos_x + 40, pos_y + 40, image[index], TRUE);
	if (face == 1)
		DrawExtendGraph(pos_x - 40, pos_y - 40, pos_x + 40, pos_y + 40, image2[index], TRUE);
}
//---------------------------------------------------------------------------------
//	I—¹ˆ—
//---------------------------------------------------------------------------------
void Character::Exit()
{
	for (int i = 0; i < 3; i++)DeleteGraph(image[i]);
}
