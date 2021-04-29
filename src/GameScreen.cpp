#include "raylib.h"
#include <stdlib.h>

#include "game.h"
#include "Screen.h"
#include "GameScreen.h"
#include "Sprite.h"
#include "utils.h"
#include "Scores.h"

void Game::GameScreen::Init() {
    //init attributes
    score = 0;
    frames = 0;
    live1 = 840.0f;
    catTexture = LoadTexture("./assets/graphics/cat.png");
    zucchiniTexture = LoadTexture("./assets/graphics/zucchini.png");
    heartTexture = LoadTexture("./assets/graphics/heart.png");
    sprite_bulletTexture = LoadTexture("./assets/graphics/sprite_bullet.png");
    bulletTexture = LoadTexture("./assets/graphics/bullet.png");

    //clear vectors
    sprites.clear();
    sprite_bullets.clear();
    lives.clear();

    //init bullet with null
    bullet = NULL;

    //create cat
    cat = new Sprite(catTexture, { (float) 10, (float)(Utils::ScreenHeight/2) }, true, 0, 3.0f, 32);
    
    //create lives
    for (int i = 0; i < 3; i++) {
    Sprite* live = new Sprite(heartTexture, { live1 - (40 * (i + 1)), (float)5 }, true, 0, 0, 16);
    lives.push_back(std::move(live));
    }

    //create enemies
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 12; y++) {
            unsigned int posX = (x + 1) * (Utils::SPRITE_WIDTH + Utils::SPACE);
            unsigned int posY = y * (Utils::SPRITE_HEIGHT + Utils::SPACE);
            Sprite* s = new Sprite(zucchiniTexture, { (float)(Utils::ScreenWidth - posX), (float)(posY + 45) }, true, 10, 0.05f, 32);
            sprites.push_back(std::move(s));
        }
    }
}

void Game::GameScreen::ProcessInput() {
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(0)) {
        if (IsMouseIn(mouse, 80, 125, 500, 520)) {
            //restart game
            Init();
            score = 0;
        } 
        else if (IsMouseIn(mouse, 750, 800, 50, 520)) {
            //return to main menu
            currentScreen = &menuScreen;
        }
        else if (bullet == NULL) {
            //cat-bullet created wih mouse click
            float bulletPosX = cat->pos.x + 12;
            float bulletPosY = cat->pos.y + 8;

            bullet = new Sprite(bulletTexture, { bulletPosX, bulletPosY }, true, 0, 5.0f, 16);
        }
    }

    //move the cat
    if (IsKeyDown(KEY_W)) {
        if (cat->pos.y >= 35)
            cat->MoveUp();
    }
    if (IsKeyDown(KEY_S)) {
        if (cat->pos.y <= Utils::ScreenHeight - 75) {
            cat->MoveDown();
        }
    }
}

void Game::GameScreen::Update() {
    
    if (sprites.empty() || lives.empty()) {
        //check if won
        if (sprites.empty()) {
            currentScreen = &winScreen;
        }

        //game over
        else {
            currentScreen = &loseScreen;
        }
        Scores* s = *scores;
        s->AddScore(score);
        s->WriteFile();
    }
    

    ManageCatBullets();

    ManageSpritesShootBack();

    MoveEnemies();
    
    //increment frames;
    frames++;
}

