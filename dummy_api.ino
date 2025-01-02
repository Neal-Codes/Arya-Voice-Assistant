#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <eSpeak.h>
#include <PicoVoice.h> // For Wake Word detection
#include <TimeLib.h>    // For time and date handling
#include <WiFiClientSecure.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Wi-Fi credentials
const char* ssid = "Jio";
const char* password = "Rekha1982";

// Define mic pin (ensure it's correctly connected)
const int micPin = 34;  // Example mic pin (check your setup)

// Hugging Face API configuration
const String apiURL = "https://api-inference.huggingface.co/models/microsoft/DialoGPT-medium";
const String hfToken = "hf_dummyToken1234567890";  // Dummy API Key

// Joke API configuration (Official Joke API)
const String jokeApiURL = "https://official-joke-api.appspot.com/random_joke";  // Random Joke API

// Wake Word and PicoVoice setup
const char* wakeWord = "Arya";  // The wake word
PicoVoice wakeWordDetector;

// NTP Setup
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Declare function prototypes
void setupTTS();
String getSpeechInput();
String sendQueryToHuggingFace(String query);
String parseResponse(String response);
void speakResponse(String text);
void connectToWiFi();
bool detectWakeWord(String speechInput);
void handleOfflineCommands(String speechInput);
void fetchAndReadNews();
void fetchWeather();
void handleMathCommands(String speechInput);
void tellTime();
void tellJoke();
String searchWikipedia(String query);
String webSearch(String query);

// Setup function
void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  connectToWiFi();

  // Initialize eSpeak
  setupTTS();

  // Initialize Wake Word detection
  wakeWordDetector.begin(wakeWord);  // Begin Wake Word detection with the word "Arya"

  // Initialize NTP Client for time synchronization
  timeClient.begin();
  timeClient.update();

  Serial.println("Assistant Arya is ready!");
}

// Main loop
void loop() {
  String query = getSpeechInput();  // Get speech input from the microphone
  
  if (query.length() > 0) {
    // Check if the wake word is detected
    if (detectWakeWord(query)) {
      Serial.println("Wake word detected: " + query);
      String response = "";

      // If connected to Wi-Fi, handle specific queries
      if (WiFi.status() == WL_CONNECTED) {
        if (query.indexOf("news") >= 0) {
          fetchAndReadNews(); // Fetch and read the latest news
        } else if (query.indexOf("weather") >= 0) {
          fetchWeather(); // Fetch the current weather
        } else if (query.indexOf("time") >= 0 || query.indexOf("date") >= 0) {
          tellTime(); // Respond with current time
        } else if (query.indexOf("joke") >= 0) {
          tellJoke(); // Tell a random joke
        } else if (query.indexOf("wikipedia") >= 0) {
          String searchQuery = query.substring(query.indexOf("wikipedia") + 10);  // Extract search term
          String result = searchWikipedia(searchQuery);
          speakResponse(result);  // Speak the Wikipedia extract
        } else if (query.indexOf("search") >= 0) {
          String searchQuery = query.substring(query.indexOf("search") + 7);  // Extract search term
          String result = webSearch(searchQuery);
          speakResponse(result);  // Speak the search results
        } else {
          response = sendQueryToHuggingFace(query);  // General query to Hugging Face
        }
      } else {
        // Handle offline commands if Wi-Fi is not connected
        handleOfflineCommands(query);
      }

      // Parse Hugging Face response or offline response
      String generatedText = parseResponse(response);

      // Output response via eSpeak
      speakResponse(generatedText);
    }
  }

  delay(1000);  // Delay between loops
}

// Function to connect to Wi-Fi with timeout
void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(1000);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to WiFi");
  } else {
    Serial.println("Failed to connect to WiFi. Retrying...");
    ESP.restart();  // Restart if Wi-Fi connection fails
  }
}

// Function to get speech input (for simulation, replace with actual mic input code)
String getSpeechInput() {
  String speechInput = "";

  // Simulate speech recognition
  // Replace with the actual implementation using your microphone or other input
  speechInput = "tell me a joke";  // This is a placeholder for demonstration

  return speechInput;
}

// Function to detect the wake word in speech input
bool detectWakeWord(String speechInput) {
  return speechInput.indexOf(wakeWord) >= 0;
}

// Function to send a query to Hugging Face API
String sendQueryToHuggingFace(String query) {
  HTTPClient http;
  String responseBody = "";

  http.begin(apiURL);
  http.addHeader("Authorization", "Bearer " + hfToken);
  http.addHeader("Content-Type", "application/json");

  String payload = "{\"inputs\": \"" + query + "\"}";

  int httpResponseCode = http.POST(payload);

  if (httpResponseCode == 200) {
    responseBody = http.getString();
  } else {
    responseBody = "Error: Unable to connect to API.";
  }

  http.end();
  return responseBody;
}

// Function to parse Hugging Face API response
String parseResponse(String response) {
  String generatedText = "";

  DynamicJsonDocument doc(1024);
  deserializeJson(doc, response);

  generatedText = doc["generated_text"];
  return generatedText;
}

// Function to handle offline commands (e.g., simple responses when no internet)
void handleOfflineCommands(String speechInput) {
  if (speechInput.indexOf("hello") >= 0) {
    speakResponse("Hello! How can I assist you?");
  } else if (speechInput.indexOf("goodbye") >= 0) {
    speakResponse("Goodbye! Take care!");
  } else {
    speakResponse("Sorry, I didn't understand that.");
  }
}

