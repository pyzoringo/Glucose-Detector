void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int timeArray[100];
  int startTime = 0; 
  int endTime = 0;
  int bufferMicros = 0;
  for (int i = 0; i < 100; i++) {
    startTime = micros();
    bufferMicros = micros();
    bufferMicros = micros();    
    bufferMicros = micros();
    bufferMicros = micros();
    bufferMicros = micros();
    bufferMicros = micros();
    bufferMicros = micros();
    bufferMicros = micros();
    bufferMicros = micros();
    bufferMicros = micros();
    bufferMicros = micros();
    bufferMicros = micros();
    bufferMicros = micros();
    bufferMicros = micros();
    bufferMicros = micros();
    bufferMicros = micros();
    bufferMicros = micros();
    bufferMicros = micros();
    bufferMicros = micros();
    endTime = micros();
    timeArray[i] = endTime - startTime;
    if (i%5==0) {
    Serial.println(timeArray[i]);
    }
  }
  int minimum = timeArray[0];
  int maximum = timeArray[0];
  int sum = 0;
  for (int i = 0; i <  100; i++) {
    if (minimum>timeArray[i]) {
      minimum = timeArray[i];
    }
    if (maximum<timeArray[i]) {
      maximum = timeArray[i];
    }
    sum = sum + timeArray[i];
  }
  Serial.print("Maximum");
  Serial.println(maximum);
  Serial.print("Minimum");
  Serial.println(minimum);
  Serial.print("Average");
  Serial.println(sum/100);
  delay(10000);
}
