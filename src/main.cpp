#include <Arduino.h>

struct Relay {
  int pin;
  volatile byte relayState;
};

// Creating array of all relay pins for easy looping usage later.
// WARN(MSR): This needs to be in order from (LSB) being on the left.
int relayPins[] = {2,3,4,5,6,7,8,9};

// Constructing all relays
struct Relay r0 = {2, LOW};
struct Relay r1 = {3, LOW};
struct Relay r2 = {4, LOW};
struct Relay r3 = {5, LOW};
struct Relay r4 = {6, LOW};
struct Relay r5 = {7, LOW};
struct Relay r6 = {8, LOW};
struct Relay r7 = {9, LOW};
struct Relay r8 = {10, LOW};
struct Relay r9 = {11, LOW};
struct Relay r10 = {12, LOW};
struct Relay r11 = {13, LOW};
struct Relay r12 = {22, LOW};
struct Relay r13 = {23, LOW};
struct Relay r14 = {24, LOW};
struct Relay r15 = {25, LOW};
struct Relay r16 = {26, LOW};
struct Relay r17 = {27, LOW};
struct Relay r18 = {28, LOW};
struct Relay r19 = {29, LOW};
struct Relay r20 = {30, LOW};
struct Relay r21 = {31, LOW};
struct Relay r22 = {32, LOW};
struct Relay r23 = {33, LOW};
struct Relay r24 = {34, LOW};

// Timer variables
long lastDebounceTime = 0;
long debounceDelay = 5000;

// Global constants
// WARN(MSR): CHANGING THESE WILL AFFECT THE ENTIRE PROJECT BECAREFUL.
const int TOTAL_RELAYS = 8;
const int COMMANDED_CLOCK_SPEED_MS = 500; // This is used to control the speed of the "shifting" for most tasks

void turn_off_all_relays() {
  digitalWrite(r0.pin, HIGH);
  r0.relayState = LOW;
  digitalWrite(r1.pin, HIGH);
  r1.relayState = LOW;
  digitalWrite(r2.pin, HIGH);
  r2.relayState = LOW;
  digitalWrite(r3.pin, HIGH);
  r3.relayState = LOW;
  digitalWrite(r4.pin, HIGH);
  r4.relayState = LOW;
  digitalWrite(r5.pin, HIGH);
  r5.relayState = LOW;
  digitalWrite(r6.pin, HIGH);
  r6.relayState = LOW;
  digitalWrite(r7.pin, HIGH);
  r7.relayState = LOW;
  delay(50);
  digitalWrite(r8.pin, HIGH);
  r8.relayState = LOW;
  digitalWrite(r9.pin, HIGH);
  r9.relayState = LOW;
  digitalWrite(r10.pin, HIGH);
  r10.relayState = LOW;
  digitalWrite(r11.pin, HIGH);
  r11.relayState = LOW;
  digitalWrite(r12.pin, HIGH);
  r12.relayState = LOW;
  digitalWrite(r13.pin, HIGH);
  r13.relayState = LOW;
  digitalWrite(r14.pin, HIGH);
  r14.relayState = LOW;
  digitalWrite(r15.pin, HIGH);
  r15.relayState = LOW;
  digitalWrite(r16.pin, HIGH);
  r16.relayState = LOW;
  digitalWrite(r17.pin, HIGH);
  r17.relayState = LOW;
  delay(50);
  digitalWrite(r18.pin, HIGH);
  r18.relayState = LOW;
  digitalWrite(r19.pin, HIGH);
  r19.relayState = LOW;
  digitalWrite(r20.pin, HIGH);
  r20.relayState = LOW;
  digitalWrite(r21.pin, HIGH);
  r21.relayState = LOW;
  digitalWrite(r22.pin, HIGH);
  r22.relayState = LOW;
  digitalWrite(r23.pin, HIGH);
  r23.relayState = LOW;
  digitalWrite(r24.pin, HIGH);
  r24.relayState = LOW;
}

