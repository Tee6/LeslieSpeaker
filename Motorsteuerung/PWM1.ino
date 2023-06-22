// PWM1 fuer Leslie Speaker

const int pwmPin = 5; // Define the PWM pin
const int startupTime = 5000;   // Zeit für das Hochfahren in Millisekunden
const int Foot1 = 5; // Fußschalter Taster 1
const int Foot2 = 2; // Fußschalter Taster 2
const int Foot3 = 3; // Fußschalter Taster 3
const int Switch = 7; // Schalter um den Motor ein und aus zu stellen
volatile bool motoron;  // Boolean variable um Status des Motors festzustellen
volatile int duty = 128;  // Standard DutyCycle (50%)

void setup() {
  Serial.begin(9600); // Serielle Kommunikation starten um Tasterabfragen zu überprüfen
  pinMode(pwmPin, OUTPUT); // PWM Pin als Output

  pinMode(Foot1, INPUT_PULLUP); // Pins für den Fußschalter auf Input inklusive Pullup Widerstand
  pinMode(Foot2, INPUT_PULLUP);
  pinMode(Foot3, INPUT_PULLUP);
  pinMode(Switch, INPUT_PULLUP);
  
  TCCR1B = TCCR1B & B11111000 | B00000001; // Register für schnellere Schaltgeschwindigkeiten.
  
  startupMotor(duty); // Motor auf Standard DutyCycle (DC) hochfahren
  motoron = true;     // Motor als an definieren
}

void loop() {

// Wenn Taster 1 gedrückt wurde, DC um 10 verkleinern außer der DC ist schon bei 50% + Ausgabe an den Serial Monitor
  if (digitalRead(Foot1) == LOW){ // Tasterabfrage
    duty = duty - 10; // DC verkleinern
    if (duty <= 128) {duty = 128;}; // Mindest DC: 50%
    // Ausgabe am Serial Monitor:
    Serial.print("Langsamer (dutycycle: ");
    Serial.print(duty);
    Serial.println(")");
     delay(150); // Tasterprellen vermeiden
     }

// Wenn Taster am Gehäuse oder am Fußschalter in der Mitte gedrückt: Motor an bzw. Ausschalten
    if (digitalRead(Foot2) == LOW || digitalRead(Switch) == LOW){ // Tasterabfrage
        if(motoron){  // Motor ausschalten + Ausgabe Serial Monitor
               motoron = false;
               Serial.println("Aus");
               stopMotor();
               delay(150);
        }else{  // Motor einschalten wenn er aus war
               motoron = true;
               Serial.println("Ein");
               startupMotor(200);
               delay(150);
      }
     }

// Wenn Taster 3 am Fußschalter gedrückt, DC um 10 erhöhen
  if (digitalRead(Foot3) == LOW){ // Tasterabfrage
   duty = duty + 10;  // DC erhöhen
     if(duty >= 255){duty = 255;} // Höchster DC: 255 = 100%
      
    // Ausgabe
    Serial.print("Schneller (dutycycle: ");
    Serial.print(duty);
    Serial.println(")");
     delay(150);
     }

    // PWM ausgeben
    analogWrite(pwmPin, duty);
}

void startupMotor(int targetDutyCycle) {
  int currentDutyCycle = 0;   // Aktueller Duty Cycle
  int increment = 5;   // Inkrement zur Erhöhung des Duty Cycles
  int incrementDelay = startupTime / (targetDutyCycle / increment);   // Verzögerung zwischen den Inkrementen

  // Hochfahren des Motors
  while (currentDutyCycle <= targetDutyCycle) {
    analogWrite(pwmPin, currentDutyCycle);   // Duty Cycle auf den Motor-Pin schreiben
    currentDutyCycle += increment;   // Duty Cycle erhöhen
    delay(incrementDelay);   // Verzögerung zwischen den Inkrementen
  }
  duty = targetDutyCycle; // derzeitiger DC umschreiben auf normalen DC
  analogWrite(pwmPin, duty);
  motoron = true;
}

void stopMotor(){
    // Motor allmählich stoppen
  for (int speed = duty; speed >= 0; speed--) {
    analogWrite(pwmPin, speed);  // Geschwindigkeit setzen
    delay(10);  // Kleine Verzögerung, um die Veränderung wahrnehmbar zu machen
    duty = speed;
  }
  motoron = false;
  }
