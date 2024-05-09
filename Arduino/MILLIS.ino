void fnBeep()
{
  if (enableBeep == HIGH)
  {
    digitalWrite(beepPin, HIGH);

    if (millis() - milBeepPre >= 25)
    {
      enableBeep = LOW;
      digitalWrite(beepPin, LOW);
    }
  }
  else {
    milBeepPre = millis();
  }
}

void cursorBeat()
{
  if (millis() - cursorTime >= 300)
  {
    cursorTime = millis();
    //Serial.println(activeData);
    if (cursorBarOn)
      cursorBarOn = LOW;
    else
      cursorBarOn = HIGH;

    displayCursor();
  }
}

void blinkTextBeat()
{
  milBlinkNow = millis();
  if (milBlinkNow - milBlinkPre >= 500)
  {
    milBlinkPre = milBlinkNow;
    indexBlinkY = 0;
    if (blinkBeat)
      blinkBeat = LOW;
    else
      blinkBeat = HIGH;
  }
}

void logoTimer()
{
  if (millis() - logoTime > 20000 && firstBoot == HIGH)
  {
    firstBoot = LOW;
    VGA.clear();
  }
}

void runTimeCounter()
{
  currentTime = millis();

  if (currentTime - previousTime > 3600000)
  {
    previousTime = currentTime;
    runTime++;
  }
}
