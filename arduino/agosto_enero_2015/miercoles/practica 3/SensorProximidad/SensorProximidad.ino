#define PEcho 2
#define PTrig 3
double duracion,distancia;
void setup() {
  Serial.begin(9600); //Inicializar puerto serial a 9600
  pinMode(PEcho,INPUT);   //Define el pin 8 como entrada (echo)
  pinMode(PTrig,OUTPUT);  //Define el pin 9 como salida (Triger)
  pinMode(13,OUTPUT);      //Define el pin 13 como salida
}

void loop() {
  digitalWrite(PTrig,LOW);
  delayMicroseconds(2);
  digitalWrite(PTrig,HIGH); // generar el pulso de triger por 10ms
  delayMicroseconds(10);
  digitalWrite(PTrig,LOW);

  duracion = pulseIn(PEcho,HIGH);
  distancia = (duracion/2)/29;    //Calcula la distancia

  if (distancia >= 500 || distancia <= 0){    //si la distancia es mayor a 500cm o menor a 0cm
    Serial.println("---");      //no mide nada
  }
  else{
    Serial.print(distancia);    //Envia el valor de la distancia por el puerto serial
    Serial.println("cm");       //Le coloca los centimetros a la distancia
    digitalWrite(13,0);         //en bajo el pin 13
  }

  if (distancia <= 10 && distancia >= 1){
    digitalWrite(13,1);         //En alto el pin 13 si la distancia es menor a 10 cm
    Serial.println("Alarma......"); //Envia la palabra alarma por el puerto serial
  }
  delay(400);
}
