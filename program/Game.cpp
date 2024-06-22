#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"

#include "Character.h"
#include "Npc.h"
#include "Npc2.h"
#include "Npc3.h"
#include "Tower.h"
#include "DefenseGate.h"

const int NPC_MAX = 10;

int time_spawn[3];


int is_portal;
int gate_num;

int npc_num[3];
int count_npc_disappear;

int mouseX;
int mouseY;
int mouse_mode;

//	クラスの宣言
Character	character;
Npc npc[NPC_MAX];
Npc2 npc2[NPC_MAX];
Npc3 npc3[NPC_MAX];
Tower tower;
Defense gateD;
//Background
int background;
int background2;
int background3;
int background4;
int screen_mode;
bool fade_effect;
int fade_alpha_x;
int fade_alpha_y;
int fade_speed;
//Other
int textWidth;
int textX;
int textY;
int score;
int color[3];
void GetTextLength(const char* text, int size, int textx, int texty) {
	textWidth = GetDrawStringWidth(text, strlen(text), size);
	textX = textx;
	textY = texty;
}
bool CheckMouseHitText(int mouse_x, int mouse_y, int x, int y, int size) {
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		if (mouse_x >= x && mouse_x <= x + textWidth &&
			mouse_y >= y && mouse_y <= y + size) {
			return true;
		}
		else return false;
	}
}
bool IsMouseHitText(int mouse_x, int mouse_y, int x, int y, int size) {

	if (mouse_x >= x && mouse_x <= x + textWidth &&
		mouse_y >= y && mouse_y <= y + size) {
		return true;
	}
	else return false;
}
void MouseHitText(int i) {
	if (CheckMouseHitText(mouseX, mouseY, textX, textY, 24)) {
		fade_effect = true;
	}
	if (IsMouseHitText(mouseX, mouseY, textX, textY, 24)) {
		color[i] = GetColor(255, 0, 0);
	}
	else color[i] = GetColor(255, 255, 0);
}

enum SCREEN {
	BEGIN,
	INGAME,
	GAME_CLEAR,
	GAME_OVER,
};

