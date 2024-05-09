// A. Libraries ==================================================================================
#include <VGA.h>
#include <Queue.h>
#include <Keypad.h>

// STRUCT ========================================================================================
struct addr {
  char yHex;
  char xHex;
  int  yDec;
  int  xDec;
};
struct addr addressData;

struct serialCommand {
  bool addressEn;
  bool keypadEn;
  bool symbolEn;
  bool styleWait;
  bool highlightEn;
  bool blinkEn;
  bool cursorWait;
  bool cursorEn;
};
struct serialCommand cmd;

struct characterProperties {
  int x;
  int y;
  char data;
  bool highlightEn;
  bool blinkEn;
};
// B. Global Variables ===========================================================================
// Constant---------------------------------------------------------------------------------------
const int vgaWidth  = 640; // 80 columns
const int vgaHeight = 400; // 50 rows


const int ledPin =  13;
const int beepPin = 11;

const byte ROWS = 6;
const byte COLS = 4;

// Queue------------------------------------------------------------------------------------------
Queue<char> queueData = Queue<char>(100);

// Integer
int nGui;
int dataAddrCount = 0;
int indexBlinkX, indexBlinkY;
int oldX, oldY;
int activeX, activeY;

// CHAR-------------------------------------------------------------------------------------------
char bufferData;
char blinkData[48][80];
char cursorData[48][80];
char activeData;


// BOOL-------------------------------------------------------------------------------------------
bool enableReadCommand    = LOW;
bool enableBeep;
bool blinkBeat;
bool tagFooter            = LOW;
bool cursorBarOn;
bool setWait;
bool firstBoot;

// LONG-----------------------------------------------------------------------------------------
unsigned long milBeepPre = 0;
unsigned long milBlinkPre = 0;
unsigned long milBlinkNow = 0;
unsigned long cursorTime = 0;
unsigned long timerClearFooter = 0;
unsigned long currentMillis;
unsigned long logoTime = 0;
volatile unsigned long runTime;
unsigned long currentTime, previousTime; 

/* KEYPAD -----------------------------------------------------------------------------------------*/
byte rowPins[ROWS] = {27, 26, 29, 28, 31, 30};
byte colPins[COLS] = {23, 22, 25, 24};
char barmagKey;

char hexaKeys[ROWS][COLS] = {
  {'7', '8', '9', 0x0B},
  {'4', '5', '6', 0x08},
  {'1', '2', '3', 0x0C},
  {'-', '0', '.', 0x16},
  {'A', 'B', 'C', 0x7F},
  {'D', 'E', 'F', 0x0D},
};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void keypadRead() {
  barmagKey = customKeypad.getKey();

  if (barmagKey && cmd.keypadEn) {
    Serial3.write(barmagKey);
    enableBeep = HIGH;
    if (firstBoot == HIGH)
    {
      firstBoot = LOW;
      VGA.clear();
    }
  }
}


//================================================================================================
void setup()
{
  VGA.begin(vgaWidth, vgaHeight);
  VGA.setPrintWindow(0, 1, 80, 47);
  Serial3.begin(9600);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(beepPin, OUTPUT);
  addressData.xHex = 0x20;
  addressData.yHex = 0x20;
  syncLogo();
  firstBoot = HIGH;
  logoTime = millis();
  cmd.keypadEn = HIGH;
}


void loop()
{
  while (1) {
    /*-------------------------------------MAIN PROGRAM-------------------------------------------*/
    /*00.Runtime Counter -------------------------------------------------------------------------*/
    runTimeCounter();
    
    /*01.Keypad-----------------------------------------------------------------------------------*/
    keypadRead();

    /*02.Beep-------------------------------------------------------------------------------------*/
    fnBeep();

    /*03.Blinking Text----------------------------------------------------------------------------*/
    blinkTextBeat();
    blinkingText();

    /*04.Display Cursor --------------------------------------------------------------------------*/
    cursorBeat();
    //displayCursor();

    /*05.Footer ----------------------------------------------------------------------------------*/
    clearFooter();
    logoTimer();

    /*06.Reset Variables if millis() reinitialize ------------------------------------------------*/
    currentMillis = millis();
    if (currentMillis < 10) {
      milBeepPre = currentMillis;
      milBlinkPre = currentMillis;
      milBlinkNow = currentMillis;
      cursorTime = currentMillis;
      timerClearFooter = currentMillis;
      currentTime = currentMillis;
      previousTime = currentMillis;
    }

    /*07.Serial Data Input Queue -----------------------------------------------------------------*/
    while (Serial3.available() > 0)
    {
      queueData.push(Serial3.read());
    }

    /*08.Unpack Data -----------------------------------------------------------------------------*/
    if (queueData.count() > 0 && firstBoot == LOW)
    {
      bufferData = queueData.pop();
      //Serial.write(bufferData);

      if (bufferData == 0x1B)
      {
        enableReadCommand = HIGH;
        goto endLoop;
      }


      if (enableReadCommand)
      {
        enableReadCommand = LOW;
        readMainCommand(bufferData);
        goto endLoop;
      }


      if (cmd.addressEn)
      {
        addressRead(bufferData);
        goto endLoop;
      }

      if (cmd.styleWait)
      {
        cmd.styleWait = LOW;
        characterStyle(bufferData);
        goto endLoop;
      }

      if (cmd.cursorWait)
      {
        cmd.cursorWait = LOW;
        cursorDetect(bufferData);
        goto endLoop;
      }

      displayOutput(bufferData);

endLoop:
      digitalWrite(ledPin, HIGH);
    }
    else
    {
      digitalWrite(ledPin, LOW);
    }
  }
}
