//--------------------------------------
// Program: PasswordGenerator
//
// Generates random character passwords
// 
// Author:  Anshul Kharbanda
// Created: 12 - 23 - 2016
//--------------------------------------

// Libraries being used
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

// Keyspace information
const char KEYSPACE[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz?!";
const unsigned KEYSPACE_LENGTH = 64;

// Separator between key groups
const char SEPARATOR = '_';

// Help tag
const char HELP_TAG[] = "-help";

/**
 * Prints the help message
 */
void help();

/**
 * Prints a randomly generated password with the given number 
 * of chunks of the given length
 *
 * @param chunks the number of chunks in the password
 * @param length the length of each chunk
 *
 * @return status of password
 */
int password(int chunks, int length);

/**
 * Generates a chunk in the given password
 *
 * @param length   the length of the chunk
 * @param password the password to print to
 * @param passlen  the length of the password to print to
 * @param end      the current end of the password
 *
 * @return status of chunk printing
 */
int chunk(int length, char *password, int passlen, int* end);

/**
 * Adds a separator to the given password
 *
 * @param password the password to print to
 * @param passlen  the length of the password to print to
 * @param end      the current end of the password
 *
 * @return status of separator printing
 */
int separator(char *password, int passlen, int* end);

/**
 * The main function in the program
 *
 * @param argc number of command line arguments
 * @param argv the command line arguments
 *
 * @return status code indicating the success of the program
 */
int main(int argc, char const *argv[])
{
	// Print help message if found in arguments
	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
		{
			if (strcmp(argv[i], HELP_TAG) == 0)
			{
				help();
				return 0;
			}
		}
	}

	// Error if not all required arguments given
	if (argc < 3)
	{
		printf("ERROR: Program requires 2 command line arguments! Got: %d\n", argc - 1);
		help();
		return 1;
	}

	// Password information
	int chunks = atoi(argv[1]);
	int length = atoi(argv[2]);
	int amount = 1;

	// Modify amount if given
	if (argc > 3) amount = atoi(argv[3]);

	// Generate passwords
	for (int i = 0; i < amount; ++i)
		if (password(chunks, length))
			return 1;

	// Return success
	return 0;
}

/**
 * Prints the help message
 */
void help()
{
	printf("$ password [arguments]\n");
	printf("1: Number of chunks in the password\n");
	printf("2: Length of each chunk in the password\n");
	printf("\n");
	printf("$ password -help\n");
	printf("Prints the help message\n");
}

/**
 * Generates a password with the given number of chunks of the given length
 *
 * @param chunks the number of chunks in the password
 * @param length the length of each chunk
 */
int password(int chunks, int length)
{
	// Initialize password
	int passlen = length*chunks + (chunks - 1);
	char password[passlen];
	int end = 0;

	// Print first chunk
	if (chunk(length, password, passlen, &end))
		return 1;

	// Print remaining chunks
	for (int i = 0; i < chunks - 1; ++i)
	{
		// Add separator
		if (separator(password, passlen, &end))
			return 1;

		// Print chunk
		if (chunk(length, password, passlen, &end))
			return 1;
	}

	// Print password to screen
	printf("%s\n", password);

	// Return success
	return 0;
};

/**
 * Generates a chunk in the given password password
 *
 * @param length   the length of the chunk
 * @param password the password buffer to print to
 * @param passlen  the length of the password to print to
 * @param end    the current end of the password
 *
 * @return status of chunk printing
 */
int chunk(int length, char *password, int passlen, int* end)
{
	// Return 1 if chunk will exceed buffer
	if (*end + length > passlen)
	{
		printf("ERROR: Adding chunk exceeds password buffer length by %d characters!\n", *end + length - passlen);
		return 1;
	}

	// Generate length number of random keys and increment end accordingly
	for (int i = 0; i < length; ++i)
		password[*end + i] = KEYSPACE[rand() % KEYSPACE_LENGTH];
	*end += length;

	// Return success
	return 0;
};

/**
 * Adds a separator to the given password
 *
 * @param password the password to print to
 * @param passlen  the length of the password to print to
 * @param end      the current end of the password
 *
 * @return status of separator printing
 */
int separator(char *password, int passlen, int* end)
{
	// Return 1 if separator will exceed buffer
	if (*end + 1 > passlen)
	{
		printf("ERROR: Adding separator exceeds password buffer length!\n");
		return 1;
	}

	// Add separator and increment end
	password[*end] = SEPARATOR;
	*end += 1;

	// Return success
	return 0;
};