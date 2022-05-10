#define VRX_PIN  A1 // Arduino pin connected to VRX pin
#define VRY_PIN  A2 // Arduino pin connected to VRY pin
#define LED 8

#define ON 1
#define OFF 0

int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis

void setup() {
	// Serial.begin(9600);
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
	// read analog X and Y analog values
	xValue = analogRead(VRX_PIN);
	yValue = analogRead(VRY_PIN);

	if (xValue < 100) {
		set_on();
	} else {
		set_off();
	}

  // print data to Serial Monitor on Arduino IDE
//   Serial.print("x = ");
//   Serial.print(xValue);
//   Serial.print(", y = ");
//   Serial.println(yValue);
	delay(40);
}