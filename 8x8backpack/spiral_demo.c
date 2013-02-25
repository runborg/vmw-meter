/* Makes a spinning pattern on the display */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "i2c_lib.h"

struct coord_list {
  int x;
  int y;
} spiral_coords[]={
   {0,7},
   {1,7},
   {2,7},
   {3,7},
   {4,7},
   {5,7},
   {6,7},
   {7,7},

   {7,6},
   {7,5},
   {7,4},
   {7,3},
   {7,2},
   {7,1},
   {7,0},
   {6,0},

   {5,0},
   {4,0},
   {3,0},
   {2,0},
   {1,0},
   {0,0},
   {0,1},
   {0,2},

   {0,3},
   {0,4},
   {0,5},
   {0,6},
   {1,6},
   {2,6},
   {3,6},
   {4,6},

   {5,6},
   {6,6},
   {6,5},
   {6,4},
   {6,3},
   {6,2},
   {6,1},
   {5,1},

   {4,1},
   {3,1},
   {2,1},
   {1,1},
   {1,2},
   {1,3},
   {1,4},
   {1,5},

   {2,5},
   {3,5},
   {4,5},
   {5,5},
   {5,4},
   {5,3},
   {5,2},
   {4,2},

   {3,2},
   {2,2},
   {2,3},
   {2,4},
   {3,4},
   {4,4},
   {4,3},
   {3,3},

   {-1,-1},
};

int plotxy(unsigned char *display, int x, int y) {

   if ((y<0) || (y>=DISPLAY_LINES)) {
      fprintf(stderr,"Y %d out of bounds!\n",y);
      return -1;
   }

   if ((x<0) || (y>7)) {
      fprintf(stderr,"X %d out of bounds!\n",y);
      return -1;
   }

   display[y]|=(1<<(7-x));

   return 0;
}

/* should make the device settable */
int spiral_demo(void) {

   int i;
   unsigned char display_buffer[DISPLAY_LINES];

   while(1) {
      for(i=0;i<DISPLAY_LINES;i++) display_buffer[i]=0;

      i=0;
      while(spiral_coords[i].x!=-1) {

         usleep(50000);

         plotxy(display_buffer,spiral_coords[i].x,spiral_coords[i].y);
         update_display(display_buffer);
         i++;
      }
      usleep(500000);
   }

   return 0;
}


int main(int argc, char **argv) {

  int result;

  result=init_display();

  result=spiral_demo();

  return result;
}

