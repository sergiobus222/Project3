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
#include <unordered_map>
#include <vector>
#include <chrono>
#include "curl/curl.h"
#include <json/json.h>
using namespace std;
using namespace std::chrono;

static size_t write_callback(char* ptr, size_t size, size_t nmemb, void* param)
{
    string jsonData(ptr, (size_t)size * nmemb);
    *((stringstream*)param) << jsonData;
    return size * nmemb;
}

class Food
{
public:
    struct Nutrient
    {
        float value;
        string unit;
        Nutrient(float _value, string _unit);
    };
    string fdcID;
    string name;
    string brand;
    string ingredients;
    unordered_map<string,Nutrient*> nutrients;
    Food();
    void insertNutrient(int _ID, string _name, float _value, string _unit);
    void printInfo();
};

Food::Nutrient::Nutrient(float _value, string _unit)
{
    value = _value;
    unit = _unit;
}

Food::Food()
{
    fdcID = "";
    name = "";
    brand = "";
    ingredients = "";
    nutrients["protein"] = new Nutrient(0, "");
    nutrients["fat"] = new Nutrient(0, "");
    nutrients["carbs"] = new Nutrient(0, "");
    nutrients["calories"] = new Nutrient(0, "");
    nutrients["sugar"] = new Nutrient(0, "");
    nutrients["sodium"] = new Nutrient(0, "");
    nutrients["fiber"] = new Nutrient(0, "");
    nutrients["saturated fat"] = new Nutrient(0, "");
}

void Food::insertNutrient(int _ID, string _name, float _value, string _unit)
{
    if (_ID == 1003)
    {
        nutrients["protein"]->value = _value;
        nutrients["protein"]->unit = _unit;
    }
    else if (_ID == 1004)
    {
        nutrients["fat"]->value = _value;
        nutrients["fat"]->unit = _unit;
    }
    else if (_ID == 1005)
    {
        nutrients["carbs"]->value = _value;
        nutrients["carbs"]->unit = _unit;
    }
    else if (_ID == 1008)
    {
        nutrients["calories"]->value = _value;
        nutrients["calories"]->unit = _unit;
    }
    else if (_ID == 2000)
    {
        nutrients["sugar"]->value = _value;
        nutrients["sugar"]->unit = _unit;
    }
    else if (_ID == 1093)
    {
        nutrients["sodium"]->value = _value;
        nutrients["sodium"]->unit = _unit;
    }
    else if (_ID == 1079)
    {
        nutrients["fiber"]->value = _value;
        nutrients["fiber"]->unit = _unit;
    }
    else if (_ID == 1258)
    {
        nutrients["saturated fat"]->value = _value;
        nutrients["saturated fat"]->unit = _unit;
    }
}

void Food::printInfo() {
    cout << this->name << endl;
    cout << "fdcID: " << this->fdcID << endl;
    cout << "Brand: " << this->brand << endl;
    cout << "Ingredients: " << this->ingredients << endl;
    cout << "Nutrients: " << endl;
    cout << "Protien: " << this->nutrients["protein"]->value << " " << this->nutrients["protein"]->unit << endl;
    cout << "Fat: " << this->nutrients["fat"]->value << " " << this->nutrients["fat"]->unit << endl;
    cout << "Carbs: " << this->nutrients["carbs"]->value << " " << this->nutrients["carbs"]->unit << endl;
    cout << "Calories: " << this->nutrients["calories"]->value << " " << this->nutrients["calories"]->unit << endl;
    cout << "Sugar: " << this->nutrients["sugar"]->value << " " << this->nutrients["sugar"]->unit << endl;
    cout << "Sodium: " << this->nutrients["sodium"]->value << " " << this->nutrients["sodium"]->unit << endl;
    cout << "Fiber: " << this->nutrients["fiber"]->value << " " << this->nutrients["fiber"]->unit << endl;
    cout << "Saturated Fat: " << this->nutrients["saturated fat"]->value << " " << this->nutrients["saturated fat"]->unit << endl;
}

void merge(vector<Food*>& foodData, int left, int middle, int right, string name);

void mergeSort(vector<Food*>& foodData, int left, int right, string name) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(foodData, left, middle, name);
        mergeSort(foodData, middle + 1, right, name);
        merge(foodData, left, middle, right, name);
    }
}

