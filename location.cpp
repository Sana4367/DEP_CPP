#include <iostream>
#include <cstring>
using namespace std;


class Location {
public:
    char name[50];
    double latitude;
    double longitude;

    Location(const char* n = "", double lat = 0.0, double lon = 0.0) {
        strncpy(name, n, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
        latitude = lat;
        longitude = lon;
    }
};

class LocationManager {
private:
    static const int MAX_LOCATIONS = 100;
    Location locations[MAX_LOCATIONS];
    int locationCount;

public:
    LocationManager() : locationCount(0) {}

    void addLocation(const char* name, double latitude, double longitude) {
        if (locationCount < MAX_LOCATIONS) {
            locations[locationCount] = Location(name, latitude, longitude);
            locationCount++;
        } else {
            cout << "Location list is full! \n";
        }
    }

    void removeLocation(const char* name) {
        for (int i = 0; i < locationCount; ++i) {
            if (strcmp(locations[i].name, name) == 0) {
                for (int j = i; j < locationCount - 1; ++j) {
                    locations[j] = locations[j + 1];
                }
                locationCount--;
                break;
            }
        }
    }

    void listLocations() {
        for (int i = 0; i < locationCount; ++i) {
            cout << "Name: " << locations[i].name << ", Latitude: " << locations[i].latitude << ", Longitude: " << locations[i].longitude << "\n";
        }
    }
};

class WeatherVariable {
public:
    char name[50];
    double value;

    WeatherVariable(const char* n = "", double v = 0.0) {
        strncpy(name, n, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
        value = v;
    }
};

class WeatherVariableManager {
private:
    static const int MAX_VARIABLES = 100;
    WeatherVariable variables[MAX_VARIABLES];
    int variableCount;

public:
    WeatherVariableManager() : variableCount(0) {}

    void addVariable(const char* name, double value) {
        if (variableCount < MAX_VARIABLES) {
            variables[variableCount] = WeatherVariable(name, value);
            variableCount++;
        } else {
            cout << "Weather variable list is full! \n";
        }
    }

    void listVariables() {
        for (int i = 0; i < variableCount; ++i) {
            cout << "Name: " << variables[i].name << ", Value: " << variables[i].value <<"\n";
        }
    }
};

class WeatherForecastingSystem {
public:
    void fetchWeatherData(const char* location) {
        cout << "Fetching weather data for: " << location << "\n";
        // Here we can include the actual API call and data handling
    }

    void displayWeatherData() {
        cout << "Displaying weather data \n";
        // Here we can include code to display the retrieved weather data
    }
};

int main() {
    LocationManager locationManager;
    WeatherVariableManager weatherVariableManager;
    WeatherForecastingSystem weatherSystem;

    // Adding locations
    locationManager.addLocation("New York", 40.7128, -74.0060);
    locationManager.addLocation("Los Angeles", 34.0522, -118.2437);

    // Listing locations
    std::cout << "Locations: \n";
    locationManager.listLocations();

    // Adding weather variables
    weatherVariableManager.addVariable("Temperature", 25.5);
    weatherVariableManager.addVariable("Wind Speed", 5.2);

    // Listing weather variables
    std::cout << "Weather Variables: \n";
    weatherVariableManager.listVariables();

    // Fetching and displaying weather data for a location
    weatherSystem.fetchWeatherData("New York");
    weatherSystem.displayWeatherData();

    return 0;
}
