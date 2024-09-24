#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from pkgs.core import (
    dimensions,
    matrix_product,
    matrix_sum,
    scalar_times_matrix,
    lu_decomposition,
)


def test_lu_decomposition(A):
    Pass = False
    m1, m2 = dimensions(A)
    if m1 == m2:
        P, L, U = lu_decomposition(A)
        NM = [[0 for j in range(m1)] for i in range(m1)]
        PA = matrix_product(P, A)
        LU = matrix_product(L, U)
        Pass = matrix_sum(PA, scalar_times_matrix(-1, LU)) == NM
    return Pass


def main():
    print(test_lu_decomposition([[1, 2], [3, 4]]))

    print(test_lu_decomposition([[1, 2, 3], [4, 5, 6], [7, 8, 9]]))

    print(
        test_lu_decomposition(
            [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]
        )
    )

    print(
        test_lu_decomposition(
            [
                [10, 11, 12, 13, 14],
                [15, 16, 17, 18, 19],
                [20, 21, 22, 23, 24],
                [25, 26, 27, 28, 29],
                [30, 31, 32, 33, 34],
            ]
        )
    )


if __name__ == "__main__":
    main()
