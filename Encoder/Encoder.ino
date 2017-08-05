int encoderPin1 = 2;
int encoderPin2 = 3;

int redPin = 11;
int bluePin = 10;
int greenPin = 9;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);

  digitalWrite(encoderPin1, HIGH);
  digitalWrite(encoderPin2, HIGH);

  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:  
  setColors();
  delay(250);
}

void setColors() {
   setColor(255, 0, 0);  // red
}

void setColor(int red, int green, int blue){
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
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
