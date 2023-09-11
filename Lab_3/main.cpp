//rovin soriano
//rsori013
//lab 3 
int red_pin = 9;
int blue_pin = 10;
int green_pin = 11;

//you will need to determine the value for dark
//its unique to the lighting in your room
//int dark_threshold = 70;

void turnoff(){
  analogWrite(red_pin, 0);
  analogWrite(blue_pin, 0);
  analogWrite(green_pin, 0);
}

enum ButtonStates{INIT,off, on} current_state;
void SM0_Tick(int light,int gg) {
   // State Transistions
   
   switch(current_state) {
       case INIT:
     	 Serial.print("CASE INIT ");
     	    if(light > 5){
             current_state = off;
           }
           else{
         	current_state = off;
           }
         break;
       case off:
     	 Serial.print("CASE OFF ");
     	 if(light < 5){	
         current_state = on;
         }
         else {
           current_state = off;
         }
         break;
       case on:
     	 Serial.print("CASE ON ");
         if(light <5){	
         current_state = on;
         }
     	 else if (light >5){	
           current_state = off;
         }	
         break;
       default:
         current_state = INIT;
         break;
   }
   // State Actions
   switch(current_state) {
   	case INIT:
      break;
    case off:
      turnoff();
      break;
    case on:
    Serial.print("\n In CASE ONE LIGHT: ");
    Serial.print(light);
    Serial.print("\n");
   //displays the color white
     	if(gg == 1){ //red
      Serial.print("\n red color led\n");
  		analogWrite(red_pin, 255);
  		analogWrite(green_pin, 0);
  		analogWrite(blue_pin, 0);
  		//delay(1000);
        }
     	if(gg == 2){ //blue
      Serial.print("\n blue color led\n");
  		analogWrite(red_pin, 0);
  		analogWrite(green_pin, 255);
  		analogWrite(blue_pin, 0);
  		//delay(1000);
        }
     	if(gg == 3){//green
      Serial.print("\n green color led\n");   
  		analogWrite(red_pin, 0);
  		analogWrite(green_pin, 0);
  		analogWrite(blue_pin, 255);
  		//delay(1000);
        }
     	if(gg == 4){ //purple
      Serial.print("\n purple color led\n");
  		analogWrite(red_pin, 255);
  		analogWrite(green_pin, 255);
  		analogWrite(blue_pin, 0);
  		//delay(1000);
        }
  
     	if(gg == 5){ //yelow
         Serial.print("\n yellow color led\n");
  		analogWrite(red_pin, 255);
  		analogWrite(green_pin, 0);
  		analogWrite(blue_pin, 255);
  		//delay(1000);
   		}
      break;
   	default:
      break;
   }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  Serial.begin(9600);
  current_state = INIT;
}
void loop() {
  int gg;
  int light;
  gg= analogRead(A0);
  light = analogRead(A1);  
  gg = map(gg, 0, 1023, 1, 5); //put 1-5 here but on my end its only reading up to 4 so when domeoing ill change it t o 1-6
   Serial.print("wheel: ");
   Serial.print(gg);
  Serial.print("\n photo: ");
  Serial.println(light);
  Serial.print("\n");
  SM0_Tick(light,gg);
  //  Serial.print("wheel: ");
  //  Serial.print(gg);
  // if(gg == 1){ //red
  //     Serial.print("\n red color led\n");
  // 		analogWrite(red_pin, 255);
  // 		analogWrite(green_pin, 0);
  // 		analogWrite(blue_pin, 0);
  // 		//delay(1000);
  //       }
  //    	if(gg == 2){ //blue
  //     Serial.print("\n blue color led\n");
  // 		analogWrite(red_pin, 0);
  // 		analogWrite(green_pin, 255);
  // 		analogWrite(blue_pin, 0);
  // 		//delay(1000);
  //       }
  //    	if(gg == 3){//green
  //     Serial.print("\n green color led\n");   
  // 		analogWrite(red_pin, 0);
  // 		analogWrite(green_pin, 0);
  // 		analogWrite(blue_pin, 255);
  // 		//delay(1000);
  //       }
  //    	if(gg == 4){ //purple
  //     Serial.print("\n purple color led\n");
  // 		analogWrite(red_pin, 255);
  // 		analogWrite(green_pin, 255);
  // 		analogWrite(blue_pin, 0);
  // 		//delay(1000);
  //       }
  
  //    	if(gg == 5){ //yelow
  //        Serial.print("\n yellow color led\n");
  // 		analogWrite(red_pin, 255);
  // 		analogWrite(green_pin, 0);
  // 		analogWrite(blue_pin, 255);
  // 		//delay(1000);
  //  		}
  // testing because photoresistor is weird
  // light = analogRead(A1);
  // Serial.print("\n photo: ");
  // Serial.println(light);
  // Serial.print("\n");

   //delay(1000);
}