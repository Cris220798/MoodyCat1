#pragma once

#include "Screen.h"

namespace Game {
    class WinScreen : public Screen {
    public:

        void ProcessInput() override;

        void Update() override;

        void Draw() override;
    };
}