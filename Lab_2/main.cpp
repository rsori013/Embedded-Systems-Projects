//LAB 2 Exercise 1'
//https://youtu.be/0tPc3yZE8pM 
// video for lab 1 is up to 9 seconds long

int B[4] = {2, 3, 4, 5};
int x = 6;
int y = 7;

int num = 750;
void setup() {

  // put your setup code here, to run once:
  pinMode(6, INPUT);
  pinMode(7, INPUT_PULLUP);

  for (int i = 0; i < 4; i++) {
    pinMode(B[i], OUTPUT);
 }
  Serial.begin(9600);
}

void flash() {
    for (int i = 0; i < 4; i++) {
      digitalWrite(B[i], HIGH);
    }
    delay(500);
    for (int i = 0; i < 4; i++) {
      digitalWrite(B[i], LOW);
    }
    delay(500);
    Serial.println(analogRead(A0));
}
void loop() {

  // put your main code here, to run repeatedly:
  int pulldown = digitalRead(x); //reading 0 or 1
  int pullup = digitalRead(y); //reading 0 or 1
  Serial.print("LOOP PULLDOWN:");
  Serial.print (pulldown);
  Serial.print("\nPull up\n");
  Serial.print (pullup);
  //All you need to do is make all the LEDs turn on when you press button button Y and turn off when you press button X.
  if( pulldown == 0x01){//x off
    for(int i = 0; i < 4; i++){
      digitalWrite(B[i],LOW);
   	}
  }
  if ( pullup == 0x00){//Y on
     for(int i = 0; i < 4; i++){
      	digitalWrite(B[i], HIGH);
     }
   }

  //flash();
}