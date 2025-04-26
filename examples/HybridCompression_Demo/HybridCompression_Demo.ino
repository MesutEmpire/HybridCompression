#include <HybridCompression.h>

HybridCompression hc;

// Example raw data
int rawData[] = { 1000, 1002, 1004, 1008, 1010, 1015, 1020, 1025, 1030, 1035 };
const int numDataPoints = sizeof(rawData) / sizeof(rawData[0]);

// Buffers for compressed and decompressed data
int compressedData[20];
float decompressedData[10];

void setup() {
  Serial.begin(9600);

  Serial.println("Starting HybridCompression Full Demo...\n");

  // Set base value as the first point
  int baseValue = rawData[0];

  // Compress the data
  int compressedLength = hc.compressMetric(rawData, numDataPoints, baseValue, compressedData);

  // Print original data
  Serial.println("Original Data:");
  for (int i = 0; i < numDataPoints; i++) {
    Serial.print(rawData[i]);
    Serial.print(", ");
  }
  Serial.println("\n");

  // Print compressed deltas
  Serial.println("Compressed Deltas:");
  for (int i = 0; i < compressedLength; i++) {
    Serial.print(compressedData[i]);
    Serial.print(", ");
  }
  Serial.println("\n");

  // Decompress
  hc.decompressMetric(compressedData, compressedLength, baseValue, decompressedData);

  // Print decompressed data
  Serial.println("Decompressed Data:");
  for (int i = 0; i < numDataPoints; i++) {
    Serial.print(decompressedData[i], 2); // 2 decimal places just in case
    Serial.print(", ");
  }
  Serial.println("\n");

  // Calculate Compression Ratio
  int originalSizeBytes = numDataPoints * sizeof(int);     // uncompressed: 10 * 2 = 20 bytes
  int compressedSizeBytes = compressedLength * sizeof(int); // compressed: N * 2 bytes
  float compressionRatio = ((float)compressedSizeBytes / (float)originalSizeBytes) * 100.0;

  Serial.print("Compression Ratio: ");
  Serial.print(compressionRatio, 2);
  Serial.println("% of original size");
}

void loop() {
  // Nothing here
}
