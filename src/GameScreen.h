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
        std::vector<Sprite> bullets;
        Sprite cat;
        //Sprite bullet;
        Sprite cloudPink1, cloudPink2, cloudYellow1, cloudYellow2;
        Snake snake;
        Sprite shieldSprite;
        Direction dir = DOWN;

        Texture2D background, sky;
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
        Texture2D cloudYellow, cloudPink;

        Sound catShoot, catHit, enemyShoot;

        Music music;
        bool playMusic = false;


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

        void MoveBackgrounds();
    };
}
