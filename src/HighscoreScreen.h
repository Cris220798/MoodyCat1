#pragma once

#include "Screen.h"
#include "Scores.h"

namespace Game {
    class HighscoreScreen : public Screen {
    public:
        Scores** scores;

        void ProcessInput() override;

        void Update() override;

        void Draw() override;

        void SetScores(Scores** scores);

    };
}