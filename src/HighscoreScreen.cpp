#include "raylib.h"

#include <vector>
#include <algorithm>

#include "game.h"
#include "Screen.h"
#include "HighscoreScreen.h"

//Game::GameScreen pkt;
char gr[6];
unsigned int count = 0;

void Game::HighscoreScreen::ProcessInput() {
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(0) && (mouse.x > 750) && (mouse.y > 50) && (mouse.x < 800) && (mouse.y < 520)) {
        //Hier kommt man zum Hauptmenü zurück
        currentScreen = &menuScreen;
    }
}

void Game::HighscoreScreen::Update() {
    
}

void Game::HighscoreScreen::Draw() {
    ClearBackground(BLACK);
    Vector2 mouse = GetMousePosition();
    
    DrawText("Highscoreliste", 225, 10, 70, LIGHTGRAY);
    DrawText("Exit", 750, 500, 25, LIGHTGRAY);

    if ((mouse.x > 750) && (mouse.y > 500) && (mouse.x < 800) && (mouse.y < 520)) {
    DrawText("Exit", 750, 500, 25, GREEN);
    }
    DrawText("Platz", 230, 100, 25, LIGHTGRAY);
    DrawText("Punkte", 585, 100, 25, LIGHTGRAY);
    
    //Liste wird geschrieben
    for (int i = 0; i < 10 && i < scores->scores.size(); i++) {
        DrawText(itoa(i+1, gr, 10), 230, 130 + (i*35), 25, LIGHTGRAY);
        for (int j = 0; j < 65; j++) {
            DrawText(".", 255+(j*5), 130 + (i * 35), 25, LIGHTGRAY);
        }
        if (!scores->scores.empty() && scores->scores.size() - 1 >= i) {
            int current = scores->scores.at(i);
            DrawText(itoa(current, gr, 10), 585, 130 + (i * 35), 25, LIGHTGRAY);
        }
    } 
}

void Game::HighscoreScreen::SetScores(Scores* scores) {
    this->scores = scores;
}
