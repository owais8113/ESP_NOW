Steps to Upload and Run

Step:1 Get MAC Addresses of both devices:

Step:2 Replace the peerAddress arrays in both NODE_A.ino and NODE_B.ino with the MAC addresses obtained.
write the address of NODE_B in NODE_A and vice-verca

Step:3 Upload Code:

Upload Node_A.ino to the first ESP32.
Upload Node_B.ino to the second ESP32.

Step:4 Open Serial Monitors:

Open the Serial Monitor for both ESP32 devices in the Arduino IDE.

Step:5 Communication:

Type a message in the Serial Monitor of one ESP32 and press enter.
The message should be sent to the other ESP32 and printed on its Serial Monitor, and vice versa.

/*--OUTPUT--*/
![image](https://github.com/owais8113/ESP_NOW/assets/127936539/fed916bc-fc8d-4ff8-a54c-9dc0fc8e3323)
