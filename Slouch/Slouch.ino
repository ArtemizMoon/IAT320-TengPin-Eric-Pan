#include <Adafruit_CircuitPlayground.h>
#define slouchTime 3000

float slouchAngle = 10;

float g = 9.81; //gravity
float rad2deg = 57.29579;
 
float defaultAngle, currentAngle;
unsigned long start;
bool slouch;


void setup() 
{
  Serial.begin(9600);
  CircuitPlayground.begin();
  defaultAngle = 0;

  
}

void loop() 
{
  currentAngle = rad2deg * -asin(CircuitPlayground.motionZ() / g);

  Serial.println("Current body angle" + String (currentAngle) );
  Serial.println("slouch angle" + String (slouchAngle) );
  Serial.println("default body angle" + String (defaultAngle) );
  Serial.println("Difference angle" + String (currentAngle - defaultAngle) );
  Serial.println("");


  //new   adjust target angle by +/- slouch angle and display is accordingly on the board through light

  if ( (CircuitPlayground.leftButton()) ) 
  {
    slouchAngle += 5;
    if (slouchAngle > 50) //reset slouchAngle to the minium(10) once it reaches beyond the maxium (90).
    {
      slouchAngle = 10;
    }
    
    CircuitPlayground.playTone(900,100);
    delay(100);

  }

  //set default sitting angle
  if ((CircuitPlayground.rightButton()))
  {
    defaultAngle = currentAngle;
    CircuitPlayground.playTone(300,100);
    delay(100);
  }


  switch (int(slouchAngle))
  {
    case 10:
      for (int i = 1; i<9; i++)
      {
        CircuitPlayground.setPixelColor(i, 0, 0, 0);
      }
      
      CircuitPlayground.setPixelColor(0, 255, 255, 0);
      break;
    case 15:
      CircuitPlayground.setPixelColor(1, 255, 255, 0);
      break;
    case 20:
      CircuitPlayground.setPixelColor(2, 255, 255, 0);
      break;
    case 25:
      CircuitPlayground.setPixelColor(3, 255, 255, 0);
      break;
    case 30:
      CircuitPlayground.setPixelColor(4, 255, 255, 0);
      break;
    case 35:
      CircuitPlayground.setPixelColor(5, 255, 255, 0);
      break;
    case 40:
      CircuitPlayground.setPixelColor(6, 255, 255, 0);
      break;
    case 45:
      CircuitPlayground.setPixelColor(7, 255, 255, 0);
      break;
    case 50:
      CircuitPlayground.setPixelColor(8, 255, 255, 0);
      break;     
  }
  






  
  if (currentAngle - defaultAngle > slouchAngle)
  {
    if (slouch == false)
    {
      start = millis();
      slouch =true;
    }  
  }
  else
  {
    slouch = false;
  }

  if (slouch == true && millis() - start > slouchTime)
  {
    CircuitPlayground.playTone(800,500); 
  }

}
