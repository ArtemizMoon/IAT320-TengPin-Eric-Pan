#include <Adafruit_CircuitPlayground.h>

void setup() 
{
  Serial.begin(9600);
  CircuitPlayground.begin();
}


int vals[8] = {3,2,0,1,12,6,9,10};

int pass[4] = {2,0,12,6};
int input[4] = {-1,-1,-1,-1};
int checkAmt = 0;


bool correct =false;

float threshhold = 200;
float pitches[8] = {800, 800, 800, 800, 800, 800, 800, 800}; //(3,2,0,1,12,6,9,10)

void loop() 
{

  for (int i=0; i<8; i++) 
  {
    
    int c = CircuitPlayground.readCap(vals[i]);
    //Serial.println(c);
    //Serial.println(checkAmt);
    // give response
    if (c > threshhold) 
    {
      CircuitPlayground.playTone(pitches[i], 100, false);
      input[checkAmt] = vals[i];
      checkAmt ++;
      
      for (int k=0; k<10; k++) 
      {
        CircuitPlayground.setPixelColor(k, 0, 0, 255);
      }
      delay(10);
    }
    else
    {
      for (int k=0; k<10; k++) 
      {
        CircuitPlayground.setPixelColor( k, 0, 0, 0);
      }
      delay(10);
    }
//
//
//    for(int g=0; g<4; g++)
//    {
//      Serial.print(String(input[g]) + " " );
//      
//    }
//   Serial.println();
    
    // check pass
    if (checkAmt == 4)
    {
      if (input[0] == pass [0] && input[1] == pass [1] && input[2] == pass [2] &&input[3] == pass [3]) //if all 4 slot matched
      {
        //light up green & play tone
        for (int k=0; k<10; k++) 
        {
          CircuitPlayground.setPixelColor( k, 0, 255, 0);
          CircuitPlayground.playTone(1500,100);
        }
        checkAmt =0; //reset condition
        for (int k=0; k<4; k++)  //reset input
        {
          input[k] = -1;
        }
        
      } 
      else // //light up red & play tone 
      {
        for (int k=0; k<10; k++) 
        {
          CircuitPlayground.setPixelColor( k, 255, 0, 0);
          CircuitPlayground.playTone(100,100);
        }
        checkAmt =0; //reset
        for (int k=0; k<4; k++) //reset input
        {
          input[k] = -1;
        }
      } 
    }

  }
  
  


  delay(100);
}
