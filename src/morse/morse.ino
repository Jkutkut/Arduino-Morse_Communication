#define UNIT_TIME 200
#define DEBUG_LIGHT 0

#define LED 8
#define SENSOR A0

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
int stomorse(const char *str)
{
  int i;
  while (*str && *str != '\n')
  {
    i = 0;
    while (morseKey[i] && morseKey[i] != *str)
      i++;
    if (!morseKey[i])
      return 0;
    morse(morseValue[i]);
    str++;
  }
  return 1;
}

/* * CODE * */

int mode;

// SENDER MODE
#define SENDER 0
#define BUFFER_SIZE 256
char senderBuffer[BUFFER_SIZE];


// RECEIVER MODE
#define RECEIVER 1
#define A 1000 // Resistencia en oscuridad en KOhm
#define B 15 // Resistencia a la luz (10 lux) en KOhm
#define RC 10 // Resistencia calibración en KOhm

int i = 0;
int avgON = 0;
int avgOFF = 0;
int light;

char receiverBuffer[BUFFER_SIZE * 7];

int readLight() {
  int v = analogRead(SENSOR);
  return ((long) v * A * 10) / ((long) B * RC * (1024 - v));
}

#define N_SAMPLES 20
void aproxAverage(int *avg, int sample)
{
  *avg -= *avg / N_SAMPLES;
  *avg += sample / N_SAMPLES;
}

int readMessage() {
  return (1);
}

// CODE LOGIC

void setup() {
	Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(SENSOR, INPUT);

  // mode = SENDER;
  mode = RECEIVER;

  switch (mode)
  {
  case SENDER:
    Serial.println("Sender mode");
    break;
  case RECEIVER:
    avgOFF = readLight();
    for (int i = 0; i < 5; i++) {
      aproxAverage(&avgOFF, readLight());
      delay(100);
    }
    
    Serial.println("Receiver mode");
    break;
  default:
    Serial.println("Unknown mode");
    break;
  }
}

void loop() {
  switch (mode)
  {
  case SENDER:
    if (Serial.available()) {
      Serial.readString().toCharArray(senderBuffer, BUFFER_SIZE);
      Serial.print("Sending: ");
      Serial.print(senderBuffer);
      if (stomorse(senderBuffer))
        Serial.println("[OK]");
      else
        Serial.println("[ERROR]");
    }
    break;
  case RECEIVER:
    // Serial.println("Receiver mode");
    // Serial.print("Input: ");
    light = readLight();
    if (light > avgOFF + 150) {
      avgON = light;
      Serial.println("[READING]");
      if (readMessage()) {
        Serial.println("[OK]");
        delay(2000);
        return;
      }
      else
        Serial.println("[ERROR]");
    }
    else
      aproxAverage(&avgOFF, light);

    Serial.println(readLight());
    break;
  default:
    Serial.println("Please select a mode");
    delay(10000);
    break;
  }
  delay(40);
}
