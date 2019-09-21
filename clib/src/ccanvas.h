#ifndef CCANVAS_H
#define CCANVAS_H

typedef struct ccanvas ccanvas;

typedef unsigned char byte;

typedef struct color {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} color;

// returns null on error
ccanvas *init(unsigned int w, unsigned int h);

void quit(ccanvas *cc);

void event_loop(ccanvas *cc);

void put_pixel(ccanvas *cc, int x, int y, byte r, byte g, byte b, byte a);

void clear_screen(ccanvas *cc, byte r, byte g, byte b, byte a);

#endif
