// Ultrasonic configuration
// Motor pins
int ENA = 5;
int ENB = 6;
int IN1 = 7;
int IN2 = 8;
int IN3 = 9;
int IN4 = 4;

// Ultrasonic sensors
const int trigLeft = 10;
const int echoLeft = 11;
const int trigRight = 12;
const int echoRight = 13;


const int trigFront = 2;
const int echoFront = 3;

long durationLeft, durationRight, durationFront;
int distLeft, distRight, distFront;

void setup() {
  Serial.begin(9600);

  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);
  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);
  
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

// --- measure distance ---
int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000); 
  if (duration == 0) return 999;                
  return duration * 0.034 / 2;
}

void loop() {
  distLeft = getDistance(trigLeft, echoLeft);
  distRight = getDistance(trigRight, echoRight);
  distFront = getDistance(trigFront, echoFront);

  Serial.print("L: "); Serial.print(distLeft);
  Serial.print("R: "); Serial.print(distRight);
  Serial.print("F: "); Serial.println(distFront);

  
  // normal behavior
  if (distLeft > 10 && distRight > 10) {
    adjustDirection(distLeft, distRight);
  } else {
    stopCar();
  }

  delay(100);
}

// --- adjust direction ---
void adjustDirection(int left, int right) {
  int baseSpeed = 150;
  int diff = left - right;

  if (abs(diff) < 5) {
    moveBackward(baseSpeed, baseSpeed);
  } else if (diff > 0) {
    moveBackward(baseSpeed - 30, baseSpeed + 30);
  } else {
    moveBackward(baseSpeed + 30, baseSpeed - 30);
  }
}

// --- motor control ---
void moveBackward(int leftSpeed, int rightSpeed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);
}
// --- stop ---
void stopCar() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
