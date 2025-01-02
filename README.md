Arya: AI-Powered Personal Assistant (ESP32-based)
Arya is an AI-powered personal assistant built using the ESP32 microcontroller. It can interact with users through voice commands and perform various tasks such as fetching news, weather updates, telling jokes, and more. Arya uses Hugging Face's DialoGPT model for conversational responses and integrates several APIs for real-time information.

Features
Wake Word Detection: Reacts to the wake word "Arya" and starts listening for further commands.
Conversational AI: Uses the DialoGPT model from Hugging Face for natural, intelligent responses.
Text-to-Speech (TTS): Converts text responses to speech using the eSpeak library.
Time & Date: Tells the current time and date using an NTP client.
News Fetching: Retrieves the latest news headlines from a public API.
Weather Updates: Provides current weather information using a weather API.
Jokes: Tells random jokes fetched from an external API.
Wikipedia Search: Allows users to search and get information from Wikipedia.
Web Search: Performs web searches using DuckDuckGo and reads the results aloud.
Requirements
To run this project, you will need the following components and libraries:

Hardware:
ESP32 board
INMP441 Microphone (I2S interface)
MP3-TF-16P MP3 SD Card Module (for Text-to-Speech)
PicoVoice (for wake word detection)
Software:
Arduino IDE (or PlatformIO)
Libraries:
WiFi
ArduinoJson
HTTPClient
TimeLib
NTPClient
eSpeak
PicoVoice
APIs:
Hugging Face Inference API (for conversational AI)
News API (for fetching news)
OpenWeatherMap API (for weather updates)
Official Joke API (for jokes)
Wikipedia API (for fetching Wikipedia data)
DuckDuckGo API (for web search)
Installation
1. Clone the Repository
bash
Copy code
git clone https://github.com/your-username/arya-assistant.git
2. Install Dependencies
Open the Arduino IDE and install the necessary libraries via Library Manager or manually through .zip files.

PicoVoice: Follow the PicoVoice setup guide to integrate wake word detection.
eSpeak: Install via the Arduino Library Manager.
Other libraries: WiFi, ArduinoJson, HTTPClient, TimeLib, and NTPClient can also be installed via the Arduino Library Manager.
3. Configure Wi-Fi Credentials
Update the ssid and password variables in the code with your Wi-Fi credentials.

cpp
Copy code
const char* ssid = "your-SSID";
const char* password = "your-WIFI-password";
4. Set Up Hugging Face API Token
To use Hugging Face's DialoGPT model, you need an API token. You can get it by creating an account at Hugging Face.

Replace hfToken with your Hugging Face API token:

cpp
Copy code
const String hfToken = "your-huggingface-api-token";
Usage
Upload the Code: Open the .ino file in Arduino IDE and upload it to your ESP32 board.
Power Up: After uploading, connect your ESP32 to a power source.
Voice Interaction: Once the ESP32 is connected to Wi-Fi, say the wake word "Arya" to trigger the assistant. You can ask for things like the weather, news, jokes, or even ask general questions.
Output: Arya will respond via the speaker or other audio output connected to the MP3-TF-16P module.
Commands
Once "Arya" is triggered, you can ask the assistant a variety of things:

News: "Tell me the news."
Weather: "What's the weather like?"
Time: "What time is it?"
Joke: "Tell me a joke."
Wikipedia: "Search Wikipedia for [topic]."
Web Search: "Search for [query]."
Contributing
Feel free to contribute to this project! Here are a few ways you can help:

Report any bugs you encounter.
Submit pull requests for improvements or additional features.
Suggest new features or ideas.
License
This project is licensed under the MIT License - see the LICENSE file for details.

Acknowledgements
Hugging Face: For providing the DialoGPT conversational AI model.
PicoVoice: For the wake word detection technology.
OpenWeatherMap API: For weather data.
News API: For fetching the latest news.
Official Joke API: For jokes
