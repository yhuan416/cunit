/*
 * Message handler internal functions
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "CUnit/InternalPoolMalloc.h"
#include "CUnit/MessageHandlers.h"



static CCU_MessageHandler* handlers[CUMSG_MAX];

static CCU_MessageHandler* alloc_MessageHandler(void) {
    CCU_MessageHandler *new;
    new = Internal_CU_StaticMalloc(sizeof(*new));
    assert(new && "CUnit: Out of memory in alloc_MessageHandler");
    memset(new, 0, sizeof(*new));
    return new;
}

static CCU_MessageHandler* clone_MessageHandler(const CCU_MessageHandler *in) {
    CCU_MessageHandler *copy = alloc_MessageHandler();
    *copy = *in;
    return copy;
}

static void _free_MessageHandler(CCU_MessageHandler* ptr)
{
    if (ptr) {
        if (ptr->prev) {
            ptr->prev->next = NULL;
        }
        _free_MessageHandler(ptr->next);
        Internal_CU_StaticFree(ptr);
    }
}

void CCU_MessageHandler_Add(CCU_MessageType type, const CCU_MessageHandler *handler) {
    CCU_MessageHandler *head;
    CCU_MessageHandler *new;

    new = clone_MessageHandler(handler);
    new->type = type;

    if (!handlers[type]) {
        // no list at all, add first entry
        head = new;
        head->tail = head;
        handlers[type] = head;
    } else {
        // append to list for this message
        head = handlers[type];
        if (!head->tail) head->tail = head;
        head->tail->next = new;
        new->prev = head->tail;
        head->tail = new;
    }
}

void CCU_MessageHandler_Clear(CCU_MessageType type)
{
    CCU_MessageHandler *head = handlers[type];
    _free_MessageHandler(head);
    handlers[type] = NULL;
}

void CCU_MessageHandler_Set(CCU_MessageType type, const CCU_MessageHandler *handler)
{
    CCU_MessageHandler_Clear(type);
    if (handler && handler->func.suite_start) {
        CCU_MessageHandler_Add(type, handler);
    }
}

static void _run_MessageHandler(CCU_MessageHandler *handler,
                                CU_pSuite pSuite,
                                CU_pTest pTest,
                                CU_pFailureRecord pFailure)
{
    if (!handler) return;
    if (!handler->func.suite_start) return;

    switch (handler->type) {
        case CUMSG_SUITE_STARTED:
            handler->func.suite_start(pSuite);
            break;
        case CUMSG_SUITE_TEARDOWN_FAILED:
            handler->func.suite_teardown_failed(pSuite);
            break;
        case CUMSG_SUITE_SETUP_FAILED:
            handler->func.suite_setup_failed(pSuite);
            break;
        case CUMSG_SUITE_COMPLETED:
            handler->func.suite_completed(pSuite, pFailure);
            break;
        case CUMSG_TEST_STARTED:
            handler->func.test_started(pTest, pSuite);
            break;
        case CUMSG_TEST_SKIPPED:
            handler->func.test_skipped(pTest, pSuite);
            break;
        case CUMSG_TEST_COMPLETED:
            handler->func.test_completed(pTest, pSuite, pFailure);
            break;
        case CUMSG_ALL_COMPLETED:
            handler->func.all_completed(pFailure);
            break;
        default:
            break;
    }
}

void CCU_MessageHandler_Run(CCU_MessageType type,
                            CU_pSuite pSuite,
                            CU_pTest pTest,
                            CU_pFailureRecord pFailure)
{
    CCU_MessageHandler *handler = handlers[type];
    while (handler) {
        _run_MessageHandler(handler, pSuite, pTest, pFailure);
        handler = handler->next;
    }
}

CCU_MessageHandler* CCU_MessageHandler_Get(CCU_MessageType type)
{
    CCU_MessageHandler *handler = handlers[type];
    return handler;
}
