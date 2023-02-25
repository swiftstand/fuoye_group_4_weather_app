# Cweather
![Swiftstand](https://avatars.githubusercontent.com/u/104315681?s=400&u=f687a07b95de974590eb131c0eabdbf01ba2d308&v=4)

### Description
This a console weather application that uses [openweathermap.org](https://openweathermap.org/) public API.

### Dependencies
The application has one external dependencies:

1. [libcurl](https://curl.haxx.se/libcurl/) to make an HTTP call to the OpenWeather API and get the data in raw JSON format.  


### Build
CWeather is built with _gcc_ compiler with a plain and simple _Cmake_; 
The executable *weatherapp* is generated into the buil/debug folder.  

### How it works

When the user provide a city to the executable the *weatherapp* application check its name against an archive of cities.
The archive is based on this list: [http://bulk.openweathermap.org/sample/](http://bulk.openweathermap.org/sample/) and is a JSON array containing over 200,000 locations.
The array is first decoded and then the provided city is searched through the archive.
If it doesn't exists *weatherapp* stops the execution.
Otherwise the name is used to compose the url to query the API; for example in case the desired city to search for the weather conditions is *Lagos*, then a url of this type is constructed:

```
"http://api.openweathermap.org/data/2.5/weather?id=524901&appid={API_KEY}&q=Lagos"
```
_NOTE :_ the first letter of the city should be uppercase

and used by curl to _GET_ the data, encoded in JSON format.
With no HTTP error the response is parsed, decoded and the weather data outputted to the terminal.

#### Flow chart



### Usage
Clone the repository, and then build the project:

```
c-weather$ make
```

Just run the *weatherapp* executable specifying the name of a city:

```
$ .\weather Lagos

--------------------------------------------------------
| Searching for current weather conditions in: Lagos
--------------------------------------------------------

Coordinates
        Latitude: 9.69
        Longitude: 45.36
Weather
        Conditions: Fog
        Temperature: 4.95 °C
        Pressure: 1035 hPa
        Humidity: 87%

--------------------------------------------------------
```

If the name of the city which you are searching to obtain the weather conditions is composed by two ore more words, then wrap its name inside quotes:

```
$ .\weather "Milton Keynes"
```
