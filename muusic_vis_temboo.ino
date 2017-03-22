#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information, as described below

int calls = 1;   // Execution count, so this doesn't run forever
int maxCalls = 10;   // Maximum number of times the Choreo should be executed
int led = 4;
int threshold = 300; //Change This
int volume;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT); 
  
  // For debugging, wait until the serial console is connected
  delay(4000);
  while(!Serial);
  Bridge.begin();
}

void loop() {
  volume = analogRead(A1); // Reads the value from the Analog PIN A1
  
  Serial.print("led value is");
  Serial.println(led);

  Serial.print("volume is");
  Serial.println(volume);
  
  
  
 
  /*
    //Debug mode
    Serial.println(volume);
    delay(100);
  */
  
  if(volume>=threshold){
    digitalWrite(led, HIGH); //Turn ON Led
  }  
  else{
    digitalWrite(led, LOW); // Turn OFF Led
  }

  delay (100);
  
  if (calls <= maxCalls) {
    Serial.println("Running AppendValues - Run #" + String(calls++));
    
    TembooChoreo AppendValuesChoreo;

    // Invoke the Temboo client
    AppendValuesChoreo.begin();

    // Set Temboo account credentials
    AppendValuesChoreo.setAccountName(TEMBOO_ACCOUNT);
    AppendValuesChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    AppendValuesChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // Set Choreo inputs
    AppendValuesChoreo.addInput("RefreshToken", "1/OLHWIefOjtz1h_QEL2Y9ndoJy-UNGhTRD8_PvrppftY");
    AppendValuesChoreo.addInput("ClientSecret", "kQhz4hSVJPEvsO8cq1wnjFVO");
    AppendValuesChoreo.addInput("Values", "[\n  [\n    \"sound on\",\n    \"sound on",\n    \"sound on"\n  ]\n]");
    AppendValuesChoreo.addInput("ClientID", "138450201694-fsq6b4a9i0c61uqqrmli2a7iebliemhk.apps.googleusercontent.com");
    AppendValuesChoreo.addInput("SpreadsheetID", "195t8JD-AHYBgehPLH9RUpIAU6T6ZlI1ETcGe_5686wg");
    
    // Identify the Choreo to run
    AppendValuesChoreo.setChoreo("/Library/Google/Sheets/AppendValues");
    
    // Run the Choreo; when results are available, print them to serial
    AppendValuesChoreo.run();
    
    while(AppendValuesChoreo.available()) {
      char c = AppendValuesChoreo.read();
      Serial.print(c);
    }
    AppendValuesChoreo.close();
  }

  Serial.println("Waiting...");
  delay(30000); // wait 30 seconds between AppendValues calls
}
