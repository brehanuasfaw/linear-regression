/**
 * Linear Regression
 * @file regression.cpp
 * @author Asfaw
 * @version 1.0
 */


// import necessary libraries 
#include <iostream>
#include <numeric>
#include <vector>

// import header file of custom CSV library
#include "csv.h"

// std:: prefix not needed
using namespace std;


/**
 * Take the average of a list of numbers.
 * @param numbers, a vector of doubles to be averaged
 * @return double, the computed average
 */
double average(vector<double> numbers) {
    return accumulate(numbers.begin(), numbers.end(), 0.0) / numbers.size();
}


/**
 * Compute Pearson's Correlation Coefficient.
 * @param x, the inputs as a vector of doubles
 * @param y, the outputs as a vector of doubles
 * @param x_average, the averaged input values
 * @param y_average, the averaged output values
 * @return double, the coefficient for the model
 */
double correlation_coefficient(vector<double> x, vector<double> y, double x_average, double y_average) {
    double numerator = 0;
    
    double x_sum = 0;
    double y_sum = 0;

    for(int index = 0; index < x.size(); index++) {
        float x_difference = (x[index] - x_average);
        float y_difference = (y[index] - y_average);

        numerator += x_difference * y_difference;

        x_sum += pow(x_difference, 2);
        y_sum += pow(y_difference, 2);
    }

    return (numerator / sqrt(x_sum * y_sum));
}


/**
 * Compute the standard deviation.
 * @param x, the inputs as a vector of doubles
 * @param average, the average of the given inputs
 * @return double, the computed standard deviation
 */
double standard_deviation(vector<double> x, double average) {
    double total = 0;
    double n = x.size() - 1.0;

    for(int index = 0; index < x.size(); index++)
        total += pow((x[index] - average), 2);

    return sqrt(total / n);
}


/**
 * Compute the slope.
 * @param r, the correlation coefficient
 * @param std_x, the standard deviation of the inputs
 * @param std_y, the standard deviation of the outputs
 * @return double, the computed slope
 */
double slope(double r, double std_x, double std_y) {
    return (r * (std_y / std_x));
}


/**
 * Compute the y-intercept.
 * @param x_average, the averaged input values
 * @param y_average, the averaged output values
 * @param slope, the slope of the model
 * @return double, the computed y-intercept
 */
double y_intercept(double x_average, double y_average, double slope) {
    return (y_average - (slope * x_average));
}


/**
 * Compute the line in slope-intercept form.
 * @param y_average, the y-intercept of the model
 * @param slope, the slope of the model
 * @param x, the model's input value
 * @return double, the computed corresponding y-value
 */
double line(double y_intercept, double slope, double x) {
    return (y_intercept + (slope * x));
}


/**
 * The linear regression model.
 * @param x, the inputs as a vector of doubles
 * @param y, the outputs as a vector of doubles
 * @param input, the model's input value
 * @return double, the computed corresponding y-value
 */
double regression_model(vector<double> x, vector<double> y, double input) {
    double x_average = average(x);
    double y_average = average(y);

    double std_x = standard_deviation(x, x_average);
    double std_y = standard_deviation(y, y_average);

    double r = correlation_coefficient(x, y, x_average, y_average);
    double b = slope(r, std_x, std_y);
    double a = y_intercept(x_average, y_average, b);

    return line(a, b, input);
}


/**
 * Run the CSV logic and model.
 * @param {none}
 * @return 0
 */
int main() {
    // ask the user to chose from the available datasets
    vector<string> datasets = list_datasets("./data");
    string dataset_path = chose_dataset(datasets);

    divider(64);

    // read and ask the user to chose the input and output headers
    string string_data = read_csv(dataset_path);
    vector<int> headers = chose_headers(string_data);

    divider(64);

    // read and re-format data
    vector<vector<string>> vector_data = csv_to_vector(string_data);

    // get the inputs and outputs
    vector<double> x = get_column(vector_data, headers[0]);
    vector<double> y = get_column(vector_data, headers[1]);

    double input;

    // ask the user for an input to test the model on and store into input
    cout << "What input would you like to test the model on? ";
    cin >> input;

    // get the result from the model
    double result = regression_model(x, y, input);

    divider(64);

    // print result to the screen
    cout << "For the given input of " << input << ", the corresponding output is " << result << " according to the regression model." << endl;

    return 0;
}