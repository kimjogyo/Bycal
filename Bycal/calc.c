#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


int waiting(int t);
void keyoff(SDL_Renderer* renderer, int seqX, int seqY);
int buchigi(SDL_Renderer* renderer);
void renderText(SDL_Renderer* renderer, SDL_Surface* surface, int x, int y);
void mooff(SDL_Renderer* renderer);


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

buchigi(renderer);

SDL_Keycode keys[] = {SDLK_ESCAPE, SDLK_9, SDLK_7, SDLK_4, SDLK_1, SDLK_0, SDLK_5, SDLK_0, SDLK_8, SDLK_5, SDLK_2, SDLK_PERIOD, SDLK_l, SDLK_6, SDLK_9, SDLK_6, SDLK_3, SDLK_BACKSPACE, SDLK_f, SDLK_SLASH, SDLK_8, SDLK_MINUS, SDLK_EQUALS, SDLK_EQUALS};
char shyn[25] = {'0', '1', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '\0'};
char keys2[25] = {'\0', '(', '7', '4', '1', '0', '%', ')', '8', '5', '2', '.', 'L', '^', '9', '6', '3', '\0', '\0', '/', '*', '-', '+', '\0', '\0'};
char spyn[25] = {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2', '3', '0', '0', '0', '0', '4', '\0'};

ev0:
char mo[250] = "";
int n = 0;
ev:
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
  else if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_KEYDOWN)
   {
   int mouseX = event.button.x;
   int mouseY = event.button.y;
   int i, seqX, seqY;
   int termX = 0;
   int line = 0;
   int emyn = 1;
   int rayn = 0;
  
   for(i=0; i<24; i++)
    { 
    if(shyn[i] =='1')
     {
     if((event.key.keysym.mod&KMOD_SHIFT)!=0 && event.key.keysym.sym==keys[i])
      {
      seqX = i/6;
      seqY = i%6;
      keyoff(renderer,seqX,seqY);
      buchigi(renderer);
      waiting(10);
      break;
      }
     }  
    if(shyn[i] =='0')
     {
     if((event.key.keysym.mod&KMOD_SHIFT)==0 && event.key.keysym.sym == keys[i])
      {
      seqX = i/6;
      seqY = i%6;
      keyoff(renderer,seqX,seqY);
      buchigi(renderer);
      waiting(10);
      break;
      }
     }
    } 
    
   if((mouseX>12.5 && mouseX<267.5 && mouseY>150 && mouseY<445) && ((mouseX-12)%(60+5)<60 && (mouseY-150)%(45+5)<45)) // 12=12.5-0.5 
    {
    seqX = (mouseX-12.5)/(60+5);
    seqY = (mouseY-150)/(45+5);
    keyoff(renderer,seqX,seqY);
    buchigi(renderer);
    rayn = 1;
    waiting(10);
    }
     
   if(event.key.keysym.sym==SDLK_RETURN){goto res;}
   if((event.type!=SDL_MOUSEBUTTONDOWN||rayn!=1) && i==24){goto ev;}  
   
    
   if(spyn[seqX*6+seqY] == '0')
    {
    mo[n] = keys2[seqX*6+seqY];
    SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF}; 
    
    for(i=0; i<n+1; i++)
     {
     //waiting(3);
     char mo2[2] = {mo[n-i], '\0'};
     SDL_Surface* surface = TTF_RenderText_Solid(font, mo2, color);
     termX = termX+(surface->w);
     if((263-termX)<=17){termX = surface->w; line = line+1;}
     }
      
    if(line > 4)
     {
     mooff(renderer);
     buchigi(renderer);
     waiting(10);
     mo[n]='\0'; n=n-1;
     }
     
    termX=0; line=0;
    for(i=0; i<n+1; i++)
     {
     waiting(3);
     char mo2[2] = {mo[n-i], '\0'};
     SDL_Surface* surface = TTF_RenderText_Solid(font, mo2, color);
     termX = termX+(surface->w);
     if((263-termX)<=17){termX = surface->w; line = line+1;}
     renderText(renderer, surface, 263-termX, 117-line*(surface->h));
     }
    n = n+1;
    waiting(50);
    goto ev;
    }
          
   if(spyn[seqX*6+seqY] == '2' && n>0)
    {
    mo[n-1] = '\0';
    n = n-2;
    buchigi(renderer);
    waiting(10);
    SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF}; 
 
    for(i=0; i<n+1; i++)
     {
     waiting(3);
     char mo2[2] = {mo[n-i], '\0'};
     SDL_Surface* surface = TTF_RenderText_Solid(font, mo2, color);
     termX = termX+(surface->w);
     if((263-termX)<=17){termX = surface->w; line = line+1;}
     renderText(renderer, surface, 263-termX, 117-line*(surface->h));
     }
    n = n+1;
    emyn = 0;
    waiting(50);
    goto ev;
    }
    
   if(spyn[seqX*6+seqY] == '2' && n==0 && emyn==1)
    {
    mooff(renderer);
    buchigi(renderer);
    waiting(50);
    goto ev0;
    }
     
   if(spyn[seqX*6+seqY] == '1')
    {
    buchigi(renderer);
    waiting(50);
    goto ev0;
    }
    
