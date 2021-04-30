#pragma once

#include "raylib.h"
#include "sprite.h"
#include <iostream>

struct Snake : public Sprite {
	int lives = 5;

	using Sprite::Sprite;
};
