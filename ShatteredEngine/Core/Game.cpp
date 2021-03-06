//
// Shattered Engine
//
// Copyright (c) 2020 John (Linuxydable) Benard
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.c
//

#include "Game.h"

namespace ShatteredEngine::Core {
    Game::Game(std::string pWindowName) {
        std::setlocale(LC_ALL, ".UTF-8");
        SDL_Init(SDL_INIT_EVERYTHING);

        this->window = std::make_unique<Window>(pWindowName);
    }

    Game::~Game() {
        bgfx_shutdown();
        SDL_Quit();
    }

    void Game::run()
    {
        this->initialize();

        // TEMP
        bgfx_render_frame(-1);

        bgfx_init_t init;
        bgfx_init_ctor(&init);
        init.type = bgfx_renderer_type::BGFX_RENDERER_TYPE_DIRECT3D11;
        init.platformData.nwh = this->window->get_window_context().info.win.window;
        init.resolution.width = 500;
        init.resolution.height = 500;
        init.resolution.reset = BGFX_RESET_VSYNC;

        if (!bgfx_init(&init)) 
        {
            std::cerr << "BGFX cannot be initialized !!!" << std::endl;
            exit(1);
        }

        const bgfx_view_id_t defaultView = 0;

        bgfx_set_view_clear(defaultView, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x6495EDFF, 1.0f, 0);
        bgfx_set_view_rect(defaultView, 0, 0, 500, 500);


        while (true) {
            SDL_PollEvent(&this->event);

            if (this->event.type == SDL_QUIT) {
                break;
            }

            bgfx_touch(defaultView);

            this->update();
            this->render();

            bgfx_frame(false);
        }
        this->shutdown();
    }

	void Game::initialize()
	{
	}

	void Game::update()
	{
	}

	void Game::render()
	{
	}

    void Game::shutdown()
    {
    }
}
