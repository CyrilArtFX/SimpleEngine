#include "Game.h"

int main(int argc, char** argv)
{
    auto& instance = Game::instance();
    bool isGameInit = instance.initialize();

    if (isGameInit)
    {
        instance.load();
        instance.loop();
        instance.unload();
    }

    instance.close();

    return 0;
}