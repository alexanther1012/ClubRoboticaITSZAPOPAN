#include <QTRSensors.h>
#include <OrangutanMotors.h>
#include <EEPROM.h>

#define CAR_ANALOG

#define primerTermino   0b1111111100000000
#define segundoTermino  0b0000000011111111

#define NUM_SENSORS                8  
#define NUM_SAMPLES_PER_SENSOR     4                              
#define EMITTER_PIN_IR             11
#define TIMEOUT                  2500    
  
#ifdef CAR_ANALOG
   #define CARGAR_SENSOR QTRSensorsAnalog 
   #define PINES (unsigned char[]) { 0, 1, 2, 3, 4, 5, 6, 7}
   #define MUESTREO NUM_SAMPLES_PER_SENSOR
   
#endif

#ifdef CAR_DIGITAL
   #define CARGAR_SENSOR QTRSensorsRC
   #define PINES (unsigned char[]) {14, 15, 16, 17, 18, 19, 12, 13}
   #define MUESTREO TIMEOUT
#endif
 
 
CARGAR_SENSOR qtr(PINES, NUM_SENSORS, MUESTREO, EMITTER_PIN_IR);

OrangutanMotors motors;

unsigned int sensorValues[NUM_SENSORS];

unsigned int minimoUno = 0,minimoDos = 0,minimoTres = 0,minimoCuatro = 0,minimoCinco = 0,minimoSeis = 0,minimoSiete = 0,minimoOcho = 0;
unsigned int maximoUno = 0,maximoDos = 0,maximoTres = 0,maximoCuatro = 0,maximoCinco = 0,maximoSeis = 0,maximoSiete = 0,maximoOcho = 0;
uint8_t intervalo1 = 0,intervalo2 = 0;
int numeroByte = 1,numeroByteLectura = 1;

//--------------------------------------------------------------------------------------//
//------------------------Velocidad Maxima Robot----------------------------------------//
int maximum = 100;                                                                     
//-------------------------------------------------------------------------------------//
//------------------------- Ganancias controlador PD-----------------------------------//
float kp = 4;    //1.45            //2.1              //7.1    //6   0.095
float kd = 40;     //30   //10     0.15
float ki = 0.2;
//--------------------------------------------------------------------------------------//
//-----------------------Velocidad de Calibracion---------------------------------------//
int velcalibrate = 35; 
//--------------------------------------------------------------------------------------//


int last_proportional = 0;
long integral = 0;
int position = 0, switchCalibration = 0;
signed int proportional = 0 , power_difference = 0, derivative = 0, motorDos = 0 , motorUno = 0,error_brake = 0;
int pin_switch = 8;

void setup()
{
   pinMode(pin_switch,INPUT);
   digitalWrite(pin_switch, HIGH);
   
   numeroByte = 1;
   numeroByteLectura = 1;
   
   Serial.begin(9600);
   
   for (int i=0; i<7 ; i++)
      {
	    for (int counter=0; counter<17; counter++)
	    {
		    if (counter < 5 || counter >= 14)
		    OrangutanMotors::setSpeeds(-velcalibrate, velcalibrate);
		    else
		    OrangutanMotors::setSpeeds(velcalibrate, -velcalibrate);
		    
			qtr.calibrate();

		    delay(20);
	    }
      }

   OrangutanMotors::setSpeeds(0, 0);
   numeroByte = 1;
   numeroByteLectura = 1;
   
   for (int i = 0; i < NUM_SENSORS; i++)
   {   
	   delay(10);
	   Serial.print(qtr.calibratedMinimumOn[i]);
	   Serial.print(' ');
	   adquirirIntervalos(qtr.calibratedMinimumOn[i]);
//	   guardarDatos();	   
   }
   
   Serial.println();
   
   for (int i = 0; i < NUM_SENSORS; i++)
   {
	   delay(10);
	   Serial.print(qtr.calibratedMaximumOn[i]);
	   Serial.print(' ');
	   adquirirIntervalos(qtr.calibratedMaximumOn[i]);
//	   guardarDatos();
   } 
    
   delay(3000);
   
   switchCalibration = digitalRead(8);
         
   while ( switchCalibration == HIGH)
     {
	     switchCalibration = digitalRead(8);
		 Serial.println("Awaiting for you");
		 delay(1000);
     };
     delay(2000); 
  
    Serial.println("Ready!!");  
}


#define RANGEBRAKE 3500


void loop()
{   
     position = qtr.readLine(sensorValues);   

	if (position<=3650 &&  position>=3350)
	{
		//	 maximum = 70; kp = 3.5;kd =80;ki=0;
		maximum = 100; kp = 2.8;kd =60;ki=0;
	}
	else{
			 if (position<=4500 &&  position>=2500)
			 {
              //kp=3.5;maximum = 70; kd =80; ki=0;
               kp=3;maximum = 70; kd =60; ki=0;
			 }
			 else{
				 //kp=3.5;maximum = 70; kd =80; ki=0;
				 kp = 2.5 ;maximum = 40; kd =80; ki=0;       //20
				 
			 }	
	}


	

	   proportional = (signed int)((66.68/7000)*(position - 3500));
	//	 Serial.print(proportional);
	//	 Serial.print(' ');   
	
	   error_brake = position -3500;
   if ( proportional <= -RANGEBRAKE )
	   {
//		   		OrangutanMotors::setM2Speed(-255);
//		   		OrangutanMotors::setM1Speed(-255);
//		   		delay(1);
//		   OrangutanMotors::setM2Speed(-200);
//		   OrangutanMotors::setM1Speed(200);
//		   delay(1);
	   }
	   else if ( proportional >= RANGEBRAKE )
	   {
//		   		OrangutanMotors::setM2Speed(-255);
//		   		OrangutanMotors::setM1Speed(-255);
//		   		delay(1);
//		   OrangutanMotors::setM2Speed(200);
//		   OrangutanMotors::setM1Speed(-200);
//		   delay(1);
	   }

	    // Calculos PD
	    derivative = proportional - last_proportional;
	//	integral = proportional + last_proportional;

	    last_proportional = proportional;


	    signed int power_difference = (proportional*kp) + (derivative*kd) +  (ki*integral);
// Serial.println(power_difference);


    motorDos = maximum - power_difference;
	motorUno = maximum + power_difference;

     if (motorDos > 255)  motorDos = 255;
	    
	 if (motorDos < -255) motorDos = -255;

     if (motorUno > 255)  motorUno = 255;
     
     if (motorUno < -255) motorUno = -255;
	 
	 
	    OrangutanMotors::setSpeeds(motorDos, motorUno);

   }

   




void adquirirIntervalos(int16_t datoFraccionar)
{
	intervalo1 = (datoFraccionar & primerTermino)>>8;
	intervalo2 = (datoFraccionar & segundoTermino);
}

int16_t concatResultado()
{
	int16_t concatenacion=0;
	concatenacion = concatenacion | intervalo1;
	concatenacion = concatenacion<<8;
	concatenacion = concatenacion | intervalo2;
	return concatenacion;
}

void guardarDatos()
{
	EEPROM.write(numeroByte, intervalo1);
	numeroByte+=1;
	EEPROM.write(numeroByte, intervalo2);
	numeroByte+=1;
}