#!/usr/bin/env python3
# -*- coding: utf-8 -*-

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
        for i in range(m1):
            for j in range(m2):
                if j == 0:
                    print("[%+12.6f" % A[i][j], end="\t")
                elif j % m2 == m2 - 1:
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
                elif j % m2 == m2 - 1:
                    print(
                        "%+12.6f][ X%d ] = [%+12.6f]" % (A[i][j], i, b[i][0]),
                        end="\n",
                    )
                else:
                    print("%+12.6f" % A[i][j], end="\t")  # }}}


def main():
    A = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    b = [[43], [0], [-1]]
    psystem(A, b)


if __name__ == "__main__":
    main()
