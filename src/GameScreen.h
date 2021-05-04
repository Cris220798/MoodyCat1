#pragma once

#include <vector>

#include "Screen.h"
#include "Sprite.h"
#include "Scores.h"
#include "Direction.h"
#include "Snake.h"


namespace Game {
    class GameScreen : public Screen {
    public:
        Scores* scores;
       
        std::vector<Sprite> sprites;
        std::vector<Sprite> sprite_bullets;
        std::vector<Sprite> lives;
        std::vector<Sprite> allowedToShotSprites;
        Sprite cat;
        Sprite bullet;
        Snake snake;
        Sprite shieldSprite;
        Direction dir = DOWN;

        Texture2D background;
        Texture2D catTexture;
        Texture2D zucchiniTexture;
        Texture2D heartTexture;
        Texture2D sprite_bulletTexture;
        Texture2D bulletTexture;
        Texture2D snakeTexture;
        Texture2D vacuumCleanerTexture;
        Texture2D balloonTexture;
        Texture2D milkTexture;
        Texture2D shieldTexture;


        int score;
        char groesse[6];
        float live1;
        unsigned int frames;
        unsigned int shield;


        void Init();

        void ProcessInput() override;

        void Update() override;

        void Draw() override;

        void SetScore(Scores* scores);

        bool CheckCollision(const Sprite& s1, const Sprite& s2);

        void ManageCatBullets();

        void ManageSpritesShootBack();

        void MoveEnemies();

        bool IsMouseIn(Vector2 mouse, int xMin, int xMax, int yMin, int yMax);

        void GameOver();

        void ManageSnake();
    };
}
