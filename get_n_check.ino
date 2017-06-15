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
    // : is used to indicate the start of a new value
    else if (incomingChar == ':')
    {
      // starts reading a new value
      if (currentSerialValueIndex >= (serialValueSize - 1)) {
        Serial.println("Error: too many values, pleas increas the array size of serialValue ");
        Serial.println("all other values will be ignored");
        endMessage();
      }
      else {
        currentSerialValueIndex += 1;
      }
      collectingMessage = false;
      collectingValue = true;
    }

    // % is used to indicate the end of a message
    else if (incomingChar == '%')
    {
      endMessage();
    }
    // If # is recieved, start reading message
    else if (collectingMessage == true && collectingValue == false) {
      serialMessage = serialMessage + incomingChar;
    }
    else if (collectingValue == true && collectingMessage == false) {
      // if one of the incoming chars is not an digit the hole value is not an int
      if (!isdigit(incomingChar) && valueIsInt[currentSerialValueIndex] == true) {
        valueIsInt[currentSerialValueIndex] = false;
      }
      serialValue[currentSerialValueIndex] = serialValue[currentSerialValueIndex] + incomingChar;
    }
    //      else {
    //        Serial.println("Error, invalid massage");
    //      }
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
  printMessage();
  delay(100); // small delay to reduce glitch/bug chance can be ajusted to your needs
  // Reset the vars
  resetVars();
}

void resetVars() {
  // sets all the indexes to true (messages are an int until proven not to be)
  for (int currIndex = 0; currIndex < (serialValueSize + 1); ++currIndex) {
    valueIsInt[currIndex] = true;
  }
  // resets all the values
  for (int currIndex = 0; currIndex < (currentSerialValueIndex + 1); ++currIndex) {
    serialValue[currIndex] = "";
  }
  collectingMessage = false;
  collectingValue = false;
  serialMessage = "";
  currentSerialValueIndex = -1;
}






// uese values

void printMessage() {
  //prints the serialMessage
  Serial.println(serialMessage);
  // loops all used values and checks if its marked as an int, if so print it as an int, ofcourse you can use this for more usefull stuff.
  for (int currIndex = 0; currIndex < (currentSerialValueIndex + 1); ++currIndex) {
    if (valueIsInt[currIndex]) {
      Serial.print(serialValue[currIndex].toInt());
      Serial.println("  is a int!");
    }
    else {
      Serial.println(serialValue[currIndex]);
    }
  }
}
