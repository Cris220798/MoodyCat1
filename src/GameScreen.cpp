#include "raylib.h"
#include <stdlib.h>

#include "game.h"
#include "Screen.h"
#include "GameScreen.h"
#include "Sprite.h"
#include "utils.h"
#include "Scores.h"
#include "Snake.h"

void Game::GameScreen::Init() {
    //init attributes
    score = 0;
    frames = 0;
    shield = 0;
    live1 = 840.0f;
    catTexture = LoadTexture("./assets/graphics/cat.png");
    zucchiniTexture = LoadTexture("./assets/graphics/zucchini.png");
    heartTexture = LoadTexture("./assets/graphics/heart.png");
    sprite_bulletTexture = LoadTexture("./assets/graphics/sprite_bullet.png");
    bulletTexture = LoadTexture("./assets/graphics/bullet.png");
    vacuumCleanerTexture = LoadTexture("./assets/graphics/vacuumCleaner.png");
    snakeTexture = LoadTexture("./assets/graphics/snake.png");
    balloonTexture = LoadTexture("./assets/graphics/balloon.png");
    milkTexture = LoadTexture("./assets/graphics/milk.png");
    shieldTexture = LoadTexture("./assets/graphics/newShield.png");
    background = LoadTexture("./assets/graphics/backgrounds/background.png");
    sky = LoadTexture("./assets/graphics/backgrounds/sky.png");
    cloudYellow = LoadTexture("./assets/graphics/backgrounds/cloudYellow.png");
    cloudPink = LoadTexture("./assets/graphics/backgrounds/cloudPink.png");

    catHit = LoadSound("./assets/audio/sfx/catHit.wav");
    catShoot = LoadSound("./assets/audio/sfx/catShoot.wav");
    enemyShoot = LoadSound("./assets/audio/sfx/enemyShoot.wav");

    music = LoadMusicStream("./assets/audio/tracks/inGame.mp3");
    

    //clear vectors
    sprites.clear();
    sprite_bullets.clear();
    lives.clear();

    //init clouds
    Vector2 cloudYellow1Pos = { 0, 0 };
    cloudYellow1 = Sprite(cloudYellow, cloudYellow1Pos, true, 0, 0.5, 540);
    Vector2 cloudYellow2Pos = { Utils::ScreenWidth-1, 0 };
    cloudYellow2 = Sprite(cloudYellow, cloudYellow2Pos, true, 0, 0.5, 540);

    Vector2 cloudPink1Pos = { 0, 0 };
    cloudPink1 = Sprite(cloudPink, cloudPink1Pos, true, 0, 0.2, 540);
    Vector2 cloudPink2Pos = { Utils::ScreenWidth - 1, 0 };
    cloudPink2 = Sprite(cloudPink, cloudPink2Pos, true, 0, 0.2, 540);

    //init snake
    Vector2 snakePos = { -200, -200 };
    this->snake = Snake(snakeTexture, snakePos, false, 100, 2.0f, 16);

    //init bullet with null
    Vector2 bulletPos = { -100, -100 };
    this->bullet = Sprite(bulletTexture, bulletPos , false, 0, 7.0f, 16);

    //create cat
    Vector2 catPos = { (float)10, (float)(Utils::ScreenHeight / 2) };
    this->cat = Sprite(catTexture, catPos, true, 0, 3.0f, 32);

    //create shield
    Vector2 shieldPos = {catPos.x + cat.size, catPos.y};
    this->shieldSprite = Sprite(shieldTexture, catPos, false, 0, 3.0f, 32);
    
    //create lives
    for (int i = 0; i < 3; i++) {
        Vector2 pos = { live1 - (40 * (i + 1)), (float)5 };
        lives.emplace_back(heartTexture, pos , true, 0, 0, 16);
    }

    //create enemies
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 7; y++) {
            unsigned int posX = (x + 1) * (Utils::SPRITE_WIDTH + Utils::SPACE);
            unsigned int posY = y * (Utils::SPRITE_HEIGHT + Utils::SPACE);
            Vector2 pos = { (float)(Utils::ScreenWidth - 60 - posX), (float)(posY + 130) };
            int rand = GetRandomValue(1, 100);
            if (rand >= 1 && rand <= 20) {
                sprites.emplace_back(vacuumCleanerTexture, pos, true, 40, 1.0f, 32);
            }
            else if (rand > 20 && rand <= 50) {
                sprites.emplace_back(balloonTexture, pos, true, 20, 1.0f, 32);
            }
            else if (rand > 50 && rand <= 55) {
                sprites.emplace_back(milkTexture, pos, true, -1, 1.0f, 32);
            }
            else {
                sprites.emplace_back(zucchiniTexture, pos, true, 10, 1.0f, 32);
            }
            
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
        else if (!bullet.visible) {
            //cat-bullet created wih mouse click
            float bulletPosX = cat.pos.x + 12;
            float bulletPosY = cat.pos.y + 8;

            bullet.pos = { bulletPosX, bulletPosY };
            bullet.visible = true;
            PlaySound(catShoot);
        }
    }

    //move the cat & shield
    if (IsKeyDown(KEY_W)) {
        if (cat.pos.y >= 135) {
            cat.MoveUp();
            shieldSprite.MoveUp();
        }
            

    }
    if (IsKeyDown(KEY_S)) {
        if (cat.pos.y <= Utils::ScreenHeight - 75) {
            cat.MoveDown();
            shieldSprite.MoveDown();
        }
    }
}

