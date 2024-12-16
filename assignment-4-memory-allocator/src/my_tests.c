//
// Created by maxim on 13.12.24.
//

#include "my_tests.h"
#include "mem.h"
#include <stdio.h>

static bool simple_alloc() {
    void* block = _malloc(128);

    if (!block) {
        return false;
    }
    _free(block);

    return true;
}

static bool free_one_block() {
    void* first = _malloc(128);
    void* second = _malloc(256);

    if (!first || !second) {
        return false;
    }
    _free(first);

    return true;
}

static bool free_two_blocks() {
    void* first = _malloc(128);
    void* second = _malloc(256);
    void* third = _malloc(64);
    void* forth = _malloc(1024);
    void* fifth = _malloc(2048);

    if (!first || !second || !third || !forth || !fifth) {
        return false;
    }
    _free(first);
    _free(second);

    return true;
}

static bool extended_region() {
    void* first = _malloc(1024);
    void* second = _malloc(1024);

    if (!first || !second) {
        return false;
    }
    _free(first);
    _free(second);

    return true;
}

static bool new_region_in_other_place() {
    void* first = _malloc(1024);
    void* second = _malloc(1024);
    void* third = _malloc(1024);

    if (!first || !second || !third) {
        return false;
    }
    _free(first);
    _free(second);
    _free(third);

    return true;
}


bool test_all() {
    heap_init(1024);

    bool success = true;
    success &= simple_alloc();
    success &= free_one_block();
    success &= free_two_blocks();
    success &= extended_region();
    success &= new_region_in_other_place();

    if (success) {
        printf("All tests passed\n");
    } else {
        printf("Not all tests passed\n");
    }
    heap_term();

    return success;
}

