#include <bits/stdc++.h>

using namespace std;
//TO DO , de dat exponent fiecarui mapper
#define ARGUMENTS_NUMBER 4

struct files_prop {
    string name;
    vector<int> numbers;
};

struct mapper_argument {
    vector<files_prop> file;
};

int string_to_number(string number) {
    return stoi(number);
}


void prioritize_files_on_mappers (mapper_argument mapper_arguments[], int mapper_threads_number, int number_of_files, vector <int> numbers[], string file_names[]) {
    multiset<pair<int,int>> prioritize;
    for(int i = 0; i < mapper_threads_number; ++i) {
        prioritize.insert({0, i});
    }

    for(int i = 0; i < number_of_files; ++i) {
        auto first_mapper = *prioritize.begin();
        int id = first_mapper.second;
        int workload = first_mapper.first + numbers[i].size();
        files_prop current_file;
        current_file.name = file_names[i];
        current_file.numbers = numbers[i];
        mapper_arguments[id].file.push_back(current_file);
        prioritize.insert({workload,id});
        prioritize.erase(prioritize.begin());
    }
}

void *create_exponents_list(void *arg) {
    mapper_argument *data = (mapper_argument *) arg;
    data->file
    return NULL;
}



int main (int argc, char *argv[]) {
    
    if(argc != ARGUMENTS_NUMBER)
        cout << ("ERROR: incorrect number of arguments!");
    else
        cout << "## Program has started ## \n";

    ifstream fin(argv[3]);
    int number_of_files;
    fin >> number_of_files;
    string file_names[number_of_files];
    for(int i = 0; i < number_of_files; ++i) {
        fin >> file_names[i];
    }
    vector<int> numbers[number_of_files];
    for(int i = 0; i < number_of_files; ++i) {
        ifstream read_from_file(file_names[i]);
        int nr_of_numbers;
        read_from_file >> nr_of_numbers;
        int number;
        for(int j = 0; j < nr_of_numbers; ++j) {
            read_from_file >> number;
            numbers[i].push_back(number);
        }
    }

    const int mapper_threads_number = string_to_number(argv[1]);
    pthread_t mapper_threads[mapper_threads_number];
    mapper_argument mapper_arguments[mapper_threads_number];

    prioritize_files_on_mappers(mapper_arguments, mapper_threads_number, number_of_files, numbers, file_names);

    //cout << mapper_arguments[1].file[0].name;
    
    const int reducer_threads_number = string_to_number(argv[2]);
    pthread_t reducer_threads[reducer_threads_number];
    // argument reducer_arguments[reducer_threads_number];

    int the_error = 0;
    for(int id = 0; id < mapper_threads_number; ++id) {
        int the_error = pthread_create(&mapper_threads[id], NULL, create_exponents_list, &mapper_arguments[id]);
        if(the_error) {
            cout << "Failed to create thread " << id << '\n';
            return 1;
        }
    }

    return 0;
}