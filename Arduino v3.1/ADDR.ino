int addressRead(char data)
{
  addressData.yHex = addressData.xHex;
  addressData.xHex = data;
  dataAddrCount++;

  if (dataAddrCount > 1)
  {
    dataAddrCount = 0;
    cmd.addressEn = LOW;
    addressData.xDec = addressData.xHex - 0x20;
    addressData.yDec = (addressData.yHex - 0x20)*2;
    nGui = 0;
  }
}
