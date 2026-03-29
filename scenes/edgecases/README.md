miniRT Parser Edge Cases

Usage:
- Run each file independently with ./miniRT scenes/edgecases/<file>.rt
- PASS means parser should accept the file.
- FAIL means parser should reject the file cleanly (no crash, no leaks, clear error).

PASS cases:
- 01_valid_minimal.rt
- 02_valid_whitespace.rt
- 03_valid_decimal_formats.rt

FAIL cases:
- 10_missing_tokens_A.rt
- 11_extra_tokens_C.rt
- 12_non_numeric_values.rt
- 13_overflow_float.rt
- 14_nan_inf_tokens.rt
- 15_bad_rgb_separator.rt
- 16_rgb_out_of_range.rt
- 17_negative_or_zero_sizes.rt
- 18_zero_normal_vector.rt
- 19_duplicate_singletons.rt
- 20_unknown_identifier.rt
- 21_malformed_vector.rt
- 22_truncated_line.rt
- 23_huge_numeric_token.rt