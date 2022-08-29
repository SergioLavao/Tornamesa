#define pinSensor A0
#define pinMotor A1

char buffer[40];

int tiempoEspera = 3000;
int contadorSensor = 0;
int contadorLimite = 5;

int contadorEscan = 0;
int totalEscan = 36;

int progreso = 0;

bool estadoSensor = false;
bool escaneo = false;

void setup() 
{

  pinMode(pinMotor,OUTPUT);
  pinMode(pinSensor,INPUT);
  
  Serial.begin(9600);
  digitalWrite( pinMotor, LOW );

}

void loop() 
{

  if (Serial.available() > 0) {
    String test = Serial.readString();

    if(test == "Escanear()\n")
    {
      escaneo = true;
      Serial.write("Inicio de escaneo.\n");
      
    }else if(test == "Detener()\n")
    {
      escaneo = false;
      digitalWrite( pinMotor, LOW );
      Serial.write("Escaneo detenido.\n");

    }else
    {
      Serial.write("Comando invalido!\n");
    }

  }
  
  if(!escaneo)
    return;

  bool estadoActual = digitalRead(pinSensor);

  if( estadoSensor != estadoActual )
  {

    contadorSensor++;
    
    sprintf(buffer, "Paso... %d %", progreso);
    Serial.println(buffer);

    progreso++;
    
    if( contadorSensor >= contadorLimite )
    {

      contadorEscan++;
      
      sprintf(buffer, "Escaneando... Foto %d / %d %", contadorEscan, totalEscan);
      Serial.println(buffer);

      digitalWrite( pinMotor, LOW );
      delay(tiempoEspera);

      if( contadorEscan >= 36 )
      {
        
          contadorEscan = 0;
          Serial.write("Escaneo finalizado!");
          escaneo = false;
          
      }
            
      contadorSensor = 0;
    }
    
  }

  estadoSensor = estadoActual;
  digitalWrite( pinMotor, HIGH );
  
  delay(100);

}
