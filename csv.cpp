/**
 * Comma Separated Values: A lightweight CSV library for reading datasets.
 * @file csv.cpp
 * @author Asfaw
 * @version 1.0
 */


// import necessary libraries 
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// import header file of custom CSV library
#include "csv.h"

// std:: prefix not needed
using namespace std;


/**
 * Scan through data folder and read file names.
 * @param path, the path to the datasets folder
 * @return files, a vector of strings of file names
 */
vector<string> list_datasets(string path) {
    vector<string> files;

    // loop through directory and add path to files vector
    for(const auto & file : __fs::filesystem::directory_iterator(path))
        files.push_back(file.path());
    
    return files;
}


/**
 * List out datasets and ask for user to select one.
 * @param datasets, a vector of strings of file names
 * @return dataset, the path to the dataset
 */
string chose_dataset(vector<string> datasets) {
    int dataset_id = 0;

    // print out the datasets and their corresponding paths for user
    for(int index = 0; index < datasets.size(); index++)
        cout << "[" << index << "]: " << datasets[index] << endl;
    
    cout << endl;

    // ask for user to input the dataset they'd like as index
    cout << "What dataset would you like to run a regression on? [0-" << datasets.size() - 1 << "]: ";
    cin >> dataset_id;

    // return the corresponding dataset based on user input
    return datasets[dataset_id];
}


/**
 * Read file into string.
 * @param dataset_path, path to the desired dataset
 * @return contents, the dataset contents as string
 */
string read_csv(string dataset_path) {
    // read data into dataset
    ifstream dataset(dataset_path);
    string result;

    ostringstream stream;

    // convert from ifstream to string
    stream << dataset.rdbuf();
    result = stream.str();

    return result;
}


/**
 * Chose the input and output headers of dataset.
 * @param dataset_path, path to the desired dataset
 * @return headers, the header indicies in a vector
 */
vector<int> chose_headers(string dataset_path) {
    vector<int> headers;
    vector<string> columns;

    int x_header, y_header;

    // read in dataset and only get first line
    string first_line;
    istringstream stream(dataset_path);
    getline(stream, first_line);

    // convert first line to stream (to loop over)
    istringstream line(first_line);
    
    while(line.good()) {
        // slip by comma and add each column name to columns vector
        string substr;
        getline(line, substr, ',');
        columns.push_back(substr);
    }

    // print out the columns and their corresponding indicies for user
    for(int index = 0; index < columns.size(); index++)
        cout << "[" << index << "]: " << columns[index] << endl;

    cout << endl;

    // ask for user to input the input column they'd like as index
    cout << "What label do you want your x (inputs) column to be? [0-" << columns.size() - 1 << "]: ";
    cin >> x_header;

    // ask for user to input the output column they'd like as index
    cout << "What label do you want your y (outputs) column to be? [0-" << columns.size() - 1 << "]: ";
    cin >> y_header;

    // return the column indicies so that later the program can instantly skip to the desired column
    headers.push_back(x_header);
    headers.push_back(y_header);

    return headers;
}


/**
 * Convert CSV text to two-dimensional vectors.
 * @param dataset_path, path to the desired dataset
 * @return data, csv to two-dimensional vectors
 */
vector<vector<string>> csv_to_vector(string dataset_path) {
    vector<vector<string>> result;

    // read dataset into dataset_stream
    istringstream dataset_stream(dataset_path);

    while(dataset_stream.good()) {
        vector<string> current_row;

        // get the current line only
        string current_line;
        getline(dataset_stream, current_line);

        istringstream current_line_stream(current_line);

        while(current_line_stream.good()) {
            // get each entry and add to current_row vector
            string current_entry;
            getline(current_line_stream, current_entry, ',');

            current_row.push_back(current_entry);
        }

        // add the row to "outer vector" result
        result.push_back(current_row);
    }

    return result;
}


/**
 * Get the data from a desired column.
 * @param data, CSV data as two-dimensional vectors
 * @return column, the desired column as a vector of doubles
 */
vector<double> get_column(vector<vector<string>> data, int index) {
    vector<double> result;

    // skip first row because those are headers
    for(int row = 1; row < data.size(); row++) {
        // skip directly to column because of chose_headers(...)
        vector<string> current_row = data[row];

        // convert string to double and push to result
        double as_number = atof(current_row[index].c_str());
        result.push_back(as_number);
    }

    return result;
}


/**
 * Print a specified amount of hyphens to act as a visual divider.
 * @param amount, the number of hyphens to print on the screen
 * @return {none}
 */
void divider(int amount) {
    string result;

    for(int hyphen = 0; hyphen < amount; hyphen++)
        result += "-";
    
    // print divider and blank line for breathing room
    cout << result << endl;
    cout << endl;
}