
//rsori013 lab 7 final project 
//video: https://www.youtube.com/watch?v=q-HWtbY07x0
#include "Timer.h"
#include "Adafruit_LiquidCrystal.h"
// Depending on the LiquidCrystal library you are able to install, it might be:
// #include "LiquidCrystal.h"
#include "pitches.h"

// Sound Variables  
int buzzer = 8;
int xValue;
int yValue;
int zValue;

// == Song 1 ==
int song1[] = {
NOTE_E4, NOTE_C5, NOTE_B1, NOTE_F3, NOTE_C4, 
NOTE_A4, NOTE_A4, NOTE_GS5, NOTE_C5, NOTE_CS4, 
NOTE_AS4, NOTE_C5, NOTE_DS4, NOTE_CS5, NOTE_GS4, 
NOTE_C3, NOTE_E3, NOTE_DS5, NOTE_D4, NOTE_D3
};
int song1_time[] = {
  2, 1, 2, 1, 1, 4, 8, 16, 8, 4, 4, 1, 8, 4, 2, 4, 4, 16, 4, 2
};

// == Song 2 ==

int song2[] = {
  NOTE_FS5, NOTE_D2, NOTE_DS5, NOTE_G2, NOTE_B3, 
  NOTE_C2, NOTE_G5, NOTE_D6, NOTE_CS5, NOTE_AS4, 
  NOTE_DS6, NOTE_D3, NOTE_CS4, NOTE_E5, NOTE_DS6,
   NOTE_E4, NOTE_B4, NOTE_F4, NOTE_E6, NOTE_DS4
};

int song2_time[] = {
  2, 2, 4, 8, 1, 8, 4, 4, 16, 8, 2, 4, 16, 8, 2, 4, 16, 4, 8, 1
};

// == Song 3 == 

int song3[] = {
  NOTE_A5, NOTE_D4, NOTE_D6, NOTE_DS3, NOTE_G4, 
  NOTE_B2, NOTE_F2, NOTE_A3, NOTE_AS2, NOTE_B5, 
  NOTE_C6, NOTE_C3, NOTE_GS3, NOTE_G2, NOTE_FS5, 
  NOTE_AS4, NOTE_GS2, NOTE_CS3, NOTE_C3, NOTE_AS2
};

int song3_time[] = {
  1, 2, 16, 4, 16, 2, 16, 1, 1, 2, 1, 8, 2, 16, 8, 1, 16, 4, 1, 2
};


// LCD variables
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
Adafruit_LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// Depending on the LiquidCrystal library you are able to install, it might be:
// LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



// Task Structure Definition
typedef struct task {
   int state;                  // Tasks current state
   unsigned long period;       // Task period
   unsigned long elapsedTime;  // Time elapsed since last task tick
   int (*TickFct)(int);        // Task tick function
} task;


const unsigned char tasksNum = 4;
task tasks[tasksNum]; // We have 4 tasks

// Task Periods

const unsigned long periodLCDOutput = 100;
const unsigned long periodJoystickInput = 100;
const unsigned long periodSoundOutput = 100;
const unsigned long periodController = 500;


// GCD 
const unsigned long tasksPeriodGCD = 100;

// Task Function Definitions
int TickFct_LCDOutput(int state);
int TickFct_JoystickInput(int state);
int TickFct_SoundOutput(int state);
int TickFct_Controller(int state);

// Task Enumeration Definitions
enum LO_States {LO_init, LO_MenuOptionSong1, LO_MenuOptionSong2, LO_MenuOptionSong3, Song1, Song2, Song3, Song1Pause, Song2Pause, Song3Pause};
enum JI_States {JI_init, JI_Sample};
enum SO_States {SO_init, SO_SoundOn, SO_SoundOff,SO_Pause};
enum C_States {C_init, C_T1};




void TimerISR() { // TimerISR actually defined here
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) { // Heart of the scheduler code
     if ( tasks[i].elapsedTime >= tasks[i].period ) { // Ready
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = 0;
     }
     tasks[i].elapsedTime += tasksPeriodGCD;
  }
}


void LCDWriteLines(String line1, String line2) {
  lcd.clear();          
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);
}

// Task Function Definitions

