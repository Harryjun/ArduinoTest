void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(14,INPUT);
  pinMode(12,OUTPUT);
}

void loop() {
  int sensorValue;
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(14);
Serial.print(sensorValue); //显示G值在x轴的加速度
     Serial.print("\n");  // tabs in between axes
     delay(1000);
}
