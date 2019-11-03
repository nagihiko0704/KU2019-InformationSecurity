#include <stdio.h>
#include <string.h>
#include <math.h>

int* permutation(int arr[16]);
int* substitution(int arr[16]);
void printArr(int arr[16]);
int* toyCipher(int plainText[16], int key[80]);
int* subKeyMixing(int plainText[16], int key[16]);

int main(void)
{
	int testArr[16] =	{	 
							0, 0, 0, 0,
							0, 0, 0, 0,
							0, 0, 0, 0,
							0, 0, 0, 1
						};

	int key[80] =	{
						0, 0, 0, 0,
						0, 0, 0, 1,
						0, 0, 1, 0,
						0, 0, 1, 1,
						0, 1, 0, 0,
						0, 1, 0, 1,
						0, 1, 1, 0,
						0, 1, 1, 1,
						1, 0, 0, 0,
						1, 0, 0, 1,
						1, 0, 1, 0,
						1, 0, 1, 1,
						1, 1, 0, 0,
						1, 1, 0, 1,
						1, 1, 1, 0,
						1, 1, 1, 1,
						0, 0, 0, 0,
						0, 0, 0, 1,
						0, 0, 1, 0,
						0, 0, 1, 1
					};

	printArr(testArr);

	toyCipher(testArr, key);

	printArr(testArr);

	return 0;
}


int* permutation(int arr[16])
{
	int copyArr[16]; 
	memcpy(copyArr, arr, sizeof(copyArr));

	int permutetationTable[16] =	{
										0, 4, 8, 12,
										1, 5, 9, 13,
										2, 6, 10, 14,
										3, 7, 11, 15
									};

	//do permutation
	for (int i = 0; i < 16; i++)
	{
		arr[i] = copyArr[permutetationTable[i]];
	}

	return arr;
}

int* substitution(int arr[16])
{
	int substitutionTable[16] = {
									0xE, 0x4, 0xD, 0x1,
									0x2, 0xF, 0xB, 0x8,
									0x3, 0xA, 0x6, 0xC,
									0x5, 0x9, 0x0, 0x7
								};

	int subBox[4];
	int temp;

	//change binary to decimal
	for (int i = 0; i < 4; i++)
	{
		temp = 0;

		for (int j = 0; j < 4; j++)
		{
			temp += (arr[4 * i + j] << (3 - j));
		}

		subBox[i] = temp;
	}


	printf("subBox: ");
	for (int i = 0; i < 4; i++)
	{
		printf("%d ", subBox[i]);
	}
	printf("\n");

	int subBoxCopy[4];
	memcpy(subBoxCopy, subBox, sizeof(subBoxCopy));

	//do substitution
	for (int i = 0; i < 4; i++)
	{
		subBox[i] = substitutionTable[subBoxCopy[i]];
	}

	printf("after sub: ");
	for (int i = 0; i < 4; i++)
	{
		printf("%d ", subBox[i]);
	}
	printf("\n");

	//change decimal to binary
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int tempBit;
			tempBit = subBox[i] >> (3 - j);

			if (tempBit & 1)
			{
				arr[4 * i + j] = 1;
			}
			else
			{
				arr[4 * i + j] = 0;
			}
		}
	}

	return arr;
}



void printArr(int arr[16])
{
	for(int i = 0; i < 16; i++)
	{
		printf("%2d ", arr[i]);
	}

	printf("\n");
}

int* toyCipher(int plainText[16], int key[80])
{
	//round 1
	int subKey1[16];
	for (int i = 0; i < 16; i++)
	{
		subKey1[i] = key[i];
	}

	subKeyMixing(plainText, subKey1);
	substitution(plainText);
	permutation(plainText);

	//round 2
	int subKey2[16];
	for (int i = 0; i < 16; i++)
	{
		subKey2[i] = key[16 + i];
	}

	subKeyMixing(plainText, subKey2);
	substitution(plainText);
	permutation(plainText);

	//round 3
	int subKey3[16];
	for (int i = 0; i < 16; i++)
	{
		subKey3[i] = key[32 + i];
	}

	subKeyMixing(plainText, subKey3);
	substitution(plainText);
	permutation(plainText);

	//round 4
	int subKey4[16];
	for (int i = 0; i < 16; i++)
	{
		subKey4[i] = key[48 + i];
	}

	subKeyMixing(plainText, subKey4);
	substitution(plainText);


	//final
	int subKey5[16];
	for (int i = 0; i < 16; i++)
	{
		subKey5[i] = key[64 + i];
	}
	subKeyMixing(plainText, subKey5);


	return plainText;
}

int* subKeyMixing(int plainText[16], int key[16])
{
	//xor key with text bit by bit
	for (int i = 0; i < 16; i++)
	{
		plainText[i] = plainText[i] ^ key[i];
	}

	return plainText;
}