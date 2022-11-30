#include <bits/stdc++.h>

using namespace std;

#define ARGUMENTS_NUMBER 4

struct argument {

};

int string_to_number(string number) {
    return stoi(number);
}

void *create_exponents_list(void *arg) {
    
    return NULL;
    pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    
    if(argc != ARGUMENTS_NUMBER)
        cout << ("ERROR: incorrect number of arguments!");
    else
        cout << "## Program has started ## \n";

    ifstream fin(argv[3]);
    int number_of_files;
    fin >> number_of_files;
    string files[number_of_files];
    for(int i = 0; i < number_of_files; ++i) {
        fin >> files[i];
    }
    vector<int> numbers;
    for(int i = 0; i < number_of_files; ++i) {
        ifstream read_from_file(files[i]);
        int nr_of_numbers;
        read_from_file >> nr_of_numbers;
        int number;
        for(int j = 0; j < nr_of_numbers; ++j) {
            read_from_file >> number;
            numbers.push_back(number);
        }
    }

    const int mapper_threads_number = string_to_number(argv[1]);
    pthread_t mapper_threads[mapper_threads_number];
    argument mapper_arguments[mapper_threads_number];

    const int reducer_threads_number = string_to_number(argv[2]);
    pthread_t reducer_threads[reducer_threads_number];
    argument reducer_arguments[reducer_threads_number];

    int the_error = 0;
    for(int id = 0; id < mapper_threads_number; ++id) {
        int the_error = pthread_create(&mapper_threads[id], NULL, create_exponents_list, &mapper_arguments[id]);
        if(the_error) {
            cout << "Failed to create thread \n";
            return 1;
        }
    }

    return 0;
}