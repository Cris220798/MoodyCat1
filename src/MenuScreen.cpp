#include "raylib.h"

#include "game.h"
#include "Screen.h"
#include "MenuScreen.h"

void Game::MenuScreen::ProcessInput() {
    Vector2 mouse = GetMousePosition();

    //start game
    if (IsMouseButtonPressed(0) && (mouse.y > 150) && (mouse.x < 600) && (mouse.y < 200)) {
        gameScreen.Init();
        currentScreen = &gameScreen;
    }

    //call highscore screen
    if (IsMouseButtonPressed(0) && (mouse.x > 355) && (mouse.y > 250) && (mouse.x < 605) && (mouse.y < 300)) {
        currentScreen = &scoreScreen;
    }

    //end game
    if (IsMouseButtonPressed(0) && (mouse.x > 360) && (mouse.y > 350) && (mouse.x < 600) && (mouse.y < 400)) {
        exit(0);
    }
}

void Game::MenuScreen::Update() {
    // TODO

}

void Game::MenuScreen::Draw() {
    ClearBackground(BLACK);
    DrawTexture(bg, 0, 0, RAYWHITE);
    
    DrawText("New Game", 360, 170, 50, LIGHTGRAY);
    DrawText("Highscore", 355, 270, 50, LIGHTGRAY);
    DrawText("Quit Game", 360, 370, 50, LIGHTGRAY);

    Vector2 mouse = GetMousePosition();

    if ((mouse.x > 360) && (mouse.y > 150) && (mouse.x < 600) && (mouse.y < 200)) {
        DrawText("New Game", 360, 170, 50, GREEN);
    }
    else if ((mouse.x > 355) && (mouse.y > 250) && (mouse.x < 605) && (mouse.y < 300)) {
        DrawText("Highscore", 355, 270, 50, GREEN);
    }
    else if ((mouse.x > 360) && (mouse.y > 350) && (mouse.x < 600) && (mouse.y < 400)) {
        DrawText("Quit Game", 360, 370, 50, GREEN);
    }
}

void Game::MenuScreen::Init() {
    bg = LoadTexture("./assets/graphics/backgrounds/mainMenuBG.png");
}