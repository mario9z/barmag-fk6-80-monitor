void displayOutput(char data)
{
  char encChar = symbolCheck(data, cmd.symbolEn);
  int x = addressData.xDec + nGui;
  int y = addressData.yDec;
 
  if (cmd.blinkEn)
  {
     blinkData[y][x] = encChar;
  }
  else
  {
     blinkData[y][x] = 0x00;
     cursorData[y][x] = encChar;
     VGA.moveCursor(x,y);
     VGA.write(encChar);
  }
  nGui++;
}
