#include "HybridCompression.h"

void HybridCompression::compressMetric(int *data, int length, int *compressed, int &compressedLength) {
  int base = data[0];
  int deltas[MAX_SAMPLES];
  deltas[0] = 0; // Base value

  for (int i = 1; i < length; i++) {
    deltas[i] = data[i] - data[i - 1];
  }

  // RLE Encoding
  compressedLength = 0;
  for (int i = 1; i < length;) {
    int delta = deltas[i];
    int count = 1;
    while (i + count < length && deltas[i + count] == delta && count < 255) {
      count++;
    }
    compressed[compressedLength++] = delta;
    compressed[compressedLength++] = count;
    i += count;
  }
}

void HybridCompression::decompressMetric(int *compressed, int compressedLength, int baseValue, float *decompressed) {
  int index = 0;
  int val = baseValue;
  int pos = 0;

  decompressed[pos++] = val / 100.0;

  for (int i = 0; i < compressedLength; i += 2) {
    int delta = compressed[i];
    int count = compressed[i + 1];
    for (int j = 0; j < count; j++) {
      val += delta;
      decompressed[pos++] = val / 100.0;
    }
  }
}

float HybridCompression::calculateCompressionRatio(int rawSize, int compressedSize) {
  return ((float)compressedSize / rawSize) * 100.0;
}

void HybridCompression::printArray(const char *label, float *array, int length) {
  Serial.print(label);
  Serial.print(": ");
  for (int i = 0; i < length; i++) {
    Serial.print(array[i], 2);
    Serial.print(" ");
  }
  Serial.println();
}

void HybridCompression::printIntArray(const char *label, int *array, int length) {
  Serial.print(label);
  Serial.print(": { ");
  for (int i = 0; i < length; i++) {
    if (array[i] < 16) Serial.print("0");
    Serial.print(array[i], HEX);
    Serial.print(" ");
  }
  Serial.println("}");
}
