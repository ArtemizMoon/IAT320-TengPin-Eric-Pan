//======================Code References / Inspirations ==================
https://www.youtube.com/watch?v=Rfko5UnqDI4&ab_channel=AdafruitIndustries
https://www.teachengineering.org/makerchallenges/view/rice3-2349-heartbeat-microcontroller-led-senor-design-challenge
https://learn.adafruit.com/heart-rate-badge/program-it
https://forum.arduino.cc/index.php?topic=314521.0
https://www.xtronical.com/pulseheartsensor/
https://learn.adafruit.com/heart-rate-badge/program-it
//=======================================================================
#include <Adafruit_CircuitPlayground.h>


//heart beat sensor
int photocell = A9;
int val;

//heart beat
long  currTime = 0; //counter for how many times before next record pulse
int counting = 0; // times the wave changes direction
int heartRate = 0; // calculated heart rate
int reading;//photocell input
bool counted = false; //when wave changes direction (towards +/- direction)

int tgtBPM = 70; //default lowest average target BPM
int selcBPM; //
bool setting = true;
int range = 5; //value for calacuarating range
int minBPM, maxBPM;  //range for target heart rate


void setup() 
{ 
  Serial.begin(9600);
  CircuitPlayground.begin();

  //==============================CircuitPlayground board test (Heart Pulse)====================================================
  CircuitPlayground.setBrightness(200); 
  //CircuitPlayground.setPixelColor(6,0,255,0); //Test: Set LED color to green (green is best absorbed by red)

}

void loop() 
{
  heartBeat();
  
}


