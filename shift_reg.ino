int latchPin = 10;  // Latch pin of 74HC595 is connected to Digital pin 5
int clockPin = 12; // Clock pin of 74HC595 is connected to Digital pin 6
int dataPin = 11;  // Data pin of 74HC595 is connected to Digital pin 4
int delayVal = 100;

byte leds = 0;    // Variable to hold the pattern of which LEDs are currently turned on or off

/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
void setup() 
{
  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(500000);
}
void loop() 
{
  leds = 0;  // Initially turns all the LEDs off, by giving the variable 'leds' the value 0
  updateShiftRegister();
  delay(delayVal);
  
  for (int i = 0; i < 23; i++) // Turn all the LEDs ON one by one.
  {
    bitSet(leds, i);
    Serial.println(i);
    updateShiftRegister();
    delay(delayVal);
  }
//int e = random(0, 20);

}

/*
 * updateShiftRegister() - This function sets the latchPin to low, then calls the Arduino function 'shiftOut' to shift out contents of variable 'leds' in the shift register before putting the 'latchPin' high again.
 */
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
