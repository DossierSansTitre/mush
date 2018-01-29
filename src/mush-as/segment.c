#include <assembler.h>

static void realloc_segment(segment* seg)
{
    size_t new_cap;

    new_cap = seg->capacity + seg->capacity / 2;
    seg->buffer = realloc(seg->buffer, new_cap);
    seg->capacity = new_cap;
}

static void realloc_if_needed(segment* seg, size_t needed)
{
    size_t new_size;

    new_size = seg->size + needed;
    while (new_size > seg->capacity)
        realloc_segment(seg);
}

segment* segment_init()
{
    segment* seg;

    seg = malloc(sizeof(segment));
    seg->buffer = malloc(256);
    seg->size = 0;
    seg->capacity = 256;

    return seg;
}

void segment_free(segment* seg)
{
    free(seg->buffer);
    free(seg);
}

void segment_append8(segment* seg, uint8_t value)
{
    realloc_if_needed(seg, 1);
    *(uint8_t*)(seg->buffer + seg->size) = value;
    seg->size += 1;
}

void segment_append16(segment* seg, uint16_t value)
{
    realloc_if_needed(seg, 2);
    *(uint16_t*)(seg->buffer + seg->size) = value;
    seg->size += 2;
}

void segment_append32(segment* seg, uint32_t value)
{
    realloc_if_needed(seg, 4);
    *(uint32_t*)(seg->buffer + seg->size) = value;
    seg->size += 4;
}

void segment_append64(segment* seg, uint64_t value)
{
    realloc_if_needed(seg, 8);
    *(uint64_t*)(seg->buffer + seg->size) = value;
    seg->size += 8;
}
