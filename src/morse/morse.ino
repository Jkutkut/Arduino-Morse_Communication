#define UNIT_TIME 200

#define LED 8

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
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED, HIGH);
}

void set_off() {
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
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


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  stomorse("SOS");
  delay(1000);
}
