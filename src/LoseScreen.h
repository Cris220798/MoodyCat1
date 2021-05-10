#pragma once

#include "Screen.h"
#include "raylib.h"

namespace Game {
    class LoseScreen : public Screen {
    public:
        Game::HighscoreScreen res;

        Music music;
        bool musicPlayed = false;

        void setHighscore();

        void ProcessInput() override;

        void Update() override;

        void Draw() override;
    };
}