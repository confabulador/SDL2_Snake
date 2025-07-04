#include <stdio.h>
#include <SDL2/SDL.h>
#include "headerSDL.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int janela_ativa = FALSE;



struct ball { 
  float *x;
  float *y;
  float largura;
  float altura;
  int quantidade;
  int mx;
  int my;
} ball;


int init_window(void){
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
    fprintf(stderr,"erro iniciando sdl\n");
    return FALSE;
  }

  window = SDL_CreateWindow(NULL,
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            LARGURA,
                            ALTURA,
                            SDL_WINDOW_BORDERLESS);

  if (!window){
    fprintf(stderr,"erro criando janela\n");
    return FALSE;
  }

  renderer = SDL_CreateRenderer(window,-1,0);
  
  if (!renderer){
    fprintf(stderr,"erro criando renderer\n");
    return FALSE;
  }

  return TRUE;
}

void check_collision(){
  
  /* verificando se bateu em parede */
  if (ball.x[ball.quantidade] >= LARGURA || ball.x[ball.quantidade] < 0 || ball.y[ball.quantidade] >= ALTURA || ball.y[ball.quantidade] < 0){
    janela_ativa = FALSE;
  }

}
void setup(){
  ball.quantidade = 20;
  ball.x = calloc(ball.quantidade,sizeof(float));
  ball.y = calloc(ball.quantidade,sizeof(float));
  ball.my = MOVIMENTO;

  for (int i = ball.quantidade ; i > 0; i -= 1){
    ball.x[i] = 20*i;
    ball.y[i] = 20;
  }
  ball.largura = 20;
  ball.altura = 20;
}

void process_input(){
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
    case SDL_QUIT:
      janela_ativa = FALSE;
      break;

    case SDL_KEYDOWN:
      if (KEY == SDLK_ESCAPE) janela_ativa = FALSE;


      if(KEY == SDLK_UP){
        ball.my = -MOVIMENTO;
        ball.mx = 0;
      }
      if(KEY == SDLK_DOWN){
          ball.my = MOVIMENTO;
          ball.mx = 0;
      }
      if(KEY == SDLK_RIGHT){
        ball.mx = MOVIMENTO;
        ball.my = 0;
      }
      if(KEY == SDLK_LEFT){
        ball.mx = -MOVIMENTO;
        ball.my = 0;
      }
      break;

  }
}

void update(){
  int last_frame_time = SDL_GetTicks();

  for (int i = 0; i < ball.quantidade; i++){

    ball.x[i] = ball.x[i+1];
    ball.y[i] = ball.y[i+1];
  }

  ball.x[ball.quantidade] += ball.mx;
  ball.y[ball.quantidade] += ball.my;


  int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

  if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME){
    SDL_Delay(time_to_wait);
  }
}

void render(void){
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderClear(renderer);
     
  for (int contador = ball.quantidade; contador > 0; contador -= 1){
    SDL_Rect ball_rect = {
      ball.x[contador],
      ball.y[contador],
      ball.largura,
      ball.altura
    };
    SDL_SetRenderDrawColor(renderer,100,255,contador*-10,255);
    SDL_RenderFillRect(renderer,&ball_rect);
  }
  
  check_collision();

  SDL_RenderPresent(renderer);
}


void window_killer(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main(void){
  janela_ativa = init_window();

  setup();
  
  while(janela_ativa){
    process_input();
    update();
    render();
  }

  window_killer();
  

  return 0;
}