void turn_on_all_relays() {
  digitalWrite(r0.pin, LOW);
  r0.relayState = HIGH;
  digitalWrite(r1.pin, LOW);
  r1.relayState = HIGH;
  digitalWrite(r2.pin, LOW);
  r2.relayState = HIGH;
  digitalWrite(r3.pin, LOW);
  r3.relayState = HIGH;
  digitalWrite(r4.pin, LOW);
  r4.relayState = HIGH;
  digitalWrite(r5.pin, LOW);
  r5.relayState = HIGH;
  digitalWrite(r6.pin, LOW);
  r6.relayState = HIGH;
  digitalWrite(r7.pin, LOW);
  r7.relayState = HIGH;
  digitalWrite(r8.pin, LOW);
  r8.relayState = HIGH;
  digitalWrite(r9.pin, LOW);
  r9.relayState = HIGH;
  digitalWrite(r10.pin, LOW);
  r10.relayState = HIGH;
  digitalWrite(r11.pin, LOW);
  r11.relayState = HIGH;
  digitalWrite(r12.pin, LOW);
  r12.relayState = HIGH;
  digitalWrite(r13.pin, LOW);
  r13.relayState = HIGH;
  digitalWrite(r14.pin, LOW);
  r14.relayState = HIGH;
  digitalWrite(r15.pin, LOW);
  r15.relayState = HIGH;
  digitalWrite(r16.pin, LOW);
  r16.relayState = HIGH;
  digitalWrite(r17.pin, LOW);
  r17.relayState = HIGH;
  digitalWrite(r18.pin, LOW);
  r18.relayState = HIGH;
  digitalWrite(r19.pin, LOW);
  r19.relayState = HIGH;
  digitalWrite(r20.pin, LOW);
  r20.relayState = HIGH;
  digitalWrite(r21.pin, LOW);
  r21.relayState = HIGH;
  digitalWrite(r22.pin, LOW);
  r22.relayState = HIGH;
  digitalWrite(r23.pin, LOW);
  r23.relayState = HIGH;
  digitalWrite(r24.pin, LOW);
  r24.relayState = HIGH;
}

void turn_on_all_relays_staggered(int stagger_ms) {
  digitalWrite(r0.pin, LOW);
  r0.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r1.pin, LOW);
  r1.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r2.pin, LOW);
  r2.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r3.pin, LOW);
  r3.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r4.pin, LOW);
  r4.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r5.pin, LOW);
  r5.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r6.pin, LOW);
  r6.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r7.pin, LOW);
  r7.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r8.pin, LOW);
  r8.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r9.pin, LOW);
  r9.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r10.pin, LOW);
  r10.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r11.pin, LOW);
  r11.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r12.pin, LOW);
  r12.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r13.pin, LOW);
  r13.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r14.pin, LOW);
  r14.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r15.pin, LOW);
  r15.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r16.pin, LOW);
  r16.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r17.pin, LOW);
  r17.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r18.pin, LOW);
  r18.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r19.pin, LOW);
  r19.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r20.pin, LOW);
  r20.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r21.pin, LOW);
  r21.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r22.pin, LOW);
  r22.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r23.pin, LOW);
  r23.relayState = HIGH;
  delay(stagger_ms);
  digitalWrite(r24.pin, LOW);
  r24.relayState = HIGH;
  delay(stagger_ms);
}

void boot_sequence() {
  turn_off_all_relays();
  delay(200);
  //turn_on_all_relays();
  //delay(1000);
  //turn_off_all_relays();
  //delay(100);
  turn_on_all_relays_staggered(COMMANDED_CLOCK_SPEED_MS);
  delay(100);
  turn_off_all_relays();
  delay(100);
  turn_on_all_relays();
  delay(100);
  turn_off_all_relays();
  delay(100);
}

void eight_bit_counter() {
  byte num = 0;
  for (int j = 0; j < 256; j++) {
    Serial.println("num: ");
    Serial.println(num);
    for (int i = 0; i < 8; i++) {
      if (bitRead(num, i) == 1) { // Turn on relay if bit is set for num
        digitalWrite(relayPins[i], LOW);
      } else {
        digitalWrite(relayPins[i], HIGH);
      }
    }
    delay(COMMANDED_CLOCK_SPEED_MS);
    num += 1;
  }
}

void four_bit_counter() {
  byte num = 0;
  for (int j = 0; j < 16; j++) {
    Serial.println("num: ");
    Serial.println(num);
    for (int i = 0; i < 4; i++) {
      if (bitRead(num, i) == 1) { // Turn on relay if bit is set for num
        digitalWrite(relayPins[i], LOW);
      } else {
        digitalWrite(relayPins[i], HIGH);
      }
    }
    delay(COMMANDED_CLOCK_SPEED_MS);
    num += 1;
  }
}

void displayByte(byte input) {
  for (int i = 0; i < 8; i++) {
    if (bitRead(input, i) == 1) { // Turn on relay if bit is set for num
      digitalWrite(relayPins[i], LOW);
    } else {
      digitalWrite(relayPins[i], HIGH);
    }
  }
  delay(COMMANDED_CLOCK_SPEED_MS);
}

byte AND_GATE(byte a, byte b) {
  byte output = 0;
  if (a == 0 && b == 0) {
    output = 0;
  } else if (a == 0 && b == 1) {
    output = 0;
  } else if (a == 1 && b == 0) {
    output = 0;
  } else {
    output = 1;
  }
  return output;
}

