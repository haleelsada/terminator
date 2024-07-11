//cube hollow with edges visible
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
int zBuffer2[160 * 44];  // boolean to check edge has been marked or not
char buffer[160 * 44];
int backgroundASCIICode = ' ';
int distanceFromCam = 100;
float horizontalOffset;
float K1 = 40;

float incrementSpeed = 0.6;

float x, y, z;
float ooz;
int xp, yp;
int idx;

float calculateX(int i, int j, int k) {
  //float sina = sin(A), sinb = sin(B), sinc = sin(C);
  //float cosa, cosb, cosC = cos(A), cos(B), cos(C);
  return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
         j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float calculateY(int i, int j, int k) {
  return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
         j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
         i * cos(B) * sin(C);
}

float calculateZ(int i, int j, int k) {
  return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch) {
  x = calculateX(cubeX, cubeY, cubeZ);
  y = calculateY(cubeX, cubeY, cubeZ);
  z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam;

  ooz = 1 / z;

  xp = (int)(width / 2 + horizontalOffset + K1 * ooz * x * 2);
  yp = (int)(height / 2 + K1 * ooz * y);

  idx = xp + yp * width;
  
  if (idx >= 0 && idx < width * height) {
    
    if ((ooz < zBuffer[idx]) && zBuffer2[idx] != 1){
      zBuffer[idx] = ooz;
      buffer[idx] = ch;
    }
    if ((abs(cubeX) == cubeWidth && abs(cubeY) == cubeWidth) ||
    (abs(cubeX) == cubeWidth && abs(cubeZ) == cubeWidth) ||
    (abs(cubeY) == cubeWidth && abs(cubeZ) == cubeWidth)){
      buffer[idx] = '.';
      zBuffer2[idx] = 1;      
    }

    
  }
}

int main() {
  printf("\x1b[2J");
  while (1) {
    memset(buffer, backgroundASCIICode, width * height);
    for (int i = 0; i < width * height; i++) {
        zBuffer[i] = 10;
    }
    for (int i = 0; i < width * height; i++) {
        zBuffer2[i] = 0;
    }
    cubeWidth = 20;
    horizontalOffset = -2 * cubeWidth;
    // cube
    for (float cubeX = -cubeWidth; cubeX < cubeWidth+1; cubeX += incrementSpeed) {
      for (float cubeY = -cubeWidth; cubeY < cubeWidth+1; cubeY += incrementSpeed) {
        calculateForSurface(cubeX, cubeY, -cubeWidth, '@');
        calculateForSurface(cubeWidth, cubeY, cubeX, '$');
        calculateForSurface(-cubeWidth, cubeY, -cubeX, '~');
        calculateForSurface(-cubeX, cubeY, cubeWidth, '#');
        calculateForSurface(cubeX, -cubeWidth, -cubeY, ';');
        calculateForSurface(cubeX, cubeWidth, cubeY, '+');
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