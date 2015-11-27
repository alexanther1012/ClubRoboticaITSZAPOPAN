char dato;
void setup() {
  pinMode(8, OUTPUT); //derecha Atras
  pinMode(9, OUTPUT); //derecha Adelante
  pinMode(10, OUTPUT); //izquierdo Atras
  pinMode(11, OUTPUT); //izquierdo Adelante
  Serial.begin(9600);
}

void loop() {
  dato = Serial.read();
  if (dato == 'L' ) {
    vamosIzquierda();
  }
  if (dato == 'R' ) {
    vamosDerecha();
  }
  if (dato == 'U' ) {
    vamosAdelante();
  }
  if (dato == 'D' ) {
    vamosAtras();
  }
  if (dato == 'S' ) {
    parar();
  }
}

void parar(){
  Serial.println(dato);

  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void vamosAdelante(){ //Funcion para avanzar hacia adelante
  Serial.println(dato);
    
  digitalWrite(9,HIGH);
  digitalWrite(11,HIGH);

  digitalWrite(8,LOW);
  digitalWrite(10,LOW);
}
void vamosAtras(){  //Funcion para avanzar hacia atras
  Serial.println(dato);
    
  digitalWrite(8,HIGH);
  digitalWrite(10,HIGH);
  
  digitalWrite(9,LOW);
  digitalWrite(11,LOW);
}
void vamosDerecha(){ //Funcion para girar a la derecha
  Serial.println(dato);
  
  digitalWrite(8,HIGH);
  digitalWrite(11,HIGH);
  
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  
  
}
void vamosIzquierda(){ //Funcion para girar a la izquierda
  Serial.println(dato);
  
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  
  digitalWrite(8,LOW);
  digitalWrite(11,LOW);
}




