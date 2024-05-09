/*│   Character  │  Default  │ Arduino  │*/
/*│      └      │    45     │    C0    │*/
/*│      ┌      │    46     │    DA    │*/
/*│       ┐     │    47     │    BF    │*/
/*│       ┘     │    48     │    D9    │*/
/*│       █     │    49     │    DB    │*/
/*│       │     │    4A     │    B3    │*/
/*│       ─     │    4B     │    C4    │*/
/*│       ┫      │    4C     │    B4    │*/
/*│       ┣      │    4D     │    C3    │*/
/*│       ┰      │    4E     │    C2    │*/
/*│       ┸      │    4F     │    C1    │*/


char symbolCheck(char charIn, bool enSym)
{
  char charOut;
  if      (charIn == 0x45 && enSym == HIGH) charOut = 0xC0;
  else if (charIn == 0x46 && enSym == HIGH) charOut = 0xDA;
  else if (charIn == 0x47 && enSym == HIGH) charOut = 0xBF;
  else if (charIn == 0x48 && enSym == HIGH) charOut = 0xD9;
  else if (charIn == 0x49 && enSym == HIGH) charOut = 0xDB;
  else if (charIn == 0x4A && enSym == HIGH) charOut = 0xB3;
  else if (charIn == 0x4B && enSym == HIGH) charOut = 0xC4;
  else if (charIn == 0x4C && enSym == HIGH) charOut = 0xB4;
  else if (charIn == 0x4D && enSym == HIGH) charOut = 0xC3;
  else if (charIn == 0x4E && enSym == HIGH) charOut = 0xC2;
  else if (charIn == 0x4F && enSym == HIGH) charOut = 0xC1;
  else charOut = charIn;

  return charOut;
}
