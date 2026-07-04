const int sensorPin = 34;
const int relayPin = 18;
unsigned long previousMillis = 0;
const long interval = 1000;
bool pumpState = false;
void setup()
{
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  Serial.println();
  Serial.println("=================================");
  Serial.println(" AUTOMATED IRRIGATION CONTROLLER ");
  Serial.println("=================================");
}
void loop()
{
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    int adcValue = analogRead(sensorPin);
    int moisture =
      map(adcValue, 4095, 0, 0, 100);
    moisture = constrain(moisture,0,100);
    if(!pumpState && moisture < 30)
    {
      pumpState = true;
    }
    if(pumpState && moisture > 45)
    {
      pumpState = false;
    }
    digitalWrite(relayPin,pumpState);
    Serial.println("--------------------------------");
    Serial.print("ADC Value : ");
    Serial.println(adcValue);
    Serial.print("Moisture  : ");
    Serial.print(moisture);
    Serial.println("%");
    if(moisture < 30)
      Serial.println("Status    : DRY");
    else if(moisture > 70)
      Serial.println("Status    : WET");
    else
      Serial.println("Status    : NORMAL");
    Serial.print("Pump      : ");
    if(pumpState)
      Serial.println("ON");
    else
      Serial.println("OFF");
    Serial.println("--------------------------------");
  }
}