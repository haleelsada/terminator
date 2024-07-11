// a fixed sphere with light rotating around it
#include <math.h>
#include <stdio.h>
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

float A = 1, B = 1, C=-2;

float radius = 20;
int width = 160, height = 44;
float zBuffer[160 * 44];
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

float dotproduct(){
  // assume the light was first at direction 1,1,1
  // now find it's direction rotating through A,B,C
  float lum1 = calculateX(1,1,-1);
  float lum2 = calculateY(1,1,-1);
  float lum3 = calculateZ(1,1,-1);
  float dot = lum1 * x + lum2 * y + lum3 * z,
      mag1 = sqrt(lum1 * lum1 + lum2 * lum2 + lum3 * lum3),
      mag2 = sqrt(x * x + y * y + z * z);

  return dot/(mag1*mag2);

}

void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch) {
  //x = calculateX(cubeX, cubeY, cubeZ);
  //y = calculateY(cubeX, cubeY, cubeZ);
  //z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam;
  x = cubeX, y = cubeY, z = cubeZ;
  ooz = 1 / (z+distanceFromCam);

  int lum = dotproduct(A,B,C,x,y,z)*12;
  xp = (int)(width / 2 + horizontalOffset + K1 * ooz * x * 2.2);
  yp = (int)(height / 2 - K1 * ooz * y);

  idx = xp + yp * width;
  if (idx >= 0 && idx < width * height) {
    if (ooz > zBuffer[idx]) {
      zBuffer[idx] = ooz;
      buffer[idx] = "-++***%%%@@@" [lum > 0 ? lum : 0];
      // add a space in the beginning of above string to 
      // make an illusion of total darkness
    }
  }
}

int main() {
  printf("\x1b[2J");
  while (1) {
    memset(buffer, backgroundASCIICode, width * height);
    memset(zBuffer, 0, width * height * 4);
    radius = 20;
    horizontalOffset = -2 * radius;
    // cube
    for (float y = -radius; y < radius; y += incrementSpeed) {
      for (float theta = 0; theta < 6.28; theta += 0.05) {
        calculateForSurface(sqrt(radius*radius-y*y)*cos(theta), y, sqrt(radius*radius-y*y)*sin(theta), '@');
        
      }
    }
    
    printf("\x1b[H");
    for (int k = 0; k < width * height; k++) {
      putchar(k % width ? buffer[k] : 10);
    }

    A += 0.05;
    B += 0.05;
    C += 0.01;
    
    
    usleep(42000);
  }
  return 0;
}