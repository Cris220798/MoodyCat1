#pragma once

#include "Screen.h"

namespace Game {
    class MenuScreen : public Screen {
        void ProcessInput() override;

        void Update() override;

        void Draw() override;
    };
}
