
from flask import Flask, render_template, request, jsonify
import requests
import socket # Import the socket module to get the host IP

app = Flask(__name__)

ESP32_IP = "http://192.168.215.211"  # ✅ Your ESP32 IP - Ensure this is correct and accessible

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/led', methods=['POST'])
def led_control():
    data = request.get_json()
    action = data.get('action')

    try:
        if action == 'yes':
            response = requests.get(f"{ESP32_IP}/led?color=green", timeout=5) # Add a timeout
            response.raise_for_status() # Raise an exception for bad status codes
        elif action == 'no':
            response = requests.get(f"{ESP32_IP}/led?color=red", timeout=5) # Add a timeout
            response.raise_for_status()
        return jsonify({"status": "success", "action": action, "esp32_response": response.text})
    except requests.exceptions.RequestException as e:
        return jsonify({"status": "error", "message": f"Could not connect to ESP32: {e}"}), 500


if __name__ == '__main__':
    # Get the local IP address of the machine running the Flask app
    # This helps in knowing what IP to connect to from your phone
    hostname = socket.gethostname()
    # Get the IP address associated with the main network interface
    # This might require some careful handling if you have multiple network interfaces
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(("8.8.8.8", 80)) # Connect to a public server to get the local IP
        host_ip = s.getsockname()[0]
    except Exception:
        host_ip = "127.0.0.1" # Fallback if IP detection fails

    print(f"Flask app running on: http://{host_ip}:5000")
    print(f"To access from your phone, ensure your phone is on the same Wi-Fi network as this computer.")
    print(f"You can try opening http://{host_ip}:5000 in your phone's browser.")

    # Run the Flask app accessible from any IP address on your network
    # debug=True is good for development, but consider False for production
    app.run(debug=True, host='0.0.0.0', port=5000)