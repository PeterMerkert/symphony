#include "SymphonyEngine.h"

#include <iostream>
#include <sstream>
#include "Screen.h"

namespace Symphony
{
    SymphonyEngine* SymphonyEngine::instance = nullptr;
    GameTimer* SymphonyEngine::gameTimer = nullptr;
    Keyboard* SymphonyEngine::keyboard = nullptr;
    Mouse* SymphonyEngine::mouse = nullptr;
    
    SymphonyEngine::SymphonyEngine()
    {
        windowManager   = new WindowManager();
        gameTimer       = new GameTimer();
        keyboard        = new Keyboard();
        mouse           = new Mouse();
        gameLoopIsActive = true;
    }

    SymphonyEngine::~SymphonyEngine()
    {
        delete keyboard;
        delete mouse;
        delete gameTimer;
        delete windowManager;
    }

    bool SymphonyEngine::InitialiseWindow(const char * windowsName, int initialWidth, int initialHeight, bool isFullscreen, bool useVSync)
    {
        if (!windowManager->Initialise(windowsName, initialWidth, initialHeight, isFullscreen, useVSync))
        {
            std::cerr << "ERROR: Symphony failed to initialise a window using SDL 2!" << std::endl;

            //Free resources and close SDL
            Shutdown();

            return false;
        }

        int numKeys;
        const Uint8* keystate = SDL_GetKeyboardState(&numKeys);
        keyboard->Initialise(keystate, numKeys);

        return true;
    }

    void SymphonyEngine::Run()
    {
        //Event handler
        SDL_Event e;

        //Enable text input
        SDL_StartTextInput();

        float deltaTime;

        //TO-DO: Code regarding FPS check could be enabled/disabled by the user
        int numberOfFrames = 0;
        float frameStartTime, frameEndTime = 0.0f, frameTotalTime;
        float nextTimeLap = frameEndTime + 1.0f;
        std::stringstream ss;

        //While application is running
        while (gameLoopIsActive)
        {
            frameStartTime = gameTimer->GetMS();

            deltaTime = gameTimer->GetDeltaTime();

            //Handle events on queue
            while (SDL_PollEvent(&e) != 0)
            {
                //User requests quit
                if (e.type == SDL_QUIT)
                {
                    gameLoopIsActive = false;
                }
                else if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        gameLoopIsActive = false;
                        continue;
                    }
                }
                else if (e.type == SDL_WINDOWEVENT)
                {
                    switch (e.window.event)
                    {
                        case SDL_WINDOWEVENT_RESIZED:
                            SDL_Log("Window %d resized to %dx%d", e.window.windowID, e.window.data1, e.window.data2);
                            break;
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            SDL_Log("Window %d size changed to %dx%d", e.window.windowID, e.window.data1, e.window.data2);
                            break;

                        Screen::SetResolution(e.window.data1, e.window.data2);

                        /*if (camera)
                            camera->AdaptToResize(e.window.data1, e.window.data2);*/

                    }
                }
            }

            keyboard->Update();
            mouse->Update(deltaTime);

            //Game logic update
            Update(deltaTime);

            //Game rendering
            Render();

            //Clear the states of inputs
            keyboard->Clear();
            mouse->Clear();
            
            //TO-DO: Code regarding FPS check could be enabled/disabled by the user
            //Frame-rendering performance check
            /*frameEndTime = gameTimer->GetMS();
            frameTotalTime = frameEndTime - frameStartTime;
            ++numberOfFrames;
            if (nextTimeLap - frameEndTime <= 0.0f)
            {
                ss.clear();
                ss.str("FPS: ");
                ss << "FPS: " << (1000.0 / double(frameTotalTime)) << " | ms/frame: " << frameTotalTime;;
                windowManager->SetWindowTitle(ss.str().c_str());

                numberOfFrames = 0;
                nextTimeLap = frameEndTime + 100.0f;
            }*/
        }

        //Disable text input
        SDL_StopTextInput();

        //Free resources and close SDL
        Shutdown();
    }

    void SymphonyEngine::Shutdown()
    {
        std::cout << "Symphony is shutting down" << std::endl;

        //Destroy window
        /*delete windowManager;*/

        //Quit SDL subsystems
        SDL_Quit();
    }

    void SymphonyEngine::Update(float deltaTime)
    {
    }

    void SymphonyEngine::Render()
    {
    }

}