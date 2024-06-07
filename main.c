#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#define MAX_NUM 1000

void count_remaining_numbers(int array[], int size, int count[]) {
    int i;
    for (i = 0; i < size; i++) {
        count[array[i] + MAX_NUM]++; // Индекс в массиве сдвинут на MAX_NUM, чтобы можно было использовать отрицательные индексы
    }
    for (i = 0; i < MAX_NUM * 2 + 1; i++) {
        if (count[i] > 0) {
            int opposite = -(i - MAX_NUM);
            if (count[opposite + MAX_NUM] > 0) {
                int minCount = (count[i] < count[opposite + MAX_NUM]) ? count[i] : count[opposite + MAX_NUM];
                count[i] -= minCount;
                count[opposite + MAX_NUM] -= minCount;
            }
        }
    }
}

// Тесты
void test_count_remaining_numbers(void) {
    int array[] = {3, 1, -1, 2, -2, 4, 3, -4, 1, 5};
    int size = sizeof(array) / sizeof(array[0]);
    int count[MAX_NUM * 2 + 1] = {0};
    int expected_count[MAX_NUM * 2 + 1] = {0};
    expected_count[3 + MAX_NUM] = 2;
    expected_count[1 + MAX_NUM] = 0;
    expected_count[2 + MAX_NUM] = 2;
    expected_count[4 + MAX_NUM] = 0;
    expected_count[5 + MAX_NUM] = 1;

    count_remaining_numbers(array, size, count);

    for (int i = 0; i < MAX_NUM * 2 + 1; i++) {
        CU_ASSERT_EQUAL(count[i], expected_count[i]);
    }
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("count_remaining_numbers_test", 0, 0);

    CU_add_test(suite, "test_count_remaining_numbers", test_count_remaining_numbers);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}