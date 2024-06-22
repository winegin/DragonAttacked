#include "Main.h"
#include "Game.h"
#include "Tower.h"

void Tower::Init() {
	pos_x = SCREEN_W / 2;
	pos_y = 500;
	Box_X = SCREEN_W / 2 - 100;
	image = LoadGraph("data/Tower.png");
	HP = 50;
}	
void Tower::Update() {

}
void Tower::Render() {
	DrawExtendGraph(pos_x - 150, -40, pos_x + 150, pos_y + 80, image, TRUE);
	DrawLineBox(Box_X, 550, Box_X+200,580, GetColor(255,255,0));
	DrawFillBox(Box_X, 550, Box_X+HP*4, 580, GetColor(255, 255, 0));	
	DrawFormatString(Box_X + 50, 550, GetColor(0, 0, 255), "HP: %d", HP);
}
void Tower::Exit() {
	DeleteGraph(image);
}