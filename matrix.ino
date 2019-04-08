#include <BasicLinearAlgebra.h>

#define baseline 10
#define radius 2.5

#define LEFTIR 11
#define RIGHTIR 10

float circumference = radius * TWO_PI;

float tickDistance = radius * deg2rad( 90 / 75.8 );

float thetaZ = 0, _thetaZ = tickDistance / baseline;

float x = 0, _x = ( baseline / 2 ) * sin ( _thetaZ ), _x0;
float y = 0, _y = ( baseline / 2 ) * ( 1 - cos ( _thetaZ ) ), _y0;

void rightTickInterrupt()
{ 
  globalMatrix = globalMatrix * transformR;

  Serial.print( acos( globalMatrix( 0, 0 ) ) ); //theta
  Serial.print( globalMatrix( 1, 3 ) ); //y
  Serial.print( globalMatrix( 0, 3 ) ); //x
}

void leftTickInterrupt()
{ 
  globalMatrix = globalMatrix * transformL;

  Serial.print( acos( globalMatrix( 0, 0 ) ) ); //theta
  Serial.print( globalMatrix( 1, 3 ) ); //y
  Serial.print( globalMatrix( 0, 3 ) ); //x
}

void setup()
{

  Serial.begin(9600); // arduino IDE

  Matrix<4,4> rotationR    = {  cos( _thetaZ ), -sin( _thetaZ ),  0,  0,
                                sin( _thetaZ ),  cos( _thetaZ ),  0,  baseline / 2,
                                0,  0,  1,  0,
                                0,  0,  0,  1};

  Matrix<4,4> rotationR    = {  cos( -_thetaZ ), -sin( -_thetaZ ),  0,  0,
                                sin( -_thetaZ ),  cos( -_thetaZ ),  0,  -baseline / 2,
                                0,  0,  1,  0,
                                0,  0,  0,  1};
                                    
  Matrix<4,4> translationR = {  1,  0,  0,  0,
                                0,  1,  0,  -baseline,
                                0,  0,  1,  0,
                                0,  0,  0,  1};

  Matrix<4,4> translationL = {  1,  0,  0,  0,
                                0,  1,  0,  baseline,
                                0,  0,  1,  0,
                                0,  0,  0,  1};
  
  Matrix<4,4> transformR = rotationR * translationR;
  Matrix<4,4> transformL = rotationL * translationL;

  Matrix<4,4> globalMatrix = {  1,  0,  0,  0,
                                0,  1,  0,  0,
                                0,  0,  1,  0,
                                0,  0,  0,  1};
  
  pinMode(LEFTIR, INPUT_PULLUP);
  pinMode(RIGHTIR, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(LEFTIR), leftTickInterrupt, CHANGE); // four interrupts per spin
  attachInterrupt(digitalPinToInterrupt(RIGHTIR), rightTickInterrupt, CHANGE); // four interrupts per spin
}

void loop()
{


}
