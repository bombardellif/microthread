/*
 * File:   ListTest.c
 * Author: william
 *
 * Created on Apr 18, 2014, 6:00:56 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "List.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testCheckRep() {
    List* listDescriber;
    boolean result = listCheckRep(listDescriber);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testFreeList() {
    List* listDescriber;
    freeList(listDescriber);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testListAdd() {
    List* listDescriber;
    void* e;
    listAdd(listDescriber, e, intPointerCompare);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testListAppend() {
    List* listDescriber;
    void* e;
    listAppend(listDescriber, e);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testListGet() {
    List* listDescriber;
    void* e;
    void* result = listGet(listDescriber, e, intPointerCompare);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testListRemove() {
    List* listDescriber;
    void* e;
    listRemove(listDescriber, e, intPointerCompare);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testNewList() {
    List* listDescriber;
    List* result = newList(listDescriber);
    
    if (1 /*check result*/) {
        CU_ASSERT(listDescriber == result);
        listCheckRep(listDescriber);
    }
}

void* listGetElement(List* listDescriber, void* e, int(*comparator)(void*, void*));

void testListGetElement() {
    List* listDescriber;
    void* e;
    void* result = listGetElement(listDescriber, e, intPointerCompare);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("ListTest", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testCheckRep", testCheckRep)) ||
            (NULL == CU_add_test(pSuite, "testFreeList", testFreeList)) ||
            (NULL == CU_add_test(pSuite, "testListAdd", testListAdd)) ||
            (NULL == CU_add_test(pSuite, "testListAppend", testListAppend)) ||
            (NULL == CU_add_test(pSuite, "testListGet", testListGet)) ||
            (NULL == CU_add_test(pSuite, "testListRemove", testListRemove)) ||
            (NULL == CU_add_test(pSuite, "testNewList", testNewList)) ||
            (NULL == CU_add_test(pSuite, "testListGetElement", testListGetElement))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