// Function to fetch and read the latest news
void fetchAndReadNews() {
  HTTPClient http;
  String responseBody = "";

  http.begin("https://newsapi.org/v2/top-headlines?country=us&apiKey=dummyNewsApiKey123456");  // Dummy News API Key

  int httpResponseCode = http.GET();

  if (httpResponseCode == 200) {
    responseBody = http.getString();
  } else {
    responseBody = "Error: Unable to fetch news.";
  }

  http.end();

  // Parse the news response
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, responseBody);

  // Get top 3 news headlines
  JsonArray articles = doc["articles"];
  String newsText = "Here are the top news headlines: ";
  
  for (int i = 0; i < 3 && i < articles.size(); i++) {
    String title = articles[i]["title"].as<String>();
    newsText += "\n" + String(i + 1) + ". " + title;
  }

  // Read the news out loud
  speakResponse(newsText);
}

// Function to fetch the weather and read it out loud
void fetchWeather() {
  HTTPClient http;
  String responseBody = "";

  http.begin("https://api.openweathermap.org/data/2.5/weather?q=Shirdi,in&appid=dummyWeatherApiKey123456");  // Dummy Weather API Key
  int httpResponseCode = http.GET();

  if (httpResponseCode == 200) {
    responseBody = http.getString();
  } else {
    responseBody = "Error: Unable to fetch weather data.";
  }

  http.end();

  // Parse the weather response
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, responseBody);

  String weatherDescription = doc["weather"][0]["description"].as<String>();
  float temp = doc["main"]["temp"].as<float>() - 273.15;  // Convert from Kelvin to Celsius
  String weatherText = "The current weather is " + weatherDescription + " with a temperature of " + String(temp) + " degrees Celsius.";

  speakResponse(weatherText);
}

// Function to handle simple math commands
void handleMathCommands(String speechInput) {
  int num1, num2;
  char operation;

  // Simple example for parsing basic math (e.g., "What's 5 plus 7?")
  if (sscanf(speechInput.c_str(), "What's %d %c %d?", &num1, &operation, &num2) == 3) {
    float result = 0;
    if (operation == '+') {
      result = num1 + num2;
    } else if (operation == '-') {
      result = num1 - num2;
    } else if (operation == '*') {
      result = num1 * num2;
    } else if (operation == '/') {
      result = (num2 != 0) ? (float)num1 / num2 : 0;
    }
    speakResponse("The result is " + String(result));
  } else {
    speakResponse("Sorry, I didn't understand the math problem.");
  }
}

// Function to tell the current time
void tellTime() {
  String currentTime = "The current time is " + String(hour()) + ":" + String(minute()) + ":" + String(second()) + ".";
  speakResponse(currentTime);
}

// Function to fetch and tell a random joke
void tellJoke() {
  HTTPClient http;
  String joke = "";

  http.begin(jokeApiURL);  // Send request to the Joke API
  int httpResponseCode = http.GET();

  if (httpResponseCode == 200) {
    String response = http.getString();  // Get the response

    // Parse the joke JSON response
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, response);

    String setup = doc["setup"].as<String>();
    String punchline = doc["punchline"].as<String>();

    joke = setup + " " + punchline;  // Combine setup and punchline
  } else {
    joke = "Sorry, I couldn't fetch a joke right now.";  // Fallback if API request fails
  }

  http.end();  // Close the HTTP connection

  speakResponse(joke);  // Speak the joke using your TTS function
}

// Function to search Wikipedia
String searchWikipedia(String query) {
  HTTPClient http;
  String url = "https://en.wikipedia.org/w/api.php?action=query&format=json&prop=extracts&exintro&titles=" + query;
  String response = "";

  http.begin(url);
  int httpResponseCode = http.GET();

  if (httpResponseCode == 200) {
    response = http.getString();
  } else {
    response = "Error: Unable to fetch Wikipedia data.";
  }

  http.end();

  DynamicJsonDocument doc(1024);
  deserializeJson(doc, response);

  JsonObject pages = doc["query"]["pages"].as<JsonObject>();
  String extract = pages.begin()->value()["extract"].as<String>();

  return extract;
}

// Function to search the web
String webSearch(String query) {
  HTTPClient http;
  String url = "https://api.duckduckgo.com/?q=" + query + "&format=json";  // Using DuckDuckGo for search
  String response = "";

  http.begin(url);
  int httpResponseCode = http.GET();

  if (httpResponseCode == 200) {
    response = http.getString();
  } else {
    response = "Error: Unable to perform web search.";
  }

  http.end();

  return response;
}

// Function to speak the response using eSpeak (Text-to-Speech)
void speakResponse(String text) {
  if (text == "") {
    text = "Sorry, I didn't catch that.";
  }

  // Use eSpeak to speak the response
  eSpeak(text.c_str());  // Use eSpeak to say the generated response
  delay(2000);  // Wait for 2 seconds for the speech to finish
}

// Function to initialize eSpeak for text-to-speech
void setupTTS() {
  eSpeak_SetVoiceByName("en");  // Set to English language
  Serial.println("eSpeak initialized.");
}
