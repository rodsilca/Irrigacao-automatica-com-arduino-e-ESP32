#include <DHT11.h>
#define rele 3
#define sensor A0
DHT11 dht11(2);

void setup()
{
  
  Serial.begin(9600);
  pinMode(rele, OUTPUT);
  pinMode(sensor, INPUT);
  
  //Inciar com a rele desligado
  digitalWrite( rele, HIGH);
}

void loop() 
{
  int temperatura =0;
  int umidade =0;
  int result = dht11.readTemperatureHumidity(temperatura, umidade);
  int valorSensor = analogRead(sensor);  // Lê o valor do sensor
  int umidadePercentual = map(valorSensor, 1023,0 , 0, 100);  // Mapeia para uma porcentagem de 0 a 100%

  if (result == 0) {
    Serial.print(temperatura);//Imprime temperatura no terminal
    Serial.print(",");
    Serial.println(umidadePercentual); //Imprime umidade no terminal
    delay(1000);
  } else {
    Serial.println(DHT11::getErrorString(result));
  }
    
  
  //512 == 50% de umidade, abaixo dessa faixa a rele é ativada e só desliga quando o Sensor retornar acima de 512
  while (valorSensor >512) {
    digitalWrite(3, LOW);   //rele / bomba
      //Serial.println("rele ligado");
    delay(1500);
    digitalWrite(3, HIGH);   //rele / bomba
      //Serial.println("rele desligado");
      
    delay(5000); 
    valorSensor = analogRead(sensor); 

    if (result == 0) {
      umidadePercentual = map(valorSensor, 1023,0 , 0, 100);
      Serial.print(temperatura);
      Serial.print(",");
      Serial.println(umidadePercentual); 
    } else {
      Serial.println(DHT11::getErrorString(result));
    }
                 
  }

}
