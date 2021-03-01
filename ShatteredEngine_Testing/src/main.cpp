#include <memory>
#include <Core/Game.h>
#include <Utils/Logs.h>

#include "MainGame.h"

using namespace ShatteredEngine::Utils;

int main(int argc, char** argv)
{
    Logs::WriteLog(Logs::LogType::INFO, "Initialization of the Engine.");
    std::unique_ptr<MainGame> game = std::make_unique<MainGame>("Hello Shattered Engine NEXT !");
    game->run();

    return 0;
}