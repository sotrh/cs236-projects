/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   relationTests.cpp
 * Author: benjamin
 *
 * Created on February 24, 2016, 9:03 PM
 */

#include <stdlib.h>
#include <iostream>
#include "Relation.h"

/*
 * Simple C++ Test Suite
 */

void testSelect()
{
    unsigned p0 = 0;
    string& p1 = "1";
    
    Relation relation("test", {"a", "b"});
    relation.add(Tuple({"1", "1"}));
    relation.add(Tuple({"0", "1"}));
    relation.add(Tuple({"1", "2"}));
    relation.add(Tuple({"1", "3"}));
    relation.add(Tuple({"0", "2"}));
    
    Relation result = relation.select(p0, p1);
    if (true /*check result*/)
    {
	std::cout << "%TEST_FAILED% time=0 testname=testSelect (relationTests) message=error message sample" << std::endl;
    }
}

void testSelect2()
{
    unsigned p0;
    unsigned p1;
    Relation relation;
    Relation result = relation.select(p0, p1);
    if (true /*check result*/)
    {
	std::cout << "%TEST_FAILED% time=0 testname=testSelect2 (relationTests) message=error message sample" << std::endl;
    }
}

void testProject()
{
    vector<unsigned>& p0;
    Relation relation;
    Relation result = relation.project(p0);
    if (true /*check result*/)
    {
	std::cout << "%TEST_FAILED% time=0 testname=testProject (relationTests) message=error message sample" << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "%SUITE_STARTING% relationTests" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testSelect (relationTests)" << std::endl;
    testSelect();
    std::cout << "%TEST_FINISHED% time=0 testSelect (relationTests)" << std::endl;

    std::cout << "%TEST_STARTED% testSelect2 (relationTests)" << std::endl;
    testSelect2();
    std::cout << "%TEST_FINISHED% time=0 testSelect2 (relationTests)" << std::endl;

    std::cout << "%TEST_STARTED% testProject (relationTests)" << std::endl;
    testProject();
    std::cout << "%TEST_FINISHED% time=0 testProject (relationTests)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