void Game::GameScreen::Update() {

    if (!playMusic) {
        
        PlayMusicStream(music);
        playMusic = true;
        std::cout << "play" << std::endl;
    }
    UpdateMusicStream(music);

    //move backgrounds
    MoveBackgrounds();
    
    //check if won
    if (sprites.empty()) {
        currentScreen = &winScreen;
        scores->AddScore(score);
        scores->WriteFile();
    }
    else if (lives.empty()) {
        GameOver();
    }    

    ManageCatBullets();

    ManageSpritesShootBack();

    MoveEnemies();

    ManageSnake();
    
    //increment frames;
    frames++;

    //manage shield
    if (shield > 0) shield--;
    if (shield <= 0) shieldSprite.visible = false;
}

void Game::GameScreen::Draw() {
    ClearBackground(BLACK);
    Vector2 mouse = GetMousePosition();

    DrawTexture(sky, 0, 0, RAYWHITE);

    cloudPink1.Draw();
    cloudPink2.Draw();

    cloudYellow1.Draw();
    cloudYellow2.Draw();

    DrawTexture(background, 0, 0, RAYWHITE);
    
    DrawText("Score", 120, 10, 25, BLACK);
    if(shield > 0) DrawText("Shield active", 400, 10, 25, BLACK);
    DrawText("Lives", 650, 10, 25, BLACK);
 
    if ((mouse.x > 80) && (mouse.y > 500) && (mouse.x < 125) && (mouse.y < 520)) {
        DrawText("New", 80, 500, 25, GREEN);
    }
    else {
        DrawText("New", 80, 500, 25, BLACK);
    }
    
    if ((mouse.x > 750) && (mouse.y > 500) && (mouse.x < 800) && (mouse.y < 520)) {
        DrawText("Exit", 750, 500, 25, GREEN);
    }
    else {
        DrawText("Exit", 750, 500, 25, BLACK);
    }

    //draw sprites
    cat.Draw();

    for (Sprite &live : lives) {
        live.Draw();
    }

    for (Sprite &s : sprites) {
        s.Draw();
    }

    if (bullet.visible) bullet.Draw();

    for (Sprite &b : sprite_bullets) {
        b.Draw();
    }

    if (shieldSprite.visible) shieldSprite.Draw();

    snake.Draw();

    //Display Score 
    DrawText(itoa(score, groesse, 10), 210, 10, 25, LIGHTGRAY);
}

void Game::GameScreen::SetScore(Scores* scores) {
    this->scores = scores;
}

bool Game::GameScreen::CheckCollision(const Sprite& s1, const Sprite& s2) {
    return (s1.pos.x < s2.pos.x + s2.size && s1.pos.x + s1.size > s2.pos.x
        && s1.pos.y < s2.pos.y + s2.size && s1.pos.y + s1.size > s2.pos.y);
}

void Game::GameScreen::ManageCatBullets() {
    if (bullet.visible) {
        bullet.MoveRight();
        //Collision detection
        for (int j = sprites.size() - 1; j >= 0 && bullet.visible; j--) {
            const Sprite& s = sprites.at(j);
            if (CheckCollision(bullet, s)) {
                bullet.visible = false;
                bullet.pos = { -100, -100 };
                if (s.points == -1) {
                    shield += 250;
                    shieldSprite.visible = true;
                }
                else score += s.points;
                sprites.erase(sprites.begin() + j);
            }
        }
        if (bullet.visible && bullet.pos.x >= Utils::ScreenWidth) bullet.visible = false;
    }
}

