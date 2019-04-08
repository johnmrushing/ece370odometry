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
  thetaZ -= _thetaZ;

  _x0 = ( ( _x * cos( _thetaZ ) ) + ( _y * sin( _thetaZ ) ) )

  _y0 = ( ( _x * sin( _thetaZ ) ) + ( _y * cos( _thetaZ ) ) )
  
  y += _y0;
  x += _x0;

  Serial.print(y);
  Serial.print(x);
}

void leftTickInterrupt()
{ 
  thetaZ += _thetaZ;

  _x0 = ( ( _x * cos( _thetaZ ) ) + ( _y * sin( _thetaZ ) ) )

  _y0 = ( ( _x * sin( _thetaZ ) ) + ( _y * cos( _thetaZ ) ) )
  
  y -= _y0;
  x += _x0;

  Serial.print(y);
  Serial.print(x);
}

void setup()
{

  Serial.begin(9600); // arduino IDE
  
  pinMode(LEFTIR, INPUT_PULLUP);
  pinMode(RIGHTIR, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(LEFTIR), leftTickInterrupt, CHANGE); // four interrupts per spin
  attachInterrupt(digitalPinToInterrupt(RIGHTIR), rightTickInterrupt, CHANGE); // four interrupts per spin
}

void loop()
{


}
