int encoderPin1 = 2;
int encoderPin2 = 3;

// these LEDs are in forward voltage when output is LOW
int redPin = 10;
int bluePin = 9;
int greenPin = 11;

int buttonPin = 8;
int buttonValue = 0;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);
  
  pinMode(buttonPin, INPUT);

  digitalWrite(encoderPin1, HIGH);
  digitalWrite(encoderPin2, HIGH);

  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);
  
}

void loop() {
  // put your main code here, to run repeatedly:  
  setColor(255, 234, 0);
  delay(250);
  buttonValue = digitalRead(buttonPin);
  Serial.println(buttonValue);
}

void setColors() {
   setColor(0, 0, 0);  // rgb all on
}

void setColor(int red, int green, int blue){
  int redValue = 255 - red;
  int greenValue = 255 - green;
  int blueValue = 255 - blue;
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

void updateEncoder(){
  int MSB = digitalRead(encoderPin1);
  int LSB = digitalRead(encoderPin2);

  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b1011 || sum == 0b0010) {
    encoderValue++;
  }
  if(sum == 0b1000 || sum == 0b0001 || sum == 0b1110 || sum == 0b0111) {
    encoderValue--; 
  }
  Serial.println(encoderValue);
  lastEncoded = encoded;
}
