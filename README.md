# Parallel Processing Big Data Files using Map-Reduce Paradigm 
This project demonstrates the implementation of The MapReduce paradigm created in 2003 to enable processing of large data sets in a massively parallel manner.
The goal of the MapReduce model is to simplify the approach to transformation and analysis of large datasets, as well as to allow developers to focus on algorithms instead of data management.
Used Google’s approach

## Features
* Correct evaluation of the files
* Mapper-Reducer Paradigm: Implemented a mapper-reducer paradigm to accurately evaluate data from files, optimizing the distribution of mappers over input data.
* Multiset Data Structure: Utilized a multiset data structure to efficiently distribute mappers based on the number of values they needed to evaluate.
* Barrier Implementation: Created a barrier to ensure reducers do not start processing until all mappers have completed their tasks.
* Thread Creation: Consecutively created mapper and reducer threads, using the barrier to synchronize their execution.
* Optimized Mapper Process: Developed an algorithm employing binary search and logarithmic exponentiation to efficiently handle the mapper process.
* Complexity Optimization: Achieved a complexity of O(n * min(log2(nr), exponent) * log2(sqrt(nr))) for the mapper process.
* Duplicate Elimination: In reducer threads, removed duplicates from the constructed lists, preserving the count of unique values.
* Thread Joining: Joined all threads to display the final solution in each file.
* First-hand Thread Experience: Represented the first active engagement with threads, providing a suitable level of difficulty for the assignment.



## Technologies
* C++


To build and run the project, follow these steps:

* Clone the repository: `git clone https://github.com/AdrianPopescuPx/Parallel-Processing-Big-Data-Files-With-Map-Reduce-Paradigm--Parallel-And-Distributed-Algorithms`
* Navigate to the project directory
* Build and run 
