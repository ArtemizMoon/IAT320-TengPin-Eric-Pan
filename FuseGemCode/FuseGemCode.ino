#include <Adafruit_CircuitPlayground.h>




int colorPresets[3][3][3] = 
{
  {{255,0,0} ,{0,255,0} ,{0,0,255}}, // red, green, blue
  
  {{0,0,255} ,{128,255,0} ,{128,128,0}}, // blue, light green, yellow
  
  {{255,0,0} ,{128,255,128} ,{128,255,128}} // blue, light yellowish green, light yellowish green
};

int preset = 0;


void setup() 
{
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() 
{

  float acc = abs(CircuitPlayground.motionX()) + abs(CircuitPlayground.motionY()) + abs(CircuitPlayground.motionZ());
  if (acc > 25) 
  {
    preset = rand() % 3;
  }
 


  for (int i=0; i<10; i++) 
  {
    CircuitPlayground.setPixelColor( i, colorPresets[preset][i%3][0], colorPresets[preset][i%3][1], colorPresets[preset][i%3][2]);
  }
  
  delay(10);
  //Serial.println(preset);
}