void Game::GameScreen::Draw() {
    ClearBackground(BLACK);
    Vector2 mouse = GetMousePosition();
    
    DrawText("Score", 120, 10, 25, LIGHTGRAY);
    DrawText("Lives", 650, 10, 25, LIGHTGRAY);
 
    if ((mouse.x > 80) && (mouse.y > 500) && (mouse.x < 125) && (mouse.y < 520)) {
        DrawText("New", 80, 500, 25, GREEN);
    }
    else {
        DrawText("New", 80, 500, 25, LIGHTGRAY);
    }
    
    if ((mouse.x > 750) && (mouse.y > 500) && (mouse.x < 800) && (mouse.y < 520)) {
        DrawText("Exit", 750, 500, 25, GREEN);
    }
    else {
        DrawText("Exit", 750, 500, 25, LIGHTGRAY);
    }

    //draw sprites
    cat->Draw();

    for (Sprite* live : lives) {
        live->Draw();
    }

    for (Sprite* s : sprites) {
        s->Draw();
    }

    if (bullet != NULL) bullet->Draw();

    for (Sprite* b : sprite_bullets) {
        b->Draw();
    }
    

    //Display Score 
    DrawText(itoa(score, groesse, 10), 210, 10, 25, LIGHTGRAY);
}

void Game::GameScreen::SetScore(Scores** scores) {
    this->scores = scores;
}

bool Game::GameScreen::CheckCollision(Sprite* s1, Sprite* s2) {
    return (s1->pos.x < s2->pos.x + s2->size && s1->pos.x + s1->size > s2->pos.x
        && s1->pos.y < s2->pos.y + s2->size && s1->pos.y + s1->size > s2->pos.y);
}

void Game::GameScreen::ManageCatBullets() {
    if (bullet != NULL) {
        bullet->MoveRight();
        //Collision detection
        bool destroyed = false;
        for (int j = sprites.size() - 1; j >= 0 && bullet != NULL; j--) {
            Sprite* s = sprites.at(j);
            if (CheckCollision(bullet, s)) {
                bullet = NULL;
                score += s->points;;
                sprites.erase(sprites.begin() + j);
                delete s;
            }
        }
        if (bullet != NULL && bullet->pos.x >= Utils::ScreenWidth) bullet = NULL;
    }
}

void Game::GameScreen::ManageSpritesShootBack() {
    //Check which enemies are allowed to shoot
    allowedToShotSprites.clear();
    if (frames % 100 == 0) {
        for (Sprite* s : sprites) {
            bool allowed = true;

            for (Sprite* c : sprites) {
                if (s->pos.y == c->pos.y) {
                    if (c->pos.x < s->pos.x) {
                        allowed = false;
                    }
                }
            }
            if (allowed) allowedToShotSprites.push_back(std::move(s));
        }
    }

    //randomly chose which sprites shoot
    int size = allowedToShotSprites.size();

    if (size > 0) {
        int random = GetRandomValue(0, size - 1);
        Sprite* shot = allowedToShotSprites.at(random);
        Sprite* b = new Sprite(sprite_bulletTexture, { shot->pos.x - 16, shot->pos.y + 8 }, true, 0, 5.0f, 16);
        sprite_bullets.push_back(std::move(b));
    }
}

void Game::GameScreen::MoveEnemies() {
    //move all enemy bullets & check if cat is hitted. then withdraw 1 live
    for (int i = sprite_bullets.size() - 1; i >= 0; i--) {
        bool hit = false;
        Sprite* sprite_bullet = sprite_bullets.at(i);
        
        //move
        sprite_bullet->MoveLeft();
        //check hit of cat
        if (CheckCollision(sprite_bullet, cat)) {
            lives.erase(lives.begin());
            sprite_bullets.erase(sprite_bullets.begin() + i);
        }
        //check if sprite bullet hits cat bullet
        if (bullet != NULL && CheckCollision(bullet, sprite_bullet)) {
            sprite_bullets.erase(sprite_bullets.begin() + i);
            bullet = NULL;
        }
    }

    //move the enemies
    for (int i = sprites.size() - 1; i >= 0; i--) {
        Sprite* sp = sprites.at(i);
        sp->MoveLeft();
        if (sp->pos.y <= 0) sprites.erase(sprites.begin() + i);
    }
}

bool Game::GameScreen::IsMouseIn(Vector2 mouse, int xMin, int xMax, int yMin, int yMax) {
    return (mouse.x > xMin) && (mouse.y > yMin) && (mouse.x < xMax) && (mouse.y < yMax);
}
