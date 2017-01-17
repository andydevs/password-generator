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
#include <stdio.h>
#include <time.h>

// Keyspace information
const char KEYSPACE[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz?!";
const unsigned int KEYSPACE_LENGTH = 64;

// Separator between key groups
const char SEPARATOR = '_';

/**
 * Generates a chunk in the given password password
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
 * The main function in the program
 *
 * @param argc number of command line arguments
 * @param argv the command line arguments
 *
 * @return status code indicating the success of the program
 */
int main(int argc, char const *argv[])
{
	if (argc < 3)
	{
		printf("Program requires 2 command line arguments. Got: %d\n", argc - 1);
		return 1;
	}

	// Password information
	int chunks  = atoi(argv[1]);
	int length  = atoi(argv[2]);
	int passlen = chunks*length + chunks - 1;

	// Seed random number generator
	srand(time(NULL));

	// Initialize password
	char password[passlen];
	int end = 0;

	// Print first chunk
	if (chunk(length, password, passlen, &end))
		return 1;

	// Print remaining chunks
	for (int i = 0; i < chunks - 1; ++i)
	{
		// Add underscore
		password[end] = SEPARATOR;
		end++;

		// Print chunk
		if (chunk(length, password, passlen, &end))
			return 1;
	}

	// Print password to screen
	printf("Password: %s\n", password);

	// Return success
	return 0;
}

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
		printf("Chunk exceeds password buffer length by %d characters.\n", *end + length - passlen);
		return 1;
	}

	// Generate length number of random keys
	for (int i = 0; i < length; ++i)
		password[*end + i] = KEYSPACE[rand() % KEYSPACE_LENGTH];

	// Increment location
	*end += length;

	// Return success
	return 0;
};