res: 
   int nuyn = 0;
   int poco = 0;
   int pacl = 0;
   int j,k;
   int popl = 1;
   double nu = 0;
   double nupa[150];
   char chpa[150][150] = {""};
   int chco, chco2, chco3;
   int dica[150] = {0};
   int dica2[100] = {0};
   char dica3[100];
   int dica4[100] = {0};
   int dica5[100] = {0};
   int cael;
   if(spyn[seqX*6+seqY]=='4' || event.key.keysym.sym==SDLK_RETURN)
    {
    SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF}; 
//err chk
    for(i=0; i<n; i++)
     {
     if(mo[0]=='%' || (mo[i+1]=='%'&&(mo[i]=='+'||mo[i]=='-'||mo[i]=='*'||mo[i]=='/'||mo[i]=='('||mo[i]=='^'||mo[i]=='L'||mo[i]=='%')) || (mo[i+1]=='%'&&(mo[i+2]=='0'||mo[i+2]=='1'||mo[i+2]=='2'||mo[i+2]=='3'||mo[i+2]=='4'||mo[i+2]=='5'||mo[i+2]=='6'||mo[i+2]=='7'||mo[i+2]=='8'||mo[i+2]=='9'||mo[i+2]=='.'||mo[i+2]=='('||mo[i+2]=='%')))
      {
      buchigi(renderer);
      waiting(10);
      char mo2[6] = "Error";
      color.g = 0x00;  
      color.b = 0x00;
      SDL_Surface* surface = TTF_RenderText_Solid(font, mo2, color);
      renderText(renderer, surface, 263-(surface->w), 117);
      goto ev0;
      }
     if(mo[i]=='0'||mo[i+2]=='1'||mo[i]=='2'||mo[i]=='3'||mo[i]=='4'||mo[i]=='5'||mo[i]=='6'||mo[i]=='7'||mo[i]=='8'||mo[i]=='9'||mo[i]=='.')
      {
      nuyn = 1;
      if(mo[i]=='.'){poco=poco+1;}
      if(nuyn==1 && poco>1)
       {
       buchigi(renderer);
       waiting(10);
       char mo2[6] = "Error";
       color.g = 0x00;  
       color.b = 0x00;
       SDL_Surface* surface = TTF_RenderText_Solid(font, mo2, color);
       renderText(renderer, surface, 263-(surface->w), 117);
       goto ev0;
       }
      }
     else{nuyn=0; poco=0;}
     if((mo[i+1]=='+'||mo[i+1]=='-'||mo[i+1]=='*'||mo[i+1]=='/'||mo[i+1]=='^'||mo[i+1]=='L') && (mo[i]=='+'||mo[i]=='-'||mo[i]=='*'||mo[i]=='/'||mo[i]=='^'||mo[i]=='L'))
      {
      buchigi(renderer);
      waiting(10);
      char mo2[6] = "Error";
      color.g = 0x00;  
      color.b = 0x00;
      SDL_Surface* surface = TTF_RenderText_Solid(font, mo2, color);
      renderText(renderer, surface, 263-(surface->w), 117);
      goto ev0;
      }
     if(mo[i]=='(' || mo[i]==')')
      {
      if(mo[i]=='('){pacl = pacl+1;}
      else{pacl = pacl-1;}
      }
     if(pacl<0 || (i==n-1&&pacl!=0))
       {
       buchigi(renderer);
       waiting(10);
       char mo2[6] = "Error";
       color.g = 0x00;  
       color.b = 0x00;
       SDL_Surface* surface = TTF_RenderText_Solid(font, mo2, color);
       renderText(renderer, surface, 263-(surface->w), 117);
       goto ev0;
       }       
     if((mo[i+1]=='('&&(mo[i]=='0'||mo[i]=='1'||mo[i]=='2'||mo[i]=='3'||mo[i]=='4'||mo[i]=='5'||mo[i]=='6'||mo[i]=='7'||mo[i]=='8'||mo[i]=='9'||mo[i]=='.'||mo[i]==')')) || (mo[i+1]==')'&&(mo[i]=='+'||mo[i]=='-'||mo[i]=='*'||mo[i]=='/'||mo[i]=='^'||mo[i]=='L'||mo[i]=='(')) || (mo[i]=='('&&(mo[i+1]=='*'||mo[i+1]=='/'||mo[i+1]=='^'||mo[i+1]=='L'||mo[i+1]==')')) || (mo[i]==')'&&(mo[i+1]=='0'||mo[i+1]=='1'||mo[i+1]=='2'||mo[i+1]=='3'||mo[i+1]=='4'||mo[i+1]=='5'||mo[i+1]=='6'||mo[i+1]=='7'||mo[i+1]=='8'||mo[i+1]=='9'||mo[i+1]=='.'||mo[i+1]=='(')))
      {
      buchigi(renderer);
      waiting(10);
      char mo2[6] = "Error";
      color.g = 0x00;  
      color.b = 0x00;
      SDL_Surface* surface = TTF_RenderText_Solid(font, mo2, color);
      renderText(renderer, surface, 263-(surface->w), 117);
      goto ev0;
      }  
     if((i==0&&(mo[i]=='*'||mo[i]=='/'||mo[i]=='^'||mo[i]=='L'||mo[i]==')')) || (i==n-1&&(mo[i]=='+'||mo[i]=='-'||mo[i]=='*'||mo[i]=='/'||mo[i]=='^'||mo[i]=='L'||mo[i]=='(')))
      {
      buchigi(renderer);
      waiting(10);
      char mo2[6] = "Error";
      color.g = 0x00;  
      color.b = 0x00;
      SDL_Surface* surface = TTF_RenderText_Solid(font, mo2, color);
      renderText(renderer, surface, 263-(surface->w), 117);
      goto ev0;
      }    
     }
