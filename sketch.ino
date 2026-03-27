#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// 1. Definirea pinilor (cablaj)
#define TRIG_PIN 9
#define ECHO_PIN 10
#define GREEN_LED 4
#define YELLOW_LED 5
#define RED_LED 6
#define BUZZER_PIN 7

// 2. Initializarea ecranului LCD (Adresa I2C standard 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Setam comportamentul pinilor (Intrare sau Iesire)
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  
  pinMode(BUZZER_PIN, OUTPUT);

  // Pornim ecranul
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  lcd.setCursor(0, 1);
  lcd.print("System Ready...");
  delay(2000); // Pauza de 2 secunde pentru mesajul de start
  lcd.clear();
}

// Functie separata pentru a citi distanta de la senzorul cu ultrasunete
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG_PIN, HIGH); // Trimitem pulsul ultrasonic
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Citim cat timp a durat pana s-a intors unda (microsecunde)
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculam distanta in centimetri (Viteza sunetului = 0.034 cm/us)
  int distance = duration * 0.034 / 2; 
  return distance;
}

void loop() {
  int distance = getDistance(); // Apelam functia de mai sus

  // Afisam distanta pe primul rand al LCD-ului
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm    "); // Spatiile goale sterg caracterele vechi

  // Logica de asistenta la parcare
  lcd.setCursor(0, 1);
  
  if (distance > 200) {
    // Zona SIGURA (> 2 metri)
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
    noTone(BUZZER_PIN); // Oprim sunetul
    lcd.print("Status: SAFE    ");
  } 
  else if (distance > 100 && distance <= 200) {
    // Zona de AVERTIZARE (1 - 2 metri)
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    
    // Buzzer-ul suna intermitent
    tone(BUZZER_PIN, 1000); 
    delay(100);
    noTone(BUZZER_PIN);
    
    lcd.print("Status: WARNING ");
  } 
  else {
    // Zona de PERICOL (< 1 metru)
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    
    // Buzzer-ul suna continuu (ca la masini)
    tone(BUZZER_PIN, 1000); 
    lcd.print("Status: STOP!   ");
  }

  delay(200); // Pauza pentru stabilitatea simularii
}