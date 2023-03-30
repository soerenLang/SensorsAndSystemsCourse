/***************************
  Simple Example Sketch for the SparkFun MEMS Microphone Breakout Board

**************************/

// Connect the MEMS AUD output to the Arduino A0 pin
int mic = A0;

// Variable to hold analog values from mic
int micOut;

void setup() 
{
  Serial.begin(115200);
  while(true){
    micOut = analogRead(mic);

  // print out the value you read:
    Serial.println(micOut);
  }
}

void loop() 
{
  micOut = analogRead(mic);

  // print out the value you read:
  Serial.println(micOut);
}