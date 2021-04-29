#pragma once

#include "Screen.h"
#include "GameScreen.h"
#include "MenuScreen.h"
#include "HighscoreScreen.h"
#include "LoseScreen.h"
#include "WinScreen.h"

extern Game::MenuScreen menuScreen;
extern Game::GameScreen gameScreen;
extern Game::HighscoreScreen scoreScreen;
extern Game::LoseScreen loseScreen;
extern Game::WinScreen winScreen;

extern Game::Screen* currentScreen;