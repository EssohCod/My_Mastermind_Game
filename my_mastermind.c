


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void print_instructions();
void play_game(char *secret_code, int max_attempts);

int main(int argc, char *argv[]) {
    char *secret_code = NULL;
    int max_attempts = 10;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            if (i + 1 < argc) {
                secret_code = argv[i + 1];
                i++;
            } else {
                fprintf(stderr, "Error: No code provided after -c flag.\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-t") == 0) {
            if (i + 1 < argc) {
                max_attempts = atoi(argv[i + 1]);
                i++;
            } else {
                fprintf(stderr, "Error: No value provided after -t flag.\n");
                return 1;
            }
        }
    }
    srand(time(NULL));
    if (secret_code == NULL) {
        char random_code[5];
        for (int i = 0; i < 4; i++) {
            random_code[i] = '0' + rand() % 9;
        }
        random_code[4] = '\0';
        secret_code = random_code;
    }
    print_instructions();
    play_game(secret_code, max_attempts);
    return 0;
}

void print_instructions() {
    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");
}

void play_game(char *secret_code, int max_attempts) {
    int attempts = 0;
    while (attempts < max_attempts) {
        char guess[5];
        printf("---\nRound %d\n>", attempts);
        char c;
        int index = 0;
        while (read(STDIN_FILENO, &c, 1) > 0) {
            if (c == '\n') {
                guess[index] = '\0';
                break;
            }
            if (index < 4) {
                guess[index++] = c;
            }
        }

        if (strcmp(guess, secret_code) == 0) {
            printf("Congratz! You did it!\n");
            return;
        }

        int well_placed = 0, misplaced = 0;
        char temp_secret[5], temp_guess[5];
        strcpy(temp_secret, secret_code);
        strcpy(temp_guess, guess);

        for (int i = 0; i < 4; i++) {
            if (temp_guess[i] == temp_secret[i]) {
                well_placed++;
                temp_secret[i] = 'X'; // Marking as checked
                temp_guess[i] = 'Y';  // Marking as checked
            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (temp_guess[i] == temp_secret[j]) {
                    misplaced++;
                    temp_secret[j] = 'X'; // Marking as checked
                    temp_guess[i] = 'Y';  // Marking as checked
                    break;
                }
            }
        }

        printf("Well placed pieces: %d\n", well_placed);
        printf("Misplaced pieces: %d\n", misplaced);
        attempts++;
    }

    printf("Sorry, you've run out of attempts. The secret code was: %s\n", secret_code);
}
