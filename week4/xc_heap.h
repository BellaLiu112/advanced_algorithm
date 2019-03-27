
#ifndef _H_XC_HEAP_H
#define _H_XC_HEAP_H
#include <inttypes.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct xc_heap_node_base_s {
  signed slot_index;
} xc_heap_node_base_t;

/*
* max heap node1 < node2
* min heap node1 > node2
*/
typedef bool(*heap_node_compare_pt)(xc_heap_node_base_t *node1, xc_heap_node_base_t *node2);
typedef void(*heap_node_free_pt)(void *node);

typedef struct xc_heap_s {
  xc_heap_node_base_t  **slots;
  unsigned               capacity, size;
  heap_node_compare_pt   compare;
  heap_node_free_pt      free;
} xc_heap_t;

void xc_heap_init(xc_heap_t *h, 
                  heap_node_compare_pt compare,
                  heap_node_free_pt free_pt);

static inline unsigned xc_heap_size(xc_heap_t *h) { return h->size; };

void xc_heap_free(xc_heap_t *h);

xc_heap_node_base_t *xc_heap_top(xc_heap_t *h);

xc_heap_node_base_t *xc_heap_pop(xc_heap_t *h);

int xc_heap_push(xc_heap_t *h, xc_heap_node_base_t *node);

int xc_heap_erase(xc_heap_t *h, xc_heap_node_base_t *node);

#ifdef __cplusplus
}
#endif

#endif //_H_XC_HEAP_H
