#include <HX711.h> // Inkluderar libary.

#define DOUT  3 // Definerar portar för load-cellen och dess cchipp HX711.
#define CLK  2 

HX711 scale(DOUT, CLK); // Ansluter portarna 3 och 2 till HX711 chippet digitallt.

float kalbritation_faktor = 8; //Definerar kalibrationsfaktor till standradvärde 8 som sen kan finjusteras i funktionen.
float units;  


void setup() {
  Serial.begin(9600); //Startar kontakt med load cellen och BT modulen.
  Serial.println("Ta bort objekt fran vagen");// skriver ut meddelande i serial monitorn.
  Serial.println("Satt kand vikt pa vagen"); //
  Serial.println("Andra kalibrationsfaktorn med '+' och '-' tills ratt vikt visas"); //
  scale.set_scale(); //Nollsätter skalan från tidigare mätningar 
  scale.tare(); //
  long zero_factor = scale.read_average(); // Införskaffar en nollfaktor som är ett tal som kan andvänds för att slippa nollställa vågen i loopen senare, samt presenterar den. 
  Serial.print("Noll faktorn ar: "); //
  Serial.println(zero_factor); //
}

void loop() {
  scale.set_scale(kalbritation_faktor); // Andvänder den nya kalibratitionsfaktorn i algoritmen.
  Serial.print("Vikt i gramm: "); // Skriver ut...
  units = scale.get_units(), 10; // Införskaffar vikten och lagrar resultat i "units", i gram som standard.
  if (units < 0)// Sätter ev negativ vikt till 0.00 gram.
  {
    units = 0;
  }
  if (units >= 950 || units <= 1050 ) //Sats som avgör om det är ett mjölkpaket(1000g) och försummar felmarginalen, notera att för fler objekt behövs fler if- satser med olika vikter.
  {
    units = 1000;
  }
  //if(matosakerhet pa objekt)// Utvecklingsmöjlighet på koden som kan göras om oändligt många gånger som if-satser.
  //{
  //  units=xxxx
  //}
  Serial.print(units); //Detta ska modifieras som enda "serial.print" om den ska visas i appen, om infomation ska visas i seriella monitorn låt vara.
  Serial.print(" kalbritation_faktor: ");// Skriver ut mneddelande i serial monitorn.
  Serial.print(kalbritation_faktor); // Skriver ut den använda kalibrationsfaktorn till respektive mätning.
  Serial.println(); //Skapar ny rad till nästa mätning i seriella monitorn.
  delay(1000); // Tidsintervall mellan varje mätning.
}
