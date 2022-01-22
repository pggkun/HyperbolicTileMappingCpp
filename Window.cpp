#include "Window.h"

void Window::init(const char *title, u32 Width, u32 Heigth)
{
  this->WindowFlags = SDL_WINDOW_OPENGL;
  this->Window = SDL_CreateWindow(title, 0, 0, Width, Heigth, WindowFlags);
  assert(this->Window);
  this->Context = SDL_GL_CreateContext(this->Window);

  this->Running = 1;
  this->FullScreen = 0;
}

void Window::run()
{
  float step = 0.01f;
  while (SDL_PollEvent(&this->Event))
  {
    if (Event.type == SDL_MOUSEMOTION)
    {
      SDL_GetGlobalMouseState(&this->mouseX, &this->mouseY);
    }
    if (Event.type == SDL_MOUSEBUTTONDOWN)
    {
      if (Event.button.button == SDL_BUTTON_LEFT)
      {
        yOff -= step;
      }
    }
    
    if (Event.type == SDL_KEYDOWN)
    {
      switch (Event.key.keysym.sym)
      {
        case SDLK_ESCAPE:
          Running = 0;
          break;
        default:
          break;
      }
    }
    else if (Event.type == SDL_QUIT)
    {
      Running = 0;
    }
  }
  const Uint8 *keystates = SDL_GetKeyboardState(NULL);
  if (keystates[SDL_SCANCODE_A])
  {
    this->xOff +=1.0f;
  }
  else if (keystates[SDL_SCANCODE_D])
  {
    this->xOff -=1.0f;
  }
  
  if (keystates[SDL_SCANCODE_W])
  {
    zOff += step;
  }
  if (keystates[SDL_SCANCODE_S])
  {
    zOff -= step;
  }
  if (keystates[SDL_SCANCODE_Q])
  {
    yOff += step;
  }
  if (keystates[SDL_SCANCODE_E])
  {
    yOff -= step;
  }
  if (keystates[SDL_SCANCODE_RIGHT])
  {
    this->horizontal = -1.0f;
  }
  else if (keystates[SDL_SCANCODE_LEFT])
  {
    this->horizontal = 1.0f;
  }
  else{
    this->horizontal = 0.0f;
  }

  if (keystates[SDL_SCANCODE_UP])
  {
    this->vertical = 1.0f;
  }
  else if (keystates[SDL_SCANCODE_DOWN])
  {
    this->vertical = -1.0f;
  }
  else
  {
    this->vertical = 0.0f;
  }
}
