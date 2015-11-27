//Parpadear el Led cada segundo
void setup(){
  pinMode(13,OUTPUT); //declaramos el pin 13 como salida
}
void loop(){
  digitalWrite(13,HIGH); //Encender el LED
  delay(1000);     //Tiempo de espera
  digitalWrite(13,LOW);   //Apagamos el LED
  delay(1000);     //Tiempo de espera
}

