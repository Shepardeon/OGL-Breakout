#pragma once

enum GameState
{
    ACTIVE,
    MENU,
    WIN
};

struct Game
{
    GameState state;
    bool keys[1024];
    unsigned int width, height;

    Game(unsigned int width, unsigned int height);
    ~Game();

    void init();
    void processInput(float dt);
    void update(float dt);
    void render();
};