//plma
    for(i=0; i<n; i++)
     {
     if((i==0&&(mo[i]=='+'||mo[i]=='-')) || (i>=1&&mo[i-1]=='('&&(mo[i]=='+'||mo[i]=='-')))
      {
      for(j=0; j<n-i; j++)
       {
       mo[n-1-j+1] = mo[n-1-j];
       }
      mo[i] = '0';
      i = i+1;
      n = n+1;
      }
     }
//%-->/100
    for(i=0; i<n; i++)
     {
     if(mo[i]=='%')
      {
      for(j=0; j<n-i-1; j++)
       {
       mo[n-1-j+3] = mo[n-1-j];
       }
      mo[i] = '/';
      mo[i+1] = '1';
      mo[i+2] = '0';
      mo[i+3] = '0';
      i = i+3;
      n = n+3;
      }
     }
    /*
    buchigi(renderer);
    waiting(10);
    termX=0; line=0;
    for(i=0; i<n; i++)
     {
     waiting(3);
     char mo2[2] = {mo[n-i-1], '\0'};
     SDL_Surface* surface = TTF_RenderText_Solid(font, mo2, color);
     termX = termX+(surface->w);
     if((263-termX)<=17){termX = surface->w; line = line+1;}
     renderText(renderer, surface, 263-termX, 117-line*(surface->h));
     }
     */
 //num,char  
    poco = 0;
    j = 0;
    for(i=0; i<n; i++)
     {
     if(mo[i]=='0'||mo[i]=='1'||mo[i]=='2'||mo[i]=='3'||mo[i]=='4'||mo[i]=='5'||mo[i]=='6'||mo[i]=='7'||mo[i]=='8'||mo[i]=='9'||mo[i]=='.')
      {
      if(mo[i]=='.' && (mo[i+1]=='0'||mo[i+1]=='1'||mo[i+1]=='2'||mo[i+1]=='3'||mo[i+1]=='4'||mo[i+1]=='5'||mo[i+1]=='6'||mo[i+1]=='7'||mo[i+1]=='8'||mo[i+1]=='9'||mo[i+1]=='.'))
      {
      poco=1; continue;
      }
      if(mo[i]!='.' && poco==0){nu=nu*10+(mo[i]-'0');}
      if(mo[i]!='.' && poco==1){nu=nu+(mo[i]-'0')*pow(10,-popl); popl=popl+1;}
      if(i==n-1 || !(mo[i+1]=='0'||mo[i+1]=='1'||mo[i+1]=='2'||mo[i+1]=='3'||mo[i+1]=='4'||mo[i+1]=='5'||mo[i+1]=='6'||mo[i+1]=='7'||mo[i+1]=='8'||mo[i+1]=='9'||mo[i+1]=='.'))
       {
       nupa[j]=nu; nu=0; poco=0; popl=1; j=j+1;
       }
      }
     }
    chco = j+1;
    j = 0;
    k = 0;
    for(i=0; i<n; i++)
     {
     if(i==0 && (mo[i]=='0'||mo[i]=='1'||mo[i]=='2'||mo[i]=='3'||mo[i]=='4'||mo[i]=='5'||mo[i]=='6'||mo[i]=='7'||mo[i]=='8'||mo[i]=='9'||mo[i]=='.'))
      {
      j = j+1; continue;
      }
     if(!(mo[i]=='0'||mo[i]=='1'||mo[i]=='2'||mo[i]=='3'||mo[i]=='4'||mo[i]=='5'||mo[i]=='6'||mo[i]=='7'||mo[i]=='8'||mo[i]=='9'||mo[i]=='.'))
      {
      if(i!=n-1 && !(mo[i+1]=='0'||mo[i+1]=='1'||mo[i+1]=='2'||mo[i+1]=='3'||mo[i+1]=='4'||mo[i+1]=='5'||mo[i+1]=='6'||mo[i+1]=='7'||mo[i+1]=='8'||mo[i+1]=='9'||mo[i+1]=='.'))
       {
       chpa[j][k]=mo[i]; k=k+1;
       }
      if(i!=n-1 && (mo[i+1]=='0'||mo[i+1]=='1'||mo[i+1]=='2'||mo[i+1]=='3'||mo[i+1]=='4'||mo[i+1]=='5'||mo[i+1]=='6'||mo[i+1]=='7'||mo[i+1]=='8'||mo[i+1]=='9'||mo[i+1]=='.'))
       {
       chpa[j][k]=mo[i]; j=j+1; k=0;
       }
      if(i==n-1){chpa[j][k]=mo[i];}
      }     
     }
    
