#include <stdlib.h>
#include "unity.h"
#include "LinkedList.h"
#include "AllocationPool.h"
#include "MemoryDescription.h"

void setUp(void) {}

void tearDown(void) {}

// set Allocation as global variable
Allocation *alloc = NULL;

/**
 *    ---------         ----------
 *   / alloc /  ---->  / memDesc / ------+
 *  ---------         ----------         |
 *                                      \/
 *                                    -------
 *                                   / NULL /
 *                                  -------
 */
void test_listAddLast_given_one_memory_description_should_return_one_memory_description(){
  alloc = createAllocationPool();

  listAddLast(alloc, createMallocMemDesc(1234, 400, "C:/ThisFile.c"));

  TEST_ASSERT_EQUAL(400, alloc->head->dataSize);
  TEST_ASSERT_EQUAL(1234, alloc->head->mallocLine);
  TEST_ASSERT_EQUAL("C:/ThisFile.c", alloc->head->mallocFile);
  TEST_ASSERT_EQUAL(1, alloc->noOfLinkedDesc);
  TEST_ASSERT_NULL(alloc->tail->next);
}

/**
 *    ---------         ----------        ----------
 *   / alloc /  ---->  / memDesc / ----> / memDesc / ------+
 *  ---------         ----------        ----------        |
 *                                                       |
 *                                                      \/
 *                                                   -------
 *                                                  / NULL /
 *                                                 -------
 */
void test_listAddLast_given_two_memory_description_should_return_two_memory_description(){
  alloc = createAllocationPool();

  listAddLast(alloc, createMallocMemDesc(80, 400, "C:/testFile.c"));
  listAddLast(alloc, createMallocMemDesc(102, 500, "C:/Dummy.c"));

  TEST_ASSERT_EQUAL(80, alloc->head->mallocLine);
  TEST_ASSERT_EQUAL(400, alloc->head->dataSize);
  TEST_ASSERT_EQUAL("C:/testFile.c", alloc->head->mallocFile);
  TEST_ASSERT_EQUAL(102, alloc->tail->mallocLine);
  TEST_ASSERT_EQUAL(500, alloc->tail->dataSize);
  TEST_ASSERT_EQUAL("C:/Dummy.c", alloc->tail->mallocFile);
  TEST_ASSERT_EQUAL(2, alloc->noOfLinkedDesc);
  TEST_ASSERT_NULL(alloc->tail->next);
}

void test_listAddFirst_given_one_memoryDescription_should_return_one(){
  alloc=createAllocationPool();
  
  listAddFirst(alloc, createMallocMemDesc(100, 200, "C:/Memory.c"));
  TEST_ASSERT_EQUAL(100, alloc->head->mallocLine);
  TEST_ASSERT_EQUAL(200, alloc->head->dataSize);
  TEST_ASSERT_EQUAL("C:/Memory.c", alloc->head->mallocFile);
  TEST_ASSERT_EQUAL(1, alloc->noOfLinkedDesc);
}

void test_listAddFirst_given_1_and_2_should_return_2_then_1(){
  alloc=createAllocationPool();
  
  listAddFirst(alloc, createMallocMemDesc(100, 200, "C:/Allocation.c"));
  listAddFirst(alloc, createMallocMemDesc(200, 400, "C:/Memory.c"));
  
  TEST_ASSERT_EQUAL(200, alloc->head->mallocLine);
  TEST_ASSERT_EQUAL(400, alloc->head->dataSize);
  TEST_ASSERT_EQUAL("C:/Memory.c", alloc->head->mallocFile);
  TEST_ASSERT_EQUAL(100, alloc->tail->mallocLine);
  TEST_ASSERT_EQUAL(200, alloc->tail->dataSize);
  TEST_ASSERT_EQUAL("C:/Allocation.c", alloc->tail->mallocFile);
  TEST_ASSERT_EQUAL(2, alloc->noOfLinkedDesc);
}
