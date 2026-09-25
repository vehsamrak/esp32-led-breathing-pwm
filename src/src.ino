#define LEDPIN 13
#define FREQUENCY 5000
#define RESOLUTION 8

// Precomputed exponential brightness lookup table (32 steps, 0..255)
// Human eye perceives brightness logarithmically, so a linear PWM ramp
// looks like a sharp jump at low levels and a long fade at high levels.
// Powing the normalized step corrects this: PWM = ((step / 31)^3) * 255
const int brightnessValuesMap[32] = {
  0,   1,   2,   2,   3,   4,   5,   7,
  9,   12,  15,  19,  24,  30,  36,  44,
  53,  63,  74,  87,  102, 118, 135, 155,
  176, 199, 224, 251, 255, 255, 255, 255
};

void setup() {
  ledcAttach(LEDPIN, FREQUENCY, RESOLUTION);
}

void loop() {
  // linear up
  for (int i = 0; i < 32; i++) {
    ledcWrite(LEDPIN, brightnessValuesMap[i]);
    delay(40); 
  }

  // linear down
  for (int i = 31; i >= 0; i--) {
    ledcWrite(LEDPIN, brightnessValuesMap[i]);
    delay(40);
  }
}

