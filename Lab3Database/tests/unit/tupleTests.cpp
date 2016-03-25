/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tupleTests.cpp
 * Author: benjamin
 *
 * Created on February 24, 2016, 8:32 PM
 */

#include <stdlib.h>
#include <iostream>
#include "Tuple.h"

/*
 * Simple C++ Test Suite
 */

void testTuple()
{
    Tuple tuple;
    if (tuple.size() > 0)
    {
	std::cout << "%TEST_FAILED% time=0 testname=testTuple (tupleTests) message=error message sample" << std::endl;
    }
}

void testTuple2()
{
    vector<string> values;
    Tuple tuple(values);
    if (tuple.size() != values.size())
    {
	std::cout << "%TEST_FAILED% time=0 testname=testTuple2 (tupleTests) message=error message sample" << std::endl;
    }
}

void testAdd()
{
    string s;
    Tuple tuple;
    tuple.add(s);
    if (tuple[0] != s)
    {
	std::cout << "%TEST_FAILED% time=0 testname=testAdd (tupleTests) message=error message sample" << std::endl;
    }
}

void testSize()
{
    Tuple tuple;
    unsigned result = tuple.size();
    if (tuple.size() > 0)
    {
	std::cout << "%TEST_FAILED% time=0 testname=testSize (tupleTests) message=error message sample" << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% tupleTests" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testTuple (tupleTests)" << std::endl;
    testTuple();
    std::cout << "%TEST_FINISHED% time=0 testTuple (tupleTests)" << std::endl;

    std::cout << "%TEST_STARTED% testTuple2 (tupleTests)" << std::endl;
    testTuple2();
    std::cout << "%TEST_FINISHED% time=0 testTuple2 (tupleTests)" << std::endl;

    std::cout << "%TEST_STARTED% testAdd (tupleTests)" << std::endl;
    testAdd();
    std::cout << "%TEST_FINISHED% time=0 testAdd (tupleTests)" << std::endl;

    std::cout << "%TEST_STARTED% testSize (tupleTests)" << std::endl;
    testSize();
    std::cout << "%TEST_FINISHED% time=0 testSize (tupleTests)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

