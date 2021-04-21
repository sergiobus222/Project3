//Sources used
//https://urldefense.proofpoint.com/v2/url?u=https-3A__www.devdungeon.com_content_curl-2Dtutorial&d=DwIGAg&c=sJ6xIWYx-zLMB3EPkvcnVg&r=cC4331qrTciUCjZOZ3vZYh-LCfXZnME31l1KMo-6804&m=jEKzMFYywJjrmRKFIAZdKIPm8a-XTYy8FdGIiO9eOCA&s=U9PoyBn771bJtk1Fhn-BpR7M7p-Yg3m4DYhPdlo7qMk&e= 
//API_KEY: NqBR3T4rTRFVvTE0DkvasKs6b63RwqQDaFAUeTh5
//https://urldefense.proofpoint.com/v2/url?u=https-3A__curl.se_libcurl_c_ftpgetresp.html&d=DwIGAg&c=sJ6xIWYx-zLMB3EPkvcnVg&r=cC4331qrTciUCjZOZ3vZYh-LCfXZnME31l1KMo-6804&m=jEKzMFYywJjrmRKFIAZdKIPm8a-XTYy8FdGIiO9eOCA&s=9E5_muu3rom9exg65q_uUa5DQ3m1UL8BAhgEb1kOvxw&e= 
//https://urldefense.proofpoint.com/v2/url?u=http-3A__www.cplusplus.com_forum_unices_45878_&d=DwIGAg&c=sJ6xIWYx-zLMB3EPkvcnVg&r=cC4331qrTciUCjZOZ3vZYh-LCfXZnME31l1KMo-6804&m=jEKzMFYywJjrmRKFIAZdKIPm8a-XTYy8FdGIiO9eOCA&s=0I7gBMOi4vqlSw-Ois4B8dRv7FTYWLvOFKkRl3L7Lp4&e= 
//https://urldefense.proofpoint.com/v2/url?u=https-3A__stackoverflow.com_questions_47257198_parsing-2Dissue-2Dwarning-2Dwith-2Djson&d=DwIGAg&c=sJ6xIWYx-zLMB3EPkvcnVg&r=cC4331qrTciUCjZOZ3vZYh-LCfXZnME31l1KMo-6804&m=jEKzMFYywJjrmRKFIAZdKIPm8a-XTYy8FdGIiO9eOCA&s=bhC9vVvgElJkVblAxOKgYIAzfP3U2QmZ1p_PCYzaUOU&e= 
//https://urldefense.proofpoint.com/v2/url?u=https-3A__fdc.nal.usda.gov_index.html&d=DwIGAg&c=sJ6xIWYx-zLMB3EPkvcnVg&r=cC4331qrTciUCjZOZ3vZYh-LCfXZnME31l1KMo-6804&m=jEKzMFYywJjrmRKFIAZdKIPm8a-XTYy8FdGIiO9eOCA&s=eCw9sAlOLNiUxWvoYEtUsBJzqoeXXvlRGBIL2OyWTR4&e= 
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
    else return;
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
    float pivot = foodVect[high]->nutrients[name]->value;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
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
    bool total = true;
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
            if (total) {
                cout << "Total Hits: " << jsonFile["totalHits"] << std::endl;
                total = false;
            }
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
    cout << "Welcome to the Food Index!" << endl;
    cout << "\n";
    vector<Food*> copy;
    while (cont) {
        cout << "Menu" << endl;
        cout << "--------------" << endl;
        cout << "1: Search for new item" << endl;
        cout << "2: View Shopping List" << endl;
        cout << "3: Exit Program" << endl;
        getline(cin, inp);
        input = stoi(inp);
        cout << "\n";
        if (input == 1)
        {

            cout << "Please input item name" << endl;
            getline(cin, food);
            if (foods.find(food) == foods.end()) {
                LoadData(jsonData, foods, food);
            }
            for (int i = 0; i < foods[food].size(); i++)
            {
                copy.push_back(foods[food].at(i));
            }
            cout << "\n";
            cout << "Please input the sorting criteria" << endl;
            cout << "--------------------------------------" << endl;
            cout << "1. Protein" << endl << "2. Carbohydrates" << endl << "3. Fat" << endl << "4. Calories" << endl;
            cout << "--------------------------------------" << endl;
            bool isValid3 = false;
            while (!isValid3) {
                getline(cin, inp);
                input = stoi(inp);
                if (input == 1) {
                    criteria = "protein";
                    isValid3 = true;
                }
                else if (input == 2) {
                    criteria = "carbs";
                    isValid3 = true;
                }
                else if (input == 3) {
                    criteria = "fat";
                    isValid3 = true;
                }
                else if (input == 4) {
                    criteria = "calories";
                    isValid3 = true;
                }
                else {
                    cout << "Invalid input: Please try again" << endl;
                }
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
            if (mstime.count() < 1 || qstime.count() < 1) {
                auto mstimeMS = duration_cast<microseconds>(stop - start);
                auto qstimeMS = duration_cast<microseconds>(stop - start);
                cout << "Time taken by merge sort: " << mstimeMS.count() << " microseconds" << endl;
                cout << "Time taken by quick sort: " << qstimeMS.count() << " microseconds" << endl;
            }
            else {
                cout << "Time taken by merge sort: " << mstime.count() << " milliseconds" << endl;
                cout << "Time taken by quick sort: " << qstime.count() << " milliseconds" << endl;
            }

            cout << "Select 0 for low-high." << endl << "Select 1 for high-low." << endl;
            bool isValid = false;
            while (!isValid) {
                getline(cin, inp);
                input = stoi(inp);
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
                    }
                    isValid = true;
                }
                else if (input == 1) {
                    lth = false;
                    int counter = 1;
                    for (int i = foods[food].size() - 1; i >= 0; i--)
                    {
                        if (counter > 10) {
                            break;
                        }
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
            bool isValid2 = false;
            while (!isValid2) {
                getline(cin, inp);
                input = stoi(inp);
                if (input == 0) {
                    isValid2 = true;
                    break;
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
        else if (input == 2)
        {
            bool viewList = true;
            while (viewList) {
                cout << "Shopping List" << endl;
                for (int i = 0; i < shoppingList.size(); i++) {
                    cout << i + 1 << ": " << shoppingList[i]->name << endl;
                }
                bool valid = false;
                while (!valid) {
                    cout << "Select a food by typing in a number" << endl;
                    cout << "Enter 0 to exit shopping list" << endl;
                    getline(cin, inp);
                    input = stoi(inp);
                    if (input < shoppingList.size() + 1) {
                        if (input == 0) {
                            viewList = false;
                            valid = true;
                        }
                        else {
                            shoppingList.at(input - 1)->printInfo();
                            valid = true;
                            cout << "\n";
                        }
                    }
                    else {
                        cout << "Invalid input: Please try again" << endl;
                    }
                }
            }
        }
        else if (input == 3)
        {
            cont = false;
        }
        else {
            cout << "Invalid input: Please try again" << endl;
            cout << "\n";
        }
    }
    return 0;
}
