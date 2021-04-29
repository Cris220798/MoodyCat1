#include "Sprite.h"
#include "utils.h"

void Sprite::Draw(){
	if(visible)
		DrawTexture(texture, pos.x, pos.y, WHITE);
}

void Sprite::RandomPos() {
	pos = { (float)GetRandomValue(0, Utils::ScreenWidth-Utils::SPRITE_WIDTH-Utils::SPACE), 
		(float)GetRandomValue(0, Utils::ScreenHeight-Utils::SPRITE_HEIGHT-Utils::SPACE) };
}

void Sprite::MoveLeft() {
	pos.x -= speed;
}

void Sprite::MoveRight() {
	pos.x += speed;
}

void Sprite::MoveUp() {
	pos.y -= speed;
}

void Sprite::MoveDown() {
	pos.y += speed;
}

