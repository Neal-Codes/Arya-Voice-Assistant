Arya - ESP32 Personal Assistant

Arya is an AI-powered personal assistant built using the ESP32. It is capable of speech recognition, time and weather updates, jokes, Wikipedia searches, and more. Arya connects to the internet and uses Hugging Face's API for natural language processing and response generation. It also uses various APIs for news, weather, and jokes.
Features
•	Wake Word Detection: Detects the wake word "Arya" to trigger voice commands.
•	Voice Interaction: Uses eSpeak for Text-to-Speech (TTS) to communicate back.
•	Wi-Fi Connectivity: Connects to a Wi-Fi network to fetch real-time data (weather, news, etc.).
•	Internet-Enabled Queries: Queries services like Wikipedia, web search, and more.
•	Offline Commands: Handles simple offline commands when the internet is unavailable.
Requirements
•	Hardware:
o	ESP32
o	I2S Microphone (INMP441 MEMS Microphone)
o	MP3-TF-16P MP3 SD Card Module (for TTS audio output)
•	Libraries:
o	WiFi.h
o	HTTPClient.h
o	ArduinoJson.h
o	eSpeak.h
o	PicoVoice.h (For Wake Word Detection)
o	TimeLib.h (For time and date handling)
o	WiFiClientSecure.h
o	NTPClient.h
o	WiFiUdp.h
Setup Instructions
1.	Install Libraries:
o	Install the necessary libraries through the Arduino Library Manager or manually from GitHub.
2.	Hardware Connections:
o	Connect the microphone module to the correct I2S pins on the ESP32.
o	Connect the MP3-TF-16P module for audio output.
3.	Configure Wi-Fi:
o	Update the Wi-Fi SSID and password in the code.
4.	Hugging Face API Token:
o	Sign up at Hugging Face and obtain an API token. Replace the API token in the code.
5.	Upload the Code:
o	Upload the code to your ESP32 using the Arduino IDE.
6.	Power on the ESP32:

o	Once the ESP32 is powered, it will connect to Wi-Fi, and you will be able to interact with Arya.
Features in Detail
•	Speech Commands:
o	After detecting the wake word ("Arya"), Arya will listen to your commands. Examples of commands include:
	"Tell me a joke."
	"What is the weather like?"
	"What is the time?"
	"Search Wikipedia for [query]."
	"Search for [query]."


•	Offline Support:
o	If no internet connection is available, Arya can still respond to basic commands like "Hello" and "Goodbye."
•	Time and Date:
o	Arya provides the current time and date using NTP (Network Time Protocol).


•	API Integrations:
o	News API: Fetches the latest news headlines.
o	Weather API: Fetches current weather data for a specified location.
o	Joke API: Fetches a random joke.
o	Wikipedia Search: Fetches and speaks the summary of a Wikipedia article.
o	Web Search: Performs a DuckDuckGo search and speaks the results.


Future Plans
•	Offline Mode: Implement a more robust offline functionality for additional commands.
•	Multi-language Support: Expand the assistant to support multiple languages.
•	Voice Command Customization: Allow users to customize voice commands.
•	Home Automation Integration: Integrate with home automation devices.


Contributions
Feel free to fork the repository and submit pull requests with improvements or new features. Contributions are always welcome!


License
This project is open-source and released under the MIT License. See the LICENSE file for more information.