void Game::GameScreen::ManageSpritesShootBack() {
    //Check which enemies are allowed to shoot
    allowedToShotSprites.clear();
    if (frames % 100 == 0) {
        for (Sprite &s : sprites) {
            bool allowed = true;

            for (Sprite &c : sprites) {
                if (s.pos.y == c.pos.y) {
                    if (c.pos.x < s.pos.x) {
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
        Sprite &shot = allowedToShotSprites.at(random);
        Vector2 pos = { shot.pos.x - 16, shot.pos.y + 8 };
        sprite_bullets.emplace_back(sprite_bulletTexture, pos, true, 0, 5.0f, 16);
        PlaySound(enemyShoot);
    }
}

void Game::GameScreen::MoveEnemies() {
    //move all enemy bullets & check if cat is hitted. then withdraw 1 live
    for (int i = sprite_bullets.size() - 1; i >= 0; i--) {
        bool hit = false;
        Sprite& sprite_bullet = sprite_bullets.at(i);
        
        //move
        sprite_bullet.MoveLeft();
        //check hit of shield
        if (shield > 0 && CheckCollision(sprite_bullet, shieldSprite)) {
            sprite_bullets.erase(sprite_bullets.begin() + i);
        }
        //check hit of cat
        if (CheckCollision(sprite_bullet, cat) && shield <= 0) {
            PlaySound(catHit);
            lives.erase(lives.begin());
            sprite_bullets.erase(sprite_bullets.begin() + i);
        }
        //check if sprite bullet hits cat bullet
        if (bullet.visible && CheckCollision(bullet, sprite_bullet)) {
            sprite_bullets.erase(sprite_bullets.begin() + i);
            bullet.visible = false;
        }
        //check if bullet leaves screen
        if(sprite_bullet.pos.x < -sprite_bullet.size)
            sprite_bullets.erase(sprite_bullets.begin() + i);
    }

    //check direction
    bool found = false;
    Direction oldDir = dir;
    Direction newDir;
    for (int i = 0; !found && i < sprites.size(); i++) {
        Sprite& sp = sprites.at(i);
        if (dir == UP && sp.pos.y - sp.speed <= 135 || dir == DOWN && sp.pos.y + sp.size + sp.speed >= Utils::ScreenHeight - 45) {
            if (oldDir == UP) newDir = DOWN;
            else newDir = UP;
            dir = LEFT;
            found = true;
        }
    }

    //move the enemies
    for (int i = sprites.size() - 1; i >= 0; i--) {
        Sprite &sp = sprites.at(i);
        int spLeft = (sprites.size() / 7);
        if (dir == LEFT) sp.speed = 20.0f;
        else sp.speed = 0.3f + 0.7f - (float)spLeft/10;
        switch (dir) {
            case LEFT: sp.MoveLeft(); break;
            case RIGHT: sp.MoveRight(); break;
            case UP: sp.MoveUp(); break;
            case DOWN: sp.MoveDown(); break;
            default: break;
        } 
        //check if enemies are too close
        if (sp.pos.x <= Utils::ScreenWidth / 3) GameOver();
    }

    if (dir == LEFT) dir = newDir;
}

bool Game::GameScreen::IsMouseIn(Vector2 mouse, int xMin, int xMax, int yMin, int yMax) {
    return (mouse.x > xMin) && (mouse.y > yMin) && (mouse.x < xMax) && (mouse.y < yMax);
}

void Game::GameScreen::GameOver() {
    currentScreen = &loseScreen;
    scores->AddScore(score);
    scores->WriteFile();
}

void Game::GameScreen::ManageSnake() {
    if (frames != 0 && frames % 2000 == 0 && !snake.visible && snake.lives > 0) {
        snake.visible = true;
        snake.pos = { Utils::ScreenWidth - 30, Utils::ScreenHeight };
    }

    if (snake.visible) {
        snake.MoveUp();
        
        if (bullet.visible && CheckCollision(bullet, snake)) {
            snake.lives--;
        }

        if (snake.pos.y - snake.size < 0) {
            snake.visible = false;
        }   
    }
}

void Game::GameScreen::MoveBackgrounds() {
    if (cloudYellow1.pos.x + Utils::ScreenWidth - cloudYellow1.speed < 0) cloudYellow1.pos.x = Utils::ScreenWidth-1;
    cloudYellow1.MoveLeft();
    if (cloudYellow2.pos.x + Utils::ScreenWidth - cloudYellow2.speed < 0) cloudYellow2.pos.x = Utils::ScreenWidth-1;
    cloudYellow2.MoveLeft();

    if (cloudPink1.pos.x + Utils::ScreenWidth - cloudPink1.speed < 0) cloudPink1.pos.x = Utils::ScreenWidth - 1;
    cloudPink1.MoveLeft();
    if (cloudPink2.pos.x + Utils::ScreenWidth - cloudPink2.speed < 0) cloudPink2.pos.x = Utils::ScreenWidth - 1;
    cloudPink2.MoveLeft();
}
