## 📦 INSTALLATION & USAGE GUIDE – **CUSTOM OLED UI**

This guide explains how to wire up the hardware and run the firmware for the **CUSTOM OLED UI** project built using **ESP32** and **SH1106 OLED**.

---

### 🧰 Required Hardware

| Component          | Description                               |
| ------------------ | ----------------------------------------- |
| ESP32 Board        | e.g., ESP32 DevKit V1                     |
| OLED Display       | SH1106 128x64 (I2C interface)             |
| 2 Tactile Switches | For Navigation and Selection              |
| Passive Buzzer     | For press feedback                        |
| Jumper Wires       | Female-to-male for breadboard connections |
| Breadboard         | (Optional) for prototyping                |

---

### 🧠 Pin Connections (based on `setup()` code)

| Function          | ESP32 Pin | Description   |
| ----------------- | --------- | ------------- |
| OLED SDA          | 21        | I2C Data      |
| OLED SCL          | 22        | I2C Clock     |
| Button (Select)   | GPIO 23   | INPUT\_PULLUP |
| Button (Navigate) | GPIO 12   | INPUT\_PULLUP |
| Buzzer            | GPIO 13   | OUTPUT        |

📌 Note: You can change the pin numbers in your code if needed.

---

### 🧪 Software Requirements

* [Arduino IDE](https://www.arduino.cc/en/software) or PlatformIO
* **U8g2 Library** (by olikraus)
* **WiFi** library (built into ESP32 core)
* Internet connection (for weather API)

---

### 🔧 Steps to Install & Upload

1. **Clone this repository**

   ```bash
   git clone https://github.com/MAATHES-THILAK-K/CUSTOM-OLED-UI-.git
   ```

2. **Open the `.ino` file** in Arduino IDE

3. **Install the required libraries** via **Library Manager**

   * Search and install: `U8g2`
   * Ensure your ESP32 board support is installed

4. **Set your board and port**

   * Tools → Board → `ESP32 Dev Module` or your variant
   * Tools → Port → Select the right COM port

5. **Customize the code**

   * Add your **WiFi SSIDs and passwords**
   * Add your **Weather API key** if required (e.g., OpenWeatherMap)

6. **Upload the code** via the Arduino IDE

---

### ▶️ How It Works (Code Logic Summary)

```cpp
void setup() {
  pinMode(13, OUTPUT);        // Buzzer
  pinMode(23, INPUT_PULLUP);  // Select Button
  pinMode(12, INPUT_PULLUP);  // Navigation Button
  u8g2.begin();               // Initialize OLED
  logo();                     // Show splash logo
  u8g2.clearBuffer();
  update_display(0);          // Draw initial UI page
  WiFi.mode(WIFI_STA);        // Set WiFi to station mode
  WiFi.setHostname("Alien X"); // Assign custom device name
}
```

---

### 🎮 Controls

* **Navigate Button** (GPIO 12): Scroll through icons and menus
* **Select Button** (GPIO 23): Open apps / confirm actions
* **Buzzer** (GPIO 13): Beeps on every valid key press

---

### 🧪 First-Time Run

1. Power the ESP32
2. OLED displays splash screen → welcome message → home UI
3. Navigate to WiFi settings → scan → select SSID
4. Open Weather App → fetch & scroll through weather data

---

