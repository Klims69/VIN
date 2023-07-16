// C++ code
//
const int echo = 7;
const int trig = 4;
const int PIN_RED   = 13;
const int PIN_GREEN = 12;
const int PIN_BLUE  = 11;
const int BUTTON_PIN_GO = 3;
const int BUTTON_PIN_RESET = 2;

float MAX_DISTANCE = 53.7;
float MIN_DISTANCE = 0;
float JUMP = 8.1;

int StartingColor = 1;
int SetDistance = 0;
int Reset = 0;
int FindMiddle = 0;
float interval = 0;
float duration = 0;
float distance = 0;
float lenght = 0;
float middle = 0;
int R = 1;
int G = 1;
int B = 1;

void setup()
{
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);
  pinMode(trig, INPUT);
  pinMode(echo, OUTPUT);
  pinMode(BUTTON_PIN_GO, INPUT);
  pinMode(BUTTON_PIN_RESET, INPUT);     
  Serial.begin(9600);
}

void loop() {
  StartingColor = 1;
  delay(100);
  digitalWrite(echo, HIGH);
  delay(10); 
  digitalWrite(echo, LOW);
  duration = pulseIn(trig, HIGH);
  distance = (duration/2) / 28.5;
  
  SetDistance = digitalRead(BUTTON_PIN_GO);
  Reset = digitalRead(BUTTON_PIN_RESET);

  if(FindMiddle == 1){
    interval = MAX_DISTANCE - distance;
    StartingColor = interval * JUMP;
    if(interval > middle - 0.5 && interval < middle + 0.5 ){
      setColor(1,255,1);
    }
    else if(interval > MIN_DISTANCE && interval < middle - 0.5){
      // R = 256 - StartingColor;
      // G = 1;
      // B = StartingColor;
      setColor(255 ,1 ,1 );
    }
    else if(interval > middle + 0.5 ) {
      // R = StartingColor;
      // G = 1;
      // B = 256-StartingColor;
      setColor(1 ,1 ,255 );
    }
    else{
        setColor(255,1,1);
    }
  }
  else {
    setColor(255,1,1);
  }

  if(SetDistance == 1){
    MIN_DISTANCE = distance;
    FindMiddle = 1;
    Serial.print("Lenght of object in cm: ");
    lenght = MAX_DISTANCE - MIN_DISTANCE;
    Serial.println(lenght);
    Serial.print("Middle: ");
    middle = lenght/2;
    JUMP = 510/middle;
    Serial.println(middle);
    Serial.println();
    delay(1000);
  }

  if(Reset == 1){
    MAX_DISTANCE = distance;
    FindMiddle = 0;
    Serial.print("Max distance reset to:");
    Serial.println(MAX_DISTANCE);
    Serial.println();
    delay(1000);
  }
}

void setColor(int R, int G, int B) {
  analogWrite(PIN_RED,   R);
  analogWrite(PIN_GREEN, G);
  analogWrite(PIN_BLUE,  B);
}

