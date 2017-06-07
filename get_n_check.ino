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
      collectingMessage = false;
      collectingValue = true;

    }

    // % is used to indicate the end of a message
    else if (incomingChar == '%')
    {
      collectingMessage = false;
      collectingValue = false;
      // Here you can use the message
      Serial.println(serialMessage);
      Serial.println(serialValue);
      delay(100);
      serialMessage = "";
      serialValue = "";

    }

    else
    {
      // If # is recieved, start reading message
      if (collectingMessage == true && collectingValue == false)
      {
        serialMessage = serialMessage + incomingChar;
      }
      else if (collectingValue == true && collectingMessage == false) {
        serialValue = serialValue + incomingChar;
      }
      else {
        Serial.println("error mate");
      }
    }
  }
}
char getChar()
{
  int readByte = Serial.read();
  char readChar = (char)readByte;
  return readChar;
}

