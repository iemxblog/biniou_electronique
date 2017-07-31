#include <CapacitiveSensor.h>

CapacitiveSensor b1 = CapacitiveSensor(2, 3);
CapacitiveSensor b2 = CapacitiveSensor(2, 4);
CapacitiveSensor b3 = CapacitiveSensor(2, 5);
CapacitiveSensor b4 = CapacitiveSensor(2, 6);
CapacitiveSensor b5 = CapacitiveSensor(2, 7);
CapacitiveSensor b6 = CapacitiveSensor(2, 8);
CapacitiveSensor b7 = CapacitiveSensor(2, 10);

const int led = 13;
const int jack = 9;
const int threshold = 100;
const int n_buttons = 7;

unsigned int base_freq = 932;
enum Mode {major, minor};
Mode mode = major;
const float st = 1.059463;

void setup()                    
{
   ADCSRA=0;  // disable ADC
   
   pinMode(led, OUTPUT);
   uint8_t fingering = 0;
   while(fingering != 64 && fingering != 32) {
    blink(50);
    fingering = getFingering();
   }
   if(fingering == 32)
    configMode();
   //ledOn();
   ledOff();
}

void configMode()
{
  uint8_t fingering = 0;

  sib();

  while(fingering != 64) {
    blink(1000);
    fingering = getFingering();
    switch(fingering) {
      case 1:
        base_freq *= st;
        sib();
        delay(1000);
        break;
      case 2:
        base_freq /= st;
        sib();
        delay(1000);
        break;
      case 4:
        mode=major;
        delay(1000);
        break;
      case 8:
        mode=minor;
        delay(1000);
        break;
    }
  }
}

void ledOn()
{
  digitalWrite(led, HIGH);
}

void ledOff()
{
  digitalWrite(led, LOW);
}

void blink(unsigned int ms)
{
  if(millis() % ms < ms/2)
    ledOn();
  else
    ledOff();
}

void la()
{
  switch(mode) {
    case major:
      tone(jack, base_freq/st);
      break;
    case minor:
      tone(jack, base_freq / pow(st, 2));
      break;
    default:
      break;
  }
}

void sib()
{
  tone(jack, base_freq);
}

void ut()
{
  tone(jack, base_freq * pow(st, 2));
}

void re()
{
  switch(mode) {
    case major:
      tone(jack, base_freq * pow(st, 4));
      break;
    case minor:
      tone(jack, base_freq * pow(st, 3));
      break;
    default:
      break;
  }
}

void mib()
{
  tone(jack, base_freq * pow(st, 5));
}

void mi()
{
  tone(jack, base_freq * pow(st, 6));
}

void fa()
{
  tone(jack, base_freq * pow(st, 7));
}

void sol()
{
  switch(mode) {
    case major:
      tone(jack, base_freq * pow(st, 9));
      break;
    case minor:
      tone(jack, base_freq * pow(st, 8));
      break;
    default:
      break;
  }
}

void lab()
{
  tone(jack, base_freq * pow(st, 10));
}

void la2()
{
  tone(jack, base_freq * pow(st, 11));
}

void sib2()
{
  tone(jack, base_freq * pow(st, 12));
}

void do2()
{
  tone(jack, base_freq * pow(st, 14));
}

uint8_t getFingering()
{
    bool pressed[n_buttons] = {
        b1.capacitiveSensor(30) > threshold
        , b2.capacitiveSensor(30) > threshold
        , b3.capacitiveSensor(30) > threshold
        , b4.capacitiveSensor(30) > threshold
        , b5.capacitiveSensor(30) > threshold
        , b6.capacitiveSensor(30) > threshold
        , b7.capacitiveSensor(30) > threshold
    };

    uint8_t fingering = 0;
    for(uint8_t i=0;i<n_buttons;i++)
      fingering |= pressed[i] ? 1<<i : 0;
    return fingering;
}

void loop()                    
{
    uint8_t fingering = getFingering();
    switch(fingering) {
      case 127:
        la();
        break;
      case 63:
        sib();
        break;
      case 31:
        ut();
        break;
      case 15:
        re();
        break;
      case 7:
        mib();
        break;
      case 11:
        mi();
        break;
      case 3:
        fa();
        break;
      case 1:
        sol();
        break;
      case 2:
        lab();
        break;
      case 0:
        la2();
        break;
      case 126:
        sib2();
        break;
      case 30:
        do2();
        break;
      default:
        noTone(jack);        
    } 
}
