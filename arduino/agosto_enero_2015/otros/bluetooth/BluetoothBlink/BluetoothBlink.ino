void setup() {
  pinMode(3,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  char dato = Serial.read();
  if( dato == 'a' ) digitalWrite(3,HIGH);
  if( dato == 'b' ) digitalWrite(3,LOW);
}
