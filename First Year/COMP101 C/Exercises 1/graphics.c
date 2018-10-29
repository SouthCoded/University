#include <stdio.h>
#include "graphics.h"

void drawLine(int x1, int x2, int x3, int x4)
{
  printf("DL %i %i %i %i\n", x1, x2, x3, x4);
}

void drawRect(int x1, int x2, int x3, int x4)
{
  printf("DR %i %i %i %i\n", x1, x2, x3, x4);
}

void drawOval(int x, int y, int width, int height)
{
  printf("DO %i %i %i %i\n",x,y,width,height);
}

void drawArc(int x, int y, int width, int height, int startAngle, int arcAngle)
{
  printf("DA %i %i %i %i %i %i\n",x,y,width,height, startAngle, arcAngle);
}

void fillRect(int x1, int x2, int x3, int x4)
{
  printf("FR %i %i %i %i\n", x1, x2, x3, x4);
}

void drawString(char* s, int x, int y)
{
  printf("DS %i %i @%s\n",x,y,s);
}

void setColour(colour c)
{
  char* colourName;
  switch(c)
  {
    case black : colourName = "black"; break;
    case blue : colourName = "blue"; break;
    case cyan : colourName = "cyan"; break;
    case darkgray : colourName = "darkgray"; break;
    case gray : colourName = "gray"; break;
    case green : colourName = "green"; break;
    case lightgray : colourName = "lightgray"; break;
    case magenta : colourName = "magenta"; break;
    case orange : colourName = "orange"; break;
    case pink : colourName = "pink"; break;
    case red : colourName = "red"; break;
    case white : colourName = "white"; break;
    case yellow : colourName = "yellow"; break;
  }
  printf("SC %s\n", colourName);
}