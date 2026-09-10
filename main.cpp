#include <Arduino.h>

// Environmental telemetry data
struct environment_data
{
  float temp;
  float pressure;
  float humidity;
  float o2_conc;
  float co2_conc;
  float n2_conc;
  float air_quality;
  float airflow;
  float cabin_leakage;
  float radiation;
  float smoke;
  float dust;
  float water_vapor;
  float fan_speed;
  float scrubber_efficiency;
};


// Binary telemetry packet
typedef struct __attribute__((packed))
{
  uint8_t header;
  uint8_t type;
  uint8_t length;
  uint8_t payload[60];
} Environment_Packet_t;

Environment_Packet_t message;


// Initial environmental conditions
environment_data packet = {
    22.5,   // temperature
    101.3,  // pressure
    45.0,   // humidity
    20.8,   // O2 concentration
    700.0,  // CO2 concentration
    78.1,   // N2 concentration
    95.0,   // air quality
    0.4,    // airflow
    0.03,   // cabin leakage
    0.18,   // radiation
    0.0,    // smoke
    12.0,   // dust
    1.1,    // water vapor
    1500.0, // fan speed
    97.0    // scrubber efficiency
};


void create_variation(environment_data &packet);
void serialize_reading(float data, int offset);
void process_packet(environment_data &packet);


void setup()
{
  Serial.begin(9600);

  // Initialize packet header
  message.header = 0xAA;
  message.type = 0x01;
  message.length = 0x3C;
}


void loop()
{
  // Convert environmental data into the binary payload
  process_packet(packet);

  // Transmit the complete packet over UART
  Serial.write((uint8_t*)&message, sizeof(message));

  // Simulate changing environmental conditions
  create_variation(packet);

  delay(2000);
}


void create_variation(environment_data &packet)
{
  packet.temp += random(-2, 6) * 0.1;
  packet.pressure += random(-3, 4) * 0.1;
  packet.humidity += random(-5, 6) * 0.1;
  packet.o2_conc += random(-5, 6) * 0.01;
  packet.co2_conc += random(-20, 21);
  packet.n2_conc += random(-5, 6) * 0.01;
  packet.air_quality += random(-3, 4) * 0.1;
  packet.airflow += random(-5, 6) * 0.01;
  packet.cabin_leakage += random(-2, 3) * 0.001;
  packet.radiation += random(-2, 3) * 0.01;
  packet.smoke += random(-1, 2) * 0.1;
  packet.dust += random(-2, 3) * 0.1;
  packet.water_vapor += random(-5, 6) * 0.01;
  packet.fan_speed += random(-20, 21);
  packet.scrubber_efficiency += random(-2, 3) * 0.1;
}


// Copy a float's raw bytes into the packet payload
void serialize_reading(float data, int offset)
{
  memcpy(&message.payload[offset * 4], &data, 4);
}


// Serialize all environmental readings
void process_packet(environment_data &packet)
{
  serialize_reading(packet.temp, 0);
  serialize_reading(packet.pressure, 1);
  serialize_reading(packet.humidity, 2);
  serialize_reading(packet.o2_conc, 3);
  serialize_reading(packet.co2_conc, 4);
  serialize_reading(packet.n2_conc, 5);
  serialize_reading(packet.air_quality, 6);
  serialize_reading(packet.airflow, 7);
  serialize_reading(packet.cabin_leakage, 8);
  serialize_reading(packet.radiation, 9);
  serialize_reading(packet.smoke, 10);
  serialize_reading(packet.dust, 11);
  serialize_reading(packet.water_vapor, 12);
  serialize_reading(packet.fan_speed, 13);
  serialize_reading(packet.scrubber_efficiency, 14);
}
