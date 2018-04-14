#include <SPFD5408_Adafruit_GFX.h>    // Core graphics Adafruit library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>     // Touchscreen library 
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#define Button 21


// *** Define Touchscreen Pin
#define YP A3  
#define XM A2  
#define YM 9   
#define XP 8   
// *** Define Value of Touchscreen input
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); 

// *** Define Pin of LCD used
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

// *** Define Name of Color
#define WHITE   0x0000
#define BLACK   0xFFFF
#define BLUE     0xF800
#define GREEN   0x07E0
#define YELLOW    0x001F
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define RED  0xFFE0
#define GREY    0x2108
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
#define MINPRESSURE 10
#define MAXPRESSURE 1000

// Meter colour schemes
#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5

void border(void);
void projectname(void);
void  mainwindow(void);
void display_status(void);


uint8_t id;
uint8_t getFingerprintEnroll();
uint8_t deleteFingerprint(uint8_t id);
int getFingerprintIDez();
uint8_t readnumber(void) ;
void connect_to_sensor(void);
uint8_t readdate(void) ;

SoftwareSerial mySerial(50,51);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

 int date=0;

uint32_t runTime = -99999;       // time for next update
int reading = 0; // Value to be displayed
int d = 0; // Variable used for the sinewave test waveform
boolean alert = 0;
int8_t ramp = 1;
int tesmod =0;
char student_name[7][10]={"Ram","Vedant","Vipul","Jayanto","Diraj","Nihal","Ajay"};
char *Name=0;
char attendance[7]={0};
void setup() 
{
////////tft set function//////////////////////////////////////////////////////////////////
tft.reset(); //Reset LCD to begin
tft.begin(0x9341); //SDFP5408 Chipset ID on Library
tft.setRotation(0); // Set Rotation at 0 degress (default) 0=vertical 1=horizontal
border();
//////////////////////////////////////////////////////////////////////////////////////////

/////////////serial and rs305 set////////////////////////////////////////////////////////
pinMode(Button, INPUT);
Serial.begin(9600);
Serial.println("Adafruit Fingerprint sensor enrollment");
      // set the data rate for the sensor serial port
finger.begin(9600);
connect_to_sensor();
////////////////////////////////////////////////////////////////////////////////////////
delay(1000);
border();
projectname();
border();
mainwindow();
date=readdate();
mainwindow();
  tft.setCursor(10,140);
  tft.setTextColor(WHITE);
  tft.fillRect(2,130,225,30,WHITE);
  tft.setCursor(10,140);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("DATE:");
  tft.print(date);
  delay(3000);
    
}


void loop()                     // run over and over again
{
   Serial.println(digitalRead(Button));
  
  if (digitalRead(Button)==1)
        {
            while(digitalRead(Button)==1);
            
                    border();

                    tft.setCursor(5,30);
                    tft.setTextColor(BLACK);
                    tft.setTextSize(2);
                    tft.print("Please Enter");
                    tft.setCursor(5,50);
                    tft.print("Enrollment ID:-");
                    tft.setTextSize(2);

             Serial.println("Ready to enroll a fingerprint! Please Type in the ID # you want to save this finger as...");
             id = readnumber();
             Serial.print("Enrolling ID #");
             Serial.println(id);
             while (!  getFingerprintEnroll() );
             border();
             mainwindow();
             Serial.println("Enrolling Done!!!!");
                     //deleteFingerprint(123);
                     //Serial.println("id 123 deleted !!!!");
        }

getFingerprintIDez();
delay(50);            //don't ned to run this at full speed.
Serial.println("PUT FINGURE.. TO SEARCH..");  

tft.setCursor(10,140);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.fillRect(2,130,225,30,WHITE);
tft.setCursor(10,140);
tft.setTextColor(BLACK);
tft.setTextSize(1);


  }


void border(void)
{
  tft.fillScreen(WHITE); //Set Background Color with BLACK
 
  tft.drawRect(0,0,240,320,CYAN); ///for rectangle in green
  tft.drawRect(1,1,238.5,318,CYAN);
  
}

