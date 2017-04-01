/*
 * main.c
 *
 *  Created on: Mar 31, 2017
 *      Author: okleinfeld
 */

#include <stdio.h>
#define CHAR_LIMIT 100

int check_char_valid(int, char);
int convert_char_to_digit(char);
int convert_num_to_decimal_base(int, char *);
char convert_digit_to_char(int);
int convert_decimal_to_base(int, int, char *);

int main() {
	int in_base, out_base;
	int scan_res;
	int decimal_num;
	char in_num[CHAR_LIMIT];
	char out_num[CHAR_LIMIT];
	int output_digits;
	printf("Please enter the number's base:\n");
	scan_res = scanf("%d", &in_base);
	if (scan_res == 0 || in_base > 16 || in_base < 2) {
		printf("Invalid input base\n");
		return 0;
	}
	printf("Please enter the desired base:\n");
	scan_res = scanf("%d", &out_base);
	if (scan_res == 0 || out_base > 16 || out_base < 2) {
		printf("Invalid input base\n");
		return 0;
	}
	printf("Please enter a number in base %d:\n", in_base);
	scanf("%s", in_num);
	decimal_num = convert_num_to_decimal_base(in_base, in_num);
	if (decimal_num == -1) {
		return 0;
	}
	output_digits = convert_decimal_to_base(out_base, decimal_num, out_num);
	printf("The result is: ");
	while (output_digits >= 0) {
		printf("%c", out_num[output_digits]);
		output_digits--;
	}
	printf("\n");
	return 1;
}

int check_char_valid(int base, char c) {
	int ascii_c = c;
	if (ascii_c >= 48 && ascii_c <= 57) { // the character is a number between 0 and 9
		ascii_c -= 48;
		return (ascii_c < base); // check if the digit is less than base - e.g belongs to base
	}
	if (ascii_c >= 65 && ascii_c <= 70) { // the character is an upper case digit between A and F
		if (base <= 10) { //base doesn't allow using letters
			return 0;
		}
		int base_uppercase_max = base - 10 + 64; // compute the biggest uppers case letter allowed by base
		return (ascii_c <= base_uppercase_max);
	}
	if (ascii_c >= 97 && ascii_c <= 102) { // the character is a a lower case digit between a and f
		if (base <= 10) { // base doesn't allow using letters
			return 0;
		}
		int base_lowercase_max = base - 10 + 96; //  compute the biggest lower case letter allowed by base
		return (ascii_c <= base_lowercase_max);
	}
	return 0; // if the character is not anywhere that range than is it an invalid character
}

int convert_char_to_digit(char c) {
	int res_digit = -99;
	if (c >= 48 && c <= 57) { // c is a number
		res_digit = c - 48;
	}
	if (c >= 65 && c <= 70) { // c is an upper case letter
		res_digit = c - 65 + 10;
	}
	if (c >= 97 && c <= 102) { // c is a lower case letter
		res_digit = c - 97 + 10;
	}
	return res_digit;
}

int convert_num_to_decimal_base(int base, char * str) {
	int decimal_num = 0;
	int i = 0;
	while (str[i] != '\0') {
		char curr_digit = str[i];
		if (check_char_valid(base, curr_digit) == 0) {
			printf("Invalid number!\n");
			return -1;
		} else {
			decimal_num = base * decimal_num
					+ convert_char_to_digit(curr_digit);
		}
		i++;
	}
	return decimal_num;
}

char convert_digit_to_char(int digit) {
	if (digit >= 0 && digit <= 9) { // the character representing this digit is also a digit
		return 48 + digit;
	}
	// the character representing this digit is a letter
	return digit - 10 + 65;
}

int convert_decimal_to_base(int base, int num, char *array) {
	int i = 0;
	while (num != 0) {
		array[i] = convert_digit_to_char(num % base);
		num = num / base;
		i++;
	}
	return i - 1;
}