void merge(vector<Food*>& foodData, int left, int middle, int right, string name) {
    int leftSize = middle - left + 1;
    int rightSize = right - middle;
    vector<Food*> leftVector;
    vector<Food*> rightVector;
    for (int i = 0; i < leftSize; i++) {
        leftVector.push_back(foodData[left + i]);
    }
    for (int j = 0; j < rightSize; j++) {
        rightVector.push_back(foodData[middle + 1 + j]);
    }
    int leftIndex = 0;
    int rightIndex = 0;
    int mergedIndex = left;
    while (leftIndex < leftSize && rightIndex < rightSize) {
        if (leftVector.at(leftIndex)->nutrients[name]->value > rightVector.at(rightIndex)->nutrients[name]->value) 
        {
            foodData.at(mergedIndex) = rightVector.at(rightIndex);
            rightIndex++;
        }
        else if (leftVector.at(leftIndex)->nutrients[name]->value <= rightVector.at(rightIndex)->nutrients[name]->value)
        {
            foodData.at(mergedIndex) = leftVector.at(leftIndex);
            leftIndex++;
        }
        mergedIndex++;
    }
    while (leftIndex < leftSize) {
        foodData.at(mergedIndex) = leftVector.at(leftIndex);
        mergedIndex++;
        leftIndex++;
    }
    while (rightIndex < rightSize) {
        foodData.at(mergedIndex) = rightVector.at(rightIndex);
        mergedIndex++;
        rightIndex++;
    }
}

void swap(Food* a, Food* b) {
    Food* t = a;
    a = b;
    b = t;
}

float partition(vector<Food*>& foodVect, int low, int high, string name) {
    int pivot = foodVect[high]->nutrients[name]->value;
    int i = (low - 1);
    for (float j = low; j <= high - 1; j++) {
        if (foodVect[j]->nutrients[name]->value < pivot) {
            i++;
            swap(foodVect[i], foodVect[j]);
        }
    }
    swap(foodVect[i + 1], foodVect[high]);
    return (i + 1);
}

void quickSort(vector<Food*>& foodVect, int low, int high, string name) {
    if (low < high) {
        int pi = partition(foodVect, low, high, name);
        quickSort(foodVect, low, pi - 1, name);
        quickSort(foodVect, pi + 1, high, name);
    }
}

void LoadData(stringstream& jsonData, unordered_map<string, vector<Food*>>& _foods, string input)
{
    CURL* curl;
    CURLcode result;
    int currentPage = 1;
    int totalPages = 0;
    int code(0);
    curl_global_init(CURL_GLOBAL_DEFAULT);
    string inputURL;
    inputURL = "https://api.nal.usda.gov/fdc/v1/foods/search?api_key=NqBR3T4rTRFVvTE0DkvasKs6b63RwqQDaFAUeTh5&query=%22";
    for (int i = 0; i < input.length(); i++) {
        if (input.at(i) != ' ') {
            inputURL = inputURL + input.at(i);
        }
        else {
            inputURL = inputURL + "%20";
        }
    }
    string inputEnd = "%22&dataType=Branded&pageSize=1000&pageNumber=";
    inputURL = inputURL + inputEnd;
    while (currentPage != totalPages)
    {
        inputURL += to_string(currentPage);
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, inputURL.c_str());
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
            totalPages = jsonFile["totalPages"].asInt() + 1;
            auto foods = jsonFile["foods"];
            for (auto it = foods.begin(); it != foods.end(); it++)
            {
                Food* food = new Food();
                food->fdcID = (*it)["fdcId"].asString();
                food->name = (*it)["description"].asString();
                food->brand = (*it)["brandOwner"].asString();
                food->ingredients = (*it)["ingredients"].asString();
                auto nutrients = (*it)["foodNutrients"];
                for (auto i = nutrients.begin(); i != nutrients.end(); i++)
                {
                    food->insertNutrient((*i)["nutrientId"].asInt(), (*i)["nutrientName"].asString(), (*i)["value"].asFloat(), (*i)["unitName"].asString());
                }
                _foods[input].push_back(food);
            }
        }
        jsonData.clear();
        for (int i = 0; i < to_string(currentPage).size(); i++)
        {
            inputURL.pop_back();
        }
        currentPage++;
        //cout << to_string(currentPage).size();
    }  
}

