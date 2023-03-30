/***************************
  Simple Example Sketch for the SparkFun MEMS Microphone Breakout Board

**************************/

// Connect the MEMS AUD output to the Arduino A0 pin
int mic = A0;

// Variable to hold analog values from mic
//int micOut;

void setup() 
{
  ADC->CTRLA.bit.ENABLE = 0;                       // Disable the ADC
  while(ADC->STATUS.bit.SYNCBUSY);                 // Wait for synchronization
  ADC->SAMPCTRL.reg = 0x00;                        // Reduce the sample time by (63 + 1) * (512 / 48MHz) / 2
  ADC->CTRLA.bit.ENABLE = 1;                       // Enable the ADC
  while(ADC->STATUS.bit.SYNCBUSY);
  Serial.begin(460800);
}

void loop() 
{
  short singleMicOut = analogRead(mic);

  // print out the value you read:
  Serial.println(singleMicOut);
}