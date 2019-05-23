
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
Adafruit_NeoPixel pixels;
int numPixels = 50;
int nbLedByPart = 14;
int nbLedByBlanckPart = 4;
#define BLINKINGTIME 2500
#define BLINKINGTIME_DISPLAY (BLINKINGTIME / 2)

enum Mode
{
  Computer = 0,
  BlinkComputer,
  TalkingMale,
  TalkingFemale,
  ActionMale,
  ActionFemale,
};

Mode mode = Computer;
unsigned long time = 0;
String inputString = "";
boolean stringComplete = false;

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
  boolean blinking = ((time - millis()) % BLINKINGTIME) <= BLINKINGTIME_DISPLAY;
  if (mode == Computer)
  {
    for(int i =nbLedByPart + nbLedByBlanckPart; i < nbLedByPart * 2 + nbLedByBlanckPart; ++i)
      pixels.setPixelColor(i, pixels.Color(150,0,0));
  }
  else if (mode == BlinkComputer)
  {
    if (blinking)
      pixels.clear();
    else
    {
      for(int i = nbLedByPart + nbLedByBlanckPart; i < nbLedByPart * 2 + nbLedByBlanckPart; ++i)
        pixels.setPixelColor(i, pixels.Color(10,0,0));
    }
  }
  else if (mode == TalkingMale)
  {
    for(int i = 0; i < nbLedByPart; ++i)
      pixels.setPixelColor(i, pixels.Color(0,150,0));
  }
  else if (mode == TalkingFemale)
  {
    for(int i = nbLedByPart * 2 + nbLedByBlanckPart ; i < numPixels; ++i)
      pixels.setPixelColor(i, pixels.Color(0,0,150));
  }
  else if (mode == ActionMale)
  {
    if (blinking)
      pixels.clear();
    else
    {
      for(int i = 0; i < nbLedByPart; ++i)
        pixels.setPixelColor(i, pixels.Color(0,10,0));
    }
  }
  else if (mode == ActionFemale)
  {
    if (blinking)
      pixels.clear();
    else
    {
      for(int i = nbLedByPart * 2 + nbLedByBlanckPart; i < numPixels; ++i)
        pixels.setPixelColor(i, pixels.Color(0,0,10));
    }
  }
  pixels.show();
}
