#pragma once
#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <SDL2/SDL.h>

typedef int32_t i32;
typedef uint32_t u32;
typedef int32_t b32;

class Window
{
    public:
        u32 WindowFlags;
        SDL_Window *Window;
        SDL_GLContext Context;
        b32 Running;
        b32 FullScreen;
        SDL_Event Event;

        float xOff = .0F;
        float yOff = .0F;
        float zOff = .0F;

        float horizontal = .0F;
        float vertical = .0F;

        int mouseX;
        int mouseY;

        void Init(const char *title, u32 Width, u32 Height);
        void Run();
};
#endif
