#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from pkgs.core import product, lu_decomposition


def test_lu_decomposition(A):
    P, L, U = lu_decomposition(A)
    return A == product(P, product(L, U))


def main():
    A = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    test_lu_decomposition()


if __name__ == "__main__":
    main()
