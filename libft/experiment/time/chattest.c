#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_STRUCTS 100000

typedef struct {
    void *x;
    void *y;
} Point;

void copy_point_by_value(Point p) {
    // Do nothing
	(void)p;
}

void copy_point_by_pointer(const Point *p) {
    // Do nothing
	(void)p;
}

int main() {
    Point points[NUM_STRUCTS];
    clock_t start_time, end_time;
    double copy_by_value_time, copy_by_pointer_time;
    int i;

    // Initialize the array of points
    for (i = 0; i < NUM_STRUCTS; i++) {
        points[i].x = (void *)(long)rand();
        points[i].y = (void *)(long)rand();
    }

    // Measure the time to copy the array of points by value
    start_time = clock();
    for (i = 0; i < NUM_STRUCTS; i++) {
        copy_point_by_value(points[i]);
    }
    end_time = clock();
    copy_by_value_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    // Measure the time to copy the array of points by pointer
    start_time = clock();
    for (i = 0; i < NUM_STRUCTS; i++) {
        copy_point_by_pointer(&points[i]);
    }
    end_time = clock();
    copy_by_pointer_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    // Print the results
    dprintf(2, "Time to copy %d points by value: %f seconds\n", NUM_STRUCTS, copy_by_value_time);
    dprintf(2, "Time to copy %d points by pointer: %f seconds\n", NUM_STRUCTS, copy_by_pointer_time);

    return 0;
}
