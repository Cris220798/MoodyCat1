#pragma once

#include "Screen.h"

namespace Game {
    class LoseScreen : public Screen {
    public:
        Game::HighscoreScreen res;

        void setHighscore();

        void ProcessInput() override;

        void Update() override;

        void Draw() override;
    };
}