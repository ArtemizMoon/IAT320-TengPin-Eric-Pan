
#include <Adafruit_CircuitPlayground.h>

bool power = false;
bool turnOn = false; //on/off switch for the blade
bool touchAgain = false; // stops touch sensor from reacting consistantly while sensor is touched
float touchHold = 0;
float threshHold = 30;

int LEDPin = 9;
float brightness;//brightness value
float lightMax = 255, lightMin = 51; //25.5; //range of brightness dims and brightens
bool isItDimming;
int sound = 250;
int soundDuration = 10;
int randomSFX = 0;

float movement; //the amount of movement
float movementLimit = 18;//the threshhold of the movement to differentiate between dramatic movements and normal movements.






//===============testing===============
bool test = false;
//=====================================


void setup() 
{
 Serial.begin(9600);
 CircuitPlayground.begin();
 CircuitPlayground.setBrightness(5);
 
}

void loop() 
{

  if ((CircuitPlayground.rightButton()))
  {
    if (test == false)
    {
      swingBladeSFX();
    test = true;
    }

  }
    if ((CircuitPlayground.rightButton()))
  {
    if (test == true)
    {
      test = false;
    }
    
  }

  
  powerOn();
  lightsOnOff();
  soundVisualFeedback();
}


void powerOn()
{
  if (power == false)
  {
   CircuitPlayground.playTone(800,300);
   CircuitPlayground.playTone(800,300);
   power = true;
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
    for (int k=0; k<10; k++) 
    {
      CircuitPlayground.setPixelColor(k, 0, 255, 0);
    }
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
    for (int k=0; k<10; k++) 
    {
      CircuitPlayground.setPixelColor(k, 0, 0, 0);
    }    
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
   lightsOnOff();
    movement = abs(CircuitPlayground.motionX()) + abs(CircuitPlayground.motionY()) + abs(CircuitPlayground.motionZ());
   // Serial.println(movement);

    //the balde is relatively stable and not moving as much
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
      lightsOnOff();
      stableBladeSFX2();
      if (isItDimming == false)//if it needs to start brighten
      {
        for (brightness; brightness < lightMax; brightness +=25.5)//start brighten until at max
        {
          analogWrite(LEDPin, brightness);
          //CircuitPlayground.playTone(sound,50);
          //sound += 100;
          delay(50);
        }
        analogWrite(LEDPin, brightness);
        
        delay(100);
           
        isItDimming = true;
        //Serial.println("check point 8");
      }
      lightsOnOff();
      stableBladeSFX1();
      if (isItDimming == true)//if it needs to start dimming
      { 
        for (brightness; brightness > lightMin; brightness -=25.5)//start dimming until at min 
        {
          analogWrite(LEDPin, brightness);

          sound -= 100;
          delay(50);
          
        }
 
        isItDimming = false;
        //Serial.println("check point 7");
      }
      lightsOnOff();
    
    
  }

}



void bladeMovement()
{
    if (movement > movementLimit) //the blade is moving drastically
    {
      //CircuitPlayground.playTone(1000,100);
      brightness = lightMax;
      analogWrite(LEDPin, brightness);
      swingBladeSFX();
      
    }
}



//======Alternate solution to technical difficulites of playing wav sound files on Circuitplayground through Arduino.============
//Utilizing the playTone function to create variation of SFX to differentiate between different states of the project.===========
void activateBladeSFX()
{
    CircuitPlayground.playTone(850,10);
    CircuitPlayground.playTone(850,10);
    CircuitPlayground.playTone(900,10);
    CircuitPlayground.playTone(900,10);
    CircuitPlayground.playTone(990,10);
    CircuitPlayground.playTone(990,10);
    CircuitPlayground.playTone(990,10);
    CircuitPlayground.playTone(990,10);
    CircuitPlayground.playTone(990,10);
    CircuitPlayground.playTone(990,10);
    CircuitPlayground.playTone(1090,10);
    CircuitPlayground.playTone(1090,10);
    CircuitPlayground.playTone(1090,10);
    CircuitPlayground.playTone(1090,10);
    CircuitPlayground.playTone(1200,10);
    CircuitPlayground.playTone(1200,10);
    CircuitPlayground.playTone(1200,10);
    CircuitPlayground.playTone(1300,10);
    CircuitPlayground.playTone(1300,10);
    CircuitPlayground.playTone(1300,10);
}


