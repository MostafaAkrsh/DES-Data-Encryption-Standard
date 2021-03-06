#include "bits/stdc++.h"
#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#endif
using namespace std;

#define ROUNDS_NUMBER 16


const int IP[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
					 60, 52, 44, 36, 28, 20, 12, 4,
					 62, 54, 46, 38, 30, 22, 14, 6,
					 64, 56, 48, 40, 32, 24, 16, 8,
					 57, 49, 41, 33, 25, 17, 9,  1,
					 59, 51, 43, 35, 27, 19, 11, 3,
					 61, 53, 45, 37, 29, 21, 13, 5,
					 63, 55, 47, 39, 31, 23, 15, 7 };


const int FP[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
					  39, 7, 47, 15, 55, 23, 63, 31,
					  38, 6, 46, 14, 54, 22, 62, 30,
					  37, 5, 45, 13, 53, 21, 61, 29,
					  36, 4, 44, 12, 52, 20, 60, 28,
					  35, 3, 43, 11, 51, 19, 59, 27,
					  34, 2, 42, 10, 50, 18, 58, 26,
					  33, 1, 41,  9, 49, 17, 57, 25 };


const int EP[48] = { 32,  1,  2,  3,  4,  5,
					  4,  5,  6,  7,  8,  9,
					  8,  9, 10, 11, 12, 13,
					 12, 13, 14, 15, 16, 17,
					 16, 17, 18, 19, 20, 21,
					 20, 21, 22, 23, 24, 25,
					 24, 25, 26, 27, 28, 29,
					 28, 29, 30, 31, 32,  1 };

const int SBOX[8][4][16] =
{ {
	14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
	0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
	4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
	15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
},
{
	15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
	3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
	0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
	13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
},


{
	10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
	13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
	13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
	1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
},
{
	7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
	13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
	10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
	3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
},
{
	2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
	14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
	4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
	11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
},
{
	12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
	10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
	9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
	4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
},
{
	4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
	13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
	1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
	6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
},
{
	13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
	1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
	7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
	2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
} };

const int PC_1[56] = { 57, 49, 41, 33, 25, 17,  9,
						1, 58, 50, 42, 34, 26, 18,
					   10,  2, 59, 51, 43, 35, 27,
					   19, 11,  3, 60, 52, 44, 36,
					   63, 55, 47, 39, 31, 23, 15,
						7, 62, 54, 46, 38, 30, 22,
					   14,  6, 61, 53, 45, 37, 29,
					   21, 13,  5, 28, 20, 12,  4 };

const int PC_2[48] = { 14, 17, 11, 24,  1,  5,
						3, 28, 15,  6, 21, 10,
					   23, 19, 12,  4, 26,  8,
					   16,  7, 27, 20, 13,  2,
					   41, 52, 31, 37, 47, 55,
					   30, 40, 51, 45, 33, 48,
					   44, 49, 39, 56, 34, 53,
					   46, 42, 50, 36, 29, 32 };


const int P[32] = { 16, 7, 20, 21, 29, 12, 28, 17,
				   1, 15, 23, 26, 5, 18, 31, 10,
				   2, 8, 24, 14, 32, 27, 3, 9,
				   19, 13, 30, 6, 22, 11, 4, 25 };


const int shift_table[16] = { 1, 1, 2, 2,
							  2, 2, 2, 2,
							  1, 2, 2, 2,
							  2, 2, 2, 1 };

typedef unsigned long long u64;

u64 read_DES_input(string data)
{
	u64 value = 0;

	for (int i = 0; i < 16; ++i)
	{
		char c = data[i];

		if (c >= '0' && c <= '9')
		{
			value |= (u64)(c - '0') << ((15 - i) << 2);
		}
		else if (c >= 'A' && c <= 'F')
		{
			value |= (u64)(c - 'A' + 10) << ((15 - i) << 2);
		}
		else if (c >= 'a' && c <= 'f')
		{
			value |= (u64)(c - 'a' + 10) << ((15 - i) << 2);
		}
	}
	return value;
}


u64 Initial_Permutations(u64 input)
{
	u64 output = 0;

	int n = 64;

	for (int i = 0; i < n; i++)
	{
		output |= (input >> (n - IP[n - i - 1]) & 1) << i;
	}
	return output;
}

u64 Final_Permutations(u64 input)
{
	u64 output = 0;

	int n = 64;

	for (int i = 0; i < n; i++)
	{
		output |= (input >> (n - FP[n - i - 1]) & 1) << i;
	}

	return output;
}

u64 Expansion_Permutations(u64 input)
{
	u64 output = 0;

	int n = 32;
	int m = 48;

	for (int i = 0; i < m; i++) {
		output |= (input >> (n - EP[m - i - 1]) & 1) << i;
	}
	return output;
}

u64 Permutations(u64 input)
{
	u64 output = 0;

	int n = 32;

	for (int i = 0; i < n; i++)
		output |= (input >> (n - P[n - i - 1]) & 1) << i;
	return output;
}

