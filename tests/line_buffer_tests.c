#include "common_test.h"
#include "line_buffer_tests.h"
#include "../src/line_buffer.h"

START_TEST(test_line_buffer_create)
{
    line_buffer *buf;
    buf = line_buffer_create(10);
    ck_assert_int_eq(line_buffer_max_lines(buf), 10);
    line_buffer_destroy(buf);
}
END_TEST
START_TEST(test_line_buffer_add_data)
{
    // Arrange.
    line_buffer *buf;
    buf = line_buffer_create(4);

    // Act.
    const color_char test_str[] = {'h', 'e', 'l', 'l', 'o', '\n', 'w', 'o', 'r', 'l', 'd', '\n', 't', 'h', 'i', 's', '\n', 'i', 's', '\n', 'a', '\n', 't', 'e', 's', 't'};
    line_buffer_write(buf, test_str, 26);

    // Assert.
    color_string *expected_line0 = color_string_create_from_c_string(256, "test");
    ck_assert(memcmp(line_buffer_get_line_relative_to_current(buf, 0)->_data, expected_line0->_data, sizeof(color_char) * color_string_length(expected_line0)) == 0);
    color_string *expected_line1 = color_string_create_from_c_string(256, "a");
    ck_assert(memcmp(line_buffer_get_line_relative_to_current(buf, 1)->_data, expected_line1->_data, sizeof(color_char) * color_string_length(expected_line1)) == 0);
    color_string *expected_line2 = color_string_create_from_c_string(256, "is");
    ck_assert(memcmp(line_buffer_get_line_relative_to_current(buf, 2)->_data, expected_line2->_data, sizeof(color_char) * color_string_length(expected_line2)) == 0);
    color_string *expected_line3 = color_string_create_from_c_string(256, "this");
    ck_assert(memcmp(line_buffer_get_line_relative_to_current(buf, 3)->_data, expected_line3->_data, sizeof(color_char) * color_string_length(expected_line3)) == 0);

    // Clean up.
    color_string_destroy(expected_line0);
    color_string_destroy(expected_line1);
    color_string_destroy(expected_line2);
    color_string_destroy(expected_line3);
    line_buffer_destroy(buf);
}
END_TEST

// Suite creation.
Suite *make_line_buffer_suite(void)
{
    Suite *s = suite_create("Line buffer");
    ADD_TEST_TO_SUITE(test_line_buffer_create, s);
    ADD_TEST_TO_SUITE(test_line_buffer_add_data, s);

    return s;
}
