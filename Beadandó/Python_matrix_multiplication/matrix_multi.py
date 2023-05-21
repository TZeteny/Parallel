import numpy as np
import random
import timeit
from concurrent.futures import ThreadPoolExecutor


def fill_matrix(matrix, n):
    k = 1
    for rows in range(n):
        for cols in range(n):
            matrix[rows][cols] = k
            k += 1


def fill_matrix_random(matrix, n):
    for rows in range(n):
        for cols in range(n):
            matrix[rows][cols] = random.randint(0, 3)


def multiply_matrices(mA, mB, n):
    result = np.zeros([n,n])

    for row in range(n): # rows
        for col in range(n): # columns
            for k in range(n): # columns of A, rows of B
                result[row][col] += mA[row][k] * mB[k][col]

    return result


def matrix_thread(mA, mB, result, n, threads, threadNum):
    for row in range(threadNum, n, threads):
        for col in range(n):
            for k in range(n):
                result[row][col] += mA[row][k] * mB[k][col]


def multiply_threaded(mA, mB, n, threads):
    result = np.zeros([n, n])

    with ThreadPoolExecutor() as executor:
        for threadNum in range(threads):
            executor.submit(matrix_thread(mA, mB, result, n, threads, threadNum))

    return result


if __name__ == "__main__":
    file = open("large.txt", "w")

    for threads in range(10, 41, 10):
        file.write(f"____________________\n{threads} threads\n____________________\n")
        print(f"____________________\n{threads} threads\n____________________\n")
        for n in range(300, 501, 50):
            file.write(f"Size: {n}^2\n")
            print(f"Size: {n}^2\n")

            mA = np.zeros([n, n])
            mB = np.zeros([n, n])

            fill_matrix_random(mA, n)
            fill_matrix_random(mB, n)

            result = np.zeros([n, n])
            time1 = timeit.default_timer()
            result = multiply_matrices(mA, mB, n)
            time1 = timeit.default_timer() - time1

            result = np.zeros([n, n])
            time2 = timeit.default_timer()
            result = multiply_threaded(mA, mB, n, threads)
            time2 = timeit.default_timer() - time2

            file.write(f"Sequential runtime: {time1}s\n")
            file.write(f"Threaded runtime: {time2}s\n")
            print(f"Sequential runtime: {time1}s\n")
            print(f"Threaded runtime: {time2}s\n")


    file.close()
    print("Done")

    """
    file = open("results.txt", "w")

    for threads in range(10, 101, 10):
        file.write(f"____________________\n{threads} threads\n____________________\n")
        print(f"____________________\n{threads} threads\n____________________\n")

        for n in range(10, 291, 10):
            file.write(f"Size: {n}^2\n")
            print(f"Size: {n}^2\n")

            mA = np.zeros([n, n])
            mB = np.zeros([n, n])

            fill_matrix_random(mA, n)
            fill_matrix_random(mB, n)

            result = np.zeros([n, n])
            time1 = timeit.default_timer()
            result = multiply_matrices(mA, mB, n)
            time1 = timeit.default_timer() - time1

            result = np.zeros([n, n])
            time2 = timeit.default_timer()
            result = multiply_threaded(mA, mB, n, threads)
            time2 = timeit.default_timer() - time2

            file.write(f"Sequential runtime: {time1}s\n")
            file.write(f"Threaded runtime: {time2}s\n")
            print(f"Sequential runtime: {time1}s\n")
            print(f"Threaded runtime: {time2}s\n")

    file.close()
    print("Done")
    """

    """
    n = 3 # n is size of matrix
    mA = np.zeros([n,n])
    mB = np.zeros([n,n])

    fill_matrix_random(mA, n)
    # print(f"Matrix A:\n{mA}")
    fill_matrix_random(mB, n)
    # print(f"Matrrix B:\n{mB}")

    result = np.zeros([n,n])
    time1 = timeit.default_timer()
    result = multiply_matrices(mA, mB, n)
    time1 = timeit.default_timer() - time1
    # print(f"Result single:\n{result}")

    result = np.zeros([n, n])
    time2 = timeit.default_timer()
    result = multiply_threaded(mA, mB, n, n)
    time2 = timeit.default_timer() - time2
    # print(f"Result multi:\n{result}")

    print(f"Execution time single: {time1 * 1000}ms")
    print(f"Execution time multi: {time2 * 1000}ms")
    # print(f"Execution time single: {time1}s")
    # print(f"Execution time multi: {time2}s")
    """

