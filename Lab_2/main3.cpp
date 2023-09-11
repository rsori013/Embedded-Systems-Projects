//Rovin Soriano
// Lab 2 exercise 3
//https://youtu.be/_ApreojzDv0?t=25
// video starts at 24 seconds, added a video for it when going back

int B[4] = {2, 3, 4, 5};
int x = 6;
int y = 7;
int i = -1;

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

void close(){
  for(int i = 0; i < 4; i++){
      digitalWrite(B[i],0);
  }
}
//on or off? send binary
void lightSwitch(String holder){
   //Serial.print("IN lightSwitch"); 
  for(int i=0; i<4; i++){  
    if(holder[i]=='1'){
    digitalWrite(B[i], HIGH);
    }
    else{
      digitalWrite(B[i], LOW);
    }
  }
}
//to convert the int from the circle to binary format
String convertToBinary(int num) {
  String binary = "";
  for (int i = 3; i >= 0; i--) {
    if (bitRead(num, i) == 1) {
      binary += "1";
    } else {
      binary += "0";
    }
  }
  return binary;
}
void loop() {
  String holder;
  int gg = analogRead(0);//to get the value of the circle from 0-15
  //map(value, fromLow, fromHigh, toLow, toHigh)
  gg = map(gg, 0, 1023, 0, 15);
  Serial.println(gg);
  holder = convertToBinary(gg);
  lightSwitch(holder);
}

