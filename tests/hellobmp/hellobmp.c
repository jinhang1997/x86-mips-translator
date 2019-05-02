#define SDL_MAIN_HANDLED

#include "SDL2/SDL.h"
#include <stdio.h>
 
int main(int argc, char *args[])
{
  const int Window_WIDTH = 640;
  const int Window_HEIGHT = 480;
  char error[20] = "error! %d\n";
  char title[20] = "hello!";
  char file[20] = "hello.bmp";
   
  SDL_Window* window = NULL;
  SDL_Renderer* render = NULL;
  SDL_Texture* tex = NULL;

  //init
  window = SDL_CreateWindow(title,
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    Window_WIDTH,
    Window_HEIGHT,
    SDL_WINDOW_SHOWN);
  if (window == NULL)
  {
    printf(error, 1);
    return 1;
  }
  render = SDL_CreateRenderer(window, -1, 0);
  if (render == NULL)
  {
    printf(error, 2);
    return 1;
  }

  //load image
  SDL_Surface* hello = NULL;
  hello = SDL_LoadBMP(file);
  if (hello == NULL)
  {
    printf(error, 3);
    return 1;
  }
  tex = SDL_CreateTextureFromSurface(render, hello);
  SDL_FreeSurface(hello);
  if (tex == NULL)
  {
    printf(error, 4);
    return 1;
  }

  //put image
  SDL_RenderCopy(render, tex, NULL, NULL);
  SDL_RenderPresent(render);
  SDL_Delay(1000);

  //quit
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(render);
  SDL_DestroyTexture(tex);
  SDL_Quit();

  return 0;
}

