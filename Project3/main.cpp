//https://www.devdungeon.com/content/curl-tutorial
//API_KEY: NqBR3T4rTRFVvTE0DkvasKs6b63RwqQDaFAUeTh5
//https://curl.se/libcurl/c/ftpgetresp.html
//https://stackoverflow.com/questions/47257198/parsing-issue-warning-with-json
#define CURL_STATICLIB
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "curl/curl.h"
#include <json/json.h>

static size_t write_callback(char* ptr, size_t size, size_t nmemb, void* param)
{
    std::string jsonData(ptr, (std::size_t)size * nmemb);
    *((std::stringstream*)param) << jsonData;
    return size * nmemb;
}

int main()
{
    CURL* curl;
    CURLcode result;
    std::stringstream jsonData;
    int code(0);

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.nal.usda.gov/fdc/v1/foods/search?api_key=NqBR3T4rTRFVvTE0DkvasKs6b63RwqQDaFAUeTh5&query=Cheddar%20Cheese&dataType=Branded&pageSize=1000");
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
    std::string s;
    if (Json::parseFromStream(reader, jsonData, &jsonFile, &s))
    {
        std::cout << "Total Hits: " << jsonFile["totalHits"] << std::endl;
        std::cout << "Current Page" << jsonFile["currentPage"] << std::endl;
        std::cout << "Total Pages:" << jsonFile["totalPages"] << std::endl;
    }

    return 0;
}
