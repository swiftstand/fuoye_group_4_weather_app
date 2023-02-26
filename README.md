# Group 4 Weather App
![Swiftstand](https://www.hawaiinewsnow.com/resizer/a_Q-DzgCKWsHR7lE16qWuCec1cY=/1200x600/arc-anglerfish-arc2-prod-raycom.s3.amazonaws.com/public/66OAG5MYKJDMVCL2ZC6FIOVACY.jpg)
### Team Leader
Sulaiman Hammed Oladeji [Swift](https://github.com/swiftstand)


### Description
This a console weather application that uses [openweathermap.org](https://openweathermap.org/) public API.

### Dependencies
The application has one external dependencies:

1. [libcurl](https://curl.haxx.se/libcurl/) to make an HTTP call to the OpenWeather API and get the data in raw JSON format.  


### Build
CWeather is built with _gcc_ compiler with a plain and simple _Cmake_; 
The executable  **weatherapp** is generated into the buil/debug folder.  

### How it works

When the user provide a city to the executable the **weatherapp** application check its name against an archive of cities.
The archive is based on this list: [http://bulk.openweathermap.org/sample/](http://bulk.openweathermap.org/sample/) and is a JSON array containing over 200,000 locations.
The array is first decoded and then the provided city is searched through the archive.
If it doesn't exists **weatherapp** stops the execution.
Otherwise the name is used to compose the url to query the API; for example in case the desired city to search for the weather conditions is **Lagos**, then a url of this type is constructed:

```
"http://api.openweathermap.org/data/2.5/weather?id=524901&appid={API_KEY}&q=Lagos"
```
**_NOTE :_** the first letter of the city should be uppercase

and used by curl to _GET_ the data, encoded in JSON format.
With no HTTP error the response is parsed, decoded and the weather data outputted to the terminal.


### Usage
Clone the repository, and then move into directory of the build executable:

```
cd build/debug
```

Just run the **weatherapp** executable specifying the name of a city:

```
$ .\weatherapp Osogbo

--------------------------------------------------------
| Searching for current weather conditions in: Osogbo
--------------------------------------------------------

Coordinates
        Latitude: 4.5667
        Longitude: 7.7667
Weather
        Conditions: Clouds
        Temperature: 302.76 ┬░C
        Pressure: 1013 hPa
        Humidity: 58%

--------------------------------------------------------

```

If the name of the city which you are searching to obtain the weather conditions is composed by two ore more words, then wrap its name inside quotes:

```
$ .\weatherapp "Milton Keynes"
```
