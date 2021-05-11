#pragma once

#include "raylib.h"
#include <iostream>

struct Sprite {
    Vector2 pos = {0.0f, 0.0f};
    Texture2D texture{};
    bool visible = true;
    Sprite() = default;
    int points;
    float speed;
    int height, width;

    explicit Sprite(Texture2D texture) : texture(texture) {}

    Sprite(Texture2D texture, Vector2 pos, bool visible, int points, float speed, int width, int height) : texture(texture), pos(pos), visible(visible), points(points), speed(speed), width(width), height(height) {}

    Sprite(Sprite && other)  noexcept : texture(other.texture), pos(other.pos), visible(other.visible) {}

    ~Sprite() = default;

    Sprite& operator=(const Sprite & other) = default;


    //~Sprite() { UnloadTexture(this->texture); }

    void Draw();

    void RandomPos();

    void MoveUp();

    void MoveDown();

    void MoveLeft();

    void MoveRight();

    //float getPosS();

};