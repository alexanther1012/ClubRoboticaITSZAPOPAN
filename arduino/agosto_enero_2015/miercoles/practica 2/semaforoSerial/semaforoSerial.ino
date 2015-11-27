void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  Serial.print("semaforo 1:Verde");
  Serial.print("\t");
  Serial.print("semaforo 2:Rojo");
  Serial.println();
  delay(3000);
  Serial.print("semaforo 1:Amarillo");
  Serial.print("\t");
  Serial.print("semaforo 2:Rojo");
  Serial.println();
  delay(1000);
  Serial.print("semaforo 1:Rojo");
  Serial.print("\t\t");
  Serial.print("semaforo 2:Verde");
  Serial.println();
  delay(3000);
  Serial.print("semaforo 1:Rojo");
  Serial.print("\t\t");
  Serial.print("semaforo 2:Amarillo");
  Serial.println();
  delay(1000);
}
