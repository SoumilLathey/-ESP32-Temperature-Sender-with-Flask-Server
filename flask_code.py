
---

## ✅ Flask Server Code (`flask_server/server.py`)

```python
# Flask server to receive temperature data from ESP32
from flask import request, Flask

app = Flask(__name__)

@app.route("/LWT/temprature", methods=["GET", "POST"])
def recieve_temp():
    # Receive JSON data from ESP32
    data = request.json
    temprature = data.get("temp")
    
    # Print temperature to console
    print(f"Recieved temprature is {temprature} degree celcius")
    
    # Send back a JSON response
    return {"status": "success", "recieved_temp": temprature}

if __name__ == "__main__":
    # Run the server on all available IP addresses at port 5000
    app.run(host="0.0.0.0", port=5000)
