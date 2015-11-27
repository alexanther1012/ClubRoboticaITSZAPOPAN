int ledPin1 = 3;
int ledPin2 = 4;
int ledPin3 = 5;

void setup(){
   pinMode(ledPin1,OUTPUT);
   pinMode(ledPin2,OUTPUT);
   pinMode(ledPin3,OUTPUT);
}

void loop(){
   for(int i = 0; i <= 7; i++){
     if( i == 2 || i == 4 || i == 6 || i == 0){
        digitalWrite(ledPin1,LOW);
     }
     else{
       digitalWrite(ledPin1,HIGH);
     }
     if( i == 2 || i == 3 || i == 6 || i == 7){
       digitalWrite(ledPin2,HIGH);
     }
     else{
       digitalWrite(ledPin2,LOW);
     }
     if( i > 3){
       digitalWrite(ledPin3,HIGH);
     }
     else{
       digitalWrite(ledPin3,LOW);
     }
     delay(1500);
   } 
}
