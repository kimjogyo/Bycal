#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int buchigi(SDL_Renderer* renderer, char* cp, int x, int y, int i, int j);


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
 
if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG))
 {
 printf("SDL_image init fail: %s\n", IMG_GetError());
 return 1;
 }

//window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 280, 450, SDL_WINDOW_SHOWN);

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

SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
SDL_RenderClear(renderer);

SDL_Rect rect = {12.5, 5, 255, 140};
SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
SDL_RenderFillRect(renderer, &rect);
 
SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
int i;
int border_thickness = 2;
for(i=0; i < border_thickness; i++)
 {
 SDL_Rect borderRect = {rect.x + i, rect.y + i, rect.w - 2 * i, rect.h - 2 * i};
 SDL_RenderDrawRect(renderer, &borderRect);
 }

int j;
int t=1;
for(i=0; i<4; i++)
 {
 for(j=0; j<6; j++)
  {
  char cp1[50] = "/home/kimjogyo/Bycal/";
  char nm[10];
  sprintf(nm, "%d", t);
  char* cp2 = ".JPG";
  strcat(nm,cp2);
  strcat(cp1,nm);
  buchigi(renderer, cp1, 12.5, 150, i, j);
  t = t+1;
  }
 }

 SDL_RenderPresent(renderer);
 
 SDL_Rect rect2 = {0, 0, 280, 450};
 Uint32 format = SDL_PIXELFORMAT_ARGB8888;
 SDL_Surface *screenshot = SDL_CreateRGBSurfaceWithFormat(0, rect2.w, rect2.h, 32, format);
 if (!screenshot) 
  {
  printf("Failed to create screenshot surface: %s\n", SDL_GetError());
  }
 SDL_RenderReadPixels(renderer, &rect2, format, screenshot->pixels, screenshot->pitch);
 
 if (IMG_SaveJPG(screenshot, "lay.JPG", 100) != 0) 
  {
  printf("Failed to save JPG file: %s\n", SDL_GetError());
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


int buchigi(SDL_Renderer* renderer, char* cp, int x, int y, int i, int j)
 {
 SDL_Surface* imageSurface = IMG_Load(cp);
 if (!imageSurface)
  {
  printf("Image load fail: %s\n", IMG_GetError());
  return 1;
  }

 int imageWidth = imageSurface->w;
 int imageHeight = imageSurface->h;

 SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
 SDL_FreeSurface(imageSurface);

 if (!imageTexture)
  {
  printf("Create texture fail: %s\n", SDL_GetError());
  return 1;
  }

 SDL_Rect imageRect;
 imageRect.x = x + (imageWidth+5)*i;     
 imageRect.y = y + (imageHeight+5)*j;     
 imageRect.w = imageWidth; 
 imageRect.h = imageHeight; 

 SDL_RenderCopy(renderer, imageTexture, NULL, &imageRect);
 
 return 0;
 }
















