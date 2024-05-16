# Benchmark AUC-PR
Benchmarks comparing the Rolling (Prequential) AUC-PR and the batch version.

## AUC-PR versions

The implementation of the rolling and batch versions of the AUC-PR was made based on the algorithms presented by [Gomes, Grégio, Alves, and Almeida, 2023](https://doi.org/10.1109/ICMLA58977.2023.00335). The batch version was used by creating a window of scores and classes of the samples received by the stream (vectors) and passing them as parameters to the batch AUC-PR function, such as one would do using, for example, the scikit-learn AUC-PR in a stream of data.

## Running

The `model` directory contains the Python code to create a CSV containing the scores and classes of the MaliciousURL dataset samples given by the Hoeffding Tree Classifier (nevertheless, the CSV is already on the repository).

To create the CSV, which will be used to run the AUC-PR benchmarks, you will need [poetry](https://python-poetry.org).
With poetry, simply run the following commands:

```
$ cd model
$ poetry install
$ poetry shell
$ python gen_csv.py -o ../scores.csv
```

With the scores.csv created, you can make the benchmark executable:

```
$ cd ..
$ make
```

It will create the `benchmark` executable on `build/exec/`, and it needs the following arguments to run:
```
$ ./benchmark -f <path to the CSV file> -w <window size> 
```

However, the `benchmark.sh` script was created, which runs the benchmark for multiple window sizes, run:
```
$ ./benchmark.sh
```

By default, it will run the benchmark for the sizes 1000, 2000, 5000, 10000, and 50000, creating the `results.csv` with the final times.


## Results

The results in the following table represent the sum of each time to calculate the Rolling and Batch AUC-PR when the window is updated, i.e., the stream receives a new instance, considering the MaliciousURL dataset.

| Window Size | Batch Time | Rolling Time | Ratio |
|-------------|------------|--------------|-------|
| 1,000       | 42.40      | 5.85         | 7.24  |
| 2,000       | 89.98      | 12.95        | 6.95  |
| 5,000       | 282.98     | 37.30        | 7.59  |
| 10,000      | 619.43     | 94.88        | 6.53  |
| 50,000      | 3418.99    | 668.66       | 5.11  |
