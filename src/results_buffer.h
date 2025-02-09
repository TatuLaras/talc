#ifndef _RESULTS_BUF
#define _RESULTS_BUF

#define RESULTS_BUFFER_SIZE 64

typedef struct {
    double result;
    char *expression;
    int erroneous;
} Result;

typedef struct {
    Result __data[RESULTS_BUFFER_SIZE];
    int __current;
    int count;
} ResultsBuffer;

// Appends a new result into the result buffer
void results_buffer_push(ResultsBuffer *buffer, Result result);

// Gets the i:th latest result from the buffer
//
// Returns 1 if there is no item there
int results_buffer_get_latest(ResultsBuffer *buffer, int i, Result *out_result);

void results_buffer_clear(ResultsBuffer *buffer);

#endif
