#include "results_buffer.h"

static int wrap_index(int i, int i_max) {
    return ((i % i_max) + i_max) % i_max;
}

void results_buffer_push(ResultsBuffer *buffer, Result result) {
    buffer->__data[(buffer->__current++) % RESULTS_BUFFER_SIZE] = result;
    buffer->count++;
}

int results_buffer_get_latest(ResultsBuffer *buffer, int i,
                              Result *out_result) {
    if (i >= buffer->count || i >= RESULTS_BUFFER_SIZE)
        return 1;

    *out_result = buffer->__data[wrap_index(buffer->__current - 1 - i,
                                            RESULTS_BUFFER_SIZE)];

    return 0;
}
