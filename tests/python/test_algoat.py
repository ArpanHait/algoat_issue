import pytest
import algoat

def test_sort_ints():
    data = [5, 2, 8, 1, 9]
    sorted_data = algoat.sort(data)
    assert sorted_data == [1, 2, 5, 8, 9]
    assert data == [5, 2, 8, 1, 9] # original is unmodified

def test_sort_floats():
    data = [5.5, 2.2, 8.8, 1.1, 9.9]
    sorted_data = algoat.sort(data)
    assert sorted_data == [1.1, 2.2, 5.5, 8.8, 9.9]

def test_search_found():
    data = [1, 2, 5, 8, 9]
    index = algoat.search(data, 5)
    assert index == 2

def test_search_not_found():
    data = [1, 2, 5, 8, 9]
    index = algoat.search(data, 3)
    assert index is None

def test_empty_list():
    assert algoat.sort([]) == []
    assert algoat.search([], 5) is None
