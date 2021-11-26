#include "bits/stdc++.h"

#define ROUNDS_NUMBER 16

using namespace std;


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

string Hex_to_Bin(string hex)
{
	string bin = "";

	unordered_map<char, string> m;

	m['0'] = "0000";
	m['1'] = "0001";
	m['2'] = "0010";
	m['3'] = "0011";
	m['4'] = "0100";
	m['5'] = "0101";
	m['6'] = "0110";
	m['7'] = "0111";
	m['8'] = "1000";
	m['9'] = "1001";
	m['A'] = "1010";
	m['B'] = "1011";
	m['C'] = "1100";
	m['D'] = "1101";
	m['E'] = "1110";
	m['F'] = "1111";

	for (int i = 0; i < hex.size(); i++) {
		bin += m[hex[i]];
	}

	return bin;
}

string Bin_to_Hex(string bin)
{
	string hex = "";
	unordered_map<string, string> m;
	m["0000"] = "0";
	m["0001"] = "1";
	m["0010"] = "2";
	m["0011"] = "3";
	m["0100"] = "4";
	m["0101"] = "5";
	m["0110"] = "6";
	m["0111"] = "7";
	m["1000"] = "8";
	m["1001"] = "9";
	m["1010"] = "A";
	m["1011"] = "B";
	m["1100"] = "C";
	m["1101"] = "D";
	m["1110"] = "E";
	m["1111"] = "F";
	for (int i = 0; i < bin.size(); i += 4) {
		string ch = "";
		ch += bin[i];
		ch += bin[i + 1];
		ch += bin[i + 2];
		ch += bin[i + 3];
		hex += m[ch];
	}

	return hex;
}

string Bin_to_Dec(string bin)
{
	string dec = "";
	unordered_map<string, string> m;
	m["00"] = "0";
	m["01"] = "1";
	m["10"] = "2";
	m["11"] = "3";

	m["0000"] = "0";
	m["0001"] = "1";
	m["0010"] = "2";
	m["0011"] = "3";
	m["0100"] = "4";
	m["0101"] = "5";
	m["0110"] = "6";
	m["0111"] = "7";
	m["1000"] = "8";
	m["1001"] = "9";
	m["1010"] = "10";
	m["1011"] = "11";
	m["1100"] = "12";
	m["1101"] = "13";
	m["1110"] = "14";
	m["1111"] = "15";
	dec = m[bin];
	return dec;
}

string Dec_to_Bin(string dec)
{
	string bin = "";
	unordered_map<string, string> m;
	m["0"] = "0000";
	m["1"] = "0001";
	m["2"] = "0010";
	m["3"] = "0011";
	m["4"] = "0100";
	m["5"] = "0101";
	m["6"] = "0110";
	m["7"] = "0111";
	m["8"] = "1000";
	m["9"] = "1001";
	m["10"] = "1010";
	m["11"] = "1011";
	m["12"] = "1100";
	m["13"] = "1101";
	m["14"] = "1110";
	m["15"] = "1111";
	bin = m[dec];
	return bin;
}

string Initial_Permutations(string input)
{
	string output = "";

	for (int i = 0; i < 64; i++)
	{
		output += input[IP[i] - 1];
	}
	return output;
}

string Final_Permutations(string input)
{
	string output = "";

	for (int i = 0; i < 64; i++)
	{
		output += input[FP[i] - 1];
	}

	return output;
}

string Expansion_Permutations(string input)
{
	string output = "";

	for (unsigned int i = 0; i < 48; i++) {
		output += input[EP[i] - 1];
	}
	return output;
}

string XOR(string input, string key)
{
	string output = "";

	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == key[i])
		{
			output += "0";
		}
		else
		{
			output += "1";
		}
	}

	return output;
}

string S_Box(string input)
{
	int box_num = 0;

	string left, right, row_val, col_val, segment, output = "";
	int row_val_dec, col_val_dec, value;

	for (int i = 0; i < 48; i += 6) {

		left = input.substr(i, 1);
		right = input.substr(i + 5, 1);
		row_val = left + right;
		row_val_dec = stoi(Bin_to_Dec(row_val));

		col_val = input.substr(i + 1, 4);
		col_val_dec = stoi(Bin_to_Dec(col_val));


		value = SBOX[box_num][row_val_dec][col_val_dec];
		box_num++;

		segment = Dec_to_Bin(to_string(value));

		output += segment;
	}

	return output;
}

