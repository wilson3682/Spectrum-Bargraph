// Define control pins for 74HC4051 and MSGEQ7
#define S0 5
#define S1 3
#define S2 4
#define ENABLE 6
#define STROBE 7
#define RESET 8

void setup() {
  // Set data direction for control pins (74HC4051)
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  
  // Set data direction for control pins (MSGEQ7)
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);

  // Initialize control pins
  digitalWrite(RESET, LOW); // reset pin low
  digitalWrite(STROBE, HIGH); // strobe pin high

  digitalWrite(S0, LOW); // clear select pins
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
}

void loop() {
  digitalWrite(RESET, HIGH); // reset pin high
  digitalWrite(RESET, LOW); // reset pin low
  delayMicroseconds(74);

  for (int i = 0; i < 7; i++) {
    digitalWrite(ENABLE, HIGH); // disable output of 74HC4051
    digitalWrite(S0, (i & 0b001) ? HIGH : LOW); // set control pins for 74HC4051
    digitalWrite(S1, (i & 0b010) ? HIGH : LOW);
    digitalWrite(S2, (i & 0b100) ? HIGH : LOW);
    digitalWrite(STROBE, LOW); // strobe low --> get output from MSGEQ7
    delayMicroseconds(36); // output settling time
    digitalWrite(ENABLE, LOW); // enable output of 74HC4051
    digitalWrite(STROBE, HIGH); // strobe high
    delayMicroseconds(36);
  }
}