int main()
{
    stringstream jsonData;
    unordered_map<string, vector<Food*>> foods;
    int input;
    string inp;
    vector<Food*> shoppingList;
    string criteria;
    string food;
    bool cont = true;
    bool lth;
    bool viewList = true;
    bool isValid = false;
    bool isValid2 = false;
    bool isValid3 = false;
    cout << "Welcome to the Food Index!" << endl;
    cout << endl;
    vector<Food*> copy;
    while (cont) {
        cout << "Menu" << endl;
        cout << "--------------" << endl;
        cout << "1: Search for new item" << endl;
        cout << "2: View Shopping List" << endl;
        cout << "3: Exit Program" << endl;
        cin >> input;
        cout << endl;
        switch (input) {
        case 1:
        {

            cout << "Please input item name" << endl;
            cin >> inp;
            food = inp;
            LoadData(jsonData, foods, inp);
            for (int i = 0; i < foods[food].size(); i++)
            {
                copy.push_back(foods[food].at(i));
            }
            cout << endl;
            cout << "Please input the sorting criteria" << endl;
            cout << "--------------------------------------" << endl;
            cout << "1. Protein" << endl << "2. Carbohydrates" << endl << "3. Fat" << endl << "4. Calories" << endl;
            cout << "--------------------------------------" << endl;
            cin >> input;
            if (input == 1) {
                criteria = "protein";
                isValid3 = true;
            }
            if (input == 2) {
                criteria = "carbs";
                isValid3 = true;
            }
            if (input == 3) {
                criteria = "fat";
                isValid3 = true;
            }
            if (input == 4) {
                criteria = "calories";
                isValid3 = true;
            }
            auto start = high_resolution_clock::now();
            mergeSort(foods[food], 0, foods[food].size() - 1, criteria);
            auto stop = high_resolution_clock::now();
            auto mstime = duration_cast<milliseconds>(stop - start);
            start = high_resolution_clock::now();
            quickSort(copy, 0, copy.size() - 1, criteria);
            stop = high_resolution_clock::now();
            auto qstime = duration_cast<milliseconds>(stop - start);
            copy.clear();
            cout << "Data sorted!" << endl;
            cout << "Time taken by merge sort: " << mstime.count() << " milliseconds" << endl;
            cout << "Time taken by quick sort: " << qstime.count() << " milliseconds" << endl;
            cout << "Select 0 for low-high." << endl << "Select 1 for high-low." << endl;
            while (!isValid) {
                cin >> input;
                if (input == 0) {
                    lth = true;
                    for (int i = 0; i < 10; i++)
                    {
                        if (i < foods[food].size())
                        {
                            cout << i + 1 << ". ";
                            foods[food].at(i)->printInfo();
                            cout << "\n";
                        }
                        else break;
                    }
                    isValid = true;
                }
                else if (input == 1) {
                    lth = false;
                    int counter = 1;
                    for (int i = foods[food].size() - 1; i > foods[food].size() - 11; i--)
                    {
                        cout << counter << ". ";
                        foods[food].at(i)->printInfo();
                        cout << "\n";
                        counter++;
                    }
                    counter = 1;
                    isValid = true;
                }
                else {
                    cout << "Invalid input: Please try again" << endl;
                }
            }
            cout << "Input 0 if you would like to return to menu" << endl;
            cout << "Input item number if you would like to store it to your shopping list" << endl;
            while (!isValid2) {
                cin >> input;
                if (input == 0) {
                    isValid2 = true;
                }
                else if (input >= 1 && input <= 10)
                {
                    if (lth)
                    {
                        shoppingList.push_back(foods[food].at(input - 1));
                    }
                    else shoppingList.push_back(foods[food].at(foods[food].size() - input));
                }
                else {
                    cout << "Invalid input: Please try again" << endl;
                }
            }
        }
        case 2:
        {
            while (viewList) {
                cout << "Shopping List" << endl;
                for (int i = 0; i < shoppingList.size(); i++) {
                    cout << i + 1 << ": " << shoppingList[i]->name << endl;
                }
                bool valid = false;
                while (!valid) {
                    cout << "Select a food by typing in a number" << endl;
                    cout << "Enter 0 to exit shopping list" << endl;
                    cin >> input;
                    if (input < shoppingList.size() + 1) {
                        if (input == 0) {
                            viewList = false;
                            valid = true;
                        }
                        else {
                            shoppingList.at(input - 1)->printInfo();
                            valid = true;
                        }
                    }
                    else {
                        cout << "Invalid input: Please try again" << endl;
                    }
                }
            }
        }
        case 3:
        {
            cont = false;
        }
        }
    }
    return 0;
}
