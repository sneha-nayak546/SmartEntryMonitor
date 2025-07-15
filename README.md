# SmartEntryMonitor 🚪📹

This smart door system, built around an **ESP32**, provides real-time person detection at your entrance.

## 🔧 Features

- 📷 Person detection via ESP32
- 🔔 Local buzzer alert when someone is detected
- 📱 Instant notification via Blynk with a link to live camera feed
- 🌐 Web dashboard to remotely 'Accept' or 'Deny' entry
- 🟢 Sends green light signal on "Accept", 🔴 red light on "Deny"

---

## 📁 Project Structure

```
SmartEntryMonitor/
├── Arduino/
│   └── SmartEntryMonitor.ino
├── WebApp/
│   ├── app.py
│   ├── requirements.txt
│   └── templates/
│       └── index.html
├── README.md
```

---

## 🚀 Getting Started

### ESP32 Setup (Arduino)
1. Upload the `SmartEntryMonitor.ino` to your ESP32 board.
2. Ensure the IP in `app.py` matches the ESP32 IP in your network.

### Web App Setup (Python)
```bash
cd WebApp
pip install -r requirements.txt
python app.py
```

### Access Web UI
Visit: `http://<your-computer-ip>:5000` on any device on the same Wi-Fi.

---

## 📲 Blynk Setup
- Integrate Blynk with ESP32 to send mobile notifications.
- Embed your camera stream link into the Blynk notification message.

---

## 📸 Demo Screenshot / GIF
*(Add demo images or videos here)*

---

## 💡 Future Improvements
- Face recognition for auto-authorize
- Logging entry times and names
- Voice command control

---

## 🔐 License
This project is open-source under the MIT License.
