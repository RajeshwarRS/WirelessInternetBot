#include <SPI.h>

#undef PIN_SPI_MISO
#undef PIN_SPI_MOSI
#undef PIN_SPI_SCK
#undef PIN_SPI_SS
// Define SPI pins for NodeMCU (ESP8266)
#define PIN_SPI_MISO  12  // Master In Slave Out (D6)
#define PIN_SPI_MOSI  13  // Master Out Slave In (D7)
#define PIN_SPI_SCK   14  // Clock (D5)
#define PIN_SPI_SS    4   // Chip Select (D2)

byte transferSPI(byte data) {
  byte receivedData = 0;

  for (int i = 7; i >= 0; i--) {
    // Set MOSI line to send data
    digitalWrite(PIN_SPI_MOSI, (data >> i) & 0x01);
    
    // Generate clock pulse
    digitalWrite(PIN_SPI_SCK, HIGH);
    delayMicroseconds(10);  // Small delay for stability
    
    // Read MISO line to receive data
    if (digitalRead(PIN_SPI_MISO)) {
      receivedData |= (1 << i);
    }
    
    digitalWrite(PIN_SPI_SCK, LOW);
    delayMicroseconds(10);  // Small delay for stability
  }
  
  return receivedData;
}

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_SPI_MISO, INPUT);
  pinMode(PIN_SPI_MOSI, OUTPUT);
  pinMode(PIN_SPI_SCK, OUTPUT);
  pinMode(PIN_SPI_SS, OUTPUT);
  digitalWrite(PIN_SPI_SS, LOW); // Enable slave (for loopback test)
  
  Serial.println("SPI Loopback Test: D6 (MISO) <--> D7 (MOSI)");
}

void loop() {
  byte dataToSend = 0xA5;  // Example test byte
  byte receivedData = transferSPI(dataToSend);
  
  Serial.print("Sent Data: 0x");
  Serial.print(dataToSend, HEX);
  Serial.print(" | Received Data: 0x");
  Serial.println(receivedData, HEX);
  
  delay(1000);
}
