/* ppm2h --- convert PPM file to C header file              2012-02-22 */
/* Copyright (c) 2012 John Honniball */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(const int argc, const char *argv[])
{
   char lin[256];
   int i;
   int row, col;
   int pixel, b;
   unsigned char map[72][96];
   FILE *fp;
   
   if (argc != 2) {
      fprintf(stderr, "Usage: ppm2h <ppm_file>\n");
      exit(1);
   }
   
   if ((fp = fopen(argv[1], "r")) == NULL) {
      perror(argv[1]);
      exit(1);
   }
   
   fgets(lin, 256, fp);
   
   if (strncmp(lin, "P3", 2) != 0) {
      fprintf(stderr, "Portable Pixel Map (PPM) file must be saved in ASCII format\n");
      exit(1);
   }
   
   fgets(lin, 256, fp);
   fgets(lin, 256, fp);
   
   for (row = 0; row < 68; row++) {
      for (col = 0; col < 96; col++) {
         fscanf(fp, "%d", &pixel);
         fscanf(fp, "%d", &pixel);
         fscanf(fp, "%d", &pixel);
         
         if (pixel == 0)
            map[row][col] = 0;
         else
            map[row][col] = 1;
      }
   }
   
   /* Fill in four dummy rows of white pixels at the bottom */
   for (row = 68; row < 72; row++) {
      for (col = 0; col < 96; col++) {
         map[row][col] = 1;
      }
   }
   
#ifdef DEBUG
   for (row = 0; row < 68; row++) {
      for (col = 0; col < 78; col++) {
         if (map[row][col] == 0)
            printf("*");
         else
            printf(" ");
      }
      
      printf("\n");
   }
   
   exit(0);
#endif

   printf("const unsigned char dork[96*9] = {\n");
   
   for (row = 0; row < 9; row++) {
      for (col = 0; col < 96; col ++) {
         b = 0;
         for (i = 0; i < 8; i++) {
            if (map[(row * 8) + i][col] == 0)
               b |= 1 << i;
         }
         
         printf("0x%02x", b);
         
         if ((row == 8) && (col == 95)) 
            printf("\n");
         else if ((col % 8) == 7)
            printf(", \n");
         else
            printf(", ");
      }
   }
   
   printf("};\n");
   
   fclose(fp);
   
   return (EXIT_SUCCESS);
}

