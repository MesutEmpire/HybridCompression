# HybridCompression

A simple hybrid compression algorithm for Arduino, designed to compress environmental sensor data (temperature, humidity, etc.) for efficient transmission.

## Features

- Delta-based compression
- Compatible with float-to-int conversion
- Easy decompression on the server (e.g., Node.js)

## Example

```cpp
#include <HybridCompression.h>

void setup() {
  Serial.begin(9600);

  HybridCompression hc;
  int readings[] = {1000, 1002, 1004, 1006};  // Example data
  int compressed[10];
  int len;

  hc.compressMetric(readings, 4, compressed, len);
  hc.printIntArray("Compressed", compressed, len);
}