int menuOption = 0;\
int play = 0;
// bool Song1play = false;
// bool Song2play = false;
// bool Song3play = false;
int joystickButton = 0;
bool isButtonRelease = false;
bool isButtonRelease2 = false;
bool isButtonRelease3 = false;
bool soundOn = false;
bool home = true;
int songFinished = 0;
int counter = 0;
int note = 0;
int pauseKey =0;
bool isPause = false;

// Task 1
int TickFct_LCDOutput(int state) {
  Serial.print("in LCDOutput state\n");
  zValue = digitalRead(10);
  joystickButton = digitalRead(10);
  if (joystickButton == 1) {
    isButtonRelease = true;
  }
  switch (state) { // State Transitions
    case LO_init:
     Serial.print("LCD LO_init\n");
     if(songFinished) {
    LCDWriteLines("Shut up", "Arduino");
     }
      lcd.begin(16, 2);
      zValue = digitalRead(10);

      LCDWriteLines("Song 1  Song 2", "Song 3  Start");
      if(menuOption == 0){
        lcd.setCursor(13, 1); // start;
        }
      else if(menuOption == 1) {
         lcd.setCursor(6, 0); // song 1 
         
         if (zValue == 0 && isButtonRelease && menuOption == 1){
           isButtonRelease = false;
           state = LO_MenuOptionSong1; 
            break;
            //LCDWriteLines("Song 1*  Song 2", "Song 3  Start");
         }
      }
      else if (menuOption == 2){
         lcd.setCursor(6, 1); // song 2 
           
          if (zValue == 0 && isButtonRelease && menuOption == 2){
             isButtonRelease = false;
             state = LO_MenuOptionSong2; 
             break;
           //LCDWriteLines("Song 1  Song 2*", "Song 3  Start");
         }
         
      }
      else if (menuOption == 3){
          lcd.setCursor(14, 0);  // song 3 
            
           if (zValue == 0 && isButtonRelease && menuOption == 3){
              isButtonRelease = false;
              state = LO_MenuOptionSong3; 
              break;
           //LCDWriteLines("Song 1  Song 2", "Song 3*  Start");
         }
      }
      //lcd.setCursor(12, 1); // start 
      lcd.blink();
      // else if(menuOption == 1){state = LO_MenuOptionA ;}
      // else if(menuOption == 2){state = LO_MenuOptionB ;}
      // else if(menuOption == 3){state = LO_MenuOptionC ;}
      
    break;
    case LO_MenuOptionSong1:
    Serial.print("LCD MENU1\n");
        isButtonRelease = false; 
        LCDWriteLines("Song 1* Song 2", "Song 3  Start");
        zValue = digitalRead(10);
        joystickButton = digitalRead(10);
         if (joystickButton == 1) {
          isButtonRelease2 = true;
        }
        lcd.setCursor(13, 1); // start;
        lcd.blink();
        if (zValue == 0 && isButtonRelease2){// if press start
        soundOn = true;
        isButtonRelease2 = false;
        state = Song1;
        break;
      }
        //LCDWriteLines("Current Song 1 ", "Song 1");
        // if(menuOption == 0){state = LO_init;}
        // else if(menuOption == 1){state = LO_MenuOptionA ;}
        // else if(menuOption == 2){state = LO_MenuOptionB ;}
        // else if(menuOption == 3){state = LO_MenuOptionC ;}
      
    break;
    case LO_MenuOptionSong2:
    Serial.print("LCD MENU2\n");
      isButtonRelease = false; 
      LCDWriteLines("Song 1  Song 2", "Song 3* Start");
      zValue = digitalRead(10);
      joystickButton = digitalRead(10);
         if (joystickButton == 1) {
          isButtonRelease2 = true;
        }
        lcd.setCursor(13, 1); // start;
        lcd.blink();
        if (zValue == 0 && isButtonRelease2){// if press start
        soundOn = true;
        isButtonRelease2 = false;
        state = Song3;
        break;
      }
      //LCDWriteLines("Current Song 2 ", "Song 2");
      // if(menuOption == 0){state = LO_init;}
      // else if(menuOption == 1){state = LO_MenuOptionA ;}
      // else if(menuOption == 2){state = LO_MenuOptionB ;}
      // else if(menuOption == 3){state = LO_MenuOptionC ;}
      

    break;
    case LO_MenuOptionSong3:
    Serial.print("LCD MENU3\n");
      isButtonRelease = false; 
      LCDWriteLines("Song 1  Song 2*", "Song 3  Start");
      zValue = digitalRead(10);
      joystickButton = digitalRead(10);
         if (joystickButton == 1) {
          isButtonRelease2 = true;
        }
        lcd.setCursor(13, 1); // start;
        lcd.blink();
        if (zValue == 0 && isButtonRelease2){// if press start
        soundOn = true;
        isButtonRelease2 = false;
        state = Song2;
        break;
      }
    break;


    case Song1:
    Serial.print("LCD SONG1\n");
     
      play = 1;
      LCDWriteLines("Current Song 1 ", "Pause   Play*");
      if (xValue < 400){
        pauseKey = 2;
        lcd.setCursor(13, 1); // playy
        } //right
      else if (xValue > 600){
        pauseKey = 3;
        lcd.setCursor(6, 1); // Pause
        if (zValue == 0 && pauseKey == 3){// if press start
        state = Song1Pause;
        break;
      }
        } //left
      if(note >= 20){
        state = LO_init;
        break;
      }
    break;
    case Song3:
    Serial.print("LCD SONG2\n");
      play = 2;
      LCDWriteLines("Current Song 3 ", "Pause   Play*");
      if (xValue < 400){
        pauseKey = 2;
        lcd.setCursor(13, 1); // playy
        } //left
      else if (xValue > 600){
        pauseKey = 3;
        lcd.setCursor(6, 1); // Pause
        if (zValue == 0 && pauseKey == 3){// if press start
        state = Song3Pause;
        break;
      }
        } //right
      if(note >= 20){
        state = LO_init;
        break;
      }
    break;
    case Song2:
    Serial.print("LCD SONG3\n");
     play = 3;
      LCDWriteLines("Current Song 2 ", "Pause   Play*");

      if (xValue < 400){
        pauseKey = 2;
        lcd.setCursor(13, 1); // playy
        } //left
      else if (xValue > 600){
        pauseKey = 3;
        lcd.setCursor(6, 1); // Pause
        if (zValue == 0 && pauseKey == 3){// if press start
        state = Song2Pause;
        break;
      }
        } //right
      if(note >= 20){
        state = LO_init;
        break;
      }
    break;


    case Song1Pause:
        LCDWriteLines("Current Song 1 ", "Pause*  Play");
        play = 4;
        zValue = digitalRead(10);
        joystickButton = digitalRead(10);
         if (joystickButton == 1) {
            isButtonRelease3 = true;
        }

        if (zValue == 0 && isButtonRelease3){// if press start
        //play = 4; 
          state = Song1;
          isButtonRelease3 = false;
          break;
          } 
    break;

    case Song2Pause:
        LCDWriteLines("Current Song 2 ", "Pause*  Play");
        play = 4; 
        zValue = digitalRead(10);
        joystickButton = digitalRead(10);
        if (joystickButton == 1) {
            isButtonRelease3 = true;
        }
        if (zValue == 0 && isButtonRelease3){// if press start
          state = Song2;
          isButtonRelease3 = false;
          break;
        } 
    break;

    case Song3Pause:
        LCDWriteLines("Current Song 3 ", "Pause*  Play");
        play = 4; 
        zValue = digitalRead(10);
        joystickButton = digitalRead(10);
         if (joystickButton == 1) {
            isButtonRelease3 = true;
        }
        if (zValue == 0 && isButtonRelease3){// if press start
          state = Song3;
          isButtonRelease3 = false;
          break;
        } 
    break;

    default:
       menuOption = 0;
       //play = false;
    break;
  }

  return state;
  
}
// Task 2
int TickFct_JoystickInput(int state) {
   Serial.print("in JoystickInput state\n");
  switch (state) { // State Transitions
    case JI_init:
    state = JI_Sample;
    break;
    case JI_Sample:
    break;
  }
  //up,left,right
   switch (state) { // State Actions
    case JI_Sample:
      xValue = analogRead(A0);
      yValue = analogRead(A1);
      menuOption =0;
      if(yValue > 600){menuOption = 1;} //up
      else if (xValue < 400){menuOption = 2;} //left
      else if (xValue > 600){menuOption = 3;} //right
      //menuOption = input < 500 ? 1 : 0;
     
    break;
  }
  return state;
}
// Sound Output
int TickFct_SoundOutput(int state) {
  Serial.print("in SOUNDOUTPUT state\n");

  switch (state) { // State Transitions
    case SO_init:
      noTone(buzzer);
      note = 0;
      home = true;
      if(soundOn == true){
      state = SO_SoundOn;
      }
    break;
    case SO_SoundOn:
      if(play == 1){
        if(counter >= song1_time[note]) { // length for song 1 
          state = SO_SoundOff;
          note++;
          counter = 0;
            if(note >= 20){ //added this if statement to make sure it stops after reading the arrayy
            noTone(buzzer);
            soundOn = false;
            songFinished = 1; // sending its done
            state = SO_init;
            break;
          }
        }}
      if(play == 2){
        if(counter >= song2_time[note]) { // length for song 2 
          state = SO_SoundOff;
          note++;
          counter = 0;
            if(note >= 20){ //added this if statement to make sure it stops after reading the arrayy
            noTone(buzzer);
            soundOn = false;
            songFinished = 1; // sending its done
            state = SO_init;
            break;
          }
        }}
      if(play == 3){
        if(counter >= song3_time[note]) { // length for song 3 
          note++;
          counter = 0;
            if(note >= 20){ //added this if statement to make sure it stops after reading the arrayy
            noTone(buzzer);
            soundOn = false;
            songFinished = 1; // sending its done
            state = SO_init;
            break;
          }
        }}
      if(play == 4){
        state = SO_Pause;
        break;
      }
        
      
    break;
    case SO_SoundOff:
      state = SO_SoundOn;
    break;

    case SO_Pause:

      if(isPause == false){
      state = SO_SoundOn;
      }
      else {
        state = SO_Pause;
      }
    break;

    
  }
   switch (state) { // State Actions
    case SO_SoundOn:

      if (play == 0) {noTone(buzzer);}
      else if( play == 1){
      tone(buzzer, song1[note], periodSoundOutput * song1_time[note]);
      counter++;
      }
      else if(play == 2){
      tone(buzzer, song2[note], periodSoundOutput * song2_time[note]);
      counter++;
      }
      else if(play == 3){
      tone(buzzer, song3[note], periodSoundOutput * song3_time[note]);
      counter++;
      }
    break;

    case SO_SoundOff:
      noTone(buzzer);
    break;

    case SO_Pause:
      noTone(buzzer);
    break;



  }
  return state;
}

