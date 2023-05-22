import numpy as np
import random
import timeit
from numpy import int64
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


def det_helper(AM, fd, n):
    for i in range(fd + 1, n):  # B) only use rows below fd row
        if AM[fd][fd] == 0:  # C) if diagonal is zero ...
            AM[fd][fd] == 1.0e-18  # change to ~zero
        # D) cr stands for "current row"
        crScaler = AM[i][fd] / AM[fd][fd]
        # E) cr - crScaler * fdRow, one element at a time
        for j in range(n):
            AM[i][j] -= crScaler * AM[fd][j]
            
            
def determinant(A):
    # Section 1: Establish n parameter and copy A
    n = len(A)
    AM = A

    # Section 2: Row ops on A to get in upper triangle form
    det_helper(AM, fd, n)

    # Section 3: Once AM is in upper triangle form ...
    product = 1.0
    for i in range(n):
        # ... product of diagonals is determinant
        product *= AM[i][i]

    return product


def determinant_parallel(A):
    # Section 1: Establish n parameter and copy A
    n = len(A)
    AM = A

    # Section 2: Row ops on A to get in upper triangle form
    # for fd in range(n):  # A) fd stands for focus diagonal
    # fd = 0

    with ThreadPoolExecutor() as executor:
        for fd in range(n):
            executor.submit(det_helper(AM, fd, n))

    # Section 3: Once AM is in upper triangle form ...
    product = 1.0
    for i in range(n):
        # ... product of diagonals is determinant
        product *= AM[i][i]

    return product


if __name__ == "__main__":
    N = 3
    file = open("results.txt", "w")

    for size in range(1, N + 1):
        file.write(f"Size = {size}\n")

        matrix = np.zeros([N, N], dtype=int64)
        fill_matrix(matrix, N)  # det will always be 0
        # print(matrix)
        matB = matrix
        # print(matB)

        time1 = timeit.default_timer()
        print(f"Det single: {determinant(matrix)}")
        time1 = timeit.default_timer() - time1

        time2 = timeit.default_timer()
        print(f"Det parallel: {determinant_parallel(matB)}")
        time2 = timeit.default_timer() - time2

        file.write(f"Sequential runtime: {time1 * 1000}ms\n")
        file.write(f"Threaded runtime: {time2 * 1000}ms\n")
        print(f"Execution time single: {time1 * 1000}ms")
        print(f"Execution time multi: {time2 * 1000}ms")

    """"
    N = 3
    matrix = np.empty([N, N], dtype=int64)
    fill_matrix(matrix, N) # det will always be 0
    # print(matrix)
    matB = matrix
    # print(matB)

    time1 = timeit.default_timer()
    print(f"Det single: {determinant(matrix)}")
    time1 = timeit.default_timer() - time1

    time2 = timeit.default_timer()
    print(f"Det parallel: {determinant_parallel(matB)}")
    time2 = timeit.default_timer() - time2

    print(f"Execution time single: {time1 * 1000}ms")
    print(f"Execution time multi: {time2 * 1000}ms")
    """
