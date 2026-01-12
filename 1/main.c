#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef enum {
    LEFT,
    RIGHT
} Direction;

int ALL_STEPS_COUNT = 100;

#define TURN_BY_BUFFER_DIGITS_COUNT 10
char turnByStepsBuffer[TURN_BY_BUFFER_DIGITS_COUNT];
int turnByStepsDigitsCount = 0;

void print_turn(Direction direction, int turnBy)
{
    printf("Turn %s by %d steps\n", direction == LEFT ? "left" : "right", turnBy);
}

void cleanUpTurnByBuffer()
{
    for (size_t j = 0; j < TURN_BY_BUFFER_DIGITS_COUNT; j++) turnByStepsBuffer[j] = '\0';
    turnByStepsDigitsCount = 0;
}

long read_file(char* file_path, char** file_buff)
{
    FILE *input_file = fopen(file_path, "r");
    if (!input_file) {
        fprintf(stderr, "Failed to open file '%s'\n", file_path);
        return 0;
    }

    fseek(input_file, 0L, SEEK_END);
    long file_buff_size = ftell(input_file);
    fseek(input_file, 0L, SEEK_SET);
    *file_buff = malloc(file_buff_size);
    fread(*file_buff, 1, file_buff_size, input_file);

    fclose(input_file);
    return file_buff_size;
}

int main() {
    char *input_file_path = "input.txt";
    char *file_buff = NULL;
    long file_buff_size = read_file(input_file_path, &file_buff);

    if (file_buff_size != 0) {
        printf("Read %ld bytes from file '%s'\n", file_buff_size, input_file_path);
    }

    if (file_buff == NULL) {
        fprintf(stderr, "Failed to read input file '%s'\n", input_file_path);
        return 1;
    }

    int position = 50;
    Direction direction = LEFT;

    int pointingAtZeroCount = 0;

    printf("\n");
    printf("Dial at: %d\n\n", position);

    for (size_t i = 0; i <= file_buff_size; i++)
    {
        char character = file_buff[i];

        if (character == 76 || character == 82) // LETTER 'R' OR 'L'
        {
            switch (character) {
            case 76: direction = LEFT; break;
            case 82: direction = RIGHT; break;
            }
        }

        if (character > 46 && character < 58) // DIGIT
        {
            turnByStepsBuffer[turnByStepsDigitsCount] = character;
            assert(turnByStepsDigitsCount + 1 < TURN_BY_BUFFER_DIGITS_COUNT);
            turnByStepsDigitsCount++;
        }

        if (character == '\n') {
            int turnByNumber = atoi(turnByStepsBuffer);
            print_turn(direction, turnByNumber);

            for (size_t j = 0; j < turnByNumber; j++) {
                if (direction == LEFT) {
                    position = (position + ALL_STEPS_COUNT - 1) % ALL_STEPS_COUNT;
                } else {
                    position = (position + ALL_STEPS_COUNT + 1) % ALL_STEPS_COUNT;
                }

                if (position == 0) pointingAtZeroCount++;
            }

            cleanUpTurnByBuffer();
        }
    }

    printf("\n");
    printf("Dial at: %d\n", position);

    printf("\n");
    printf("--------------------------------------------------\n");
    printf("Pointing at zero count: %d\n", pointingAtZeroCount);
    printf("--------------------------------------------------\n");

    if (file_buff != NULL)
    {
        free(file_buff);
    }
    return 0;
}
