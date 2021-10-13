#include <SPI.h>
#include <MFRC522.h>
#include <Keyboard.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   
 
void setup() 
{
  Serial.begin(9600);  
  SPI.begin();
       
  mfrc522.PCD_Init();   
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  Keyboard.begin();
  delay(10000);

}
void loop() 
{
  
  
 
  Serial.print("UID tag :");
  String content= "";
  String contentAfter = "";
  byte letter;
  bool cardId = false;
  while(true){
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
    {
      //return;
      cardId = false;
    }else{
      cardId = true;
    }
    
    if ( ! mfrc522.PICC_ReadCardSerial()) 
    {
      cardId = false;
    }else{
      cardId = true;
    }
    if(cardId){
      content = "";
       for (byte i = 0; i < mfrc522.uid.size; i++) 
        {
           content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
           content.concat(String(mfrc522.uid.uidByte[i], HEX));
        }
        content.toUpperCase();
        if(content != contentAfter){
          Serial.println(content);
          contentAfter = content;
          Keyboard.println(content);
          Keyboard.press(KEY_RETURN);
          Keyboard.releaseAll(); 
          delay(3000);
        }
    }
   
  }
}
//https://www.luisllamas.es/como-emular-un-teclado-o-un-raton-con-arduino/
//https://create.arduino.cc/projecthub/shubamtayal/rfid-scanner-full-tutorial-6518db
