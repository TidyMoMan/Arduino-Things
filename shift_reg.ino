int latchPin = 10;  // Latch pin of 74HC595 is connected to Digital pin 10
int clockPin = 12; // Clock pin of 74HC595 is connected to Digital pin 12
int dataPin = 11;  // Data pin of 74HC595 is connected to Digital pin 11
int busyPin = A7;
int writeEnable = 13;

int romD0 = 2; //bottom data pin
int romD7 = 10; //top data pin

int delayVal = 100;
int count = 0;

byte program[] = {0x01, 0x02, 0x03, 0x04, 0x05};


void setup() 
{
  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);   
  pinMode(clockPin, OUTPUT);
  pinMode(busyPin, OUTPUT);
  analogWrite(busyPin, 1);
  digitalWrite(writeEnable, HIGH);
  pinMode(writeEnable, OUTPUT);
  Serial.begin(500000);
  
  for(int address = 0; address <= 255; address++){ //erase on startup
      WriteRom(address, 0xff);
    }
  
  for(int address = 0; address <= 4; address++){     // for(int address = 0; address <= (sizeof(prog[]) / sizeof(byte)); address++){
      WriteRom(address, program[address]);
    }
  
  PrintRom();
  analogWrite(busyPin, LOW);

}

void SetAddress(int address, boolean outputEnable)
{                                                         //outputenable true? if yes then 00000 if no then 10000
  
   shiftOut(dataPin, clockPin, MSBFIRST, (address >> 8) | (outputEnable ? 0x00 : 0x80));
   shiftOut(dataPin, clockPin, MSBFIRST, address);
   digitalWrite(latchPin, LOW);
   digitalWrite(latchPin, HIGH);
   digitalWrite(latchPin, LOW);

}

byte ReadRom(int address){
  for(int pin = romD0; pin < romD7; pin++){
      pinMode(pin, INPUT);
    }
  SetAddress(address, true);
  byte data = 0;
  for(int pin = romD7; pin >= romD0; pin -= 1){
      data = (data << 1) + digitalRead(pin);
    }
    return data;
}

void PrintRom(){    
     for(int i = 0; i <= 255; i+= 16){
    byte data[16];
    for(int offset = 0; offset <= 15; offset+=1){
        data[offset] = ReadRom(i + offset);
      }
      char buf[80];
      sprintf(buf, "%03x:    %02x %02x %02x %02x %02x %02x %02x %02x   %02x %02x %02x %02x %02x %02x %02x %02x",
        i, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);
      Serial.println(buf);
    }
  }

void WriteRom(int address, byte data){
  SetAddress(address, false);
  
   for(int pin = romD0; pin <= romD7; pin++){
      pinMode(pin, OUTPUT);
    }
    
  for(int pin = romD0; pin <= romD7; pin++){
      digitalWrite(pin, data & 1);
      data = (data >> 1);
    }
    digitalWrite(writeEnable, LOW);
    delayMicroseconds(1);
    digitalWrite(writeEnable, HIGH);
    delay(10);
  }
  

void loop() 
{
//    WriteRom(count, 0x55);
//    delay(500);
//    count++;
//    PrintRom(); Serial.println(count);
//    delay(500);

}

/*
 * updateShiftRegister() - This function sets the latchPin to low, then calls the Arduino function 'shiftOut' to shift out contents of variable 'leds' in the shift register before putting the 'latchPin' high again.
 */
