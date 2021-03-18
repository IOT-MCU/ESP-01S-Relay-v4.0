// Modified by Tiago Prata (31-Jan-2021)
// https://github.com/TiagoPrata
// This software is distributed AS IS and there is no warranty

#include <ESP8266WiFi.h>
 
const char* ssid = "wifi-ssid"; // fill in here your router or wifi SSID
const char* password = "wifi-pass"; // fill in here your router or wifi password
#define RELAY 0           // relay connected to  GPIO0
#define PULSE_DELAY 500   // pulse delay in miliseconds
WiFiServer server(80);

// Set your Static IP address
IPAddress local_IP(10, 0, 0, 80);
// Set your Gateway IP address
IPAddress gateway(10, 0, 0, 2);

IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional
 
void setup() 
{
  Serial.begin(115200); // must be same baudrate with the Serial Monitor
 
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WiFi.mode(WIFI_STA);
  pinMode(RELAY,OUTPUT);
  digitalWrite(RELAY, HIGH);

  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
 
}
 
void loop() 
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) 
  {
    return;
  }
 
  // Wait until the client sends some data
  delay(50);
  Serial.println("new client");
  while(!client.available())
  {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
  int value = LOW;
  if (request.indexOf("/RELAY=ON") != -1)  
  {
    Serial.println("RELAY=ON");
    digitalWrite(RELAY,LOW);
    value = LOW;
  }
  if (request.indexOf("/RELAY=OFF") != -1)  
  {
    Serial.println("RELAY=OFF");
    digitalWrite(RELAY,HIGH);
    value = HIGH;
  }
  if (request.indexOf("/RELAY=PULSE") != -1)  
  {
    Serial.println("RELAY=PULSE");
    digitalWrite(RELAY,LOW);
    value = LOW;
    delay(PULSE_DELAY);
    digitalWrite(RELAY,HIGH);
    value = HIGH;
    // Redirect to home page
    client.println("<!DOCTYPE html>");
    client.println("<html>");
    client.println("<head>");
    client.println("    <meta charset=\"utf-8\"/>");
    client.println("    <title>Redirecting</title>");
    client.println("");
    client.println("    <meta http-equiv=\"refresh\" content=\"0; URL='/'\"/>");
    client.println("</head>");
    client.println("<body>");
    client.println("</body>");
    client.println("</html>");
    delay(1);
    return;
  }
  
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  this is a must
  client.println("<!DOCTYPE html>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>Relay control</title>");
  client.println("<style>");
  client.println(".button {");
  client.println("  background-color: #4CAF50; /* Green */");
  client.println("  border: none;");
  client.println("  color: white;");
  client.println("  padding: 15px 32px;");
  client.println("  text-align: center;");
  client.println("  text-decoration: none;");
  client.println("  display: inline-block;");
  client.println("  font-size: 90px;");
  client.println("  margin: 4px 2px;");
  client.println("  cursor: pointer;");
  client.println("  width: 100%;");
  client.println("  height: 200px;");
  client.println("}");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("<form action=\"/RELAY=ON\">");
  client.println("  <button class=\"button\">Relay ON</button>");
  client.println("</form>");
  client.println("<form action=\"/RELAY=OFF\">");
  client.println("  <button class=\"button\">Relay OFF</button>");
  client.println("</form>");
  client.println("<form action=\"/RELAY=PULSE\">");
  client.println("  <button class=\"button\">Pulse relay</button>");
  client.println("</form>");
  client.println("</body>");
  client.println("</html>");

 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
