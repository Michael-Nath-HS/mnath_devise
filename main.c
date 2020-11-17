// Michael Nath
// Period 10 - Systems Level Programming
// Work 11: /dev[ise a]/random plan
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// generate_random_number: takes input from /dev/urandom and returns a random number
int generate_random_number()
{
    // define a random_number integer pointer that will contain random number once file is read
    int random_number[1];

    // open the urandom file and get the file descriptor
    int urandom = open("/dev/urandom", O_RDONLY);
    if (urandom == -1)
    {
        printf("Open Error %d: Message: %s\n", errno, strerror(errno));
    }
    int message = read(urandom, random_number, sizeof(random_number));

    if (message == -1)
    {
        printf("Read Error %d: Message: %s\n", errno, strerror(errno));
    }
    close(urandom);
    return random_number[0];
}

int main()
{
    int i;
    int out;
    // iters represents the number of random numbers being generated
    int iters = 10;
    int my_numbers[iters];
    int result;
    printf("Generating random numbers:\n");
    for (i = 0; i < iters; i++)
    {
        // generate a random number and add it to the array
        my_numbers[i] = generate_random_number();
        printf("\tRandom %d: %d\n", i, my_numbers[i]);
    }
    // open an output file, and write the contents of your array there.
    out = open("./out.out", O_CREAT | O_WRONLY, 0664);
    if (out == -1)
    {
        printf("Open Error %d: Message: %s\n", errno, strerror(errno));
        return 1;
    }
    printf("Writing numbers to file...\n\n");
    result = write(out, my_numbers, sizeof(my_numbers));
    if (result == -1)
    {
        printf("Write Error %d: Message: %s\n", errno, strerror(errno));
        return 1;
    }
    close(out);
    out = open("./out.out", O_RDONLY);
    if (out == -1)
    {
        printf("Open Error %d: Message: %s\n", errno, strerror(errno));
        return 1;
    }
    int same_random_numbers[iters];
    // read in the same numbers, but into a different array (tests usage of read/write functions)
    read(out, same_random_numbers, sizeof(same_random_numbers));
    if (out == -1)
    {
        printf("Read Error %d: Message: %s\n", errno, strerror(errno));
    }
    printf("Reading numbers from file...\n\n");
    // determine equality ( in content ) of both arrays
    printf("Verification that written values were the same:\n");
    for (i = 0; i < iters; i++)
    {
        printf("\tRandom %d: %d\n", i, my_numbers[i]);
    }
    close(out);
}