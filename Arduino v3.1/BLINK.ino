void matrixBlink(struct addr addressL, char data, int index)
{
  int x = addressL.xDec + index;
  int y = addressL.yDec;
  blinkData[y][x] = data;
}

void blinkingText()
{
  if (indexBlinkY < 47)
  {
    if (blinkBeat && blinkData[indexBlinkY][indexBlinkX] != 0x00 )
    {
      VGA.moveCursor(indexBlinkX, indexBlinkY);
      VGA.write(blinkData[indexBlinkY][indexBlinkX]);
    }
    else if (blinkData[indexBlinkY][indexBlinkX] != 0x00)
    {
      VGA.moveCursor(indexBlinkX, indexBlinkY);
      VGA.write(0x00);
    }

    indexBlinkX++;
    if (indexBlinkX >= 80)
    {
      indexBlinkX = 0;
      indexBlinkY++;
    }
  }
}