void projectname(void)
{
 tft.setCursor(85,40);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("BRACT's");

 tft.setCursor(45,65);
 tft.setTextColor(BLACK);
 tft.setTextSize(3);
 tft.print("VIT PUNE");

 tft.setCursor(67,105);
 tft.setTextColor(BLACK);
 tft.setTextSize(1);
 tft.print("ATTECDANCE REGISTER");

 tft.setCursor(80,140);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("WELCOME");

 
 tft.setCursor(28,170);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("Dr.Rambabu Vatti"); 

 delay(4000);
 

 }

 void mainwindow(void)
 {


tft.setCursor(5,55);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.fillRect(2,55,225,30,WHITE);

//while(1);
 tft.setCursor(5,30);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("Please Enter the");
 tft.setCursor(5,55);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("Date: - ");
 tft.print(date);


 tft.setCursor(40,270);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("PRESS KEY FOR");
 tft.setCursor(50,293);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print(" ENROLLMENT");
 tft.drawRect(30,262,175,53,CYAN); 
 tft.drawRect(31,263,173,51,CYAN); 

 }


 uint8_t getFingerprintEnroll() 
 {

  int p = -1;


tft.setCursor(10,140);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.fillRect(2,130,225,30,WHITE);
tft.setCursor(10,140);
tft.setTextColor(BLACK);
tft.setTextSize(1);
 
  
  Serial.println("  in getFingerprintEnroll");
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      tft.print("Image taken"); 
      delay(1000);  
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      tft.print("."); delay(1000);  
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      tft.print("Communication error"); delay(1000);  
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      tft.print("Imaging error"); delay(1000);  
      break;
    default:
      Serial.println("Unknown error");
       tft.print("Unknown error"); delay(1000);  
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
tft.setCursor(10,140);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.fillRect(2,130,225,30,WHITE);
tft.setCursor(10,140);
tft.setTextColor(BLACK);
tft.setTextSize(1);
  
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      tft.print("Image converted"); delay(1000);  
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      tft.print("Image too messy"); delay(1000);  
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
       tft.print("Communication error"); delay(1000);  
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      tft.print("Could not find fingerprint features"); delay(1000);  
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      tft.print("Could not find fingerprint features");delay(1000);   
      return p;
    default:
      Serial.println("Unknown error");
      tft.print("Unknown error"); delay(1000);  
      return p;
  }

tft.setCursor(10,140);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.fillRect(2,130,225,30,WHITE);
tft.setCursor(10,140);
tft.setTextColor(BLACK);
tft.setTextSize(1);

  Serial.println("Remove finger");
  tft.print("Remove finger");   
  delay(2000);
  tft.setCursor(10,140);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.fillRect(2,130,225,30,WHITE);
tft.setCursor(10,140);
tft.setTextColor(BLACK);
tft.setTextSize(1);

  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
   tft.print("Place same finger again"); delay(1000);  
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      tft.print("Image taken");delay(1000);  
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
       tft.print(".");delay(1000);  
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
       tft.print("Communication error");delay(1000);
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      tft.print("Imaging error");delay(1000);
      break;
    default:
      Serial.println("Unknown error");
      tft.print("Unknown error");delay(1000);
      break;
    }
  }

  // OK success!
tft.setCursor(10,140);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.fillRect(2,130,225,30,WHITE);
tft.setCursor(10,140);
tft.setTextColor(BLACK);
tft.setTextSize(1);
  
  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      tft.print("Image converted");delay(1000);
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      tft.print("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
       tft.print("Communication error");delay(1000);
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      tft.print("Could not find fingerprint features");delay(1000);
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      tft.print("Could not find fingerprint features");delay(1000);
      return p;
    default:
      Serial.println("Unknown error");
      tft.print("Unknown error");delay(1000);
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
tft.setCursor(10,140);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.fillRect(2,130,225,30,WHITE);
tft.setCursor(10,140);
tft.setTextColor(BLACK);
tft.setTextSize(1);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
    tft.print("Prints matched!");delay(1000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    tft.print("Communication error");delay(1000);
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
     tft.print("Fingerprints did not match");delay(1000);
    return p;
  } else {
    Serial.println("Unknown error");
    tft.print("Unknown error");delay(1000);
    return p;
  }   


tft.setCursor(10,140);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.fillRect(2,130,225,30,WHITE);
tft.setCursor(10,140);
tft.setTextColor(BLACK);
tft.setTextSize(1);
  
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
    tft.print("Stored!");delay(1000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    tft.print("Communication error");delay(1000);
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    tft.print("Could not store in that location");delay(1000);
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    tft.print("Error writing to flash");delay(1000);
    return p;
  } else {
    Serial.println("Unknown error");
    tft.print("Unknown error");delay(1000);
    return p;
  }   
}




uint8_t deleteFingerprint(uint8_t id) 

{
  uint8_t p = -1;
   Serial.println("  in deleteFingerprint");
  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) {
    Serial.println("Deleted!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    return p;
  }   
}



int getFingerprintIDez() 
{
uint8_t p = finger.getImage();

tft.setCursor(10,140);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.fillRect(2,130,225,30,WHITE);
tft.setCursor(10,140);
tft.setTextColor(BLACK);
tft.setTextSize(1);
  
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      tft.print("Image taken");delay(1000);
      
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      tft.print("Reday to scan");
      tft.setCursor(10,150);
      tft.print("No finger detected");delay(1000);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      tft.print("Communication error");delay(1000);
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      tft.print("Imaging error");delay(1000);
      return p;
    default:
      Serial.println("Unknown error");
      tft.print("Unknown error");delay(1000);
      return p;
  }

  // OK success!

  p = finger.image2Tz();
