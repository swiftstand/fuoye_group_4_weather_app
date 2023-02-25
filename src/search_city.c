#include <stdio.h>
#include <string.h>
#include "../lib/jsmn.h"
#include "./check_json_string.c"
// # define cc 10000
/**
 * Search the "to_search" string parameter in the given string "data"
 * that is an array of chars with all the parsed cities.
 * Return 1 if there is a match, 0 otherwise.
 * 
 * @param char * to_search
 * @param char * data
 * @param jsmntok_t * tokens
 * @return boolean
 */
int search_city(char * to_search, char * data, jsmntok_t * tokens) {
    //Iterate the json array to find the desired city.
    for (int i = 1; i <= tokens[0].size; i++) {
        // Compute the length of the string
        const int length = tokens[i].end - tokens[i].start;
        int cc = length + 1;
        char city[1000];

        // Copy the value of the string.
        strncpy(city, data + tokens[i].start, length);
        city[length] = '\0';

        if (check_json_string(to_search, city, tokens[i]) == 0) {
            return 0;
        }
    }

    return -1;
}


#ifndef SEARCH_CITY
#define SEARCH_CITY
/**
 * Search the "to_search" string parameter in the given string "data"
 * that is an array of chars with all the parsed cities.
 * Return 1 if there is a match, 0 otherwise.
 * 
 * @param char * to_search
 * @param char * data
 * @param jsmntok_t * tokens
 * @return boolean
 */
int search_city(char * to_search, char * data, jsmntok_t * tokens);
#endif