#include <Arduino.h>

#define NUM_RELAYS 40 // Total amount of relays.
#define CLOCK_SPEED_HZ 1 // Global clock speed to drive operations in hz.

// Sanity check for calculated period (avoid division by zero or too fast).
#if CLOCK_SPEED_HZ <= 0
  #error "CLOCK_SPEED_HZ is too high or zero, resulting in an invalid period."
#endif

// Calculating the corresponding period in milliseconds. Useful for delay()'s.
const unsigned long CLOCK_SPEED_PERIOD_MS = (unsigned long)(1000.0f / (float)CLOCK_SPEED_HZ);

// Input manip:
uint8_t INPUT_A = HIGH;
uint8_t INPUT_B = HIGH;

typedef struct {
  const char name[15];
  const byte pin;
  volatile byte relayState;
} Relay;

// Storing all relays for ease of use later.
Relay allRelays[NUM_RELAYS] = {
  {"r0", 2, LOW},
  {"r1", 3, LOW},
  {"r2", 4, LOW},
  {"r3", 5, LOW},
  {"r4", 6, LOW},
  {"r5", 7, LOW},
  {"r6", 8, LOW},
  {"r7", 9, LOW},
  {"r8", 10, LOW},
  {"r9", 11, LOW},
  {"r10", 12, LOW},
  {"r11", 13, LOW},
  {"r12", 22, LOW},
  {"r13", 23, LOW},
  {"r14", 24, LOW},
  {"r15", 25, LOW},
  {"r16", 26, LOW},
  {"r17", 27, LOW},
  {"r18", 28, LOW},
  {"r19", 29, LOW},
  {"r20", 30, LOW},
  {"r21", 31, LOW},
  {"r22", 32, LOW},
  {"r23", 33, LOW},
  {"r24", 34, LOW},
};

// This converts the user's input signal nomenclature to what is expected when commanding relays. Considering the relays are active LOW.
// Sending a HIGH signal to the relay's input will result in it being switched off. So, this function lives to make setting the
// relays easier by inverting the relay logic to what a user would expect.
void set_relay(Relay& r, uint8_t signal) {
  if (signal != LOW && signal != HIGH) {
    Serial.println("set_relay(ERROR): input signal was not either LOW or HIGH. Will default to turning off relay.");
    digitalWrite(r.pin, HIGH);
    r.relayState = HIGH;
    return;
  }

  Serial.print("set_relay(");
  Serial.print(r.name);
  Serial.print("): ");
  Serial.println(signal);

  // Invert the signal sent as too follow common nomenclature of what HIGH and LOW means.
  // HIGH = ON | LOW = OFF.
  digitalWrite(r.pin, !signal);
  r.relayState = signal;
}

// Handles turning off all relays one by one.
void turn_off_all_relays() {
  for (int i = 0; i < NUM_RELAYS; i++) {
    set_relay(allRelays[i], LOW);
  }
}

void check_relays() {
  for (int i = 0; i < NUM_RELAYS; i++) {
    set_relay(allRelays[i], HIGH);
    delay(CLOCK_SPEED_PERIOD_MS);
    set_relay(allRelays[i], LOW);
    delay(60);
  }
}

void boot_sequence() {
  turn_off_all_relays();
  check_relays();
  delay(100);
}

// Runs through an or gate truth table test with the relays supplied.
void test_or_gate(Relay& r0, Relay& r1) {
  Serial.print("test_or_gate(");
  Serial.print(r0.name);
  Serial.print(", ");
  Serial.print(r1.name);
  Serial.println("): ");
  set_relay(r0, LOW);
  set_relay(r1, LOW);
  Serial.print("relay states: ");
  Serial.print(r0.relayState);
  Serial.print(", ");
  Serial.println(r1.relayState);
  delay(1000);
  Serial.print("test_or_gate(");
  Serial.print(r0.name);
  Serial.print(", ");
  Serial.print(r1.name);
  Serial.println("): ");
  set_relay(r0, HIGH);
  set_relay(r1, LOW);
  Serial.print("relay states: ");
  Serial.print(r0.relayState);
  Serial.print(", ");
  Serial.println(r1.relayState);
  delay(1000);
  Serial.print("test_or_gate(");
  Serial.print(r0.name);
  Serial.print(", ");
  Serial.print(r1.name);
  Serial.println("): ");
  set_relay(r0, LOW);
  set_relay(r1, HIGH);
  Serial.print("relay states: ");
  Serial.print(r0.relayState);
  Serial.print(", ");
  Serial.println(r1.relayState);
  delay(1000);
  Serial.print("test_or_gate(");
  Serial.print(r0.name);
  Serial.print(", ");
  Serial.print(r1.name);
  Serial.println("): ");
  set_relay(r0, HIGH);
  set_relay(r1, HIGH);
  Serial.print("relay states: ");
  Serial.print(r0.relayState);
  Serial.print(", ");
  Serial.println(r1.relayState);
  delay(1000);
}

void setup() {
  // Setting all relay pins as outputs
  // NOTE(MSR): Have to set the pinMode to INPUT_PULLUP at the start so that the bootloader doesn't
  //            start the pins LOW on reset causing the relays to toggle momentarily.
  for (int i = 0; i < NUM_RELAYS; i++) {
    pinMode(allRelays[i].pin, INPUT_PULLUP);
    pinMode(allRelays[i].pin, OUTPUT);
  }


  Serial.begin(9600);
  Serial.println("Serial communication began (9600baudrate).");
  delay(10); // Just for safety/consistency.


  Serial.println("Turning off all relays.");
  turn_off_all_relays();

  // boot sequence that turns relays on and off for functionality verification purposes
  // boot_sequence();
  Serial.println("Boot sequence complete.");
  // set_relay(allRelays[0], LOW);
  delay(50);
}


void loop() {
  test_or_gate(allRelays[0], allRelays[1]);


}