void GameInit()
{
	//Setting Number of NPC
	npc_num[0] = 0;
	npc_num[1] = 0;
	npc_num[2] = 0;
	//Setting Time Spawn
	time_spawn[0] = GetRand(120) + 120;
	time_spawn[1] = GetRand(120) + 180;
	time_spawn[2] = GetRand(120) + 120;

	//Setting Character
	character.Init();
	is_portal = false;
	//Setting Background
	background = LoadGraph("data/background.jpg");
	background2 = LoadGraph("data/BG2.jpg");
	background3 = LoadGraph("data/GameOver.jpg");
	background4 = LoadGraph("data/GameCLear.jpg");
	//Setting NPC
	for (int i = 0; i < 10; i++) {
		npc[i].Init();
		npc2[i].Init();
		npc3[i].Init();


	}
	count_npc_disappear = 0;
	//Setting Tower
	tower.Init();
	screen_mode = BEGIN;
	//Setting Defense
		gateD.Init();
	gate_num = 0;
SCREEN_INIT:
	{
		screen_mode = BEGIN;
		fade_effect = false;
		fade_alpha_x = 0;
		fade_alpha_y = 0;
		fade_speed = 10;
	}

ORTHER_INIT:
	{
		//Orther Setting
		score = 1;
		for (int i = 0; i < 3; i++)
		{
			color[i] = GetColor(255, 0, 0);
		}
	}
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void gamereset() {
	character.portal_size = 0;
	tower.HP = 50;
	count_npc_disappear = 0;
	for(int i = 0; i < 3; i ++)
	gateD.combo_hit[i] = 0;
	for (int i = 0; i < NPC_MAX; i++) {
		npc[i].mode = 0;
		npc2[i].mode = 0;
		npc3[i].mode = 0;
	}

}
void GameUpdate()
{
	//Get Mouse Position
	mouseX = GetMouseX();
	mouseY = GetMouseY();

	switch (screen_mode)
	{
	case BEGIN:
	{
		GetTextLength("Game Start", 24, SCREEN_W / 2 - 80, SCREEN_H / 2 - 30);
		MouseHitText(0);
		if (fade_alpha_x > SCREEN_W && fade_effect == true) {
			screen_mode = INGAME;
		}
		GetTextLength("Exit Game", 24, SCREEN_W / 2 - 75, SCREEN_H / 2 + 20);
		MouseHitText(1);
		if (CheckMouseHitText(mouseX, mouseY, textX, textY, 24)) {
			exit('0');
		}
		break;
	}
	case INGAME: {
	Game_Update:
		{
			if (fade_effect == false)
			{
				//Update Tower
				tower.Update();
				//If OrtherGate is used
				if (PushMouseInput(MOUSE_INPUT_LEFT)) {
					for (int i = 0; i < NPC_MAX; i++) {
						if (npc[i].mode == 7 || npc2[i].mode == 7 || character.portal_change != 0) {
							return;
						}

					}
				}
				is_portal = false;
				for (int i = 0; i < NPC_MAX; i++) {
					if (npc[i].mode == 7 || npc2[i].mode == 7) {
						is_portal = true;
					}
				}

				//Update Character
				character.Update(mouseX, mouseY);
				//Update NPCs
				for (int i = 0; i < NPC_MAX; i++) {
					npc[i].Update(mouseX, mouseY);
					npc2[i].Update(mouseX, mouseY);
					npc3[i].Update();

				}
			}
		}
	Spawn_Time:
		{
			//UnderGround Spawn
			{
				time_spawn[0]--;
				if (time_spawn[0] <= 0) {
					npc[npc_num[0]].mode = 1;
					npc_num[0]++;
					if (npc_num[0] > 9) {
						npc_num[0] = 0;
					}
					time_spawn[0] = GetRand(180) + 120;
				}
			}
			//Flying Spawn
			{
				time_spawn[1]--;
				if (time_spawn[1] <= 0) {
					npc2[npc_num[1]].mode = 1;
					npc_num[1]++;
					if (npc_num[1] > 9) {
						npc_num[1] = 0;
					}
					time_spawn[1] = GetRand(120) + 180;
				}
			}
			//Delay Spawn
			{
				time_spawn[2]--;
				if (time_spawn[2] <= 0) {
					npc3[npc_num[2]].mode = 1;
					npc_num[2]++;
					if (npc_num[2] > 9) {
						npc_num[2] = 0;
					}
					time_spawn[2] = GetRand(120) + 180;
				}

			}
		}

	Npc2_Hit_Npc2_Rules:
		{
			for (int i = 0; i < NPC_MAX; i++) {

				for (int j = 0; j < NPC_MAX; j++) {
					if (npc2[i].mode == 3 && npc2[j].mode == 3)
					{
						if (j != i) {
							if (CheckBoxHit(npc2[i].pos_x - 10, npc2[i].pos_y, 40, 30, npc2[j].pos_x - 10, npc2[j].pos_y, 40, 30)) {
								npc2[i].mode = 4;
								npc2[j].mode = 4;
							}
						}
					}
				}
			}
		}
	Npc_Hit_Npc2_Rules:
		{
			for (int i = 0; i < NPC_MAX; i++) {
				for (int j = 0; j < NPC_MAX; j++) {
					if (npc2[i].mode == 3 && npc[j].mode == 6) {
						if (CheckBoxHit(npc2[i].pos_x - 10, npc2[i].pos_y, 40, 40, npc[j].pos_x - 10, npc[j].pos_y, 40, 40)) {
							npc2[i].mode = 6;
							npc[j].mode = 6;
						}
					}
				}
			}
		}
	Npc3_Hit_Gate_Rules:
		{
			if (gateD.is_gate1 == false && (gateD.combo_hit[0] > 1|| gateD.combo_hit[1] > 1|| gateD.combo_hit[2] > 1))
			{
				if (PushHitKey(KEY_INPUT_R)) {

					gateD.is_gate1 = true;
				
				}
			}

			for (int j = 0; j < NPC_MAX; j++)
			{
				if(gateD.is_gate1 == true)
				{
					if (npc3[j].spawn_posX == 0 && npc3[j].mode == 5)
					{
						if (CheckBoxHit(npc3[j].pos_x - 10, npc3[j].pos_y, 10, 40, gateD.pos_x - 100, gateD.pos_y - 100, 50, 150)) {
							npc3[j].pos_x = SCREEN_W / 2 + 100;
						}
					}
					if (npc3[j].spawn_posX == 1 && npc3[j].mode == 5)
					{
						if (CheckBoxHit(npc3[j].pos_x - 10, npc3[j].pos_y, 40, 40, gateD.pos_2x - 50, gateD.pos_2y - 100, 50, 150)) {
							npc3[j].pos_x = SCREEN_W / 2 - 225;
						}
					}
				}
		
			}
		}
	NPCs_Hit_Tower:
		{
			for (int i = 0; i < NPC_MAX; i++)
			{
				if (npc[i].mode == 3)
				{
					if ((npc[i].pos_x >= SCREEN_W / 2 - 170 && npc[i].pos_x <= SCREEN_W / 2 + 20)) {
						tower.HP -= 10;
						npc[i].mode = 0;
					}
				}
				if (npc2[i].mode == 3)
				{
					if ((npc2[i].pos_x >= SCREEN_W / 2 - 170 && npc2[i].pos_x <= SCREEN_W / 2 + 20)) {
						tower.HP -= 10;
						npc2[i].mode = 0;
					}
				}
				if (npc3[i].mode == 5)
				{
					if ((npc3[i].pos_x >= SCREEN_W / 2 - 150 && npc3[i].pos_x <= SCREEN_W / 2 )) {
						tower.HP -= 5;
						npc3[i].mode = 0;
					}
				}
			}
		}
	Count_Npc_Disappear:
		{
			for (int i = 0; i < NPC_MAX; i++)
			{
				if ((npc2[i].pos_x <= -150 || npc2[i].pos_x >= SCREEN_W + 50)) {
					count_npc_disappear += 1;
					npc2[i].mode = 0;
				}
				if ((npc3[i].pos_x <= -150 || npc3[i].pos_x >= SCREEN_W + 50)) {
					count_npc_disappear += 1;
					npc3[i].mode = 0;
				}
				if ((npc2[i].mode == 4 && npc2[i].time_s == 1) || (npc[i].mode == 4 && npc[i].time_s == 1))
				{
					count_npc_disappear += 1;
				}
			}
		}
	Game_Clear_Rules:
		{
			if (count_npc_disappear >= 5) {
				fade_effect = true;

			}
			if (fade_alpha_x > SCREEN_W && fade_effect == true && count_npc_disappear >= 10) {

				screen_mode = GAME_CLEAR;
			}
		}
	Game_Over_Rules:
		{
			if (tower.HP <= 0) {
				fade_effect = true;
			}
			if (fade_alpha_x > SCREEN_W && fade_effect == true && tower.HP == 0) {
				screen_mode = GAME_OVER;
			}
		}
	Defense_Gate: {
		
			gateD.Update();
		}
	break;
	case GAME_CLEAR:
	{

		GetTextLength("Play Again", 24, SCREEN_W / 2 - 85, SCREEN_H / 2 + 80);
		MouseHitText(0);

		GetTextLength("Exit Game", 24, SCREEN_W / 2 - 80, SCREEN_H / 2 + 120);
		MouseHitText(1);
		if (CheckMouseHitText(mouseX, mouseY, textX, textY, 24)) {
			exit('0');
		}
		if (fade_alpha_x == SCREEN_W) {
			gamereset();
			screen_mode = INGAME;
		}
		break;
	}

	case GAME_OVER:
	{

		GetTextLength("Play Again", 24, SCREEN_W / 2 - 85, SCREEN_H / 2 + 80);
		MouseHitText(0);

		GetTextLength("Exit Game", 24, SCREEN_W / 2 - 80, SCREEN_H / 2 + 120);
		MouseHitText(1);
		if (CheckMouseHitText(mouseX, mouseY, textX, textY, 24)) {
			exit('0');
		}

		if (fade_alpha_x == SCREEN_W) {
			
			gamereset();
			screen_mode = INGAME;
		}
		break;
	}
	}

	}

FADE_EFFECT:
	{
		if (fade_effect == true) {
			fade_alpha_x += fade_speed;
		}
		if (fade_alpha_x > SCREEN_W * 2) {
			fade_alpha_x = 0;
			fade_effect = false;
		}
	}

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void DrawGamePlay() {
	//Draw Background
	DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H + 80, background, TRUE);

	//Draw Tower
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	tower.Render();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//Draw NPC
	for (int i = 0; i < 10; i++) {
		npc[i].Render();
		npc2[i].Render();
		npc3[i].Render();
	}
	//Draw Gate
		gateD.Render();
	//Draw Character
	character.Render();
}
void GameRender()
{
	switch (screen_mode)
	{
	case BEGIN:
	{
		DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, background2, TRUE);
		SetFontSize(48);
		DrawString(SCREEN_W / 2 - 150, 100, " ", GetColor(25, 250, 25));
		SetFontSize(24);
		DrawString(SCREEN_W / 2 - 80, SCREEN_H / 2 - 30, "Game Start", color[0]);
		DrawString(SCREEN_W / 2 - 75, SCREEN_H / 2 + 20, "Exit Game", color[1]);

		if (fade_alpha_x < SCREEN_W * 2 && fade_effect == true) {
			DrawFillBox(fade_alpha_x - SCREEN_W, fade_alpha_y, fade_alpha_x, fade_alpha_y + SCREEN_H, GetColor(0, 0, 0));
		}

		break;
	}

	case INGAME:
	{
		if (fade_alpha_x < SCREEN_W)
		{
			DrawGamePlay();
			DrawFillBox(fade_alpha_x - SCREEN_W, fade_alpha_y, fade_alpha_x, fade_alpha_y + SCREEN_H, GetColor(0, 0, 0));
			if (is_portal == true)
			{
				DrawCircle(SCREEN_W / 2 - 3, 15, 15, GetColor(255, 0, 0), TRUE);
			}
		}
		if (fade_alpha_x > SCREEN_W) {
			DrawGamePlay();
			DrawFillBox(fade_alpha_x - SCREEN_W, fade_alpha_y, fade_alpha_x, fade_alpha_y + SCREEN_H, GetColor(0, 0, 0));

		}
		break;
	}
	case GAME_CLEAR:
	{
		DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, background4, TRUE);
		SetFontSize(48);
		DrawString(SCREEN_W / 2 - 130, SCREEN_H / 2 - 50, "GAME CLEAR", GetColor(25, 250, 25));

		SetFontSize(24);
		DrawFormatString(SCREEN_W / 2 - 90, SCREEN_H / 2 + 30, GetColor(0, 0, 255), "Score: %d", 99999);

		DrawString(SCREEN_W / 2 - 85, SCREEN_H / 2 + 80, "Play Again", color[0]);
		DrawString(SCREEN_W / 2 - 80, SCREEN_H / 2 + 120, "Exit Game", color[1]);
		if (fade_alpha_x < SCREEN_W * 2 && fade_effect == true) {
			DrawFillBox(fade_alpha_x - SCREEN_W, fade_alpha_y, fade_alpha_x, fade_alpha_y + SCREEN_H, GetColor(0, 0, 0));
		}
		break;
	}
	case GAME_OVER:
	{
		DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, background3, TRUE);
		SetFontSize(48);
		DrawString(SCREEN_W / 2 - 125, SCREEN_H / 2 - 50, "GAME OVER", GetColor(25, 250, 25));

		SetFontSize(24);
		DrawFormatString(SCREEN_W / 2 - 90, SCREEN_H / 2 + 30, GetColor(0, 0, 255), "Score: %d", score*200* count_npc_disappear);

		DrawString(SCREEN_W / 2 - 85, SCREEN_H / 2 + 80, "Play Again", color[0]);
		DrawString(SCREEN_W / 2 - 80, SCREEN_H / 2 + 120, "Exit Game", color[1]);
		if (fade_alpha_x < SCREEN_W * 2 && fade_effect == true) {
			DrawFillBox(fade_alpha_x - SCREEN_W, fade_alpha_y, fade_alpha_x, fade_alpha_y + SCREEN_H, GetColor(0, 0, 0));
		}
		break;
	}
	}
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	for (int i = 0; i < 10; i++) {
		npc[i].Exit();
		npc2[i].Exit();
	}
	character.Exit();
	tower.Exit();
}
