/*Declaracion e inicializacion
de una variable global llamada
"mivariable"*/
int mivariable=0;
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(char(mivariable));
  Serial.println(mivariable);
  mivariable = mivariable+1;
  delay(1000);
}