cal:
///(n)-->n
    for(i=0; i<chco-1; i++)
     {
     chco2 = strlen(chpa[i]);
     chco3 = strlen(chpa[i+1]);
     while(chco2>=1 && chpa[i][chco2-1]=='(' && chpa[i+1][0] == ')')
      {
      chpa[i][chco2-1] = '\0';
      for(j=0; j<chco3-1; j++)
       {
       chpa[i+1][j] = chpa[i+1][j+1];
       }
      chpa[i+1][j] = '\0';
      chco2 = chco2-1;
      chco3 = chco3-1;
      } 
     }
///dica 
    for(i=0; i<chco-2; i++)
     {
     chco2 = strlen(chpa[i+1]);
     if(chco2==1 && (chpa[i+1][0]=='+'||chpa[i+1][0]=='-'||chpa[i+1][0]=='*'||chpa[i+1][0]=='/'||chpa[i+1][0]=='^'||chpa[i+1][0]=='L'))
      {
      dica[i] = 1;
      }
     }
    j = 0;
    for(i=0; i<chco-2; i++)
     {
     if(dica[i]==1){dica2[j]=i; dica3[j]=chpa[i+1][0]; j=j+1;}
     }
    pacl = 0;
    for(i=0; i<chco-2; i++)
     {
     chco2 = strlen(chpa[i]);
     for(j=0; j<chco2; j++)
      {
      if(chpa[i][j]=='('){pacl=pacl+1;}
      if(chpa[i][j]==')'){pacl=pacl-1;}     
      }
     dica4[i] = pacl;
     }
    j = 0;
    for(i=0; i<chco-2; i++)
     {
     if(dica[i]==1){dica5[j]=dica4[i]; j=j+1;}
     }
    cael = dica2[0]; 
    for(i=0; i<chco-3; i++)
     {
     if(dica5[i+1]>dica5[i] || (dica5[i+1]==dica5[i]&&(dica3[i+1]=='^'||dica3[i+1]=='L')) || (dica5[i+1]==dica5[i]&&(dica3[i+1]=='*'||dica3[i+1]=='/')&&(dica3[i]=='+'||dica3[i]=='-')))
      {
      cael=dica2[i+1];
      }
     }
    if(strlen(chpa[cael+1])==1)
     {
     if(chpa[cael+1][0]=='+'){nupa[cael]=nupa[cael]+nupa[cael+1];}
     if(chpa[cael+1][0]=='-'){nupa[cael]=nupa[cael]-nupa[cael+1];}
     if(chpa[cael+1][0]=='*'){nupa[cael]=nupa[cael]*nupa[cael+1];}
     if(chpa[cael+1][0]=='/'){nupa[cael]=nupa[cael]/nupa[cael+1];}
     if(chpa[cael+1][0]=='^'){nupa[cael]=pow(nupa[cael],nupa[cael+1]);}
     if(chpa[cael+1][0]=='L'){nupa[cael]=log(nupa[cael])/log(nupa[cael+1]);}
     if(chpa[cael+1][0]=='+' || chpa[cael+1][0]=='-' || chpa[cael+1][0]=='*' || chpa[cael+1][0]=='/' || chpa[cael+1][0]=='^' || chpa[cael+1][0]=='L')
      {
      for(i=0; i<chco-cael-2; i++)
       {
       nupa[cael+1+i] = nupa[cael+1+i+1];
       }
      for(i=0; i<chco-cael-1; i++)
       {
       chco2 = strlen(chpa[cael+1+i]);
       chco3 = strlen(chpa[cael+1+i+1]);
       for(j=0; j<chco2; j++)
        {
        chpa[cael+1+i][j] = '\0';
        }
       for(j=0; j<chco3; j++)
        {
        chpa[cael+1+i][j] = chpa[cael+1+i+1][j]; 
        }
       }
      }
     }
    if(!(chpa[0][0]=='\0'&&chpa[1][0]=='\0'))
     {
     for(i=0; i<150; i++)
      {
      dica[i] = 0;
      if(i>=100){continue;}
      dica2[i] = dica4[i] = dica5[i] = 0;
      dica3[i] = '\0';
      }
     goto cal;
     }
     
  
    
    if(nupa[cael]-(long long)nupa[cael] == 0)
     {
     sprintf(mo, "%lld", (long long)nupa[cael]);
     n = strlen(mo);
     }
    else
     {
     sprintf(mo, "%.08lf", nupa[cael]);
     n = strlen(mo);
     for(i=0; i<8; i++)
      {
      if(mo[n-1-i]!='0'){break;}
      }
     n = n-i; 
     }
    
    
    color.r = 0x00;  
    color.b = 0x00;
    buchigi(renderer);
    waiting(10);
    termX=0; line=0;
    for(i=0; i<n; i++)
     {
     waiting(3);
     char mo2[2] = {mo[n-i-1], '\0'};
     SDL_Surface* surface = TTF_RenderText_Solid(font, mo2, color);
     termX = termX+(surface->w);
     if((263-termX)<=17){termX = surface->w; line = line+1;}
     renderText(renderer, surface, 263-termX, 117-line*(surface->h));
     }
 
    waiting(50);
    goto ev;
  
  
    } 
  
   
   
   
   }
  } 
 }
 

ed:
TTF_CloseFont(font);
TTF_Quit();
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();


return 0;
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


void keyoff(SDL_Renderer* renderer, int seqX, int seqY)
 {
 SDL_Rect rect2 = {12.5+(60+5)*seqX, 150+(45+5)*seqY, 60, 45};
 SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
 SDL_RenderFillRect(renderer, &rect2);
 SDL_RenderPresent(renderer);
 int qyn;
 qyn = waiting(50); /*if(qyn==1){goto ed;}*/   
 }  


int buchigi(SDL_Renderer* renderer)
 {
 SDL_Surface* imageSurface = IMG_Load("/home/kimjogyo/Bycal/lay.JPG");
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
 imageRect.x = 0;     
 imageRect.y = 0;     
 imageRect.w = imageWidth; 
 imageRect.h = imageHeight; 

 SDL_RenderCopy(renderer, imageTexture, NULL, &imageRect);

 SDL_RenderPresent(renderer);

 return 0;
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
 
 SDL_RenderPresent(renderer);

 SDL_DestroyTexture(texture);
 }

void mooff(SDL_Renderer* renderer)
 {
 SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
 SDL_RenderClear(renderer);
 SDL_RenderPresent(renderer);
 waiting(50);
 }