tft.setCursor(10,140);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.fillRect(2,130,225,30,WHITE);
tft.setCursor(10,140);
tft.setTextColor(BLACK);
tft.setTextSize(1);
  
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      tft.print("Image converted");delay(1000);
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      tft.print("Image too messy");delay(1000);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
       tft.print("Communication error");delay(1000);
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
       tft.print("Could not find fingerprint features");delay(1000);
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
       tft.print("Could not find fingerprint features");delay(1000);
      return p;
    default:
      Serial.println("Unknown error");
       tft.print("Unknown error");delay(1000);
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
tft.setCursor(10,140);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.fillRect(2,130,225,30,WHITE);
tft.setCursor(10,140);
tft.setTextColor(BLACK);
tft.setTextSize(1);
  
  if (p == FINGERPRINT_OK)
  {
    Serial.println("Found a print match!");
     tft.print("Found a print match!");delay(1000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
     tft.print("Communication error");delay(1000);
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    tft.print("Did not find a match");delay(1000);
    return p;
  } else {
    Serial.println("Unknown error");
    tft.print("Unknown error");delay(1000);
    return p;
  }   
  
  // found a match!
  tft.setCursor(10,140);
  tft.setTextColor(WHITE);
  tft.fillRect(2,130,225,30,WHITE);
  tft.setCursor(10,140);
  tft.setTextColor(BLACK);
  tft.setTextSize(1);

  Serial.print("Found ID #"); 
  Serial.print(finger.fingerID); 
  if(finger.fingerID!=0)
  {
     attendance[finger.fingerID-1]=1;
     Name=&student_name[finger.fingerID-1][0];
     Serial.print(Name); 
     tft.print(Name);
     tft.setCursor(10,160);
     tft.print("Present");
     delay(1000);
     tft.setCursor(10,160);
     tft.setTextColor(WHITE);
     tft.fillRect(2,130,225,60,WHITE);
    
     
    
   }
 
  if(finger.fingerID==0)
  {
    Serial.print("Date:");
    Serial.print(date);
    
    Serial.println(" ");
    for(int i=0;i<7;i++)
    {
      
      Name=&student_name[i][0];
      Serial.print(Name); Serial.print(":"); 
      if(attendance[i]==1)
      {
       Serial.println("Present");
      
      }
      else
      {
        Serial.println("Absent");
       }
    }
    
    display_status();
    delay(4000);
    border();
    mainwindow();
    date=readdate();
    mainwindow();
  tft.setCursor(10,140);
  tft.setTextColor(WHITE);
  tft.fillRect(2,130,225,30,WHITE);
  tft.setCursor(10,140);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("DATE:");
  tft.print(date);
  delay(3000);
  
  }

  
  //Serial.print(" with confidence of "); Serial.println(finger.confidence); 

}

uint8_t readnumber(void) 
{
  uint8_t num = 0;
  int count=0;
  boolean validnum = false; 
  while (1) {
    while (! Serial.available());
    char c = Serial.read();
    Serial.println(c);
    if (isdigit(c)) {
       num *= 10;
       num += c - '0';
       validnum = true;
    
    
    
    } 
    else if (validnum) 
    {
      if(count<10 && c!='#')
      {
      student_name[num-1][count]=c;
      count++;
      }

      
      if(c=='#'){
         student_name[num-1][count]='\0';
         return num;
      }
    }
  }
}

void connect_to_sensor(void)
{
    tft.setCursor(10,110);
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    
    
    if (finger.verifyPassword()) 
    {
    Serial.println("Found fingerprint sensor!");
    tft.print("Fingerprint Sensor");
    tft.setCursor(70,140);
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.print("Detected");
    } 
    else 
    {
    Serial.println("Did not find fingerprint sensor :(");
    tft.print("Module ERROR!!!");
    tft.setCursor(35,130);
    tft.print("PRESS RESET!!!");
    while (1);
    
    }
  
}


void display_status(void)
{
  int tft_row=5;
border();

tft.setTextColor(BLACK);
tft.setTextSize(2);

  for(int x=0;x<7;x++)
   {
     tft.setCursor(5,tft_row); 
     Name=&student_name[x][0];
     tft.print(Name);
     tft.print(":");
     if(attendance[x]==1)
      {
      // Serial.println("Present");
      tft.print("PRESENT");
      
      }
      else
      {
       //Serial.println("Absent");
       tft.print("ABSENT");
       }
     
     tft_row=tft_row+20;
 
   }
}


uint8_t readdate(void) 
{
  uint8_t num = 0;
  int count=0;

  boolean validnum = false; 
    date=0; 
  tft.setCursor(10,140);
  tft.setTextColor(WHITE);
  tft.fillRect(2,130,225,30,WHITE);
  tft.setCursor(10,140);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("Waiting for DATE");
  while (1) {
    while (! Serial.available());
    char c = Serial.read();
    Serial.println(c);
    if (isdigit(c)) {
       num *= 10;
       num += c - '0';
       validnum = true;
     } 
    else if (validnum) 
    {
      if(c=='#'){
         for(int i=0;i<7;i++) {
         attendance[i]=0; }
         return num;
      }
    }
  }
}



