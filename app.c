// Alonso Vazquez Tena
// November 20, 2024
// Milestone 3: Embedded Application Release 2
// This is my own work.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// We must include the header file for hardware-related functions.
#include "hardware.h"

// This main function will hold all the application logic.
int main()
{
    // These variables will serve as the states that will take in
    // the results of the rolls and the exit flag respectively.
    int result, exit;

    // This seeds the random number generator.
    srand(time(NULL));

    // This initializes the hardware.
    if (initializeHardware() == -1)
        return -1;

    // This is the welcome message and the instructions.
    printf("Welcome to the Die Simulator!\n\n");
    printf("Please press KEY3 to roll the die, or KEY2 to exit the program!\n\n");

    while (1)
    {
        // This checks for any key presses and reads the status for the results and exit flag.
        pollKeys();
        readHardwareStatus(&result, &exit);

        // If the exit button has been pressed, the program exits the loop.
        if (exit)
        {
            printf("Bye bye! Exiting the program...\n\n");
            break;
        }

        // If the roll button has been pressed, the program displays what number was rolled.
        if (result != 0)
        {
            printf("%d was rolled!\n\n", result);
            result = 0;
        }

        // This is a small delay to reduce CPU usage.
        usleep(100000);
    }

    // This cleans up the hardware processes before exiting the program.
    cleanupHardware();
    return EXIT_SUCCESS;
}
