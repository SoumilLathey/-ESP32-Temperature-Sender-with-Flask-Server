#include <WiFi.h>
#include <HTTPClient.h>

// ==========================
// 🔑 WiFi Credentials
// ==========================
// ⚠️ Replace with your own WiFi SSID and Password
// Do not commit real credentials to GitHub!
const char* ssid = "YOUR_WIFI_SSID";      
const char* password = "YOUR_WIFI_PASSWORD";  

// ==========================
// 🌐 Flask Server Endpoint
// ==========================
// Change IP to the one shown by your computer running Flask
// Example: http://<your_local_IP>:5000/LWT/temprature
String serverName = "http://192.168.29.43:5000/LWT/temprature";

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ Connected to WiFi");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP()); // Print IP for debugging
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Connect to Flask server
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    // Generate random temperature (replace with real sensor reading later)
    float temp = random(25, 33);  

    // Create JSON payload
    String jsonData = "{\"temp\":" + String(temp) + "}";

    // Send POST request
    int httpResponseCode = http.POST(jsonData);

    // Handle server response
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("📩 Server response: " + response);
    } else {
      Serial.println("❌ Error: " + String(httpResponseCode));
    }

    http.end();
  } else {
    Serial.println("⚠️ WiFi Disconnected");
  }

  delay(5000); // Send data every 5 seconds
}
