int led = 13;
void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  Serial.begin(9600);
}
void loop()
{
  if (Serial.available() > 0) { // Check if data is available to read
    char incomingByte = Serial.read(); // Read the incoming byte
 
    if (incomingByte == '1') {
      digitalWrite(led, LOW); // Turn on motor
      Serial.println("LED ON");
    }
    else{
      digitalWrite(led, HIGH); // Turn LED off
      Serial.println("LED OFF");
    }
  }
}
 