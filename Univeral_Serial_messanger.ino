bool collectingMessage = false;
bool collectingValue = false;
String serialMessage = "";
String serialValue = "";

void setup() {
  Serial.begin(115200);
  

}

void loop() {
  checkRemote();
}


