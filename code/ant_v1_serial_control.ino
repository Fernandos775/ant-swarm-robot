#define IN1 12
#define IN2 13
#define IN3 14
#define IN4 15

unsigned long moveTime = 0;
bool isMoving = false;

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopMotors();
  
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);

  Serial.println("Муравей готов!");
  Serial.println("Команды: f b l r s");
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();

    if (cmd == 'f') { forward();  moveTime = millis(); isMoving = true; Serial.println("Вперёд"); }
    else if (cmd == 'b') { backward(); moveTime = millis(); isMoving = true; Serial.println("Назад"); }
    else if (cmd == 'l') { left();     moveTime = millis(); isMoving = true; Serial.println("Налево"); }
    else if (cmd == 'r') { right();    moveTime = millis(); isMoving = true; Serial.println("Направо"); }
    else if (cmd == 's') { stopMotors(); isMoving = false; Serial.println("Стоп"); }
  }

  // Автостоп через 2 секунды движения
  if (isMoving && millis() - moveTime > 2000) {
    stopMotors();
    isMoving = false;
    Serial.println("Автостоп");
  }
}

void forward()  { digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  }
void backward() { digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); }
void left()     { digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  }
void right()    { digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); }
void stopMotors() { 
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, LOW); 
}