u64 S_Box(u64 input)
{
	u64 output = 0;
	for (int i = 0; i < 8; i++) {

		int byte = (input >> (42 - 6 * (i))) & 0x3F;
		int row_index = (byte & 0x01) | (byte & 0x20) >> 4;
		int col_index = (byte & 0x1E) >> 1;
		output |= SBOX[i][row_index][col_index] << (4 * (7 - i));
	}

	return output;
}

u64 Permuted_Choice_1(u64 input)
{
	u64 output = 0;

	int n = 64;
	int m = 56;

	for (int i = 0; i < m; i++) {
		output |= (input >> (n - PC_1[m - i - 1]) & 1) << i;
	}
	return output;
}

u64 Permuted_Choice_2(u64 input)
{
	u64 output = 0;

	int n = 56;
	int m = 48;

	for (int i = 0; i < m; i++) {
		output |= (input >> (n - PC_2[m - i - 1]) & 1) << i;
	}
	return output;
}

vector<u64> Generate_Subkeys(u64 key) {

	key = Permuted_Choice_1(key);

	vector<u64> subkeys;

	u64 left, right, newLeft, newRight, temp_key, new_key = 0;

	for (int i = 0; i < 16; i++) {
		if (i == 0)
		{
			left = key & 0xFFFFFFF0000000;
			right = key & 0x0000000FFFFFFF;
		}
		else
		{
			left = temp_key & 0xFFFFFFF0000000;
			right = temp_key & 0x0000000FFFFFFF;
		}
		if (shift_table[i] == 1)
		{
			newLeft = left << 1;
			newLeft = (newLeft & 0xFFFFFFF0000000) | (left & 0x80000000000000) >> 27;
			newRight = right << 1;
			newRight = (newRight & 0x0000000FFFFFFF) | (right & 0x00000008000000) >> 27;
		}
		else if (shift_table[i] == 2)
		{
			newLeft = left << 2;
			newLeft = (newLeft & 0xFFFFFFF0000000) | (left & 0xC0000000000000) >> 26;
			newRight = right << 2;
			newRight = (newRight & 0x0000000FFFFFFF) | (right & 0x0000000C000000) >> 26;
		}
		temp_key = newLeft | newRight;

		u64 new_key = Permuted_Choice_2(temp_key);

		subkeys.push_back(new_key);
	}

	return subkeys;
}


int main(int argc, char** argv)
{
	string choice = argv[1];
	if (choice == "encrypt")
	{

		string keystring = argv[3];
		u64 key = 0;
		key = read_DES_input(keystring);

		vector<u64> subkeys;
		subkeys = Generate_Subkeys(key);

		string plainstring = argv[2];

		u64 plain = 0;
		plain = read_DES_input(plainstring);

		long long t1 = __rdtsc();

		u64 left, right, encrypted = 0;

		plain = Initial_Permutations(plain);

		left = plain & 0xFFFFFFFF00000000;
		right = plain & 0x00000000FFFFFFFF;

		u64 round_output, ep_output, xor_output, sbox_output, p_output, previous_left = 0;

		for (int i = 0; i < 16; i++) {

			ep_output = Expansion_Permutations(right);
			xor_output = ep_output ^ subkeys[i];

			sbox_output = S_Box(xor_output);

			p_output = Permutations(sbox_output);

			previous_left = left;

			left = right << 32;

			right = p_output ^ previous_left >> 32;

			round_output = left | right;
		}

		left = round_output & 0x00000000FFFFFFFF;
		right = round_output & 0xFFFFFFFF00000000;

		encrypted = left << 32 | right >> 32;
		encrypted = Final_Permutations(encrypted);
		long long t2 = __rdtsc();

		printf("cipher: %016llX\n", encrypted);

		printf("Cycles: %lld\n", t2 - t1);
	}

	else if (choice == "decrypt")
	{

		string keystring = argv[3];
		u64 key = 0;
		key = read_DES_input(keystring);

		vector<u64> subkeys;
		subkeys = Generate_Subkeys(key);
		reverse(subkeys.begin(), subkeys.end());

		string plainstring = argv[2];
		u64 plain = 0;
		plain = read_DES_input(plainstring);

		long long t1 = __rdtsc();

		u64 left, right, decrypted = 0;

		plain = Initial_Permutations(plain);

		left = plain & 0xFFFFFFFF00000000;
		right = plain & 0x00000000FFFFFFFF;

		u64 round_output, ep_output, xor_output, sbox_output, p_output, previous_left = 0;

		for (int i = 0; i < 16; i++) {

			ep_output = Expansion_Permutations(right);
			xor_output = ep_output ^ subkeys[i];

			sbox_output = S_Box(xor_output);

			p_output = Permutations(sbox_output);

			previous_left = left;

			left = right << 32;

			right = p_output ^ previous_left >> 32;

			round_output = left | right;
		}

		left = round_output & 0x00000000FFFFFFFF;
		right = round_output & 0xFFFFFFFF00000000;

		decrypted = left << 32 | right >> 32;
		decrypted = Final_Permutations(decrypted);

		long long t2 = __rdtsc();
		printf("plain: %016llX\n", decrypted);

		printf("Cycles: %lld\n", t2 - t1);
	}

	else
	{
		cout << "Invalid";
	}

	return 0;
}
