#include "ccanvas.h"
#include "stdio.h"

#include "SDL2/SDL.h"

typedef struct ccanvas {
  unsigned int w;
  unsigned int h;
  SDL_Renderer *ren;
  SDL_Window   *win;
} ccanvas;

ccanvas *init(unsigned int w, unsigned int h) {
  ccanvas *cc = malloc(sizeof(ccanvas));
  if(!cc) {
    printf("unable to allocate ccanvas struct\n");
    exit(-1);
  }

  cc->w = w;
  cc->h = h;

  if(SDL_Init(SDL_INIT_VIDEO) == -1) {
    printf("unable to initialize SDL\n");
    exit(-1);
  }

  if(SDL_CreateWindowAndRenderer(w, h, 0, &cc->win, &cc->ren) == -1) {
    printf("unable to create window and renderer\n");
    exit(-1);
  }


  return cc;
}

void quit(ccanvas *cc) {
  SDL_DestroyRenderer(cc->ren);
  SDL_DestroyWindow(cc->win);
  SDL_Quit();
  free(cc);
}

void event_loop(ccanvas *cc) {
  SDL_Event event;
  for(;;) {
    if(!SDL_PollEvent(&event)) {
      continue;
    }

    if(event.type == SDL_QUIT) {
      break;
    }
  }
}

void put_pixel(ccanvas *cc, int x, int y, byte r, byte g, byte b, byte a) {
  if(SDL_SetRenderDrawColor(cc->ren, r, g, b, a)) {
    printf("unable to set draw color");
    exit(-1);
  }
  if(SDL_RenderDrawPoint(cc->ren, x, y)) {
    printf("unable to draw point\n");
    exit(-1);
  }
  SDL_RenderPresent(cc->ren);
}

void clear_screen(ccanvas *cc, byte r, byte g, byte b, byte a) {
  if(SDL_SetRenderDrawColor(cc->ren, r, g, b, a)) {
    printf("unable to set draw color");
    exit(-1);
  }
  if(SDL_RenderClear(cc->ren)) {
    printf("unable to clear screen\n");
    exit(-1);
  }
  SDL_RenderPresent(cc->ren);
}
