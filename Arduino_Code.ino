#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


#define trigPin 10
#define echoPin 13

int switchPin = 9;   // momentary switch on 8, other side connected to ground
int Display = 0;
int duration;
int distance;
const int speakerPin = 8;

bool state = false;

String languages[4] = {"English", "French", "German", "Mandarin"};
String fare[4] = {"Bye!", "Adieu", "tschus", "Bai bai"};


void setup()
{
  lcd.begin(16, 2);
  pinMode(switchPin, INPUT);
  digitalWrite(switchPin, HIGH);      // turn on pullup resistor

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(speakerPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;

  if (digitalRead(switchPin) == HIGH) {
    state = true;
    delay(500);                        // delay to debounce switch

    Display ++;
    if (Display >= 4) {
   //   lcd.clear();
      Display = 0;
    }
    delay(200);
  }
  if (distance <= 20 || distance >= 2 && digitalRead(switchPin) == HIGH && state == true) {
    lcd.println(String(languages[Display]) + ":" + String(fare[Display]));    
              
                lcd.setCursor(1, 1);

    Serial.println(Display);
    Serial.println(String(languages[Display]) + ": " + String(fare[Display]));
   
    tone(speakerPin, 220);
    delay(200);
    noTone(speakerPin);
    delay(200);

  }

  else {
    Serial.println(Display);
    Serial.println(String(languages[Display]));
                lcd.setCursor(1, 1);

    lcd.println(String(languages[Display]));
    delay(200);
 
  }
  lcd.clear();
  state = false;

}




