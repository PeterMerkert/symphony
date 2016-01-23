#pragma once

#include "Vector2.h"
#include <iostream>

namespace Symphony
{
    //TO-DO: check https://wiki.libsdl.org/SDL_SetRelativeMouseMode
    class Mouse
    {
        friend class SymphonyEngine;
        
    public:
        enum Button { LEFT, RIGHT, MIDDLE, MAX };

        inline bool ButtonDown(Button b)
        {
            return buttonState[b];
        }

        inline bool ButtonHold(Button b)
        {
            return buttonHoldState[b];
        }

        inline bool ButtonClicked(Button b)
        {
            return buttonClickState[b];
        }

        void Update(float deltaTime);//  int currentX, int currentY, int deltaX, int deltaY);

        inline void SetAbsolutePosition(Vector2 pos)
        {
            absolutePosition = pos;
        }

        inline Vector2 AbsolutePosition() const
        {
            return absolutePosition;
        }

        inline Vector2 RelativePosition() const
        {
            return relativePosition;
        }

        inline void Clear()
        {
            relativePosition.ToZero();

            //TO-DO: A memcpy might be useful in this case
            for (int i = 0; i < Button::MAX; ++i)
            {
                buttonHoldState[i] = buttonState[i];
                //buttonClickState[i] = false;
            }
        }

    protected:
        //Current mouse absolute position
        Vector2 absolutePosition,
            relativePosition;

        bool buttonState[Button::MAX];
        bool buttonHoldState[Button::MAX];
        bool buttonClickState[Button::MAX];

        float sensitivity = 0.25f;
        
        //The mouse destructor and constructor should be protected 
        //and only manageable by a friend class as anyone could just
        //delete the reference used by the engine
        Mouse();
        ~Mouse();
    };
}