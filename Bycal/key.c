#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void grigi(SDL_Renderer* renderer, TTF_Font* font, const char* key, int cr1, int cr2, int cr3, int cr4, int cr5, int cr6, int cr7, int cr8);
int waiting(int t);
void renderText(SDL_Renderer* renderer, SDL_Surface* surface, int x, int y);
int waiting(int t);


int main(int argc, char* argv[])
{
SDL_Window* window = NULL;

if(SDL_Init(SDL_INIT_VIDEO) < 0)
 {
 printf("SDL init fail: %s\n", SDL_GetError());
 return 1;
 }

if(TTF_Init() == -1)
 {
 printf("SDL_ttf init fail: %s\n", SDL_GetError());
 return 1;
 }

//window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

if(!window) //window==NULL
 {
 printf("Window create fail: %s\n", SDL_GetError());
 return 1;
 }

SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

if(!renderer)
 {
 printf("Renderer create fail: %s\n", SDL_GetError());
 return 1;
 }

TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
char key[24][4] = {"AC", "(", "7", "4", "1", "0", "%", ")", "8", "5", "2", ".", "log", "^", "9", "6", "3", "\u232B", "fx", "\u00F7", "\u00D7", "-", "+", "="};


int i;
for(i=0; i<24; i++)
{ 
 SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
 SDL_RenderClear(renderer);
 grigi(renderer, font, key[i], 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF);
 waiting(50);

 SDL_Rect rect = {100, 100, 60, 45};

/*
 SDL_Surface *screenshot = SDL_Creat75eRGBSurface(0, rect.w, rect.h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF,  0xFF000000);
 if (!screenshot) 
  {
 printf("Failed to create screenshot surface: %s\n", SDL_GetError());
  }
 SDL_RenderReadPixels(renderer, &rect, format, screenshot->pixels, screenshot->pitch);
*/

 Uint32 format = SDL_PIXELFORMAT_ARGB8888;
 SDL_Surface *screenshot = SDL_CreateRGBSurfaceWithFormat(0, rect.w, rect.h, 32, format);
 if (!screenshot) 
  {
  printf("Failed to create screenshot surface: %s\n", SDL_GetError());
  }
 SDL_RenderReadPixels(renderer, &rect, format, screenshot->pixels, screenshot->pitch);

/*
 if (SDL_SaveBMP(screenshot, "output_image.bmp") != 0) 
  {
  printf("Failed to save BMP file: %s\n", SDL_GetError());
  }
*/

 char nm[10];
 sprintf(nm, "%d", i+1);
 char* cp = ".JPG";
 strcat(nm,cp);
 if (IMG_SaveJPG(screenshot, nm, 100) != 0) 
  {
  printf("Failed to save JPG file: %s\n", SDL_GetError());
  }

 SDL_FreeSurface(screenshot);
 }


SDL_Event event;
int quit = 0;
while(!quit)
 {
 while(SDL_PollEvent(&event))
  {
  if(event.type == SDL_QUIT)
   {
   quit = 1;
   }
  } 
 }
 

TTF_CloseFont(font);
TTF_Quit();
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();


return 0;
}


void grigi(SDL_Renderer* renderer, TTF_Font* font, const char* key, int cr1, int cr2, int cr3, int cr4, int cr5, int cr6, int cr7, int cr8)
 {
 SDL_Rect rect = {100, 100, 60, 45};
 SDL_SetRenderDrawColor(renderer, cr1, cr2, cr3, cr4);
 SDL_RenderFillRect(renderer, &rect);
 
 SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
 int i;
 int border_thickness = 2;
 for(i=0; i < border_thickness; i++)
  {
  SDL_Rect borderRect = {rect.x + i, rect.y + i, rect.w - 2 * i, rect.h - 2 * i};
  SDL_RenderDrawRect(renderer, &borderRect);
  }

 SDL_Color color = {cr5, cr6, cr7, cr8}; 
 SDL_Surface* surface = TTF_RenderUTF8_Blended(font, key, color);
 renderText(renderer, surface, rect.x+rect.w/2-(surface->w/2), rect.y+rect.h/2-(surface->h/2));

 SDL_RenderPresent(renderer);
 
 SDL_FreeSurface(surface);
 }

void renderText(SDL_Renderer* renderer, SDL_Surface* surface, int x, int y)
 {
 SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

 SDL_Rect textRect;
 textRect.x = x;
 textRect.y = y;
 textRect.w = surface->w;
 textRect.h = surface->h;

 SDL_RenderCopy(renderer, texture, NULL, &textRect);

 SDL_DestroyTexture(texture);
 }


int waiting(int t)
 { 
 Uint32 start_time = SDL_GetTicks();
    SDL_Event event;
    while (SDL_GetTicks() - start_time < t) 
     {
     while (SDL_PollEvent(&event)) 
      {
      if (event.type == SDL_QUIT) 
       {
       return 1;
       }
      }
     }
 return 0;
 }

















