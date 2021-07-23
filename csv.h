#include <string>
#include <vector>

using namespace std;

vector<double> get_column(vector<vector<string>> data, int index);
vector<vector<string>> csv_to_vector(string dataset);
string chose_dataset(vector<string> datasets);
vector<string> list_datasets(string path);
vector<int> chose_headers(string dataset);
string read_csv(string dataset_path);
void divider(int amount);