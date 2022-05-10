#define UNIT_TIME 200

#define LED 8

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
//  wait(5);
  wait(3);
}

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


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
   pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // stomorse("SOS");
  stomorse("ESTAMOS EN CLASE DE IOT");
  delay(1000);                       // wait for a second
}
