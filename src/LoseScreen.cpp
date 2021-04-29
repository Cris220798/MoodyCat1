#include "raylib.h"

#include "game.h"
#include "Screen.h"
#include "LoseScreen.h"



void Game::LoseScreen::setHighscore() {
    //res.UpdatePkt();
}

void Game::LoseScreen::ProcessInput() {
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(0) && (mouse.x > 285) && (mouse.y > 200) && (mouse.x < 650) && (mouse.y < 260)) {
        //restart the game
        gameScreen.Init();
        currentScreen = &gameScreen;
        setHighscore();
    }
    else if (IsMouseButtonPressed(0) && (mouse.x > 410) && (mouse.y > 350) && (mouse.x < 540) && (mouse.y < 410)) {
        //return to main menu
        currentScreen = &menuScreen;
        setHighscore();
    }
}

void Game::LoseScreen::Update() {

}



void Game::LoseScreen::Draw() {
    ClearBackground(BLACK);
    Vector2 mouse = GetMousePosition();

    DrawText("You Failed", 90, 10, 150, LIGHTGRAY);
    DrawText("Play Again", 285, 200, 70, LIGHTGRAY);
    DrawText("Exit", 410, 350, 70, LIGHTGRAY);

    if ((mouse.x > 285) && (mouse.y > 200) && (mouse.x < 650) && (mouse.y < 260)) {
        DrawText("Play Again", 285, 200, 70, GREEN);
    }
    else if ((mouse.x > 410) && (mouse.y > 350) && (mouse.x < 540) && (mouse.y < 410)) {
        DrawText("Exit", 410, 350, 70, GREEN);
    }
    
}