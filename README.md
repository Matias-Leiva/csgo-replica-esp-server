# ESP8266 NodeMCU IoT Project

This project is a replica system inspired by the CS:GO game, adapted for use in airsoft games. It includes features such as an LCD for status display, a buzzer for sound alerts, an LED for visual indicators, and a button for user input. The system is controlled by an ESP8266 NodeMCU and can be interacted with using a React Native mobile app.

## Materials

- ESP8266 NodeMCU 1
- LCD 16x2
- Buzzer
- LED
- Button
- Breadboard and Jumper Wires

## Installation

1. **Clone the repository:**
    ```bash
    git clone https://github.com/Matias-Leiva/csgo-replica-esp-server.git
    cd csgoServerMode
    ```

2. **Open the project in Arduino IDE:**
    - Open Arduino IDE.
    - Open `main.ino` from the `src` folder.

3. **Install required libraries:**
    - Install the `LiquidCrystal` and `ESP8266WebServer` libraries via Arduino Library Manager.
    - Install the `ArduinoJson` library via Arduino Library Manager.

4. **Upload the code to the ESP8266:**
    - Connect your ESP8266 to your computer.
    - Select the correct board and port in Arduino IDE.
    - Click `Upload`.

## How to Use

1. **Connect to the ESP8266 AP:**
    - SSID: `ESP8266_AP`
    - Password: `12345678`

2. **Use Postman to test the API:**
    - Send a POST request to `http://192.168.4.1/connect` to check server status.
      ```json
      {
        "device": 1234
      }
      ```
    - Send a POST request to `http://192.168.4.1/start` with a JSON body:
      ```json
      {
        "device": 1234,
        "hourGame": "01",
        "minutesGame": "00",
        "secondsGame": "00",
        "hourBomb": "00",
        "minutesBomb": "01",
        "secondsBomb": "00",
      }
      ```

## Integration with React Native App

The frontend for this project is developed using React Native. You can find the React Native app repository here: [React Native Frontend](https://github.com/Matias-Leiva/csgo-replica-front).

Follow the instructions in the React Native repository to set up and run the app, which will interact with this ESP8266 server.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.