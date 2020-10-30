#include <SDL.h>
#include <memory>
#include <Core/Initialize.h>

#if _SHATTERED_WINRT
#include <windows.h>

int fake_main(int argc, char** argv);
int real_main(int argc, char** argv);


int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    SDL_main_func mainFunc = fake_main;

    SDL_WinRTRunApp(mainFunc, nullptr);

    return 0;
}

int fake_main(int argc, char** argv)
{
    real_main(argc, argv);

    return 0;
}

int real_main(int argc, char** argv)
#elif _SHATTERED_WIN32 || _SHATTERED_MINGW
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#else
int main(int argc, char** argv)
#endif
{
    std::unique_ptr<ShatteredEngine_Core::Initialize> _initialize = std::make_unique<ShatteredEngine_Core::Initialize>();

    return 0;
}