void heartBeat()
{
  
  //==============================Setting target BPM========================
     //confirm setting
    if ((CircuitPlayground.rightButton()))
    {
      if (setting == true)
      {
        setting = false;
      }
      else
      {
        for (int i = 1; i<10; i++)
        {
          CircuitPlayground.setPixelColor(i, 0, 0, 0);
        }
        setting = true;
      }

      CircuitPlayground.playTone(900,100);
      minBPM = tgtBPM - tgtBPM/20; //selected heart rate's minium value for range
      maxBPM = tgtBPM + tgtBPM/20;  //selected heart rate's maxium value for range
      CircuitPlayground.playTone(100,100);
      delay(100);
    }
  
  if (setting == true)
  {

      if ( (CircuitPlayground.leftButton()) ) 
      {
        tgtBPM += 20; //add 20 to target heart rate
        
        if (tgtBPM > 200) //reset tgtBPM to default if over limit
        {
          tgtBPM = 70; //reset to default
        }
        Serial.println("tgtBPM: " + String(tgtBPM));
        CircuitPlayground.playTone(900,100);
        delay(100);
      }


    
    switch (tgtBPM) //feedback of each selected target BPM
      {
        case 70:
          for (int i = 1; i<9; i++)
          {
            CircuitPlayground.setPixelColor(i, 0, 0, 0);
          }
          CircuitPlayground.setPixelColor(0, 255, 255, 255);
          selcBPM = 70;
          break;
        case 90:
          CircuitPlayground.setPixelColor(1, 255, 255, 255);
          selcBPM = 90;
          break;
        case 110:
          CircuitPlayground.setPixelColor(2, 255, 255, 255);
          selcBPM = 110;
          break;
        case 130:
          CircuitPlayground.setPixelColor(3, 255, 255, 255);
          selcBPM = 130;
          break;
        case 150:
          CircuitPlayground.setPixelColor(4, 255, 255, 255);
          selcBPM = 150;
          break;
        case 170:
          CircuitPlayground.setPixelColor(5, 255, 255, 255);
          selcBPM = 170;
          break;
        case 190:
          CircuitPlayground.setPixelColor(6, 255, 255, 255);
          selcBPM = 190;
          break;
      }



  }
 //==============================BPM Monitor in action========================
  else
  {
    //CircuitPlayground.readCap(1); //lightsensor on board
    float light = analogRead(A9);
    
    
    //Serial.println(CircuitPlayground.lightSensor());//read the inputs (wave of brightness level due to heart pulses)
  
    currTime = millis();
    //val = analogRead(A9); //heart beat reading
    //Serial.println(val); //prints readings
    while (millis()<currTime+20) //reading pulse for every .02 seconds
    {
      
      reading = light; //CircuitPlayground.readCap(1);
      int holder = light;
      if(reading > 11 && counted == false) //counting the pulse
      {
        timer++;
            if (timer <= 10) //reseting value every 10 seconds
            {
              counting ++;
            }
            else
            {
              heartRate = counting*6; //output heart rate before reseting for next calculation
              counting =0;
              timer = 0;
            }
        counted = true;
        //CircuitPlayground.playTone(900,100);
      }
      else if(reading <= 11)
      {
        counted = false;
        //CircuitPlayground.playTone(100,100);
      }
      Serial.println();Serial.println();
      Serial.println(light);
    }


    
   // heartRate = counting*3; // multiplying by 3 to get pulse per minut
    
    Serial.println("minBPM: " + String(minBPM));
    Serial.println("tgtBPM: " + String(tgtBPM));
    Serial.println("maxBPM: " + String(maxBPM));  
    Serial.println(timer);
    Serial.println(counting); //print "frequency"
    Serial.println(heartRate); //print heartrate
 
    //less than minium selcBPM is in rest
    if (heartRate < minBPM)
    {
      //the first 2 bars of the "meter bars" are color blue with the rest turned off.
      CircuitPlayground.setPixelColor(0, 0, 150, 255);
      CircuitPlayground.setPixelColor(1, 0, 150, 255);
      CircuitPlayground.setPixelColor(8, 0, 255, 255);
      CircuitPlayground.setPixelColor(9, 0, 255, 255);
      CircuitPlayground.playTone(100,100); //notify user their current heart rate has changed into rest
      CircuitPlayground.setPixelColor(2, 0, 0, 0);
      CircuitPlayground.setPixelColor(3, 0, 0, 0);
      CircuitPlayground.setPixelColor(4, 0, 0, 0);
      CircuitPlayground.setPixelColor(5, 0, 0, 0);
      CircuitPlayground.setPixelColor(6, 0, 0, 0);
      CircuitPlayground.setPixelColor(7, 0, 0, 0);
    //  delay (20);
    }
      
    //+/- 20%(minBPM/MaxBPM) of selcBPM is in target bpm
    if (heartRate >= minBPM && heartRate <= maxBPM)
    {
      //the first 2 bars of the "meter bars" are color blue, the 3 bar is orange,  with the rest turned off.
      CircuitPlayground.setPixelColor(0, 0, 150, 255);
      CircuitPlayground.setPixelColor(1, 0, 150, 255);
      
      CircuitPlayground.setPixelColor(2, 255, 196, 0);
      CircuitPlayground.setPixelColor(7, 255, 196, 0);
      
      CircuitPlayground.setPixelColor(8, 0, 255, 255);
      CircuitPlayground.setPixelColor(9, 0, 255, 255);
      
      CircuitPlayground.playTone(500,100); //notify user their current heart rate has changed into target bpm
      CircuitPlayground.playTone(500,100);
      CircuitPlayground.playTone(500,100);
      
      CircuitPlayground.setPixelColor(3, 0, 0, 0);
      CircuitPlayground.setPixelColor(4, 0, 0, 0);
      CircuitPlayground.setPixelColor(5, 0, 0, 0);
      CircuitPlayground.setPixelColor(6, 0, 0, 0);
      //delay (20);

    }
    //over than maxium selcBPM is max bpm = user should slow down a bit
    if (heartRate > maxBPM)
    {
      //the first 2 bars of the "meter bars" are color blue, the 3rd bar is orange,  the last 2 bar red
      CircuitPlayground.setPixelColor(3, 255, 0, 0);
      CircuitPlayground.setPixelColor(4, 255, 0, 0);
      
      CircuitPlayground.setPixelColor(0, 0, 150, 255);
      CircuitPlayground.setPixelColor(1, 0, 150, 255);
      
      CircuitPlayground.setPixelColor(2, 255, 196, 0);
      CircuitPlayground.setPixelColor(7, 255, 196, 0);
      
      CircuitPlayground.setPixelColor(8, 0, 255, 255);
      CircuitPlayground.setPixelColor(9, 0, 255, 255); 

      CircuitPlayground.setPixelColor(5, 255, 0, 0);
      CircuitPlayground.setPixelColor(6, 255, 0, 0); 
      CircuitPlayground.playTone(900,100); //notify user their current heart rate has changed into overwork  
      //delay (20); 
    }
 
  }
  

  //delay(20);
}