void deactivateBladeSFX()
{
    CircuitPlayground.playTone(1300,10);
    CircuitPlayground.playTone(1300,10);
    CircuitPlayground.playTone(1300,10);
    CircuitPlayground.playTone(1200,10);
    CircuitPlayground.playTone(1200,10);
    CircuitPlayground.playTone(1200,10);
    CircuitPlayground.playTone(1090,10);
    CircuitPlayground.playTone(1090,10);
    CircuitPlayground.playTone(1090,10);
    CircuitPlayground.playTone(1090,10);
    CircuitPlayground.playTone(990,10);
    CircuitPlayground.playTone(990,10);
    CircuitPlayground.playTone(990,10);
    CircuitPlayground.playTone(990,10);
    CircuitPlayground.playTone(990,10);
    CircuitPlayground.playTone(990,10);
    CircuitPlayground.playTone(900,10);
    CircuitPlayground.playTone(900,10);
    CircuitPlayground.playTone(850,10);
    CircuitPlayground.playTone(850,10);
    
}

void stableBladeSFX1()
{

    CircuitPlayground.playTone(450,soundDuration);
    CircuitPlayground.playTone(450,soundDuration);
    CircuitPlayground.playTone(450,soundDuration);
    bladeMovement();
    CircuitPlayground.playTone(450,soundDuration);
    CircuitPlayground.playTone(450,soundDuration);
    CircuitPlayground.playTone(450,soundDuration);
    bladeMovement();
    CircuitPlayground.playTone(450,soundDuration);
    CircuitPlayground.playTone(450,soundDuration);
    CircuitPlayground.playTone(460,soundDuration);
    bladeMovement();
    CircuitPlayground.playTone(460,soundDuration);
    CircuitPlayground.playTone(460,soundDuration);
    CircuitPlayground.playTone(460,soundDuration);
    CircuitPlayground.playTone(460,soundDuration);
    bladeMovement();
    CircuitPlayground.playTone(460,soundDuration);
    CircuitPlayground.playTone(470,soundDuration);
    CircuitPlayground.playTone(470,soundDuration);
    CircuitPlayground.playTone(470,soundDuration);
    bladeMovement();
    CircuitPlayground.playTone(470,soundDuration);
    CircuitPlayground.playTone(470,soundDuration);
    CircuitPlayground.playTone(470,soundDuration);
    CircuitPlayground.playTone(480,soundDuration);
    bladeMovement();
    CircuitPlayground.playTone(480,soundDuration);
    CircuitPlayground.playTone(480,soundDuration);
    CircuitPlayground.playTone(480,soundDuration);
    bladeMovement();
    CircuitPlayground.playTone(500,soundDuration);
    CircuitPlayground.playTone(500,soundDuration);
    CircuitPlayground.playTone(500,soundDuration);
    CircuitPlayground.playTone(500,soundDuration);
    bladeMovement();
    CircuitPlayground.playTone(550,soundDuration);
    CircuitPlayground.playTone(550,soundDuration);
    CircuitPlayground.playTone(550,soundDuration);
    CircuitPlayground.playTone(550,soundDuration);
    bladeMovement();
 
}
void stableBladeSFX2()
{
    CircuitPlayground.playTone(550,soundDuration);
    CircuitPlayground.playTone(550,soundDuration);
    CircuitPlayground.playTone(550,soundDuration);
    bladeMovement();
    CircuitPlayground.playTone(550,soundDuration);
    CircuitPlayground.playTone(500,soundDuration);
    CircuitPlayground.playTone(500,soundDuration);
    CircuitPlayground.playTone(500,soundDuration);
    bladeMovement();
    CircuitPlayground.playTone(500,soundDuration);
    CircuitPlayground.playTone(480,soundDuration);
    CircuitPlayground.playTone(480,soundDuration);
    CircuitPlayground.playTone(480,soundDuration);
    bladeMovement();
    CircuitPlayground.playTone(480,soundDuration);
    CircuitPlayground.playTone(470,soundDuration);
    CircuitPlayground.playTone(470,soundDuration);
    bladeMovement();
    CircuitPlayground.playTone(470,soundDuration);
    CircuitPlayground.playTone(470,soundDuration);
    CircuitPlayground.playTone(470,soundDuration);
    bladeMovement();
    CircuitPlayground.playTone(470,soundDuration);
    CircuitPlayground.playTone(460,soundDuration);
    CircuitPlayground.playTone(460,soundDuration);
    bladeMovement();
    CircuitPlayground.playTone(460,soundDuration);
    CircuitPlayground.playTone(460,soundDuration);
    CircuitPlayground.playTone(460,soundDuration);
    bladeMovement();
    CircuitPlayground.playTone(460,soundDuration);
    CircuitPlayground.playTone(450,soundDuration);
    CircuitPlayground.playTone(450,soundDuration);
    bladeMovement();
    CircuitPlayground.playTone(450,soundDuration);
    CircuitPlayground.playTone(450,soundDuration);
    CircuitPlayground.playTone(450,soundDuration);
    bladeMovement();
    CircuitPlayground.playTone(450,soundDuration);
    CircuitPlayground.playTone(450,soundDuration);
    CircuitPlayground.playTone(450,soundDuration);
    bladeMovement();
}

