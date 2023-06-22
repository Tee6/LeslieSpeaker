# LeslieSpeaker
Im Rahmen des HWE Projekts wurde ein Leslie Lautsprecher realisiert. Teammitglieder: Pius Bickel, Niko Leimegger

Niko Leimegger, Pius Bickel HWE-Übung Franz Lauritsch

![](RackMultipart20230622-1-fkn1xe_html_75aa094423f0afd.png)

Elektronik und technische Informatik

HWE Übungen Semester Projekt

Dokumentation zur Projektarbeit

# **Leslie Speaker**

**Anfangsdatum: 28.02.2023**

**Abgabedatum: 22.06.2023**

(Bild des fertigen Speakers)

**Projektteam:**

Niko Leimegger

Pius Bickel

**Betreuungslehrer:**

Franz Lauritsch

# Inhalt

[Abstract 3](#_Toc138316231)

[Pflichtenheft: 3](#_Toc138316232)

[Einleitung 3](#_Toc138316233)

[Arbeitsziel: 3](#_Toc138316234)

[Grobe Technische Einteilung 4](#_Toc138316235)

[(Rahmenbedingungen) 4](#_Toc138316236)

[Verwendete Entwicklungsoberflächen: 4](#_Toc138316237)

[Blockschaltbild: 4](#_Toc138316238)

[Hardware 5](#_Toc138316239)

[BLDC-Ansteuerung 5](#_Toc138316240)

[Simulation: 5](#_Toc138316241)

[Lautsprecher und Simulation des Resonanzkörpers: 7](#_Toc138316242)

[Lautsprecher: 7](#_Toc138316243)

[Simulation mit SubSim: 7](#_Toc138316244)

[Verstärker: 8](#_Toc138316245)

[Endstufe 9](#_Toc138316246)

[Spannungsversorgung: 10](#_Toc138316247)

[Simulation: 10](#_Toc138316248)

[PCB: 11](#_Toc138316249)

[Mechanik 12](#_Toc138316250)

[Gehäuse 12](#_Toc138316251)

[Entwicklung 12](#_Toc138316252)

[Designs 12](#_Toc138316253)

[Einzelne Bauteile: 12](#_Toc138316254)

[Software 13](#_Toc138316255)

[Struktogramme: 13](#_Toc138316256)

[Gesamter Code: 15](#_Toc138316257)

[Footswitch: 18](#_Toc138316258)

[Schaltung: 18](#_Toc138316259)

[PCB: 19](#_Toc138316260)

[Funktionstest 19](#_Toc138316261)

[Ausgabe am Arduino: 19](#_Toc138316262)

[Konklusion: 20](#_Toc138316263)

## Abstract

Der Leslie benötigt eine Betriebsspannung von 12V und mindestens 1A. Oben am Gehäuse sind 3 Steuerungsmöglichkeiten angebracht. Mit dem Dreiwegeschalter können Sie auswählen welche Signalquelle am Lautsprecher ausgegeben werden soll. Der Lautsprecher kann damit aktiv und passiv betrieben werden.

(Bild vom Schalter)

Mit dem Taster kann der Motor ausgeschalten werden, falls ausschließlich der Verstärker verwendet werden soll, oder man keine 1A zur Verfügung hat.

(Bild vom Taster)

Mit dem Drehregler kann die Lautstärke des Verstärkers geregelt werden.

(Bild vom Poti)

#

# Pflichtenheft:

## Einleitung

Ein Leslie Speaker ist ein passiver oder aktiver Lautsprecher, welcher im Inneren Schall mit Hilfe eines drehenden Objekts ("Cake") lenkt. Somit wird ein Effekt erzeugt, der in der Audiotechnik „Phaser" genannt wird. Leslie Speaker wurden früher bei Orgeln eingesetzt und später bei E-Gitarren. Heute gibt es Software und Digitale Schaltungen, die denselben Effekt nachahmen.

Beispiele für den Leslie gibt es in folgenden Liedern:

- Echoes – Pink Floyd
- Something – The Beatles
- Let It Loose – The Rolling Stones
- …

Im Rahmen des HWE Übungen Unterrichts ist es Ziel, einen solchen Lautsprecher innerhalb eines Semesters zu realisieren.

## Arbeitsziel:

  1. Leslie Cabinet mir variabler Drehfrequenz
    1. Holzgehäuse
    2. Styropor „Cake"
    3. DC-Motor Ansteuern
    4. Stabile Stromversorgung
    5. Knöpfe oder Potis zum steuern
  2. Erweiterungsmöglichkeiten
    1. Eingebauter Verstärker
    2. Display für Systemsteuerung
    3. Fußschalter

## Grobe Technische Einteilung

  1. Hardware
    1. Stromversorgung für µC und Motor
  2. Software
    1. Motor Ansteuerung mit Potentiometer und Knöpfen
  3. Mechanik
    1. Akustisch angepasstes und Standhaftes Gehäuse Bauen

## (Rahmenbedingungen)

| Projektmitarbeiter | Pius Bickel, Niko Leimegger |
| --- | --- |
| Beginn | 28.02.2023 |
| Betreuer | Prof. Franz Lauritsch |

#

# Verwendete Entwicklungsoberflächen:

| **Name** | **Version** |
| --- | --- |
| EAGLE | 9.6.2 |
| LTSpice XVII | 17.0.35.0 |
| Word | 2304 |
| Excel | 2304 |
| subsim.exe (by Isaac MCN) | http://users.on.net/~isaacmcn/audio/subsim/newsubsim.htm |
| SolidWorks | 2022-2023 |
| Arduino IDE | 2.1.1 |

# Blockschaltbild:

![](RackMultipart20230622-1-fkn1xe_html_d1d4638f0d24fd62.png)

_Abbildung 1: Blockschaltbild des ganzen Systems_

Das Signal wird verstärkt und am Lautsprecher ausgegeben. Die Klangführung, welche durch einen Arduino mit Motorsteuerung angetrieben wird, erzeugt durch die asymmetrische Form und Drehbewegung den typischen Leslie-Sound.

# Hardware

## BLDC-Ansteuerung

Anforderungen: Steuerung, um Styroporzylinder schnell und langsam drehen zu können.

Richtwert: mindestens 60 RPM, maximal 300-400 RPM.

Für den Motor, der die Klangführung rotiert, wird ein BLDC-Motor verwendet. Die Ansteuerung erfolgt durch eine einfache Transistor Schaltung, welche mit einem Arduino Nano gesteuert wird. Der Motor benötigt mindestens einen Duty Cycle von 50%, um ohne Probleme zu laufen, deshalb wird die Betriebsspannung des Leslies für den Motor mittels eines 7805 ICs auf 5V geregelt um ihn langsamer laufen lassen zu können.

![](RackMultipart20230622-1-fkn1xe_html_2ab4507770a3a710.png)

_Abbildung 2: Schaltung für den 5V Spannnungsregler_

![](RackMultipart20230622-1-fkn1xe_html_4fae6cf969593f4a.png)

_Abbildung 3: Schaltung der gesamten Motorsteuerung_

## Simulation:

![](RackMultipart20230622-1-fkn1xe_html_d2b856c274e89cc3.png)

_Abbildung 4: Spannung über dem Motor bei Duty Cycle 50%_

Man kann erkennen, dass die Spannung allmählich steigt und dann ein maximum erreicht. Es ist noch ein leichten Rippel zu erkennen der jedoch mit einem zusätzlichen Kondensator geglättet werden könnte. In der Praxis macht dieser Rippel hier keine Probleme.

![](RackMultipart20230622-1-fkn1xe_html_5ddb1a04eefda26a.png)

_Abbildung 5: Spannung über dem Motor bei einem Duty Cycle von 100%_

Bei einem 100%igen Duty Cycle steigt die Spannung um einiges schneller auf das Maximum, die Betriebsspannung.

Für diese simple Schaltung lohnt es sich eine Lochrasterplatine mit folgendem Layout zu benutzen: ![](RackMultipart20230622-1-fkn1xe_html_d064aa4506c20ac3.png)

_Abbildung 6: Layout der Lochrasterplatine für die Motorsteuerung_

## Lautsprecher und Simulation des Resonanzkörpers:

Anforderungen: Niederohmig für maximale Effizienz, ausgerichtet für 20W, Vollspektrum

### Lautsprecher:

Für Gitarrenverstärker sind 8 Zoll Lautsprecher üblich. Um einen maximalen Wirkungsgrad des Verstärkers zu erzielen, ist es sinnvoll, einen niederohmigen Lautsprecher zu benutzen wie hier mit einer Impedanz von 4 Ohm.

![](RackMultipart20230622-1-fkn1xe_html_727771cdba11e737.png)

_Abbildung 7: Datenblatt des Lautsprechers_

### Simulation mit SubSim:

![](RackMultipart20230622-1-fkn1xe_html_edc1323b0b2e16ff.png)

_Abbildung 8: Simulationsparameter_

_Abbildung 9: Simulationsergebnis_

U ![](RackMultipart20230622-1-fkn1xe_html_42337dfafa92771a.png) m das Verhalten des Lautsprechers zu simulieren, kann ein Subwoofer Simulationsprogramm wie Subsim verwendet werden.

In Grün erkennt man das Frequenzverhalten des Lautsprechers im Leslie inklusive Resonanzkörper. In Gelb kann man die Impedanz des Lautsprechers erkennen. Man sieht, dass der Widerstand bei der Resonanzfrequenz ein peak aufzeigt und ab ~2000Hz stetig steigt. In Rosa kann man die Phase der Impedanz erkennen.

Zusammengefasst kann man feststellen, dass der gewählte Lautsprecher für Musik geeignet ist, denn er dämpft nur im sehr tiefen Bass Bereich und im Hohen Frequenzbereich

## Verstärker:

Um den Lautsprecher auch aktiv betrieben zu können muss ein Verstärker eingebaut werden. Hier lohnt sich ein Klasse AB-Verstärker, denn er bietet einen Kompromiss zwischen Klangreinheit, Effizienz und Komplexität. Der Verstärker besteht aus mehreren Stufen:

![](RackMultipart20230622-1-fkn1xe_html_6454cb98b8db2600.png)

_Abbildung 10: Blockschaltbild des Verstärkers_

Das Signal (Amplitude: Gitarrensignal \<50mV, Aux (~500mV-1V)) wird vorverstärkt damit die Lautstärke eingestellt werden kann. Dies wird mit einer einfachen OP-Schaltung (Nicht invertierender Verstärker) bewirkt. Um von 0.5V auf maximal 10V zu kommen, benötigen wir eine Verstärkung von 20. R6 wäre als Potentiometer verbaut

![](RackMultipart20230622-1-fkn1xe_html_afcd9a33c217b8cc.png)

_Abbildung 11: Schaltung des Vorverstärkers_

## Endstufe

![](RackMultipart20230622-1-fkn1xe_html_46aca26672f0b7a5.png)

_Abbildung 12: Klasse AB-Endstufe mit OP_

Die Endstufe besteht aus einem Operationsverstärker und einer „Push-Pull" Transistor Konfiguration. Der OP regelt seinen Ausgang so, dass am Ausgang ein fast unverzerrtes Signal, erzeugt wird. Der NPN-Transistor verstärkt die positive halbwelle, der PNP die negative. R11 und R12 sollen den Strom bei hohen Temperaturen stabilisieren. Optional könnte man noch Dioden ober und unter dem Ausgang des OPs dazuschalten, jedoch hat dies in unserem Fall zu Übersteuerung und unnötigen Problemen geführt. Außerdem können Basiswiderstände zur Verbesserung des Arbeitspunktes dazugeschaltet werden. Diese haben ebenfalls zu unnötigen Problemen geführt, deshalb haben wir uns für dieses Design entschieden. Das Signal wird dann über einen Kondensator, der den DC-Anteil im Signal filtert am 4 Ohm Lautsprecher ausgegeben. Der Nachteil des AB-Verstärkers ist der hohe Ruhestrom. Er ist zwar kleiner als beim A-Verstärker jedoch liegt er beim Verbauten Transistor bei .

## Spannungsversorgung:

![](RackMultipart20230622-1-fkn1xe_html_2803f8105c1dbc4d.png)

_Abbildung 13: Schaltung der Spannungsversorgung_

Für den OP und die Endstufe werden minus Spannungen benötigt. Diese erzeugen wir mit einem einfachen Spannungsteiler. Dieser Ansatz ist nicht ideal, für unsere Anwendung jedoch ausreichend.

Wenn man den Punkt zwischen den Widerständen als Ground für die Schaltung definiert, ist der wirkliche Ground als -Vcc anzusehen.

Die Kondensatoren dienen als einfache Glättungsfilter.

### Simulation:

Eingangssignal: 20mV (Typisch für manche Tonabnehmer von E-Gitarren), 20kHz

![](RackMultipart20230622-1-fkn1xe_html_25f149c2513462d7.png)

_Abbildung 13: LTSpice Simulation des Verstärkers_

Obwohl eine leichte Phasenverschiebung zu erkennen ist, sieht man, dass die Spannung und der Strom des Signals verstärkt wurden.

### PCB:

Bei Audioanwendungen ist es ratsam, eine Platine zu erstellen:

D1, D2, R3, R4 und C4 sind optional zu bestücken, jedoch müssen die Dioden D1 und D2 mit einem Draht überbrückt werden. C4 wäre dafür da einen Tiefpass zu realisieren, falls hochfrequente Störungen am Lautsprecher stören würden.

![](RackMultipart20230622-1-fkn1xe_html_7cfaecd6354598ae.png)

_Abbildung 14: Layout der Platine_

Im Nachhinein sind folgende Punkte zu verbessern:

- Widerstände R5 und R6 weiter weg von den größten Wärmeerzeugern (BDX33C, BDX34C)
- Größeres Package für R7
- Größeres Package für C1 und C2

(Bild von der Bestückten Platine)

# Mechanik

## Gehäuse

Anforderungen: 3 Kammern, Stabil, akustisch fördernde Eigenschaften

### Entwicklung

Das Gehäuse besteht aus 3 Kammern, in der obersten Kammer befindet sich die Motorsteuerung, im mittleren der aus Styropor hergestellte „Cake", und im untersten Abteil der Verstärker und Lautsprecher.

### Designs

Das Ganze Gehäuse hat Außenmaße von 800mm \* 500mm \* 500mm, und eine Wandstärke von 12mm.

### Einzelne Bauteile:

_Abbildung 14: Frontplatte mit Loch für Schall_

_Abbildung 15: Seitenwände mit Fräsung_

 ![](RackMultipart20230622-1-fkn1xe_html_8aa24c3f1cf19fd1.png) ![](RackMultipart20230622-1-fkn1xe_html_71f6bbb0dd31e339.png) ![](RackMultipart20230622-1-fkn1xe_html_797e0a0b7896cf64.png)

_Abbildung 16: Gesamtkonstrukt_

Die Ober- und Unterplatte sowie die Zwischenböden wurden nach dem Zusammenbau korrekt zugeschnitten.

![](RackMultipart20230622-1-fkn1xe_html_cd7188331a763470.png)

_Abbildung 17: Verbindungsteil zwischen Motor und Klangführung_

Nachdem Leim allein keine ausreichend starke Verbindung zwischen Metall (Rotor) und Styropor herstellen kann, wird per 3D Druck ein Adapter gefertigt, der mittels Schrauben und Leim festgemacht ist, und am Rotor ausschließlich durch Reibung festgehalten wird.

Bei einer zweiten Version wäre es sinnvoll, den Halter vom Rotor zu stützen damit die Fliehkräfte weniger Auswirkung auf die Drehbewegung haben.

#### Fertiges Gehäuse

![](RackMultipart20230622-1-fkn1xe_html_3f110259a2f7a86a.jpg) ![](RackMultipart20230622-1-fkn1xe_html_dd128bb74d60ccf3.jpg)

Die Tonkammer für den Lautsprecher wurde mit Styropor abgedichtet, um einen besseren Klang zu realisieren.

# Software

Anforderungen: Motor PWM steuern, Taster abfragen.

Eigentlich war für dieses Projekt eine MEGACARD vorhergesehen, durch Schwierigkeiten in der permanenten Beschaffung einer MEGACARD hat sich ein Arduino Nano als ökonomischer herauskristallisiert.

Software geschrieben in der Arduino IDE

## Struktogramme:

![](RackMultipart20230622-1-fkn1xe_html_138ae5fa6439a7fa.png)

_Abbildung 12 Struktogramm der Motor-Startup-Routine_

![](RackMultipart20230622-1-fkn1xe_html_a8edf7251a240b13.png)

_Abbildung 13 Struktogramm der Motor-Stopp-Routine_

![](RackMultipart20230622-1-fkn1xe_html_6bee5cc24e22b176.png)

_Abbildung 18: Struktogramm für die Setup Funktion_

![](RackMultipart20230622-1-fkn1xe_html_20e69655273aceb0.png)

_Abbildung 19: Struktogramm des Main programms_

## Gesamter Code:

// PWM1 fuer Leslie Speaker

constint pwmPin = 5; // Define the PWM pin

constint startupTime = 5000;   // Zeit für das Hochfahren in Millisekunden

constint Foot1 = 5; // Fußschalter Taster 1

constint Foot2 = 2; // Fußschalter Taster 2

constint Foot3 = 3; // Fußschalter Taster 3

constint Switch = 7; // Schalter um den Motor ein und aus zu stellen

volatilebool motoron;  // Boolean variable um Status des Motors festzustellen

volatileint duty = 128;  // Standard DutyCycle (50%)

voidsetup(){

  Serial.begin(9600); // Serielle Kommunikation starten um Tasterabfragen zu überprüfen

  pinMode(pwmPin, OUTPUT); // PWM Pin als Output

  pinMode(Foot1, INPUT\_PULLUP); // Pins für den Fußschalter auf Input inklusive Pullup Widerstand

  pinMode(Foot2, INPUT\_PULLUP);

  pinMode(Foot3, INPUT\_PULLUP);

  pinMode(Switch, INPUT\_PULLUP);

  TCCR1B = TCCR1B & B11111000 | B00000001; // Register für schnellere Schaltgeschwindigkeiten.

  startupMotor(duty); // Motor auf Standard DutyCycle (DC) hochfahren

  motoron = true;     // Motor als an definieren

}

voidloop(){

// Wenn Taster 1 gedrückt wurde, DC um 10 verkleinern außer der DC ist schon bei 50% + Ausgabe an den Serial Monitor

  if(digitalRead(Foot1) == LOW){ // Tasterabfrage

    duty = duty - 10; // DC verkleinern

    if(duty \<= 128){duty = 128;}; // Mindest DC: 50%

    // Ausgabe am Serial Monitor:

    Serial.print("Langsamer (dutycycle: ");

    Serial.print(duty);

    Serial.println(")");

     delay(150); // Tasterprellen vermeiden

     }

// Wenn Taster am Gehäuse oder am Fußschalter in der Mitte gedrückt: Motor an bzw. Ausschalten

    if(digitalRead(Foot2) == LOW || digitalRead(Switch) == LOW){ // Tasterabfrage

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

  if(digitalRead(Foot3) == LOW){ // Tasterabfrage

   duty = duty + 10;  // DC erhöhen

     if(duty \>= 255){duty = 255;} // Höchster DC: 255 = 100%

    // Ausgabe

    Serial.print("Schneller (dutycycle: ");

    Serial.print(duty);

    Serial.println(")");

     delay(150);

     }

    // PWM ausgeben

    analogWrite(pwmPin, duty);

}

voidstartupMotor(inttargetDutyCycle){

  int currentDutyCycle = 0;   // Aktueller Duty Cycle

  int increment = 5;   // Inkrement zur Erhöhung des Duty Cycles

  int incrementDelay = startupTime / (targetDutyCycle / increment);   // Verzögerung zwischen den Inkrementen

  // Hochfahren des Motors

  while(currentDutyCycle \<= targetDutyCycle){

    analogWrite(pwmPin, currentDutyCycle);   // Duty Cycle auf den Motor-Pin schreiben

    currentDutyCycle += increment;   // Duty Cycle erhöhen

    delay(incrementDelay);   // Verzögerung zwischen den Inkrementen

  }

  duty = targetDutyCycle; // derzeitiger DC umschreiben auf normalen DC

  analogWrite(pwmPin, duty);

  motoron = true;

}

voidstopMotor(){

    // Motor allmählich stoppen

  for(int speed = duty; speed \>= 0; speed--){

    analogWrite(pwmPin, speed);  // Geschwindigkeit setzen

    delay(10);  // Kleine Verzögerung, um die Veränderung wahrnehmbar zu machen

    duty = speed;

  }

  motoron = false;

  }

## Footswitch:

![Shape10](RackMultipart20230622-1-fkn1xe_html_b88b3739c7a56b12.gif) ![Shape9](RackMultipart20230622-1-fkn1xe_html_3141aa4944e08436.gif) ![Shape8](RackMultipart20230622-1-fkn1xe_html_6b354d5a266156b1.gif) ![Shape7](RackMultipart20230622-1-fkn1xe_html_1929a77e26729bd2.gif) ![Shape6](RackMultipart20230622-1-fkn1xe_html_1929a77e26729bd2.gif) ![Shape5](RackMultipart20230622-1-fkn1xe_html_1929a77e26729bd2.gif)

Taster 3 : Schneller

Taster 2 : Ein / Aus

Taster 1 : Langsamer

 ![Grafik 1](RackMultipart20230622-1-fkn1xe_html_a4817af64916722c.gif)

_Abbildung 8 Footswitch mit Taster Beschriftung_

Für die Steuerung des ganzen Systems verwenden wir einen Fußschalter eines Diktiergeräts.

### Schaltung:

Um die einzelnen Switches einfach mit dem Arduino ansprechen zu können, war es leichter eine neue Platine zu designen, als den internen Bus abzufragen. Die Schaltung leitet lediglich einen Pin auf alle anderen und somit kann man abfragen welcher Pin z.B. an Vcc anliegt.

![](RackMultipart20230622-1-fkn1xe_html_d9014f56a2e2b48d.png)

_Abbildung 9 Schaltplan der Verbindungsplatine im Footswitch_

### PCB:

![](RackMultipart20230622-1-fkn1xe_html_c1184b8e1172fde5.png)

_Abbildung 10 Boardplan der Verbindungsplatine_

## Funktionstest

### Ausgabe am Arduino:

Langsamer : Taster 1 links

Ein/Aus : Taster 2 in der Mitte

Schneller: Taster 3 rechts

![](RackMultipart20230622-1-fkn1xe_html_f044ca4e73694f8d.png)

_Abbildung 20: UART-Ausgabe des Arduino während der Geschwindigkeitsanpassung_

# Konklusion:

Es wurde ein Leslie Speaker realisiert, der Passiv sowie Aktiv betrieben werden kann. Der Verstärker im Lautsprecher hat eine maximale Ausgangsleistung von 20W. Der Motor des Lautsprechers kann Mit einem externen Fußschalter gesteuert werden. Im Projekt wurden Elektrotechnische-, Softwaretechnische- und Mechanische Elemente verbaut und entwickelt. Erweiterungsmöglichkeiten wären zum Beispiel ein Bluetooth Modul um Wireless Musik abspielen zu können, Verzierung des Gehäuses, Rollen auf der Unterseite des Gehäuses, neuer Adapter zwischen Rotor und Klangführung für stabilere Anwendung.

![Shape12](RackMultipart20230622-1-fkn1xe_html_7b89e2691ea754f7.gif) ![Shape11](RackMultipart20230622-1-fkn1xe_html_59017ec3759b462e.gif)

20
