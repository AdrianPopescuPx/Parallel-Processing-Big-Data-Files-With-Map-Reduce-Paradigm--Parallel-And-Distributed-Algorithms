#include <bits/stdc++.h>

using namespace std;

#define NUMBER_OF_ARGUMENTS 4

struct file_numbers {
    string name;
    vector<long long> numbers;
};

struct map_data {
    vector<file_numbers> file;
    vector<vector<long long>> exponents_list;
    int exponent;
    int id;
    pthread_barrier_t *barrier;
};

struct reducer_data {
    vector<vector<long long>> lists;
    int exponent_to_check;
    int unique_values;
    int mappers_number;
    pthread_barrier_t *barrier;
    map_data *mapper_arguments;
};

int string_to_number(string number) {
    return stoi(number);
}

void prioritize_files_on_mappers (map_data mapper_arguments[], int mapper_threads_number, int number_of_files, vector <long long> numbers[], string file_names[], int exponent, pthread_barrier_t &barrier) {
    multiset<pair<int,int>> prioritize;
    for(int i = 0; i < mapper_threads_number; ++i) {
        prioritize.insert({0, i});
        mapper_arguments[i].exponent = exponent;
        mapper_arguments[i].barrier = &barrier;
        mapper_arguments[i].id = i;
        mapper_arguments[i].exponents_list.resize(exponent + 2);
    }

    for(int i = 0; i < number_of_files; ++i) {
        auto first_mapper = *prioritize.begin();
        int id = first_mapper.second;
        int workload = first_mapper.first + numbers[i].size();
        file_numbers current_file;
        current_file.name = file_names[i];
        current_file.numbers = numbers[i];
        mapper_arguments[id].file.push_back(current_file);
        prioritize.erase(prioritize.begin());
        prioritize.insert({workload,id});
    }
}       
             
int check(long long a, long long b, long long c) {
    int result = 1;
    while(b) {
        if(b & 1) {
            result *= a;
        }
        b /= 2;
        a *= a;
        if(result > c) {
            return 1;
        }
    }
    if(result == c) {
        return 0;
    }
    return -1;
}

void *create_exponent_list(void *arg) {

    map_data *data = (map_data *) arg;
    
    int exponent = data->exponent;
    for(auto file: data->file) {
        for(auto number: file.numbers) {
            if(number == 1) {
                for(long long i = 2; i <= exponent; i++) {
                    data->exponents_list[i].push_back(number);
                }
                continue;
            }
            for(long long i = 2; i <= exponent; ++i) {
                if(check(2, i, number) > 0)
                    break;
                long long left = 1, right = sqrt(number);
                bool ok = 0;
                while (left <= right) {
                    long long middle = left + (right - left) / 2;
                    short check_result = check(middle, i, number);
                    if (check_result == 0) {
                        ok = 1;
                        left = right + 1;
                        continue;
                    }
                    if (check_result < 0) {
                        left = middle + 1;
                        continue;
                    }
                    right = middle - 1;
                }
            if (ok) {
                    data->exponents_list[i].push_back(number);
                }
            }

        }
    }
    pthread_barrier_wait(data->barrier);
    return NULL;
}



int main (int argc, char *argv[]) {
    
    if(argc != NUMBER_OF_ARGUMENTS)
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
    vector<long long> numbers[number_of_files];
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
    map_data mapper_arguments[mapper_threads_number];

    const int reducer_threads_number = string_to_number(argv[2]);
    pthread_t reducer_threads[reducer_threads_number];
    reducer_data reducer_arguments[reducer_threads_number];
    pthread_barrier_t barrier;

    pthread_barrier_init(&barrier, NULL, mapper_threads_number + reducer_threads_number);
    
    prioritize_files_on_mappers(mapper_arguments, mapper_threads_number, number_of_files, numbers, file_names, reducer_threads_number + 1, barrier);

    int the_error = 0;
    for(int id = 0; id < mapper_threads_number; ++id) {
        int the_error = pthread_create(&mapper_threads[id], NULL, create_exponent_list, &mapper_arguments[id]);
        if(the_error) {
            cout << "Failed to create thread " << id << '\n';
            return 1;
        }
    }

    





    return 0;
}