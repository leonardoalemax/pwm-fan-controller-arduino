#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();


  pinMode(10,OUTPUT); //1B
  setupTimer();

  setPWM(0.2f);
}

void loop() {
  delay(100);

  float temp = dht.readTemperature();
  float percent = temperaturaParaPorcentagem(temp);

  Serial.print("Temperature:");
  Serial.print(temp);
  Serial.println("C");

  Serial.print("Fan speed:");
  Serial.print(percent);
  Serial.println("%");

  setPWM(percent); 
}


float temperaturaParaPorcentagem(float temperatura) {
    if (temperatura < 25) {
        return 0.0f;
    } else if (temperatura > 60) {
        return 1.0f;
    } else {
        return ((float)(temperatura - 25) / (60 - 25));
    }
}

void setupTimer(){
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
    TCCR1B = (1 << CS10) | (1 << WGM13);
    ICR1 = 320;
    OCR1A = 0;
    OCR1B = 0;
}

void setPWM(float f){
    f=f<0?0:f>1?1:f;
    OCR1B = (uint16_t)(320*f);
}
