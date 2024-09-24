#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from copy import deepcopy
from functools import reduce


def dimensions(A: list[list]) -> tuple[int]:  # {{{
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


def pmatrix(A: list[list]) -> None:  # {{{
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


def psystem(A: list[list], b: list[list]) -> None:  # {{{
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


def matrix_product(A1: list[list], A2: list[list]) -> list[list]:  # {{{
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


def matrix_sum(A1: list[list], A2: list[list]) -> list[list]:  # {{{
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


def scalar_times_matrix(a: float, A: list[list]) -> list[list]:  # {{{
    B = None
    m1, m2 = dimensions(A)
    c0 = m1 is not None
    c1 = m2 is not None
    if c0 and c1:
        B = [[a * A[i][j] for j in range(m2)] for i in range(m1)]
    return B  # }}}


def matrix_transpose(A: list[list]) -> list[list]:  # {{{
    m1, m2 = dimensions(A)
    return [[A[j][i] for j in range(m2)] for i in range(m1)]  # }}}


def lu_decomposition(A: list[list]) -> tuple[list[list]]:  # {{{
    P = None
    L = None
    U = None
    m1, m2 = dimensions(A)
    c0 = m1 is not None
    c1 = m2 is not None
    c2 = m1 == m2
    if c0 and c1 and c2:
        P = [[(1 if i == j else 0) for j in range(m1)] for i in range(m1)]
        L = [[(1 if i == j else 0) for j in range(m1)] for i in range(m1)]
        U = deepcopy(A)
        for i in range(m1 - 1):
            p, M = sorted(
                [(k, abs(U[k][i])) for k in range(m1)],
                key=lambda t: t[1],
                reverse=True,
            )[0]
            if p != i:
                U[p], U[i] = U[i], U[p]
                P[p], P[i] = P[i], P[p]
            if M == 0:
                M = 1
            else:
                M = U[i][i]
            for k in range(i + 1, m1):
                L[k][i] = U[k][i] / M
                for l in range(i, m1):
                    U[k][l] -= L[k][i] * U[i][l]
    return P, L, U  # }}}


def main():
    A = [[1, 2, 3, 0], [0, 4, 5, 6], [7, -1, 8, 9], [0, -1, 1, 2]]
    b = [[43], [0], [-1], [3.141592]]

    print("\nAX=b:")
    psystem(A, b)

    P, L, U = lu_decomposition(A)

    print("\nP:")
    pmatrix(P)

    print("\nL:")
    pmatrix(L)

    print("\nU:")
    pmatrix(U)

    print("\nPA:")
    pmatrix(matrix_product(P, A))

    print("\nLU:")
    pmatrix(matrix_product(L, U))


if __name__ == "__main__":
    main()
