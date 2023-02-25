
// Simple C program to display "Hello World"

// Header file for input output functions
// #define CURL_STATICLIB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl.h>
// #include "lib/jsmn.c"
// #include "src/include/Buffer.h"
// #include "src/include/Parsed_Json.h"
// #include "src/check_json_string.c"

#include "src/parse_json.c"
#include "src/print_weather_data.c"
#include "src/read_file.c"
#include "src/search_city.c"



/**
 * Save the data from received from the server into a Buffer struct.
 * @see https://curl.haxx.se/libcurl/c/CURLOPT_WRITEDATA.html for the function signature.
 */
size_t write_to_buffer(void *data, size_t size, size_t nmemb, void *pointer) {
    size_t real_size = size * nmemb;

    // Cast the received pointer to the Buffer structured data.
    struct Buffer * buffer = (struct Buffer *) pointer;

    // Reallocate the memory for the Buffer char pointer
    buffer->memory = realloc(buffer->memory, buffer->size + real_size + 1);
    buffer->size += real_size;

    if (buffer->memory == NULL) {
        printf("Failed to allocate memory for the http get data");
        return 1;
    }

    // Copy the fetched data to the Buffer char pointer
    memcpy(buffer->memory, data, real_size);
    buffer->memory[real_size] = '\0';
    
    return real_size;
};

/**
 * Retrieve the weather data from https://openweathermap.org/api
 * with an HTTP GET request.
 * Return an array of chars.
 * 
 * @param char * city
 * @return char * buffer.memory
 */
char * get_weather_data(char * city) {

    curl_global_init(CURL_GLOBAL_ALL);

    // Build the url
    // char base_url[] = "http://api.openweathermap.org/data/2.5/weather?appid=70415bbd102e57c88ab9b2320ce8631b&units=metric&q=";
    // char length = strlen(base_url) + strlen(city);
    // char * url = malloc(sizeof(char) * length + 1);
    // printf(url);
    // memset(url, 0, length);

    // strcat(url, base_url);
    // strcat(url, city);
    
    // Allocate an empty buffer that will hold the http get data

    struct Buffer buffer;
    buffer.memory = NULL;
    buffer.size = 0;

//     CURL *hnd = curl_easy_init();

// curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST);
// curl_easy_setopt(hnd, CURLOPT_URL, "https://openweatherapp.p.rapidapi.com/");

// struct curl_slist *headers = NULL;
// headers = curl_slist_append(headers, "X-RapidAPI-Key: 8d65e02f6fmsh09351c5f55bd875p127781jsnaa6916989258");
// headers = curl_slist_append(headers, "X-RapidAPI-Host: openweatherapp.p.rapidapi.com");
// curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

// CURLcode ret = curl_easy_perform(hnd);

    CURL *handle;
    int result;
    handle = curl_easy_init();

    // Set curl options
    curl_easy_setopt(handle, CURLOPT_URL,strcat("http://api.openweathermap.org/data/2.5/weather?id=524901&appid=70415bbd102e57c88ab9b2320ce8631b&q=", city));
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_to_buffer);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *) &buffer);
    result = curl_easy_perform(handle);


    if (result != CURLE_OK) {
        printf("A occurred during the HTTP CALL to:\n\n%s\n\nWith the following error: %s\n\n", "http://api.openweathermap.org", curl_easy_strerror(result));
        exit(1);
    }

    // free(hnd);


    return buffer.memory;
};


// main function -
// where the execution of program begins
int main(int argc, char *argv[])
{

if (argc == 1) {
        printf("\n--------------------------------------------------------\n");
        printf("| Please specify the name of a city to search for\n");
        printf("--------------------------------------------------------\n\n");
        exit(1);
    } else {
        printf("\n--------------------------------------------------------\n");
        printf("| Searching for current weather conditions in: %s\n", argv[1]);
        printf("--------------------------------------------------------\n\n");
    }
    
    // Read data from file

    char * data = read_file("c:/Users/swift/Desktop/xyz/Group4App/data/city.json");

    // Parse the json. 209580 is the precomputed number of
    // tokens that will be used to allocate the memory.
    struct Parsed_Json cities = parse_json(data, 209580);


    // Search the city
    int found = search_city(argv[1], data, cities.tokens);


    if (found == -1) {
        printf("\nError: THe city with name %s was not found in the archive. Please provide another city to search for\n", argv[1]);
        exit(1);
    }
    // Retrieve the data from the API
    char * weather_data = get_weather_data(argv[1]);


    // // Parse the api json result
    struct Parsed_Json weather = parse_json(weather_data, 2048);

    // // Print the result
    print_weather_data(weather_data, weather);

    free(data);
    free(cities.tokens);
    free(weather.tokens);
    return 0;

return 0;
}

