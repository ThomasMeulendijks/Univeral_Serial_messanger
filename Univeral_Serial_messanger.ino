bool collectingMessage = false;
bool collectingValue = false;
String serialMessage = "";
const int serialValueSize = 10; // Pleas ajust the leaght of the array to suit your needs
String serialValue[serialValueSize]; 
int currentSerialValueIndex = 0;

void setup() {
  Serial.begin(115200);
  

}

void loop() {
  checkRemote();
}


