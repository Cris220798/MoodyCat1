#pragma once

#include "Screen.h"
#include "raylib.h"

namespace Game {
    class MenuScreen : public Screen {
    public:
        Texture2D bg;
        void Init();

        void ProcessInput() override;

        void Update() override;

        void Draw() override;
    };
}
