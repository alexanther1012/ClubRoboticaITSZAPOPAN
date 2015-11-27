int time_one=1000;
void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
}

void loop() {
  digitalWrite(2,1);  //verde puerto 2
  digitalWrite(7,1);  //rojo puerto 7
  delay(time_one);
  digitalWrite(2,0);  //verde puerto 2
  
  
  digitalWrite(3,1);  //amarillo puerto 3
  delay(4000);        
  digitalWrite(3,0);  //amarillo puerto 3
  digitalWrite(7,0);  //rojo puerto 7
  digitalWrite(4,1);  //rojo puerto 4
  
  digitalWrite(5,1);  //verde puerto 5  
  delay(time_one);
  digitalWrite(5,0);  //verde puerto 5
  
  digitalWrite(6,1);  //amarillo puerto 6
  delay(4000);
  digitalWrite(6,0);  //amarillo puerto 6
  digitalWrite(4,0);  //rojo puerto 4
}
