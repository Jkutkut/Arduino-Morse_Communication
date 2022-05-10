#define IR_SENSOR 7
#define LED 8

#define ON 1
#define OFF 0

void setup() {
  Serial.begin(9600);
  Serial.println("INITIALIZING");
  pinMode(IR_SENSOR, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED, OUTPUT);
}

void set_on() {
   digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED, HIGH);
}

void set_off() {
   digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(LED, LOW);
}

void loop() {
  static int current = OFF;
  int actual = digitalRead(IR_SENSOR);
  Serial.print("IR: ");
  Serial.println(actual);

  delay(300);
  // if (actual != current) {
  //   current = actual;
  //   Serial.println(actual);
  //   if (actual == ON)
  //     set_on();
  //   else
  //     set_off();
  // }
}
