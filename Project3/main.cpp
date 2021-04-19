//https://www.devdungeon.com/content/curl-tutorial
//API_KEY: NqBR3T4rTRFVvTE0DkvasKs6b63RwqQDaFAUeTh5
//https://curl.se/libcurl/c/ftpgetresp.html
//http://www.cplusplus.com/forum/unices/45878/
//https://stackoverflow.com/questions/47257198/parsing-issue-warning-with-json
#define CURL_STATICLIB
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <vector>
#include "curl/curl.h"
#include <json/json.h>
using namespace std;

static size_t write_callback(char* ptr, size_t size, size_t nmemb, void* param)
{
    string jsonData(ptr, (size_t)size * nmemb);
    *((stringstream*)param) << jsonData;
    return size * nmemb;
}

class Food
{
    struct Nutrient 
    {
        string name;
        float value;
        string unit;
    };
public:
    string fdcID;
    string name;
    string brand;
    string ingredients;
    unordered_map<int,Nutrient*> nutrients;
};

void LoadData(stringstream& jsonData, unordered_map<string, Food*>& foods)
{
    CURL* curl;
    CURLcode result;
    int code(0);
    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.nal.usda.gov/fdc/v1/foods/search?api_key=NqBR3T4rTRFVvTE0DkvasKs6b63RwqQDaFAUeTh5&query=Orange");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonData);
        result = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
        if (result != CURLE_OK) {
            std::cerr << "Error during curl request: "
                << curl_easy_strerror(result) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    else {
        std::cerr << "Error initializing curl." << std::endl;
    }
    curl_global_cleanup();
    Json::Value jsonFile;
    Json::CharReaderBuilder reader;
    string s;
    if (Json::parseFromStream(reader, jsonData, &jsonFile, &s))
    {
        cout << "Total Hits: " << jsonFile["totalHits"] << std::endl;
        cout << "Current Page: " << jsonFile["currentPage"] << std::endl;
        cout << "Total Pages:" << jsonFile["totalPages"] << std::endl;
        auto foods = jsonFile["foods"];
        for (auto it = foods.begin(); it != foods.end(); it++)
        {
            Food* food = new Food();
            food->fdcID = (*it)["fdcId"].asString();
            food->name = (*it)["description"].asString();
            food->brand = (*it)["brandOwner"].asString();
            food->ingredients = (*it)["ingredients"].asString();
        }
    }
}

int main()
{
    stringstream jsonData;
    unordered_map<string, Food*> foods;
    LoadData(jsonData, foods);

    return 0;
}
