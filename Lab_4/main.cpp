//ONCE YOU GUYS ARE CHECKING IT PLEASE CHANGE THE VALUE OF DARK because mine is really low.
// ROVIN SORIANO
//LAB 4
// video: https://www.youtube.com/watch?v=YKX-MGzriQg

#include "Timer.h"

/* A simple program to sequentially turn on and turn off 3 LEDs */ 

int LEDWHITE = 4;
int LEDGREEN = 3;
int BUTTON = 5;
int PHOTO;
int switchpress;

// range of my faulty photo resistor, 12 is whats is being read with the flash light, 
int dark = 12;

enum BL_States { BL_SMStart, BL_LedOff, BL_LedOn } BL_State;

void TickFct_Blink() {

   switch ( BL_State ) { //Transitions
      case BL_SMStart:
         BL_State = BL_LedOff; //Initial state
         break;
      case BL_LedOff:
        Serial.print("OFFFFFF \n");
         if(PHOTO < dark || switchpress == 1){
           BL_State = BL_LedOn;
         } 
         else{
           BL_State = BL_LedOff;
         }
         break;
      case BL_LedOn:
         Serial.print("ONNNNNN \n");
         if(PHOTO < dark || switchpress == 1){
           BL_State = BL_LedOn;
         } 
         else{
           BL_State = BL_LedOff;
         }
         break;
      default:
         BL_State = BL_SMStart;
         break;
   }

   switch (BL_State ) { //State actions
      case BL_LedOff:
        Serial.print("OFFFFFF \n");
         digitalWrite(3, HIGH);
         digitalWrite(4, LOW);
         break;
      
      case BL_LedOn:
      int press = digitalRead(BUTTON);
      // we press it it reads to be in on state but at the same time its gotta be let go so we can hold it as long as possible!
      if(switchpress == 1 && press == 0|| PHOTO < dark  ){ 
      //  TickFct_Blink();
      //  while (!TimerFlag){}  // Wait for BL's period
      //  TimerFlag = 0;  
        Serial.print("ONNNNNN NOwWW \n");
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
       
        TimerSet(20000); //20,000 ms is 20 sec
        TimerOn();
      
       
        while (!TimerFlag){
            Serial.print("ON FOR 20 sec \n ");
        
             PHOTO = analogRead(A0);
          if(PHOTO < dark){ // if felt meotion within the 20 seconds its open... 
              Serial.print("IN TIMER RESET 20\n");
              reset20();
              break;
          }
            
            press = digitalRead(BUTTON);
            if (press == 1){ // the the button is press it will turn off
                Serial.print("Switch press GOTTA TURN OFF \n");
                digitalWrite(3, HIGH);
                digitalWrite(4, LOW);
                TimerSet(10000); //10,000 ms is 10 sec
                TimerOn();
                while (!TimerFlag){
                Serial.print("OFF Right now waiting\n");
            }
                TimerFlag = 0;
                break;
             }
         }  // Wait for BL's period
       TimerFlag = 0;  
      }
         break;

        default:
          break;
   }
}

void reset20 (){ // will be called if motion is felt within the 20 seconds light is on....
  
  Serial.print("RESET 20 function!!! \n");
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  TimerSet(20000); //20,000 ms is 20 sec
  TimerOn();
  while (!TimerFlag){
    Serial.print("WILL LAST for 20sec more RESET \n");
    PHOTO = analogRead(A0);
    if(PHOTO < dark){
      reset20 ();
      break;
  }
  int press = digitalRead(BUTTON);
            if (press == 1){
                Serial.print("Switch press GOTTA TURN OFF \n");
                digitalWrite(3, HIGH);
                digitalWrite(4, LOW);
                TimerSet(10000); //10,000 ms is 10 sec
                TimerOn();
                while (!TimerFlag){
                Serial.print("OFF Right now waiting\n");
            }
                TimerFlag = 0;
                break;
             }
         }  // Wait for BL's period
  
  TimerFlag = 0;
}

void setup() {
   pinMode(4, OUTPUT);
   pinMode(3, OUTPUT);
   pinMode(5, OUTPUT);
  //digitalWrite(4, LOW);
  
  Serial.begin(9600);
}

void loop() {
  Serial.print("In void LOOOP again \n");
  // put your main code here, to run repeatedly:
  //delay(1000);
  TickFct_Blink();

  // testing light works
  // digitalWrite(LEDWHITE, HIGH);    // turn on LED1 
  // digitalWrite(LEDGREEN, HIGH);    // turn on LED2
  //Serial.print("Hello world \n");
  PHOTO = analogRead(A0);
  switchpress = digitalRead(BUTTON);
  Serial.print("Button: ");
  Serial.print(switchpress);
  Serial.print("\n PHOTOs: ");
  Serial.print(PHOTO);
  Serial.print ("\n");

  
  
}