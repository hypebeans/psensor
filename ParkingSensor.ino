#include <Servo.h>
Servo myServoIn, myServoOut;

#include <LiquidCrystal.h> 
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

int pin1 = A0;
int pin2 = A1;
int pin3 = A4;
int pin4 = A5;
int in = 11;
int out = 12;
int servoPinIn = 8; //servo in
int servoPinOut = 9; //servo out

int val1, val2, val3, val4;
int valin, valout;

//int flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;
//int jum1 = 0, jum2 = 0, jum3 = 0, jum4 = 0;
//int av1, av2, av3, av4;

int pos = 0;
int count = 0;
boolean stateIn=true, statenowIn=true;
boolean stateOut=true, statenowOut=true;

void setup() {
  lcd.begin(16,2);
//  Serial.begin(9600);  
  lcd.setCursor(0,0);
  lcd.print("Welcome to");
  lcd.setCursor(8,1);
  lcd.print("how to detect car parking sensor xd");
  delay(5000);
  lcd.clear();

  myServoIn.attach(servoPinIn);
  myServoIn.write(0);
  myServoOut.attach(servoPinOut);
  myServoOut.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  pinMode(pin1,INPUT);
  pinMode(pin2,INPUT);
  pinMode(pin3,INPUT);
  pinMode(pin4,INPUT);
  pinMode(in,INPUT);
  pinMode(out,INPUT);

  val1= analogRead(pin1);
  val2 = analogRead(pin2);
  val3 = analogRead(pin3);
  val4 = analogRead(pin4);
  valin = digitalRead(in);
  valout = digitalRead(out);

//  if(val1 < av1+30){
//  jum1 = jum1 + val1;
//  flag1++;
//  }
//  av1 = jum1/flag1;
//
//  if(val2 < av2+30){
//  jum2 = jum2 + val2;
//  flag2++;
//  }
//  av2 = jum2/flag2;
//
//  if(val3 < av3+50){
//  jum3 = jum3 + val3;
//  flag3++;
//  }
//  av3 = jum3/flag3;
//
//  if(val4 < av4+50){
//  jum4 = jum4 + val4;
//  flag4++;
//  }
//  av4 = jum4/flag4;
//  

//  Serial.print(av1); 
//  Serial.print(" ");
//  Serial.print(av2); 
//  Serial.print(" ");
//  Serial.print(av3); 
//  Serial.print(" ");
//  Serial.print(av4); 
//  Serial.print(" ");
//  Serial.print("||"); 
//  Serial.print(" ");
//  Serial.print(val1); 
//  Serial.print(" ");
//  Serial.print(val2); 
//  Serial.print(" ");
//  Serial.print(val3); 
//  Serial.print(" ");
//  Serial.print(val4);
//  Serial.print(" ");
//  Serial.print(valin);
//  Serial.print(" ");
//  Serial.println(valout);

  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);
  pinMode(in,OUTPUT);

// LCD ******************************************************** 
//  lcd.setCursor(0,0);
  lcd.print("P:");
  lcd.setCursor(2,1);

// LED ******************************************************** 
  
  if (val1 > 30 && val1<90) {
    digitalWrite(pin1,HIGH);
    lcd.print("1");
  }
  else {
    digitalWrite(pin1,LOW);
  }

  if (val2 > 30 && val2<90) {
    digitalWrite(pin2,HIGH);
    lcd.print("2");
  }
  else {
    digitalWrite(pin2,LOW);
  }
  
  if (val3 > 60 && val3<90) {
    digitalWrite(pin3,HIGH);
    lcd.print("3");
  }
  else {
    digitalWrite(pin3,LOW);
  }

  if (val4 > 60 && val4<90) {
    digitalWrite(pin4,HIGH);
    lcd.print("4");
  }
  else {
    digitalWrite(pin4,LOW);
  }

// IN ******************************************************** 
  if (valin == HIGH) {
    tone(in,1000);
    statenowIn = true;
    if(stateIn != statenowIn) { 
      spinCW();
      count++;
      stateIn = statenowIn;
      delay(3000);
    }
  }
  else {
    noTone(in);
    statenowIn = false;
    if(stateIn != statenowIn) { 
      spinCCW();
      stateIn = statenowIn;
      
      delay(3000);
    }
  }

// OUT ******************************************************** 
  if(valout == HIGH) {
    tone(in,1000);
    statenowOut = true;
    if(stateOut != statenowOut) {
      spinCWOut();
      count--;
      stateOut = statenowOut;
      delay(3000);
    }
  }
  else {
    noTone(in);
    statenowOut = false;
    if(stateOut != statenowOut) {
      spinCCWOut();
      stateOut = statenowOut;
      delay(3000);
    }
  }

  // Total Cars ******************************************************** 
  lcd.setCursor(9,1);
  lcd.print("Total:");
  if(count > 4) {
    myServoIn.write(0);
    delay(1000);
    myServoIn.detach();
    lcd.setCursor(8,1);
    lcd.print(" Full  ");
    count = 4;
  }
  if(count<0) {
    myServoOut.write(0);
    delay(1000);
    myServoOut.detach();
    count = 0;
  }
  lcd.print(count);

  delay(300);
  lcd.clear();
}


//To the right
void spinCW() {
  for (pos = 90; pos >= 0; pos -= 1) {
      myServoIn.write(pos);
      delay(10); 
    }
}

//To the left
void spinCCW() {
  for (pos = 0; pos <= 90; pos += 1) {
      myServoIn.write(pos);
      delay(10);
    }
}

//To the right
void spinCWOut() {
  for (pos = 90; pos >= 0; pos -= 1) {
      myServoOut.write(pos);
      delay(10); 
    }
}

//To the left
void spinCCWOut() {
  for (pos = 0; pos <= 90; pos += 1) {
      myServoOut.write(pos);
      delay(10);
    }
}
