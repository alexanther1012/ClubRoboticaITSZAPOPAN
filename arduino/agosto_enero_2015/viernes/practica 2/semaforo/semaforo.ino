#define verde 8
#define amarillo 9
#define rojo 10
int tiempo = 1000;
void setup() {
  pinMode(verde, OUTPUT); //verde
  pinMode(amarillo, OUTPUT); //amarillo
  pinMode(rojo, OUTPUT); //rojo
}

void loop() {
  digitalWrite(verde, HIGH);
  delay(5000);
  digitalWrite(verde, LOW);
  for (int i = 0; i < 6; i++) {
    digitalWrite(verde, HIGH);
    delay(tiempo);
    digitalWrite(verde, LOW);
    delay(tiempo);
    tiempo = tiempo / 2;
  }
  tiempo = 1000;
  digitalWrite(amarillo, HIGH);
  delay(3000);
  digitalWrite(amarillo, LOW);
  digitalWrite(rojo, HIGH);
  delay(5000);
  digitalWrite(rojo, LOW);  
}
