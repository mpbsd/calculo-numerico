#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from copy import deepcopy
from functools import reduce


def dimensions(A: list[list[float]]) -> tuple[int]:  # {{{
    m1 = None
    m2 = None
    b1 = 0
    b2 = 0
    if isinstance(A, list) is True:
        m1 = len(A)
        b1 = reduce(
            lambda x, y: x * y,
            [
                (1 if (isinstance(A[i], list) is True) else 0)
                for i in range(m1)
            ],
        )
        if b1 == 1:
            b2 = reduce(
                lambda x, y: x * y,
                [(1 if (len(A[i]) == len(A[0])) else 0) for i in range(m1)],
            )
            if b2 == 1:
                m2 = len(A[0])
    return (m1, m2)  # }}}


def pmatrix(A: list[list[float]]) -> None:  # {{{
    m1, m2 = dimensions(A)
    if (m1 is not None) and (m2 is not None):
        if m2 == 1:
            for i in range(m1):
                print("[%+12.6f]" % A[i][0], end="\n")
        else:
            for i in range(m1):
                for j in range(m2):
                    if j == 0:
                        print("[%+12.6f" % A[i][j], end="\t")
                    elif j == m2 - 1:
                        print("%+12.6f]" % A[i][j], end="\n")
                    else:
                        print("%+12.6f" % A[i][j], end="\t")  # }}}


def psystem(A: list[list[float]], b: list[list[float]]) -> None:  # {{{
    m1, m2 = dimensions(A)
    n1, n2 = dimensions(b)
    c0 = m1 is not None
    c1 = m2 is not None
    c2 = n1 is not None
    c3 = n2 is not None
    c4 = m2 == n1
    if c0 and c1 and c2 and c3 and c4:
        for i in range(m1):
            for j in range(m2):
                if j == 0:
                    print("[%+12.6f" % A[i][j], end="\t")
                elif j == m2 - 1:
                    print(
                        "%+12.6f][ X%d ] = [%+12.6f]" % (A[i][j], i, b[i][0]),
                        end="\n",
                    )
                else:
                    print("%+12.6f" % A[i][j], end="\t")  # }}}


def matrix_product(  # {{{
    A1: list[list[float]], A2: list[list[float]]
) -> list[list[float]]:
    A3 = None
    m1, m2 = dimensions(A1)
    n1, n2 = dimensions(A2)
    c0 = m1 is not None
    c1 = m2 is not None
    c2 = n1 is not None
    c3 = n2 is not None
    c4 = m2 == n1
    if c0 and c1 and c2 and c3 and c4:
        A3 = [
            [
                reduce(
                    lambda x, y: x + y,
                    [A1[i][k] * A2[k][j] for k in range(m2)],
                )
                for j in range(n2)
            ]
            for i in range(m1)
        ]
    return A3  # }}}


def matrix_sum(  # {{{
    A1: list[list[float]], A2: list[list[float]]
) -> list[list[float]]:
    A3 = None
    m1, m2 = dimensions(A1)
    n1, n2 = dimensions(A2)
    c0 = m1 is not None
    c1 = m2 is not None
    c2 = n1 is not None
    c3 = n2 is not None
    c4 = m1 == n1
    c5 = m2 == n2
    if c0 and c1 and c2 and c3 and c4 and c5:
        A3 = [[A1[i][j] + A2[i][j] for j in range(m2)] for i in range(m1)]
    return A3  # }}}


def scalar_times_matrix(  # {{{
    a: float, A: list[list[float]]
) -> list[list[float]]:
    B = None
    m1, m2 = dimensions(A)
    c0 = m1 is not None
    c1 = m2 is not None
    if c0 and c1:
        B = [[a * A[i][j] for j in range(m2)] for i in range(m1)]
    return B  # }}}


def matrix_transpose(A: list[list[float]]) -> list[list[float]]:  # {{{
    m1, m2 = dimensions(A)
    return [[A[j][i] for j in range(m2)] for i in range(m1)]  # }}}


def lu_decomposition(A: list[list[float]]) -> tuple[list[list[float]]]:
    P = None
    L = None
    U = None
    m1, m2 = dimensions(A)
    c0 = m1 is not None
    c1 = m2 is not None
    c2 = m1 == m2
    if c0 and c1 and c2:
        P = [[(1 if j == i else 0) for j in range(m1)] for i in range(m1)]
        L = [[(1 if j == i else 0) for j in range(m1)] for i in range(m1)]
        U = deepcopy(A)
        for k in range(m1):
            p = k
            m = U[p][k]
            for i in range(k, m1):
                if abs(U[i][k]) > abs(m):
                    p = i
                    m = U[p][k]
            if p != k:
                U[k], U[p] = U[p], U[k]
                P[k], P[p] = P[p], P[k]
            for i in range(k + 1, m1):
                if U[k][k] != 0:
                    L[i][k] = U[i][k] / U[k][k]
                for j in range(k, m1):
                    U[i][j] -= L[i][k] * U[k][j]
    return P, L, U


def main():
    A = [[1, -3, 2], [-2, 8, -1], [4, -6, 5]]

    print("\nA:")
    pmatrix(A)

    P, L, U = lu_decomposition(A)

    print("\nP:")
    pmatrix(P)

    print("\nL:")
    pmatrix(L)

    print("\nU:")
    pmatrix(U)


if __name__ == "__main__":
    main()
