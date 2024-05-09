//01. MAIN COMMAND *********************************************************************
/*-------------------------------------------------------------*/
/*| Header      |                  Function                   |*/
/*-------------------------------------------------------------*/
/*| 1B 22       | Enable Keypad Input                         |*/
/*| 1B 23       | Disable Keypad Input                        |*/
/*| 1B 24       | Draw text in box drawing mode               |*/
/*| 1B 25       | Draw text in ASCII mode                     |*/
/*| 1B 3D       | Address header ( 1B 3D XX XX ...data...)    |*/
/*| 1B 3F       | Feed Back Posisi Kursor                     |*/
/*| 1B 54       | Add space from X = 0x22 to 0x4B             |*/
/*| 1B 59       | Clear Screen                                |*/
/*| 1B 2E       | Enable Cursor                               |*/
/*| 1B 47       | Enable Text Style                           |*/
/*-------------------------------------------------------------*/
char readMainCommand(char machineData)
{
  switch (machineData)
  {
    case 0x22:
      cmd.keypadEn = HIGH;
      break;

    case 0x23:
      cmd.keypadEn = LOW;
      break;

    case 0x24: // Box Drawing mode enable
      cmd.symbolEn  = HIGH;
      break;

    case 0x25: // Ascii mode enable
      cmd.symbolEn  = LOW;
      break;

    case 0x3D: // Read Address Command
      cmd.addressEn = HIGH;
      break;

    case 0x3F: // Send feedback cursor position
      Serial3.write(addressData.yHex);
      Serial3.write(addressData.xHex + nGui);
      break;

    case 0x54: // Add Space
      generateSpaceData(addressData);
      break;

    case 0x59: // Clear Screen
      VGA.clear();
      VGA.setPrintWindow(0, 1, 80, 47);
      clearMatrix();
      generateFrameWindow();
      footer();
      break;

    case 0x2E: // Enable Cursor
      cmd.cursorWait = HIGH;
      break;

    case 0x47:
      cmd.styleWait = HIGH;
      break;

    default:
      break;
  }
}

//02. STYLE ****************************************************************************
/*----------------------------------------------------*/
/* 1B 47 30    | Disable text hightlight & blinking   */
/* 1B 47 32    | Enable text blinking                 */
/* 1B 47 34    | Enable text highlight                */
/*----------------------------------------------------*/
void characterStyle (char machineData)
{
  switch (machineData)
  {
    case 0x30:
      VGA.setInk(1);
      cursorBarOn = LOW;
      cmd.blinkEn = LOW;
      break;

    case 0x32:
      cmd.blinkEn = HIGH;
      break;

    case 0x34:
      VGA.setInk(0);
      cursorBarOn = LOW;
      break;

    default:
      break;
  }
}


//03. CURSOR ************************************************************
/*---------------------------*/
/* 1B 2E 30    | Hide cursor */
/* 1B 2E 31    | Show cursor */
/*---------------------------*/
int cursorDetect(char machineData)
{
  switch (machineData)
  {
    case 0x30:
      cmd.cursorEn = LOW;
      break;

    case 0x31:
      cmd.cursorEn = HIGH;
      break;

    default:
      break;
  }
}
