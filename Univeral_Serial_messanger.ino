// two bools that track what we are collecting
bool collectingMessage;
bool collectingValue;

String serialMessage; // often used as a command
String serialValue[serialValueSize]; // often used as params of the command (can contain ints(short I think))

const int serialValueSize = 10; // Pleas ajust the leaght of the array to suit your needs

bool valueIsInt[serialValueSize]; // used to trak if a value is a int

int currentSerialValueIndex; // the index of the value we are currently collecting


void setup() {
  Serial.begin(115200);

  //sets all the values
  resetVars();

}

void loop() {
  checkRemote();
}


// Foot note, I kept all the code in two tabs to make it easly exportable and inportable.
// If you are using this in a bigger project I whould advice to make a "SerialGetter" , "SerialChecker" and a tab whre you use the values.
