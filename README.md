# 🚀 HybridCompression

**HybridCompression** is a lightweight and efficient compression library for Arduino (and embedded systems).  
It uses a hybrid approach combining **delta encoding**, **threshold-based run-length encoding**, and **bit-packing** to minimize the size of numeric datasets — perfect for constrained networks like LoRa, GSM (SIM800L), or satellite modules.

---

## ✨ Features

- Hybrid compression algorithm:
  - **Delta encoding**: stores differences between values.
  - **Threshold run-length encoding**: efficiently handles near-constant values.
  - **Bit-packing**: reduces memory footprint even further.
- Very fast (suitable for real-time transmission).
- Supports scaling for fixed-point precision.
- Minimal memory overhead.
- Designed for low-bandwidth communication systems.

---

## 📦 Installation

1. Download or clone this repository.
2. Move the `HybridCompression` folder into your Arduino `libraries` directory.
3. Restart Arduino IDE.

Or, if using PlatformIO:

```ini
lib_deps =
  MesutEmpire/HybridCompression
```
4. Include the library in your sketch:

```cpp
#include <HybridCompression.h>
```

---

## 🔥 Quick Example

```cpp
#include <HybridCompression.h>

HybridCompression hc;

// Example raw data (generic numeric readings)
const int rawData[] = {1000, 1005, 1010, 1015, 1020, 1020, 1025};
const int rawSize = sizeof(rawData) / sizeof(rawData[0]);

int compressed[2 * rawSize]; // Sufficient size for worst-case
int compressedLength = 0;

// Compress the data
compressedLength = hc.compressMetric(rawData, rawSize, compressed);

// Decompress the data
float decompressed[rawSize];
hc.decompressMetric(compressed, compressedLength, rawData[0], decompressed);

// Print results
Serial.begin(9600);
Serial.println("Original vs Decompressed:");
for (int i = 0; i < rawSize; i++) {
  Serial.print("Original: ");
  Serial.print(rawData[i] / 100.0, 2);
  Serial.print(" | Decompressed: ");
  Serial.println(decompressed[i], 2);
}

// Show compression ratio
float ratio = (float)(rawSize * sizeof(int)) / (compressedLength * sizeof(int));
Serial.print("Compression Ratio: ");
Serial.println(ratio, 2);
```

---

## 📚 API Reference

| Method | Description |
| :--- | :--- |
| `int compressMetric(const int *input, int inputLength, int *output);` | Compresses an array of integers. Returns compressed length. |
| `void decompressMetric(const int *input, int inputLength, int baseValue, float *output);` | Decompresses a compressed array back to floating-point values. |

---

## 📊 How It Works

**HybridCompression** uses three layered techniques:

- **Delta Encoding**: Saves space by storing changes between consecutive values.
- **Threshold-Based Run-Length Encoding**: If changes are below a specified threshold, they are encoded more compactly.
- **Bit Packing**: Packs multiple small numbers tightly into fewer bytes.

This results in a very high compression ratio for data that changes gradually or stays relatively stable over time.

---

## 🛠 Use Cases

- GSM modules (e.g., SIM800L, A7670)
- LoRaWAN data compression
- Satellite IoT messaging
- BLE or Zigbee telemetry
- Data logging for constrained flash memory devices

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

You are free to use it in open or closed source projects.  
Attribution appreciated but not required.

---

## 👨‍💻 Author

Created with ❤️ by **Samuel Wainaina**  
- GitHub: [MesutEmpire](https://github.com/MesutEmpire)

---

## 📢 Contributing

Pull requests are welcome!  
If you plan major changes, please open an issue first to discuss your idea.

---