#include <ESP8266WiFi.h>

const char* ssid = "TP-Link_0C74";                  // Your wifi Name
const char* password = "79054768"; // Your wifi Password

const char * host = "192.168.0.108";        // IP Server

const int httpPort = 5000;

const char* Commands;                       // The command variable that is sent to the server
int T = 0;
int Z = 0;
int con = 0;                                // Variables for mode

int command = 0;
String line = "";
String CHECK = "";
String ACCIDENT = "";
String HOSPITAL = "";
String LIGHT = "";
String TRAFFIC = "";

String send_commands() {    // Modified to return the response

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return "";
  }

  // This will send the request to the server
  client.print(String("GET ") + Commands + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: Close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return "";
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    line = client.readStringUntil('\r');
  }
  line.trim();
  //    Serial.print("response: ");
  //    Serial.println(line);

  return line;   // Return the response

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);                     // initialize serial:

  Serial.println("");
  Serial.println("Client-------------------------------");
  Serial.print("Connecting to Network");
  WiFi.mode(WIFI_STA);                      // Mode Station
  WiFi.begin(ssid, password);               // Matching the SSID and Password
  delay(1000);

  // Waiting to connect to wifi
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("Successfully Connecting");
  Serial.println("Status : Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("-------------------------------------");
  Serial.println("");
}

void loop() {

  if (T == 0) {
    Commands = "/CHECK/XXXXX";
    CHECK = send_commands();


    Commands = "/ACCIDENT/XXXXX";
    ACCIDENT = send_commands();


    Commands = "/HOSPITAL/XXXXX";
    HOSPITAL = send_commands();



    Commands = "/TRAFFIC/XXXXX";
    TRAFFIC = send_commands();
    delay(500);
    Serial.print(ACCIDENT);
    Serial.print("_");
    Serial.print(HOSPITAL);
    Serial.print("_");
    Serial.print(TRAFFIC);
    T = 1;
  }
  if (Z == 0) {
    if (Serial.available() > 0) {                // Check if there is data from the Arduino
      command = Serial.read();    // Read the command from Arduino
      if (command == '6') {
        Commands = "/LIGHT/XXXXX";
        LIGHT = send_commands();
        if (LIGHT == "RED") {
          Commands = "/GREEN/XXXXX";
          LIGHT = send_commands();
        }
        Z = 1;
      }
    }
  }

}
