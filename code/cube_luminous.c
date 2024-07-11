//cube with surface shadowed by light
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
void usleep(__int64 usec)
{
  HANDLE timer;
  LARGE_INTEGER ft;

  ft.QuadPart = -(10 * usec); // Convert to 100 nanosecond interval, negative value indicates relative time

  timer = CreateWaitableTimer(NULL, TRUE, NULL);
  SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
  WaitForSingleObject(timer, INFINITE);
  CloseHandle(timer);
}
#endif

float A, B, C;

float cubeWidth = 20;
int width = 160, height = 44;
float zBuffer[160 * 44];
char buffer[160 * 44];
int backgroundASCIICode = ' ';
int distanceFromCam = 100;
float horizontalOffset;
float K1 = 40;

float incrementSpeed = 0.6;

float x, y, z, lum;
float ooz;
int xp, yp;
int idx;

float* calculateXYZ(int i, int j, int k, int arr[]){
  float sinA = sin(A);
  float cosA = cos(A);
  float sinB = sin(B);
  float cosB = cos(B);
  float sinC = sin(C);
  float cosC = cos(C);

  float light[3] = {1,-1,-1};

  float X = j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
         j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
  float Y = j * cos(A) * cos(C) + k * sin(A) * cos(C) -
         j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
         i * cos(B) * sin(C);
  float Z = k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);

  float L1 = arr[1] * sin(A) * sin(B) * cos(C) - arr[2] * cos(A) * sin(B) * cos(C) +
         arr[1] * cos(A) * sin(C) + arr[2] * sin(A) * sin(C) + arr[0] * cos(B) * cos(C);
  float L2 =  arr[1] * cos(A) * cos(C) + arr[2] * sin(A) * cos(C) -
         arr[1] * sin(A) * sin(B) * sin(C) + arr[2] * cos(A) * sin(B) * sin(C) -
         arr[0] * cos(B) * sin(C);
  float L3 = arr[2] * cos(A) * cos(B) - arr[1] * sin(A) * cos(B) + arr[0] * sin(B);

  float L = L1*light[0]+ L2*light[1]+ L3*light[2];
  float* values = (float*)malloc(3 * sizeof(float));
  values[0] = X;
  values[1] = Y;
  values[2] = Z;
  values[3] = L;
  return values;
}


void calculateForSurface(float cubeX, float cubeY, float cubeZ, int index, int p_or_n) {
  
  int arr[3] = {0, 0, 0};
  arr[index] = p_or_n;
  // arr contain the direction index of the surface, ie surface normal
  // used to calculate luminocity, ie shade of each side
  float* values = calculateXYZ(cubeX, cubeY, cubeZ, arr);
  x = values[0];
  y = values[1];
  z = values[2];
  lum = values[3];
  ooz = 1 / (z + distanceFromCam);

  xp = (int)(width / 2 + horizontalOffset + K1 * ooz * x * 2);
  yp = (int)(height / 2 + K1 * ooz * y);

  int N = 6.5*lum;
  idx = xp + yp * width;
  if (idx >= 0 && idx < width * height) {
    if (ooz > zBuffer[idx]) {
      zBuffer[idx] = ooz;
      buffer[idx] = ".--***/%/%/%@@@" [N > 0 ? N : 0];
    }
  }
}

int main() {
  printf("\x1b[2J");
  while (1) {
    memset(buffer, backgroundASCIICode, width * height);
    memset(zBuffer, 0, width * height * 4);
    cubeWidth = 20;
    horizontalOffset = -2 * cubeWidth;
    // cube
    for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) {
      for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed) {
        calculateForSurface(cubeX, cubeY, -cubeWidth, 2, -1);
        calculateForSurface(cubeWidth, cubeY, cubeX, 0, 1);
        calculateForSurface(-cubeWidth, cubeY, -cubeX, 0, -1);
        calculateForSurface(-cubeX, cubeY, cubeWidth, 2, 1);
        calculateForSurface(cubeX, -cubeWidth, -cubeY, 1, -1);
        calculateForSurface(cubeX, cubeWidth, cubeY, 1, 1);
      }
    }
    
    printf("\x1b[H");
    for (int k = 0; k < width * height; k++) {
      putchar(k % width ? buffer[k] : 10);
    }

    A += 0.05;
    B += 0.05;
    C += 0.01;
    usleep(12000);
  }
  return 0;
}