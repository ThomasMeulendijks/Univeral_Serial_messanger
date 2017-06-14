void checkRemote()
{
  if (Serial.available() > 0)
  {

    char incomingChar = getChar();
    // # is used to indicate the start of a message
    if (incomingChar == '#')
    {
      collectingMessage = true;
      collectingValue = false;

    }
    else if (incomingChar == ':')
    {
      // starts reading a new value
      if (collectingValue == true) {
        if (currentSerialValueIndex >= (serialValueSize - 1)) {
          Serial.println("Error: too many values, pleas increas the array size of serialValue ");
          Serial.println("all other values will be ignored");
          endMessage();
        }
        else {
          currentSerialValueIndex += 1;
        }
      }
      else {
        collectingMessage = false;
        collectingValue = true;
      }

    }

    // % is used to indicate the end of a message
    else if (incomingChar == '%')
    {
      endMessage();
    }

    else
    {
      // If # is recieved, start reading message
      if (collectingMessage == true && collectingValue == false)
      {
        serialMessage = serialMessage + incomingChar;
      }
      else if (collectingValue == true && collectingMessage == false) {
        serialValue[currentSerialValueIndex] = serialValue[currentSerialValueIndex] + incomingChar;
      }
      //      else {
      //        Serial.println("Error, invalid massage");
      //      }
    }
  }
}
char getChar()
{
  int readByte = Serial.read();
  char readChar = (char)readByte;
  return readChar;
}
void  endMessage() {

  // Here you can use the message
  Serial.println(serialMessage);
  for (int currIndex = 0; currIndex < (currentSerialValueIndex + 1); ++currIndex) {
    Serial.println(serialValue[currIndex]);
  }
  
  delay(100); // small delay to reduce glitch/bug chance can be ajusted to your needs

  // Reset the vars
  collectingMessage = false;
  collectingValue = false;
  serialMessage = "";
  for (int currIndex = 0; currIndex < (currentSerialValueIndex + 1); ++currIndex) {
    serialValue[currIndex] = "";;
  }
  currentSerialValueIndex = 0;
}

