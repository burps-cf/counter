/*
 * MIT License
 * 
 * Copyright (c) 2018 burps-cf
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * This code uses interrupts to measure the time to count a number of FALLING edge
 * signals on a pin.
 * 
 */

const byte interruptPin = 2;
const byte countLimit = 100;
volatile byte counter = 0;
volatile bool start = false;
volatile unsigned long t0, t1;

// counting starts when button is pressed
const byte buttonPin = 4;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), countTics, FALLING);

  Serial.begin(9600);
} // setup

void loop() {

  if (digitalRead(buttonPin) == HIGH) {
    counter = 0;
    start = true;
    while (start) delay(10);
    Serial.println(t1-t0);
  }

} // loop

// ISR
void countTics () {

  // record time of the first tic
  if (start && counter == 0) {
    t0 = millis();
  }

  counter++;

  // record time of the last tic
  if (start && counter == countLimit) {
    t1 = millis();
    // disable time measurement
    start = false;
  }
} //countTics


