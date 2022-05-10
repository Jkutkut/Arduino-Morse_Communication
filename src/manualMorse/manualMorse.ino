#define BTN 5
#define LED 8

#define ON 1
#define OFF 0

void setup() {
  Serial.begin(9600);
  pinMode(BTN, INPUT);
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
  int actual = digitalRead(BTN);

  if (actual != current) {
    current = actual;
    Serial.println(actual);
    if (actual == ON)
      set_on();
    else
      set_off();
  }
  delay(40);
}
