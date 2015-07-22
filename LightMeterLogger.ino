/* Light Meter Logger. 

Every readInterval millis() the photocell is sampled numSamples times at sampleRate millis() 
interval, recording the samples average in an array. If the maximum log entries is reached an 
LED will blink as notification. The dump data pushbutton will dump the log to the serial port.

Connect one end of the photocell to 5V, the other end to Analog In 0. Then connect one end of 
a 10K resistor from Analog In 0 to ground. Uses LED on prototype shield for log full indicator.
Uses pushbutton on prototype shield for dump data request.

*/

const byte photocellPin = 0;                          // Photocell input connected to Analog In 0.
const byte vBattPin = 1;                              // Battery input connected to Analog In 1.
const byte dumpDataBtnPin = 2;                        // Dump Data button connected to Digital I/O 2.
const byte ledPin = 3;                                // Sample and Log Full LED connected to Digital I/O 3.
const byte ledLowBattPin = 4;                         // Battery Low LED to Digital I/O 4.
boolean ledLowBattState = false;                      // Battery Low Indicator.
const unsigned long ledOffCnt = 750;                  // Battery Low LED Off Count in millis().
const unsigned long ledOnCnt = 250;                   // Battery Low LED On Count in millis().
const unsigned long readInterval = 10000;             // Photocell read interval in millis().
const int samplesMax = 5;                             // Number of photocell samples to average.
const unsigned long sampleRate = 100;                 // Sample rate in millis().
unsigned long nextMillis;                             // Next millis() to take sample.
unsigned int logIndex = 0;                            // Sample Index.
const unsigned int logIndexMax = 480;                 // Maximum number of samples.
unsigned int sampleLog[logIndexMax];                  // Sample storage.
unsigned int sampleLogBatt[logIndexMax];              // Batter voltage storage.

void setup(void) {
  // Init Serial.
  Serial.begin(9600);
  // Init Sample & Log Full LED.
  pinMode(ledPin, OUTPUT);
  // Init Low Battery LED.
  pinMode(ledLowBattPin, OUTPUT);
  // Init Dump Data button.
  pinMode(dumpDataBtnPin, INPUT_PULLUP);
  // Init nextMillis for first photocell sample.
  nextMillis = millis() + readInterval;
  // DEBUG
  Serial.println("Logging Begin");
}
 
void loop(void) {
  // Log Full?
  if (logIndex >= logIndexMax) {
    // Yes, Flash LED Slowly (Steady).
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(1000);
  }
  // Time to sample?
  else if (millis() >= nextMillis) {
    // Yes, Increment nextMillis.
    nextMillis += readInterval;
    // DEBUG
    Serial.println("Reading # " + String(logIndex));
    // Sample photocell.
    int photocellAverage = 0;
    for (int samples = 1; samples <= samplesMax; samples++) {
      photocellAverage += analogRead(photocellPin);
      delay(sampleRate);
    }
    // Average samples.
    photocellAverage /= samplesMax;
    // DEBUG
    Serial.println("Average reading = " + String(photocellAverage));
    // Save sample.
    sampleLog[logIndex++] = photocellAverage;
    // Flash LED Quickly (Once/Sample).
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
    // Read Battery Voltage
    int vBatt = analogRead(vBattPin);
    Serial.println("vBatt=" + String(vBatt) + ".");
    // Save vBatt sample
    sampleLogBatt[logIndex - 1] = vBatt;
  }
  // Dump Data Button?
  if (!digitalRead(dumpDataBtnPin)) {
    // Yes.
    Serial.println("Data Dump Begin");
    Serial.println(String(logIndex) + " log entries");
    Serial.println("Sunlight Sensor");
    for (int sample = 0; sample < logIndex; sample++) {
      Serial.print(sampleLog[sample]);
      Serial.print(",");
    }
    /*Serial.println("Battery Voltage");
    for (int sample = 0; sample < logIndex; sample++) {
      Serial.print(sampleLogBatt[sample]);
      Serial.print(",");
    }*/
    Serial.println();
    // Stop Sampling
    while(true);
  }
  // Low Battery?
  if (ledLowBattState) {
    
  }
}

