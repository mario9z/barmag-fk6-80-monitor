void displayCursor()
{
  if (cursorBarOn == HIGH && cmd.cursorEn == HIGH)
  {
    activeX = addressData.xDec;
    activeY = addressData.yDec;
    activeData = cursorData[activeY][activeX];

    if (activeData == 0x00)
      activeData = 0x20;

    VGA.moveCursor(activeX, activeY);
    VGA.setInk(0);
    VGA.write(activeData);
    VGA.setInk(1);
  }

  if (cursorBarOn == LOW && cmd.cursorEn == HIGH)
  {
    if (oldX != activeX || oldY != activeY)
    {
      VGA.moveCursor(oldX, oldY);
      VGA.write(cursorData[oldY][oldX]);
      oldX = activeX;
      oldY = activeY;
    }
    VGA.moveCursor(activeX, activeY);
    VGA.write(cursorData[activeY][activeX]);
  }
}
