#include <Servo.h> 
#include <IRremote.h>

int val;
Servo s1;
Servo s2;
int x=90;
int y=90;
const int pinServo1 = 11;
const int pinServo2 = 12;
// Pin di input per il ricevitore infrarossi
const int pinIR = 9;
const int pinMotore = 13;
// Oggetto per gestire il ricevitore IR
//IRrecv irrecv(pinIR);

// Struttura per memorizzare i dati del segnale IR
//decode_results results;
// sx = F708FF00; dx = A55AFF00
// high = E718FF00; low = AD52FF00
//sium = E31CFF00

void setup() {
  Serial.begin(9600);
  pinMode(pinMotore, OUTPUT);
   IrReceiver.begin(pinIR, ENABLE_LED_FEEDBACK);
   s1.attach(pinServo1);
   s2.attach(pinServo2);
   s1.write(x);
   s2.write(y);
}

void loop() {
  if (IrReceiver.decode()) {
    // Stampa il codice del pulsante premuto
    auto rawdata = IrReceiver.decodedIRData.decodedRawData; 
    //Serial.println(rawdata, HEX);
    switch(rawdata){
      //sx
      case 0xF708FF00: 
        Serial.println("sx");
        x=x+10;
        s1.write(x);
      break;
      //dx
      case 0xA55AFF00: 
        Serial.println("dx");
        x=x-10;
        s1.write(x);
        break;
      //high
      case 0xE718FF00: 
        y=y+10;
        s2.write(y);
        Serial.println("high");
      break;
      //low
      case 0xAD52FF00: 
        y=y-10;
        s2.write(y);
        Serial.println("low");
      break;
      //sium
      case 0xE31CFF00: 
        Serial.println("SIUUUUM");
        analogWrite(pinMotore, 255);
        delay(4000);
        analogWrite(pinMotore, 0);

      break;

      default: break;

    }
    // Ripeti la ricezione del segnale IR
    IrReceiver.resume();
  }
}
