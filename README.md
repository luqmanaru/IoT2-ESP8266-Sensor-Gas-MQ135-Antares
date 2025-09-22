# IoT2-ESP8266-Sensor-Gas-MQ135-Antares

Implementasi sensor gas MQ135 dengan ESP8266 dan platform Antares untuk pemantauan kualitas udara secara real-time.

## 📖 Deskripsi
Proyek ini merupakan solusi **pemantauan kualitas udara** berbasis IoT yang mengintegrasikan sensor gas MQ135 dengan mikrokontroler ESP8266. Data sensor dikirim ke platform **Antares** untuk visualisasi dan analisis lebih lanjut. Sistem ini dirancang untuk memantau tingkat polusi udara dalam ruangan atau lingkungan tertutup.

## ✨ Fitur Utama
- Pembacaan data analog dan digital dari sensor MQ135
- Pengiriman data ke platform Antares setiap 30 detik
- Koneksi HTTPS yang aman ke platform Antares
- Deteksi ambang batas gas berbahaya (melalui output digital)
- Monitoring real-time via dashboard Antares

## 🛠️ Komponen
| Komponen       | Spesifikasi          |
|----------------|----------------------|
| Mikrokontroler | ESP8266 (NodeMCU)    |
| Sensor         | MQ-135 (Gas)         |
| Platform       | Antares IoT          |
| Koneksi        | WiFi (HTTPS)         |
| Interval Kirim | 30 detik             |

## 🚀 Cara Kerja
```
+-----------+     +--------+     +-----------+     +----------+
| Sensor    | --> | ESP8266| --> | Antares   | --> | Dashboard|
| MQ-135    |     |        |     | Platform  |     | Antares  |
+-----------+     +--------+     +-----------+     +----------+
```

### Langkah-langkah:
1. **Sensor MQ135** mendeteksi konsentrasi gas di udara.
2. **ESP8266** membaca nilai analog (konsentrasi) dan digital (status ambang batas).
3. **ESP8266** mengirim data ke platform Antares melalui HTTPS.
4. **Antares** menyimpan data dan menampilkannya di dashboard.
5. **Pengguna** dapat memantau data melalui dashboard Antares.

## ⚙️ Instalasi
1. **Prasyarat**:
   - Arduino IDE dengan ESP8266 board manager
   - Library `ESP8266WiFi.h` dan `WiFiClientSecure.h`
   - Akun Antares (https://antares.id/)
   - Sensor MQ135
<img width="827" height="399" alt="image" src="https://github.com/user-attachments/assets/c06a5732-4fdd-4098-8c13-e2cfe5b252d9" />

2. **Konfigurasi**:
   - Ganti nilai berikut di kode:
     ```cpp
     #define WIFI_SSID "YOUR_WIFI_SSID"
     #define WIFI_PASS "YOUR_WIFI_PASSWORD"
     const char* accessKey = "YOUR_ACCESS_KEY";
     const char* projectName = "YOUR_PROJECT_NAME";
     const char* deviceName = "YOUR_DEVICE_NAME";
     ```

3. **Wiring**:
   - VCC → 3.3V/5V
   - GND → GND
   - AOUT → Pin A0 ESP8266
   - DOUT → Pin D0 ESP8266
<img width="669" height="675" alt="image" src="https://github.com/user-attachments/assets/92140163-ea15-4675-90c1-6ae703639f67" />

4. **Upload**:
   - Hubungkan ESP8266 ke komputer
   - Pilih board dan port yang sesuai di Arduino IDE
   - Upload kode

5. **Testing**:
   - Buka Serial Monitor (baudrate: 115200)
   - Pastikan WiFi terhubung
   - Periksa respons dari Antares

## 🔍 Analisis Data
### Output Sensor
| Parameter      | Deskripsi                          | Range      |
|----------------|------------------------------------|------------|
| Nilai Analog   | Konsentrasi gas (semakin tinggi = semakin berbahaya) | 0-1023     |
| Nilai Digital  | Status ambang batas (1 = berbahaya, 0 = aman) | 0/1        |

### Interpretasi Data
- **Nilai Analog**: 
  - 0-300: Udara bersih
  - 300-700: Sedikit tercemar
  - 700-1023: Sangat tercemar/berbahaya
- **Nilai Digital**:
  - 0: Di bawah ambang batas
  - 1: Di atas ambang batas (bahaya)

## 📊 Hasil Output
Contoh output di Serial Monitor:
```
Connecting to WiFi.........
WiFi connected
MQ135 Analog Value: 245
MQ135 Digital Value: 0
Response: HTTP/1.1 201 Created
...
```

Contoh data di Antares:
```json
{
  "m2m:cin": {
    "con": "{\"sensorValue\":245,\"digitalValue\":0}"
  }
}
```

---
**luqmanaru**  
