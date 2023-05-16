
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <chrono>
#include <windows.h>
#include <map>
#include <sstream>
#include <list>
#include <algorithm>

using namespace std;

/////////////////////       config      //////////////////////////////

map<string, string> load_config(string sort)
{
    ifstream config_file(sort);

    if (config_file.good())
    {
        cout << "Config file detected" << endl;
        map<string, string> config;
        string line;

        while (getline(config_file, line)) {
            string key, value;
            key = line.substr(0, line.find("="));
            value = line.substr(line.find("=") + 1);
            config[key] = value;
        }

        return config;
    }
    else
    {
        cout << "No config file detected" << endl;
        cout << "\nPress any key to close" << endl;
        _getch();
        exit(0);
    }

}

///////////////////////        read     /////////////////////////////

void read(int* data, int elements, string file)
{
    ifstream dataFile(file);

    if (dataFile.good())
    {
        cout << "Data: Data reading successful" << endl;
        string buf;
        for (int i = 0; i < elements; i++)
        {
            getline(dataFile, buf, ',');
            data[i] = atoi(buf.c_str());
            //dataFile >> data[i];
            //cout << data[i] << "\t";
        }
    }
    else
    {
        cout << "Reading error" << endl;
        cout << "\nPress any key to close" << endl;
        _getch();
        exit(0);
    }
    dataFile.close();

}

/////////////////////////       write       /////////////////////////

void write(int* data, int elements, string file)
{
    ofstream saveFile(file);
    if (saveFile.good())
    {
        cout << "Data: Data writing successful" << endl;

        for (int i = 0; i < elements; i++)
        {
            saveFile << data[i] << ";" <<endl;
            //cout << data[i] << "\t";
        }
    }
    else
    {
        cout << "Writing error" << endl;
    }
    saveFile.close();
}
///////////////////     bucket sort      /////////////////////////////

void bucketSort(int arr[], int n, int numBuckets) 
{
    int maxElem = *std::max_element(arr, arr + n);
    int minElem = *std::min_element(arr, arr + n);
    int bucketRange = (maxElem - minElem) / numBuckets + 1;
    int** buckets = new int* [numBuckets];

    for (int i = 0; i < numBuckets; i++) 
    {
        buckets[i] = new int[n];
        for (int j = 0; j < n; j++) 
        {
            buckets[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) 
    {
        int bucketIndex = (arr[i] - minElem) / bucketRange;
        int j = 0;
        while (buckets[bucketIndex][j] != 0 && buckets[bucketIndex][j] < arr[i])
        {
            j++;
        }
        for (int k = n - 1; k > j; k--) 
        {
            buckets[bucketIndex][k] = buckets[bucketIndex][k - 1];
        }
        buckets[bucketIndex][j] = arr[i];
    }

    for (int i = 0; i < numBuckets; i++) 
    {
        std::sort(buckets[i], buckets[i] + n);
    }

    int index = 0;
    for (int i = 0; i < numBuckets; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            if (buckets[i][j] != 0) 
            {
                arr[index++] = buckets[i][j];
            }
        }
    }

    for (int i = 0; i < numBuckets; i++) 
    {
        delete[] buckets[i];
    }
}

  ///////////////////     qucik sort      //////////////////////

void quickSort(int arr[], int left, int right) 
{
    int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];


    while (i <= j) 
    {
        while (arr[i] < pivot) 
        {
            i++;
        }
        while (arr[j] > pivot) 
        {
            j--;
        }
        if (i <= j) 
        {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    if (left < j) 
    {
        quickSort(arr, left, j);
    }
    if (i < right) 
    {
        quickSort(arr, i, right);
    }
}

/////////////////////////       bubble sort     ////////////////////////////////

int bubble(int* tab, int elements)
{
    double pc;

    for (int i = 1; i < elements; i++)
    {
            pc = (double) i / elements;
        cout << pc*100 << "%" << endl;
        for (int j = 0; j < elements - i; j++)
        {
            if (tab[j] < tab[j + 1])
            {
                int x = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = x;
            }
        }
    }

    //cout << "\nTime: " << elapsed.count() * 1e-9 << endl;

    /*      Display elements
    for (int i = 0; i < elements; i++)
    {
        cout << tab[i] << " ";
    }
    */


    return 0;
}

void wait()
{
    cout << '-' << flush;
    while (true) {
        Sleep(100);
        cout << "\b\\" << flush;
        Sleep(100);
        cout << "\b|" << flush;
        Sleep(100);
        cout << "\b/" << flush;
        Sleep(100);
        cout << "\b-" << flush;
    }
}


int main()
{

    map<string, string> config = load_config("sort.ini");

    int liczba = stoi(config["elements"]);
    string data_file = config["data_file"];
    string saved_to = config["saved_to"];
    string algorithm = config["algorithm"];
    string times = config["times"];
    int repeats = stoi(config["repetitions"]);

    int* data = new int[liczba];

    read(data, liczba, data_file);

    //Sleep(1000);

    if(algorithm == "bubble")
    {
        ofstream timesFile(times);

        for (int i = 0; i < repeats; i++)
        {
            auto begin = std::chrono::high_resolution_clock::now();

            bubble(data, liczba);


            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

            if (timesFile.good())
            {
                cout << "Time: Data writing successful" << endl;

                timesFile << elapsed.count() * 1e-9 << ";s" << endl;

            }
            else
            {
                cout << "Writing error" << endl;
            }
        }
        
        timesFile.close();
    }
    else if(algorithm == "quick")
    {
        ofstream timesFile(times);

        for (int i = 0; i < repeats; i++)
        {
            auto begin = std::chrono::high_resolution_clock::now();

            quickSort(data, 0, liczba - 1);

            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

            if (timesFile.good())
            {
                cout << "Time: Data writing successful" << endl;

                timesFile << elapsed.count() * 1e-9 << ";s" << endl;

            }
            else
            {
                cout << "Writing error" << endl;
            }
        }
        
        timesFile.close();
    }
    else if (algorithm == "bucket")
    {
        ofstream timesFile(times);

        for (int i = 0; i < repeats; i++)
        {
            auto begin = std::chrono::high_resolution_clock::now();

            bucketSort(data, liczba, 10);

            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

            if (timesFile.good())
            {
                cout << "Time: Data writing successful" << endl;

                timesFile << elapsed.count() * 1e-9 << ";s" << endl;

            }
            else
            {
                cout << "Writing error" << endl;
            }
        }
        
        timesFile.close();
    }
    //write(data, liczba, saved_to);

    cout << "\nPress any key to close" << endl;
    _getch();

    return 0;
}
