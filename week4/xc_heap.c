

#include "xc_heap.h"
#include <stdlib.h>

void xc_heap_init(xc_heap_t *h,
  heap_node_compare_pt compare,
  heap_node_free_pt free_pt)
{
  h->slots = 0;
  h->size = 0;
  h->capacity = 0;
  h->compare = compare;
  h->free = free_pt;
}

void xc_heap_free(xc_heap_t *h)
{
  unsigned i;
  if (h->free) {
    for (i = 0; i < h->size; ++i)
      h->free(h->slots[i]);
  }
  free(h->slots);
}

static int 
xc_heap_reserve(xc_heap_t* h, unsigned n)
{
  if (h->capacity < n)
  {
    xc_heap_node_base_t** p;
    unsigned capacity = h->capacity ? (h->capacity << 1) : 8;
    if (capacity < n)
      capacity = n;
    if (!(p = (xc_heap_node_base_t **)realloc(h->slots, capacity * sizeof *p)))
      return -1;
    h->slots = p;
    h->capacity = capacity;
  }
  return 0;
}

static void 
xc_heap_shift_up(xc_heap_t *h, unsigned slot_index, xc_heap_node_base_t *node)
{
  unsigned parent = (slot_index - 1) / 2;
  while (slot_index && h->compare(h->slots[parent], node)) {
    (h->slots[slot_index] = h->slots[parent])->slot_index = slot_index;
    slot_index = parent;
    parent = (slot_index - 1) / 2;
  }
  (h->slots[slot_index] = node)->slot_index = slot_index;
}

static void
xc_heap_shift_up_fast(xc_heap_t *h, unsigned slot_index, xc_heap_node_base_t *node)
{
  unsigned parent = (slot_index - 1) / 2;
  do {
    (h->slots[slot_index] = h->slots[parent])->slot_index = slot_index;
    slot_index = parent;
    parent = (slot_index - 1) / 2;
  } while (slot_index && h->compare(h->slots[parent], node));
  (h->slots[slot_index] = node)->slot_index = slot_index;
}

static 
void xc_heap_shift_down(xc_heap_t *h, unsigned slot_index, xc_heap_node_base_t *node)
{
  unsigned smaller_child = (slot_index + 1) << 1;
  while (smaller_child <= h->size) {
    smaller_child -= (smaller_child == h->size ||
      h->compare(h->slots[smaller_child], h->slots[smaller_child - 1]));
    if (!h->compare(node, h->slots[smaller_child])) {
      break;
    }
    (h->slots[slot_index] = h->slots[smaller_child])->slot_index = slot_index;
    slot_index = smaller_child;
    smaller_child = (slot_index + 1) << 1;
  }
  (h->slots[slot_index] = node)->slot_index = slot_index;
}

xc_heap_node_base_t *xc_heap_top(xc_heap_t *h)
{
  return h->size ? *h->slots : NULL;
}

xc_heap_node_base_t *xc_heap_pop(xc_heap_t *h)
{
  if (h->size) {
    xc_heap_node_base_t * node = *h->slots;
    xc_heap_shift_down(h, 0, h->slots[--h->size]);
    node->slot_index = -1;
    return node;
  }
  return NULL;
}

int xc_heap_push(xc_heap_t *h, xc_heap_node_base_t *node)
{
  if (xc_heap_reserve(h, h->size + 1)) {
    return -1;
  }

  xc_heap_shift_up(h, h->size++, node);
  return 0;
}

int xc_heap_erase(xc_heap_t *h, xc_heap_node_base_t *node)
{
  if (node->slot_index >= 0 && node->slot_index < h->size) {
    xc_heap_node_base_t *last = h->slots[--h->size];
    signed parent = (node->slot_index - 1) >> 1;
    if (node->slot_index > 0 && h->compare(h->slots[parent], last)) {
      xc_heap_shift_up_fast(h, (unsigned)node->slot_index, last);
    } else {
      xc_heap_shift_down(h, (unsigned)node->slot_index, last);
    }
    node->slot_index = -1;
    return 0;
  }

  return -1;
}
