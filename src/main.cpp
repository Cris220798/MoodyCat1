#include <cstdlib>

#include "raylib.h"

#include "config.h"
#include "helper.h"
#include "game.h"
#include "Scores.h"

Game::MenuScreen menuScreen;
Game::GameScreen gameScreen;
Game::HighscoreScreen scoreScreen;
Game::LoseScreen loseScreen;
Game::WinScreen winScreen;

Game::Screen* currentScreen = &menuScreen;

Scores scores = Scores();


int main() {
    // Enable config flags for resizable window and vertical synchro
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetWindowMinSize(Game::ScreenWidth / 2, Game::ScreenHeight / 2);
    // Set game to run at 60 frames-per-second
    SetTargetFPS(60);

    // Render texture initialization, used to hold the rendering result so we can easily resize it
    RenderTexture2D target = LoadRenderTexture(Game::ScreenWidth, Game::ScreenHeight);
    // Texture scale filter to use
    SetTextureFilter(target.texture, FILTER_BILINEAR);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Load your assets
    Texture2D texture = LoadTexture("assets/graphics/testimage.png");

    gameScreen.Init();
    gameScreen.SetScore(&scores);
    scores.Init();
    scores.ReadFile();
    scoreScreen.SetScores(&scores);

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Compute required framebuffer scaling
        float scale = min((float)GetScreenWidth() / Game::ScreenWidth, (float)GetScreenHeight() / Game::ScreenHeight);

        // ---------------------------------------------------------------------------------
        // Draw
        // ---------------------------------------------------------------------------------

        BeginDrawing();
        ClearBackground(BLACK); // Letterbox color

        // Draw everything in the render texture, note this will not be rendered on screen, yet
        BeginTextureMode(target);
        {
            //            // Your drawing code here...
            //            ClearBackground(WHITE);         // Clear render texture background color
            //            DrawText(TextFormat("Default Mouse: [%i , %i]", (int) mouse.x, (int) mouse.y), 350, 25, 20, BLUE);
            //            DrawText(TextFormat("Virtual Mouse: [%i , %i]", (int) virtualMouse.x, (int) virtualMouse.y), 350, 55, 20,
            //                     GREEN);
            //            DrawTexture(texture, 100, 100, WHITE);

            currentScreen->ProcessInput();
            currentScreen->Update();
            currentScreen->Draw();
        }

        EndTextureMode();

        // Draw RenderTexture2D to window, properly scaled
        DrawTexturePro(target.texture,
            { 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
            { (static_cast<float>(GetScreenWidth()) - ((float)Game::ScreenWidth * scale)) * 0.5f,
             (static_cast<float>(GetScreenHeight()) - ((float)Game::ScreenHeight * scale)) * 0.5f,
             (float)Game::ScreenWidth * scale, (float)Game::ScreenHeight * scale },
            { 0, 0 }, 0.0f, WHITE);

        EndDrawing();
    } // Main game loop end

    // De-Initialization here...

    // Unload render texture
    UnloadRenderTexture(target);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
