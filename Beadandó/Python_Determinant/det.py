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
            matrix[rows][cols] = random.randint(0, 4)



def determinant(A):
    # Section 1: Establish n parameter and copy A
    n = len(A)
    AM = A

    # Section 2: Row ops on A to get in upper triangle form
    for fd in range(n - 1):  # A) fd stands for focus diagonal
            det_helper(AM, fd, n);
            print(f"Matrix after {fd + 1}. loop:\n{AM}\n")
    # Section 3: Once AM is in upper triangle form ...
    product = 1.0
    for i in range(n):
        # ... product of diagonals is determinant
        product *= AM[i][i]

    return product


def det_helper(AM, fd, n):
    for i in range(fd + 1, n):  # B) only use rows below fd row
        if AM[fd][fd] == 0:  # C) if diagonal is zero ...
            # AM[fd][fd] += 1.0e-18  # change to ~zero
            for k in range(n):
                temp = -1 * AM[fd][k]
                AM[fd][k] = AM[i][k]
                AM[i][k] = temp
        # D) cr stands for "current row"
        crScaler = AM[i][fd] / AM[fd][fd]
        # E) cr - crScaler * fdRow, one element at a time
        for j in range(n):
            AM[i][j] -= crScaler * AM[fd][j]


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
    """
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
    """

    N = 3
    # matrix = [ [0, 1, 3], [2, 1, 1], [1, 3, 2] ]
    matrix = np.zeros([N, N])
    fill_matrix_random(matrix, N)
    print(matrix)

    time1 = timeit.default_timer()
    print(f"Det single: {determinant(matrix)}")
    time1 = timeit.default_timer() - time1

    time2 = timeit.default_timer()
    print(f"Det parallel: {determinant_parallel(matrix)}")
    time2 = timeit.default_timer() - time2

    print(f"Execution time single: {time1 * 1000}ms")
    print(f"Execution time multi: {time2 * 1000}ms")