// Task 4 (Unused)
int TickFct_Controller(int state) {
  switch (state) { // State Transitions
    case 0:
    break;
  }

   switch (state) { // State Actions
    case 0:
    break;
  }
  return state;
}



void InitializeTasks() {
  zValue = digitalRead(10);
  unsigned char i=0;
  tasks[i].state = LO_init;
  tasks[i].period = periodLCDOutput;
  tasks[i].elapsedTime = tasks[i].period;
  tasks[i].TickFct = &TickFct_LCDOutput;
  ++i;
  tasks[i].state = JI_init;
  tasks[i].period = periodJoystickInput;
  tasks[i].elapsedTime = tasks[i].period;
  tasks[i].TickFct = &TickFct_JoystickInput;
  ++i;
  tasks[i].state = SO_init;
  tasks[i].period = periodSoundOutput;
  tasks[i].elapsedTime = tasks[i].period;
  tasks[i].TickFct = &TickFct_SoundOutput;
  ++i;
  tasks[i].state = C_init;
  tasks[i].period = periodController;
  tasks[i].elapsedTime = tasks[i].period;
  tasks[i].TickFct = &TickFct_Controller;

}

void setup() {
  // put your setup code here, to run once:
  InitializeTasks();

  TimerSet(tasksPeriodGCD);
  TimerOn();
  Serial.begin(9600);
  pinMode(10, INPUT_PULLUP);
  // Initialize Outputs
  lcd.begin(16, 2);
  // Initialize Inputs

}

void loop() {
  // put your main code here, to run repeatedly:
  // Task Scheduler with Timer.h
  xValue = analogRead(A0);
  yValue = analogRead(A1);
  zValue = digitalRead(10);
  //just for seeing values purposes when checking everything
  Serial.print("x = ");
  Serial.print(xValue);
  Serial.print(", y = ");
  Serial.println(yValue);
  Serial.print("z = ");
  Serial.print(zValue);
  Serial.print("menu Option: ");
  Serial.print(menuOption);
   Serial.print("\n ");

   Serial.print("Current note: ");
  Serial.println(note);

  delay(9000);
}