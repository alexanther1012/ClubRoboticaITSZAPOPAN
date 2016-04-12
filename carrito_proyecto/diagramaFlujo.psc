Proceso Sigelineas
	num_sensor<-8
	Dimension sensorValue(num_sensor)
	Definir minimo1,minimo2,minimo3,minimo4,minimo5,minimo6,minimo7,minimo8 Como Entero
	minimo1<-0
	minimo2<-0
	minimo3<-0
	minimo4<-0
	minimo5<-0
	minimo6<-0
	minimo7<-0
	minimo8<-0
	Definir maximo1,maximo2,maximo3,maximo4,maximo5,maximo6,maximo7,maximo8 Como Entero
	maximo1<-0
	maximo2<-0
	maximo3<-0
	maximo4<-0
	maximo5<-0
	maximo6<-0
	maximo7<-0
	maximo8<-0
	Definir intervalo1,intervalo2 Como Entero
	intervalo1<-0
	intervalo2<-0
	Definir numeroByte,numeroByteLectura Como Entero
	numeroByte<-1
	numeroByteLectura<-1
	Definir posicionAnterior Como Entero
	posicionAnterior<-3500
	Definir maximum Como Entero
	maximum<-100
	Definir kp,kd,ki Como Real
	kp<-4
	kd<-40
	ki<-.2
	Definir Velcalibrate Como Entero
	Velcalibrate<-35
	Definir last_proportional Como Entero
	last_proportional<-0
	Definir integral Como Real
	integral<-0
	Definir position,switchCalibration Como Entero
	position<-0
	switchCalibration<-0
	Definir proportional,power_diference,derivative,motor_dos,motor_uno,error_brake Como Entero
	proportional<-0
	power_diference<-0
	derivative<-0
	motor_uno<-0
	motor_dos<-0
	error_brake<-0
	Definir pinSwitch Como Entero
	pinSwitch<-8
FinProceso

SubProceso setup()
	numeroByte<-1
	numeroByteLectura<-1
	Serialbegin(9600)
	Para i<-0 Hasta 7 Hacer
		Para counter<-0 Hasta 17 Hacer
			Si counter<5 O couter>=14 Entonces
				OrangutanMotorsSetSpeed(-Velcalibrate,Velcalibrate)
			Sino
				OrangutanMotorsSetSpeed(Velcalibrate,-Velcalibrate)
			FinSi
			qrtcalibrate()
			Esperar 20 Milisegundos
		FinPara
	FinPara
	OrangutanMotorsSetSpeed(0,0)
	numeroByte<-1
	numeroByteLectura<-1
	Para i<-0 Hasta num_sensor Hacer
		Esperar 10 Milisegundos
		SerialPrint(calibrateMin)
		SerialPrint('')
		AdquirirIntervalo(calibrateMin)
	FinPara
	SerialPrintln('')
	Para i<-0 Hasta num_sensor Hacer
		Esperar 10 Milisegundos
		SerialPrint(calibrateMax)
		SerialPrint('')
		AdquirirIntervalo(calibrateMax)
	FinPara
	Esperar 3000 Milisegundos
	switchCalibration<-digitalRead(8)
	Mientras switchCalibration==1 Hacer
		switchCalibration<-digitalRead(8)
		SerialPrintln('Esperando')
		Esperar 1000 Milisegundos
	FinMientras
	Esperar 2000 Milisegundos
	SerialPrintln('Listo')
FinSubProceso

SubProceso loop()
	position<-qrtreadLine(sensorValues)
	Si position<=3650 Y position>=3350 Entonces
		maximum<-95
		kp<-4
		kd<-50
		ki<-0
	Sino
		Si position<=4500 Y position>=2500 Entonces
			maximum<-75
			kp<-3.3
			kd<-60
			ki<-0
		Sino
			maximum<-50
			kp<-2.5
			kd<-80
			ki<-0
		FinSi
	FinSi
	proportional<-((66.68/7000)*(position-3500))
	error_brake<-position-3500
	derivative<-proportional-last_proportional
	last_proportional<-proportional
	power_diference<-(proportional*kp)+(derivative*kd)+(ki*integral)
	motor_dos<-maximum-power_diference
	motor_uno<-maximum+power_diference
	Si motor_dos>255 Entonces
		motor_dos<-255
	FinSi
	Si motor_dos<-255 Entonces
		motor_dos<--255
	FinSi
	Si motor_dos>255 Entonces
		motor_dos<-255
	FinSi
	Si motor_dos<-255 Entonces
		motor_dos<--255
	FinSi
	OrangutanMotorsSetSpeed(motor_dos,motor_uno)
FinSubProceso

SubProceso sensor<-qrtreadLine(sensor)
FinSubProceso

SubProceso qrtcalibrate()
FinSubProceso

SubProceso num<-digitalRead(num)
FinSubProceso

SubProceso SerialPrintln(text)
FinSubProceso

SubProceso AdquirirIntervalo(inter)
FinSubProceso

SubProceso SerialPrint(text)
FinSubProceso

SubProceso calibracion<-calibrate()
FinSubProceso

SubProceso OrangutanMotorsSetSpeed(min,max)
FinSubProceso

SubProceso Serialbegin(numero)
FinSubProceso

SubProceso digitalWrite(pin,MODO)
FinSubProceso

SubProceso pinMode(pin,MODO)
FinSubProceso

SubProceso qrt(pines,num_sensor,muestreo,muestreoIR)
FinSubProceso

