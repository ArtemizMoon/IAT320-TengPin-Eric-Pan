/* =====================Audio Reference=======================
https://www.soundboard.com/sb/sound/930977 = Hum2:        Stable saber sound
https://www.soundboard.com/sb/sound/930980 = lasrhit1:    Activate saber sound
https://www.soundboard.com/sb/sound/931006 = Swing01:     Swinging sfx #1
https://www.soundboard.com/sb/sound/931007 = Swing02:     Swinging sfx #2
============================================================*/


#include <Adafruit_CircuitPlayground.h>


bool turnOn = false; //on/off switch for the blade
bool touchAgain = false; // stops touch sensor from reacting consistantly while sensor is touched
float touchHold = 0;
float threshHold = 200;

int LEDPin = 9;
float brightness;//brightness value
float lightMax = 255, lightMin = 25.5; //range of brightness dims and brightens
bool isItDimming;

float movement; //the amount of movement
float movementLimit = 17;//the threshhold of the movement to differentiate between dramatic movements and normal movements.

void setup() 
{
 Serial.begin(9600);
 CircuitPlayground.begin();
 CircuitPlayground.setBrightness(100);
 
}

void loop() 
{
  powerOn();
  lightsOnOff();
  soundVisualFeedback();
}


void powerOn()
{
  for (int k=0; k<10; k++) 
  {
    CircuitPlayground.setPixelColor(k, 0, 255, 0);
  }
}

//Interatcion #1
void lightsOnOff()
{
 touchHold = CircuitPlayground.readCap(1); 
 if (touchHold < threshHold) //resets condidtion if user is not touching
 {
  touchAgain = false;
  //Serial.println("check point");
 }
 else
 {
   if (turnOn == false && touchAgain == false) // the blade is turned off & user is not touching the sensor
   {
    turnOn = true;
    //CircuitPlayground.setPixelColor(1, 0, 0, 255);
    brightness = 255;
    //Serial.println("check point 1");    
    analogWrite(LEDPin, brightness);
    activateBladeSFX();
    delay(10);
   }
   else if (turnOn  == true && touchAgain == false) //the blade is turned on & user is not touching the sensor
   {
    turnOn = false;
    //CircuitPlayground.setPixelColor(1, 0, 0, 0);
    brightness = 0;
    //Serial.println("check point 2");
    analogWrite(LEDPin, brightness);
    deactivateBladeSFX();
    
    delay(10);
   }
  while (touchHold >= threshHold )
  {
    touchAgain = true;
    //Serial.println("check point 3");
    touchHold = CircuitPlayground.readCap(1); 
  }
  
 }
}



//Interactions #2 & #3
void soundVisualFeedback()
{  
  if (turnOn == true)
  {
    //Serial.println("check point 4");
    //Serial.println(brightness);

    movement = abs(CircuitPlayground.motionX()) + abs(CircuitPlayground.motionY()) + abs(CircuitPlayground.motionZ());
    Serial.println(movement);
    if (movement > movementLimit) //the blade is moving drastically
    {
      CircuitPlayground.playTone(1000,100);
      brightness = lightMax;
      analogWrite(LEDPin, brightness);
      swingBladeSFX();
      
    }
    else //the balde is relatively stable and not moving as much
    {
      if (brightness == lightMax)//if brightness is at max
      {
        isItDimming = true; //start dimming
        //Serial.println("check point 5");
      }
      else if (brightness == lightMin)//if brightness is at min
      {
        isItDimming = false; //start brighten
        //Serial.println("check point 6");
      }
      
      if (isItDimming == true)//if it needs to start dimming
      {
        stableBladeSFX();
        for (brightness; brightness > lightMin; brightness -=25.5)//start dimming until at min 
        {
          analogWrite(LEDPin, brightness);
          delay(50);
        }
        isItDimming = false;
        //Serial.println("check point 7");
      }
      else if (isItDimming == false)//if it needs to start brighten
      {
        stableBladeSFX();
        for (brightness; brightness < lightMax; brightness +=25.5)//start brighten until at max
        {
          analogWrite(LEDPin, brightness);
          delay(50);
        }    
        isItDimming = true;
        //Serial.println("check point 8");
      }
    }
    
  }

}



void activateBladeSFX()
{
  CircuitPlayground.playTone(1000,100);
}


void deactivateBladeSFX()
{
  CircuitPlayground.playTone(100,100);
}

void stableBladeSFX()
{
  CircuitPlayground.playTone(300,100);
}

void swingBladeSFX()
{
  CircuitPlayground.playTone(800,100);
}
