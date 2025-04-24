#ifndef HYBRID_COMPRESSION_H
#define HYBRID_COMPRESSION_H

#include <Arduino.h>

class HybridCompression {
public:
  static const int MAX_SAMPLES = 12;

  void compressMetric(int *data, int length, int *compressed, int &compressedLength);
  void decompressMetric(int *compressed, int compressedLength, int baseValue, float *decompressed);
  float calculateCompressionRatio(int rawSize, int compressedSize);
  void printArray(const char *label, float *array, int length);
  void printIntArray(const char *label, int *array, int length);
};

#endif
