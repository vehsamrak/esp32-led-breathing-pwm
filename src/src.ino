#define LEDPIN 13
#define FREQUENCY 5000
#define RESOLUTION 8
#define STEPS 30

// Precomputed gamma brightness lookup table (30 steps, 0..255).
// Human eye perceives brightness logarithmically, so a linear PWM ramp
// looks like a sharp jump at low levels and a long fade at high levels.
// Applying gamma corrects this: PWM = ((step / (STEPS - 1))^2.4) * 255.
// Duplicate values are removed to remove pauses
const int brightnessValuesMap[STEPS] = {
  0,   1,   2,   3,   5,   7,   10,  13,
  17,  21,  26,  32,  38,  45,  52,  60,
  69,  79,  89,  100, 112, 125, 138, 152,
  167, 183, 200, 217, 236, 255
};

void setup() {
  ledcAttach(LEDPIN, FREQUENCY, RESOLUTION);
}

void loop() {
  // fade up
  for (int i = 0; i < STEPS; i++) {
    ledcWrite(LEDPIN, brightnessValuesMap[i]);
    delay(40);
  }

  // fade down
  for (int i = STEPS - 1; i >= 0; i--) {
    ledcWrite(LEDPIN, brightnessValuesMap[i]);
    delay(40);
  }
}
