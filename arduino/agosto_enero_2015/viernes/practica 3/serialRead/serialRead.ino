int incomingByte = 0;  // for incoming serial data

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {

  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    //Serial.print("I received: ");
    //Serial.println(incomingByte, DEC);
    if(incomingByte=='u'){
      Serial.println("arriba");
    }
    if(incomingByte=='d'){
      Serial.println("abajo");
    }
    if(incomingByte=='l'){
      Serial.println("izquierda");
    }
    if(incomingByte=='r'){
      Serial.println("derecha");
    }
  }
}
