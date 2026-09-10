# Habitat Telemetry Emulator

Arduino UNO-based environmental telemetry emulator for a modular space-habitat monitoring system.

It simulates environmental conditions such as temperature, pressure, humidity, gas concentrations, air quality, and radiation. The readings are serialized into a binary telemetry packet and transmitted over UART to a central controller.

## Packet Format

```text
HEADER | TYPE | LENGTH | PAYLOAD
  1B   |  1B  |   1B   |   60B
```

The 60-byte payload contains 15 environmental readings, each represented as a 32-bit float.

## Future Updates

* CRC-based packet integrity checking
* Telemetry packet validation and fault detection
* Simulating system anomalies :
    * Pressure loss
    * Temperature spikes
    * CO2 level increase
    * etc.