void setup() {
  // Setting all relay pins as outputs
  //pinMode(r0.pin, INPUT_PULLUP);
  //delay(100);
  //pinMode(r0.pin, INPUT);
  //delay(100);
  // NOTE(MSR): Have to set the pinMode to INPUT_PULLUP at the start so that the bootloader doesn't
  //            start the pins LOW on reset causing the relays to toggle momentarily.
  pinMode(r0.pin, INPUT_PULLUP);
  pinMode(r0.pin, OUTPUT);
  pinMode(r1.pin, INPUT_PULLUP);
  pinMode(r1.pin, OUTPUT);
  pinMode(r2.pin, INPUT_PULLUP);
  pinMode(r2.pin, OUTPUT);
  pinMode(r3.pin, INPUT_PULLUP);
  pinMode(r3.pin, OUTPUT);
  pinMode(r4.pin, INPUT_PULLUP);
  pinMode(r4.pin, OUTPUT);
  pinMode(r5.pin, INPUT_PULLUP);
  pinMode(r5.pin, OUTPUT);
  pinMode(r6.pin, INPUT_PULLUP);
  pinMode(r6.pin, OUTPUT);
  pinMode(r7.pin, INPUT_PULLUP);
  pinMode(r7.pin, OUTPUT);
  pinMode(r8.pin, INPUT_PULLUP);
  pinMode(r8.pin, OUTPUT);
  pinMode(r9.pin, INPUT_PULLUP);
  pinMode(r9.pin, OUTPUT);
  pinMode(r10.pin, INPUT_PULLUP);
  pinMode(r10.pin, OUTPUT);
  pinMode(r11.pin, INPUT_PULLUP);
  pinMode(r11.pin, OUTPUT);
  pinMode(r12.pin, INPUT_PULLUP);
  pinMode(r12.pin, OUTPUT);
  pinMode(r13.pin, INPUT_PULLUP);
  pinMode(r13.pin, OUTPUT);
  pinMode(r14.pin, INPUT_PULLUP);
  pinMode(r14.pin, OUTPUT);
  pinMode(r15.pin, INPUT_PULLUP);
  pinMode(r15.pin, OUTPUT);
  pinMode(r16.pin, INPUT_PULLUP);
  pinMode(r16.pin, OUTPUT);
  pinMode(r17.pin, INPUT_PULLUP);
  pinMode(r17.pin, OUTPUT);
  pinMode(r18.pin, INPUT_PULLUP);
  pinMode(r18.pin, OUTPUT);
  pinMode(r19.pin, INPUT_PULLUP);
  pinMode(r19.pin, OUTPUT);
  pinMode(r20.pin, INPUT_PULLUP);
  pinMode(r20.pin, OUTPUT);
  pinMode(r21.pin, INPUT_PULLUP);
  pinMode(r21.pin, OUTPUT);
  pinMode(r22.pin, INPUT_PULLUP);
  pinMode(r22.pin, OUTPUT);
  pinMode(r23.pin, INPUT_PULLUP);
  pinMode(r23.pin, OUTPUT);
  pinMode(r24.pin, INPUT_PULLUP);
  pinMode(r24.pin, OUTPUT);

  Serial.begin(9600);

  // boot sequence that turns relays on and off for functionality verification purposes
  // turn_off_all_relays();
  // delay(1000);
  // turn_on_all_relays_staggered(COMMANDED_CLOCK_SPEED_MS);
  //digitalWrite(r20.pin, LOW);


  // boot_sequence();
  // Serial.println("Boot sequence complete.");
  //delay(50);
}

void loop() {
  





  // Turn on relays if they are off.
  // if (relayState_0 == LOW) {
  //   digitalWrite(relay_0_pin, LOW);
  //   digitalWrite(relay_1_pin, LOW);
  //   relayState_0 = HIGH;
  //   relayState_1 = HIGH;
  //   Serial.println("relay_0: ON");
  //   Serial.println("relay_1: ON");
  //   lastDebounceTime = millis();
  // }
  
  // // Turn off relays after debounce Delay (5 seconds)
  // if ((millis() - lastDebounceTime) > debounceDelay && relayState_0 == HIGH && relayState_1 == HIGH) {
  //   digitalWrite(relay_0_pin, HIGH);
  //   digitalWrite(relay_1_pin, HIGH);
  //   relayState_0 = LOW;
  //   relayState_1 = LOW;
  //   Serial.println("relay_0: OFF");
  //   Serial.println("relay_0: OFF");
  //   delay(1000);
  // }
  // delay(50);

}
