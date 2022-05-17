#define UNIT_TIME 200
#define DEBUG_LIGHT 0

#define SENDER 0
#define RECEIVER 1

#define LED 8
// #define SENSOR A0

/* * MORSE LOGIC * */

const char *morseKey = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const char *morseValue[] = {
  " ",
  ".-",
  "-...",
  "-.-.",
  "-..",
  ".",
  "..-.",
  "--.",
  "....",
  "..",
  ".---",
  "-.-",
  ".-..",
  "--",
  "-.",
  "---",
  ".--.",
  "--.-",
  ".-.",
  "...",
  "-",
  "..-",
  "...-",
  ".--",
  "-..-",
  "-.--",
  "--.."
};

void set_on() {
  if (DEBUG_LIGHT)
    digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(LED, HIGH);
}

void set_off() {
  if (DEBUG_LIGHT)
    digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(LED, LOW);
}

void wait(int s)
{
  delay(s * UNIT_TIME);
}

void dot()
{
  set_on();
  wait(1);
  set_off();
  wait(1);
}

void line()
{
  set_on();
  wait(3);
  set_off();
  wait(1);
}

void space()
{
  wait(3); // 3 dots + 2 spaces on the sides
}

/**
 * @brief Outputs the given morse character (string) using the Light system.
 * 
 * @param str Morse string to output.
 */
void morse(const char *str)
{
  while (*str)
  {
    if (*str == '.')
      dot();
    else if (*str == '-')
      line();
    else
      space();
    str++;
  }
}

/**
 * @brief Outputs the given string using the Light system.
 * 
 * @param str Message to output.
 */
void stomorse(const char *str)
{
  int i;
  while (*str)
  {
    i = 0;
    while (morseKey[i] != *str)
      i++;
    morse(morseValue[i]);
    str++;
  }
}

/* * CODE * */

int mode;

void setup() {
	Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(A0, INPUT);

  mode = RECEIVER;
}

#define A 1000 // Resistencia en oscuridad en KOhm
#define B 15 // Resistencia a la luz (10 lux) en KOhm
#define RC 10 // Resistencia calibración en KOhm
int readLight() {
  int v = analogRead(A0);
  return ((long) v * A * 10) / ((long) B * RC * (1024 - v));
}

int readResult;

void loop() {
  switch (mode)
  {
  case SENDER:
    Serial.println("Sender mode");
    if (Serial.available())
    {
      char c = Serial.read();
      Serial.print("Sending: ");
      Serial.println(c);
      stomorse(&c);
    }
    break;
  case RECEIVER:
    // Serial.println("Receiver mode");
    readResult = analogRead(A0);
    // Serial.print("Input: ");
    Serial.println(readResult);
    delay(100);
    return;
  default:
    Serial.println("Unknown mode");
    break;
  }
  delay(1000);
}
