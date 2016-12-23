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
const char KEYSPACE[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz$@";
const unsigned int KEYSPACE_LENGTH = 64;

/**
 * Generates a chunk in the given password password
 *
 * @param length   the length of the chunk
 * @param password the password to print to
 * @param passlen  the length of the password to print to
 * @param start    the location to start printing at
 *
 * @return status of chunk printing
 */
int chunk(int length, char *password, int passlen, int* start);

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

	// Create password buffer
	char password[passlen];

	// Print first chunk
	int loc = 0;
	if (chunk(length, password, passlen, &loc))
		return 1;

	// Print remaining chunks
	for (int i = 0; i < chunks - 1; ++i)
	{
		// Add underscore
		password[loc] = '_';
		loc++;

		// Print chunk
		if (chunk(length, password, passlen, &loc))
			return 1;
	}

	// Print chunk to screen
	printf("Password: %s\n", password);

	// Return success
	return 0;
}

/**
 * Generates a chunk in the given password password
 *
 * @param length   the length of the chunk
 * @param password the password to print to
 * @param passlen  the length of the password to print to
 * @param start    the location to start printing at
 *
 * @return status of chunk printing
 */
int chunk(int length, char *password, int passlen, int* start)
{
	// Return 1 if chunk will exceed buffer
	if (*start + length > passlen)
	{
		printf("Chunk exceeds password buffer length by %d characters.\n", *start + length - passlen);
		return 1;
	}

	// Generate length number of random keys
	for (int i = 0; i < length; ++i)
		password[*start + i] = KEYSPACE[rand() % KEYSPACE_LENGTH];

	// Increment location
	*start += length;

	// Return success
	return 0;
};