void swingBladeSFX()
{
    randomSFX = random(1,3);
    switch(randomSFX) //randomly plays 3 variations of swing SFX
    {
      case 1:
        CircuitPlayground.playTone(1800,10);
        CircuitPlayground.playTone(1800,10);
        CircuitPlayground.playTone(1700,10);
        CircuitPlayground.playTone(1700,10);
        CircuitPlayground.playTone(1600,9);
        CircuitPlayground.playTone(1600,9);
        CircuitPlayground.playTone(1600,9);
        CircuitPlayground.playTone(1500,8);
        CircuitPlayground.playTone(1500,8);
        CircuitPlayground.playTone(1500,8);
        CircuitPlayground.playTone(1500,8);
        CircuitPlayground.playTone(1400,9);
        CircuitPlayground.playTone(1400,9);
        CircuitPlayground.playTone(1400,9);
        CircuitPlayground.playTone(1300,10);
        CircuitPlayground.playTone(1200,10);
        CircuitPlayground.playTone(1100,10);
        CircuitPlayground.playTone(1000,10);
        CircuitPlayground.playTone(900,10);
        CircuitPlayground.playTone(800,10);
        CircuitPlayground.playTone(700,10);    
        soundVisualFeedback();  
        break;
        
      case 2:
        CircuitPlayground.playTone(70,10);
        CircuitPlayground.playTone(80,10);
        CircuitPlayground.playTone(90,10);
        CircuitPlayground.playTone(100,10);
        CircuitPlayground.playTone(100,10);
        CircuitPlayground.playTone(200,10);
        CircuitPlayground.playTone(300,10);
        CircuitPlayground.playTone(400,9);
        CircuitPlayground.playTone(400,9);
        CircuitPlayground.playTone(400,9);
        CircuitPlayground.playTone(500,8);
        CircuitPlayground.playTone(500,8);
        CircuitPlayground.playTone(500,8);
        CircuitPlayground.playTone(500,8);  
        CircuitPlayground.playTone(600,9);
        CircuitPlayground.playTone(600,9);
        CircuitPlayground.playTone(600,9);
        CircuitPlayground.playTone(700,10);
        CircuitPlayground.playTone(700,10);        
        CircuitPlayground.playTone(800,10);
        CircuitPlayground.playTone(800,10);
        soundVisualFeedback();        
        break;
        
      case 3:
        CircuitPlayground.playTone(1400,10);
        CircuitPlayground.playTone(1400,10);
        CircuitPlayground.playTone(1100,10);
        CircuitPlayground.playTone(1100,10);
        CircuitPlayground.playTone(1400,9);
        CircuitPlayground.playTone(1400,9);
        CircuitPlayground.playTone(1300,9);
        CircuitPlayground.playTone(1400,8);
        CircuitPlayground.playTone(1400,8);
        CircuitPlayground.playTone(1400,8);
        CircuitPlayground.playTone(1100,8);
        CircuitPlayground.playTone(1400,9);
        CircuitPlayground.playTone(1400,9);
        CircuitPlayground.playTone(1100,9);
        CircuitPlayground.playTone(1300,10);
        CircuitPlayground.playTone(1100,10);
        CircuitPlayground.playTone(1100,10);
        CircuitPlayground.playTone(1400,10);
        CircuitPlayground.playTone(1400,10);
        CircuitPlayground.playTone(1400,10);
        CircuitPlayground.playTone(1400,10);
        soundVisualFeedback();     
        break;      
    }
  

}
