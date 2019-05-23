
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
Adafruit_NeoPixel pixels;
int numPixels = 50;
int nbLedByPart = 14;
int nbLedByBlanckPart = 4;
int startMan = 0;
int endMan = nbLedByPart;
int startComputer = nbLedByPart + nbLedByBlanckPart;
int endComputer = nbLedByPart * 2 + nbLedByBlanckPart;
int startWoman = nbLedByPart * 2 + nbLedByBlanckPart * 2;
int endWoman = numPixels;

enum Mode
{
  Computer = 0,
  BlinkComputer,
  TalkingMale,
  TalkingFemale,
  ActionMale,
  ActionFemale,
  All,
};

Mode mode = Computer;
unsigned long time = 0;
String inputString = "";
boolean stringComplete = false;
#define BLINKINGDISLAY 250
#define BLINKINGHIDE 2125
#define BLINKINGTIME (BLINKINGDISLAY + BLINKINGHIDE)

void setup()
{
  Serial.begin(9600);
  inputString.reserve(200);
  pixels = Adafruit_NeoPixel(numPixels, PIN, NEO_GRB + NEO_KHZ800);

#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
}

void loop()
{
  readInput();
  displayMode();
}

void readInput()
{
  while (Serial.available())
  {
    char inChar = (char)Serial.read();
    if (inChar == '$')
      stringComplete = true;
     else
      inputString += inChar;
  }
  if (stringComplete)
  {
    //Serial.println(inputString);
    mode = (Mode)inputString.toInt();
    time = millis();
    pixels.clear();
    inputString = "";
    stringComplete = false;
  }
}

void displayMode()
{
  boolean blinking = ((time - millis()) % BLINKINGTIME) <= BLINKINGDISLAY;
  if (mode == Computer)
  {
    for(int i = startComputer; i < endComputer; ++i)
      pixels.setPixelColor(i, pixels.Color(150,0,0));
  }
  else if (mode == BlinkComputer)
  {
    if (blinking)
      pixels.clear();
    else
    {
      for(int i = startComputer; i < endComputer; ++i)
        pixels.setPixelColor(i, pixels.Color(10,0,0));
    }
  }
  else if (mode == TalkingMale)
  {
    for(int i = startMan; i < endMan; ++i)
      pixels.setPixelColor(i, pixels.Color(0,150,0));
  }
  else if (mode == TalkingFemale)
  {
    for(int i = startWoman; i < endWoman; ++i)
      pixels.setPixelColor(i, pixels.Color(0,0,150));
  }
  else if (mode == ActionMale)
  {
    if (blinking)
      pixels.clear();
    else
    {
      for(int i = startMan; i < endMan; ++i)
        pixels.setPixelColor(i, pixels.Color(0,10,0));
    }
  }
  else if (mode == ActionFemale)
  {
    if (blinking)
      pixels.clear();
    else
    {
      for(int i = startWoman; i < endWoman; ++i)
        pixels.setPixelColor(i, pixels.Color(0,0,10));
    }
  }
  else if (mode == All)
  {
    for(int i = startComputer; i < endComputer; ++i)
      pixels.setPixelColor(i, pixels.Color(10,0,0));
    for(int i = startMan; i < endMan; ++i)
      pixels.setPixelColor(i, pixels.Color(0,10,0));
    for(int i = startWoman; i < endWoman; ++i)
      pixels.setPixelColor(i, pixels.Color(0,0,10));
  }
  pixels.show();
}
