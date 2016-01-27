

#include <SPI.h>
#include <Andee.h>
#include <Servo.h> 


AndeeHelper btncut;
AndeeHelper btnPowerLevel;
AndeeHelper displaybox;

Servo theServo; 

char userPos[4];
int currentPosition; 
int newPosition;
int scalers = 0; 
const int servoPin = 3;

void setup()
{
  Andee.begin();  
  Andee.clear();  
  currentPosition = 36; 
  theServo.attach(servoPin);
  theServo.write(36); 
  delay(1000);
  setInitialData(); 
}


void setInitialData()
{
 
  
  btncut.setId(1);
  btncut.setType(BUTTON_IN);
  btncut.setLocation(0,0,FULL);
  btncut.setTitle("Power Off");
  btncut.requireAck(false); 
  
  btnPowerLevel.setId(2);
  btnPowerLevel.setType(KEYBOARD_IN); 
  btnPowerLevel.setLocation(1,0,FULL);
  btnPowerLevel.setTitle("Set Power Level (0 - 100)");
  btnPowerLevel.setKeyboardType(ANDEE_NUMERIC_A); 

  displaybox.setId(3);
  displaybox.setType(DATA_OUT); 
  displaybox.setLocation(2,0,FULL);
  displaybox.setTitle("Current Power");
  displaybox.setData(0);
}


void loop()
{
  if( btnPowerLevel.isPressed() )
  {
    memset(userPos, 0x00, 4);
    btnPowerLevel.ack();
    btnPowerLevel.getKeyboardMessage(userPos);

    newPosition = atoi(userPos); 
    
    if(newPosition < 0) newPosition = 0;
    if(newPosition > 100) newPosition = 100;
    
    scalers = map(newPosition, 0, 100, 67, 118);
    theServo.write(scalers);
    displaybox.setData(newPosition);
  }
  
  
  
  if( btncut.getButtonPressCount() > 0 )
  {
    btncut.ack(); 
   newPosition = 36;
    {
      theServo.write(newPosition);
      displaybox.setData(0); 
      displaybox.update();
      delay(15);
    }
  }    
  
  
  btncut.update();
  btnPowerLevel.update();
  displaybox.update();
  
  delay(500); 
}