string Permutations(string input)
{
	string output = "";
	for (int i = 0; i < 32; i++)
		output += input[P[i] - 1];
	return output;
}

string Permuted_Choice_1(string input)
{
	string output = "";
	for (int i = 0; i < 56; i++) {
		output += input[PC_1[i] - 1];
	}
	return output;
}

string Permuted_Choice_2(string input)
{
	string output = "";
	for (int i = 0; i < 48; i++) {
		output += input[PC_2[i] - 1];
	}
	return output;
}

vector<string> Generate_Subkeys(string key) {
	vector<string> subkeys;

	string left, right, newLeft, newRight, temp_key, new_key = "";

	for (int i = 0; i < 16; i++) {
		if (i == 0)
		{
			left = key.substr(0, 28);
			right = key.substr(28, 28);
		}
		else
		{
			left = temp_key.substr(0, 28);
			right = temp_key.substr(28, 28);
		}
		if (shift_table[i] == 1)
		{
			newLeft = left.substr(1, 27) + left.substr(0, 1);
			newRight = right.substr(1, 27) + right.substr(0, 1);
		}
		else if (shift_table[i] == 2)
		{
			newLeft = left.substr(2, 26) + left.substr(0, 2);
			newRight = right.substr(2, 26) + right.substr(0, 2);
		}
		temp_key = newLeft + newRight;

		string new_key = Permuted_Choice_2(temp_key);

		subkeys.push_back(new_key);
	}

	return subkeys;
}

int main(int argc, char** argv)
{
    string choice = argv[1];

        if(choice == "encrypt")
        {
        string plaintext, left,right,key,encrypted;
		vector<string> subkeys;

		plaintext = Hex_to_Bin(argv[2]);
		plaintext = Initial_Permutations(plaintext);
		left = plaintext.substr(0, 32);
		right = plaintext.substr(32, 32);

		key = Hex_to_Bin(argv[3]);
		key = Permuted_Choice_1(key);
		subkeys = Generate_Subkeys(key);

        string round_output,ep_output, xor_output, sbox_output, p_output, previous_left = "";

        for ( int i = 0 ; i < ROUNDS_NUMBER ; i++ ){
		ep_output = Expansion_Permutations(right);
		xor_output = XOR(ep_output, subkeys[i]);

		sbox_output = S_Box(xor_output);
		p_output = Permutations(sbox_output);
		previous_left = left;
		left = right;
		right = XOR(p_output, previous_left);

		round_output = left + right;
        }

        left = round_output.substr(32, 32);
		right = round_output.substr(0, 32);
		encrypted = left + right;
		encrypted = Final_Permutations(encrypted);
		encrypted = Bin_to_Hex(encrypted);

		cout <<"cipher: "<<encrypted << endl;

        }

        else if (choice == "decrypt")
        {
        string crypted, left,right,key,decrypted;
		vector<string> subkeys;

        crypted = Hex_to_Bin(argv[2]);
		crypted = Initial_Permutations(crypted);
		left = crypted.substr(0, 32);
		right = crypted.substr(32, 32);

		key = Hex_to_Bin(argv[3]);
		key = Permuted_Choice_1(key);
		subkeys = Generate_Subkeys(key);

        reverse(subkeys.begin(),subkeys.end());

        string round_output, ep_output, xor_output, sbox_output, p_output, previous_left = "";

        for ( int i = 0 ; i < ROUNDS_NUMBER ; i++ ){
		ep_output = Expansion_Permutations(right);
		xor_output = XOR(ep_output, subkeys[i]);

		sbox_output = S_Box(xor_output);
		p_output = Permutations(sbox_output);
		previous_left = left;
		left = right;
		right = XOR(p_output, previous_left);

		round_output = left + right;
        }


		left = round_output.substr(32, 32);
		right = round_output.substr(0, 32);
		decrypted = left + right;
		decrypted = Final_Permutations(decrypted);
		decrypted = Bin_to_Hex(decrypted);

        cout<<"plain: "<<decrypted;

        }

        else
        {
            cout<<endl<<"Invalid Parameters";
        }

		return 0;
}
