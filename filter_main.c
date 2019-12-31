#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filter.h"

int main(int argc, char **argv) {
  if (argc != 4 ) {
      printf("Usage ./filter <input file>  <filter file> <output file> \n");
      return 1;
  }
  char *infile = argv[1];
  char *outfile = argv[3];
  int n = 0, scale;
  int matrix[n][n];
  FILE *kernel = fopen(argv[2],"r");
  fscanf(kernel, "%u", &n);
  fscanf(kernel, "%u", &scale);
  for (int k = 0; k < n; k++){
    for (int l = 0; l < n; l++){
      fscanf(kernel, "%u", &matrix[k][l]);
    }
  }
  Image *ppm = readPPM(infile);
  Image *ppmCopy = readPPM(infile);
  if (!ppm || !ppmCopy) printf("Error opening files\n");
  for (int i = 0; i < ppm->height; i++){
    for (int j = 0; j < ppm->width; j++) {
      int sumR = 0, sumG = 0, sumB = 0;
      for (int k = 0; k < n; k++){
        for (int l = 0; l < n; l++){
          if ( k + i-((n-1)/2) >= 0  &&  l + j -((n-1)/2) >= 0 && (l + j -((n-1)/2)) < ppm->width && (k + i -((n-1)/2)) < ppm->height) {
            sumR += (matrix[k][l] * ppm->data[i + k-((n-1)/2)][j + l-((n-1)/2)].r);
            sumG += (matrix[k][l] * ppm->data[i + k-((n-1)/2)][j + l-((n-1)/2)].g);
            sumB += (matrix[k][l] * ppm->data[i + k-((n-1)/2)][j + l-((n-1)/2)].b);
          }
        }
      }
      sumR = sumR/scale;
      if (sumR > 255) sumR = 255;
      if (sumR < 0) sumR = 0;
      ppmCopy->data[i][j].r = sumR;
      sumG = sumG/scale;
      if (sumG > 255) sumG = 255;
      if (sumR < 0) sumR = 0;
      ppmCopy->data[i][j].g = sumG;
      sumB = sumB/scale;
      if (sumB > 255) sumB = 255;
      if (sumR < 0) sumR = 0;
      ppmCopy->data[i][j].b = sumB;
    }
  }
  if (ppmCopy) {
      writePPM(outfile, ppmCopy);
      writePPM("testing.ppm", ppm);
  }
  fclose(kernel);
  return 0;
}
