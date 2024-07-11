// 3d Tetrahedron
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

float A, B, C;

float facelength = 20;
int width = 160, height = 44;
float zBuffer[160 * 44];
char buffer[160 * 44];
int backgroundASCIICode = ' ';
int distanceFromCam = 100;
float horizontalOffset = -20;
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

void calculateForSurface(float cubex, float cubey, float cubez, int ch) {
  float dumm = cubey;
  cubey = cubey + facelength*0.5824;
  x = calculateX(cubex, cubey, cubez);
  y = calculateY(cubex, cubey, cubez);
  z = calculateZ(cubex, cubey, cubez) + distanceFromCam;

  ooz = 1 / z;

  xp = (int)(width / 2 + horizontalOffset + K1 * ooz * x * 2);
  yp = (int)(height / 2 - K1 * ooz * y);

  idx = xp + yp * width;
  if (idx >= 0 && idx < width * height) {
    if (ooz > zBuffer[idx]) {
      zBuffer[idx] = ooz;
      buffer[idx] = ch;
    }
    if (cubex == 0){
      buffer[idx] = 'I';
      buffer[idx-1] = 'I';
      buffer[idx+1] = 'I';
    }
  }
}

int main() {
  printf("\x1b[2J");
  while (1) {
    memset(buffer, backgroundASCIICode, width * height);
    memset(zBuffer, 0, width * height * 4);
    facelength = 50;
    // cube
    for (float cubey = 0; cubey > -facelength*0.8165; cubey -= incrementSpeed) {
      for (float cubex = cubey*0.6123 ; cubex < -cubey*0.6123 ; cubex += incrementSpeed) {
        // most of these constants are decimal value of numbers such as root3/2. 1/root3 etc
        // the loop works based on the line from top vertex to base face, everything else is 
        // ratio based on that axis
        
        calculateForSurface(cubex, cubey, cubey*0.3535, '@');
        calculateForSurface(-0.866*cubey*0.3535 - 0.5*cubex, cubey, -cubey*0.3535*0.5 + cubex*0.866, '$');
        calculateForSurface(0.866*cubey*0.3535 - 0.5*cubex, cubey, -cubey*0.3535*0.5 - cubex*0.866, '*');
        calculateForSurface(cubex, -0.943*cubey*0.3535 + 0.333*cubey  -facelength*0.8165, cubey*0.3535*0.333 + cubey*0.943  +facelength*0.5824, ';');
        
        
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