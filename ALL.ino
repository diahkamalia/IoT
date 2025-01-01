#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <DHT.h>
DHT dht(2, DHT11); //Pin, Jenis DHT

int powerPin = 3;    // untuk pengganti VCC/5vOLT
int soilPin = A1;
int nilai ;
 
#define analogInPin A2 
#define analogOnPin A0


 //sambungkan kabel hitam (output) ke pin A0
int sensorValue = 0;
int sensorvalue1 = 0 ;        
float outputValue = 0.0;        
void setup() {
    lcd.init();
  // Print a message to the LCD.
    lcd.backlight(); 
  // jadikan pin power sebagai output
    pinMode(powerPin, OUTPUT);
  // default bernilai LOW
    digitalWrite(powerPin, LOW);
    lcd.clear();
  Serial.begin(9600);
  dht.begin();
}
void loop() {
  digitalWrite(powerPin, HIGH);
  
  float kelembaban = dht.readHumidity();
  float suhu = dht.readTemperature();

  Serial.print("kelembaban udara: ");
  Serial.print(kelembaban);
  Serial.print(" ");
  Serial.print("suhu: ");
  Serial.println(suhu);
  //read the analog in value:
  sensorValue = analogRead(analogInPin);
  //rumus didapat berdasarkan datasheet 
  outputValue = (-0.0139*sensorValue)+7.7851;
  Serial.print("nilai adc  = ");
  Serial.print(sensorValue);
  Serial.print("  output Ph= ");
  Serial.println(outputValue);
  int nilai = analogRead (soilPin);
  Serial.print ("kelembaban tanah = ");
  Serial.print(nilai);
  Serial.print("\n");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("KT");
  lcd.setCursor(3,0);
  lcd.print(nilai);
  lcd.setCursor(0,1);
  lcd.print("PH");
  lcd.setCursor(3,1);
  lcd.print(outputValue);
  lcd.setCursor(8,0);
  lcd.print("KU");
  lcd.setCursor(11,0);
  lcd.print(kelembaban);
  lcd.setCursor(8,1);
  lcd.print("SU");
  lcd.setCursor(11,1);
  lcd.print(suhu);



//   if(nilai > 700){a
//   Serial.println("  tanah kondisi kering");
//   }else if(nilai < 700 && nilai > 350){
//   Serial.println("  tanah kondisi normal");
//   }else{
//   Serial.println("  tanah kondisi basah");
  delay(1000);
// }
}