#include <SoftwareSerial.h>
#define RX 2
#define TX 3
String AP = "FAMILIA-AGUDELO";       // AP NAME
String PASS = "1061279933eliza25098761"; // AP PASSWORD

String HOST = "192.168.101.8";
String PORT = "80";
String field = "field1";

int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;

SoftwareSerial esp8266(RX,TX); 
 
void setup() {
  pinMode(9, OUTPUT); 
  
  Serial.begin(9600);
  esp8266.begin(115200);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
  
}

void loop() {
 digitalWrite(9, LOW);
 
 valSensor = getSensorData();

 String getData = "GET /hello/index.php?field="+String(valSensor);
 
 sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,7,"OK") ; //15
 sendCommand("AT+CIPSEND=0," +String(getData.length()+4),2,">"); //4
 esp8266.println(getData);
 delay(1500); //delay 1500
 
 countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");

 digitalWrite(9, HIGH);
 Serial.println("Data send: "+String(valSensor));
 
}

int getSensorData(){
  return random(1000); // Replace with your own sensor code
}

void sendCommand(String command, int maxTime, char readReplay[]) {
 // Serial.print(countTrueCommand);
 // Serial.print(". at command => ");
 // Serial.print(command);
 // Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
 //   Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
   // Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
  
 }


 
