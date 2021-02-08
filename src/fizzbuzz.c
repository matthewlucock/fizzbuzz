#include <stdbool.h>
#include <stdio.h>

#define INPUT_BUFFER_SIZE 11
#define PROMPT_MESSAGE "Enter a limit: "
#define INVALID_LIMIT_MESSAGE "You must provide a positive integer."
#define TOO_MANY_ARGUMENTS_MESSAGE "Too many arguments."

bool parseLimit (char *rawLimit, int *limit) {
  return sscanf(rawLimit, "%d", limit) == 1 && *limit > 0;
}

void fizzbuzz (int limit) {
  for (int number = 1; number <= limit; number++) {
    bool fizz = number % 3 == 0;
    bool buzz = number % 5 == 0;

    if (fizz) {
      printf("Fizz");
    }

    if (buzz) {
      if (fizz) {
        printf("buzz");
      } else {
        printf("Buzz");
      }
    }

    if (!fizz && !buzz) {
      printf("%d", number);
    }

    if (number < limit) {
      printf("\n");
    }
  }
}

int cliInput (char *rawLimit) {
  int limit;

  if (parseLimit(rawLimit, &limit)) {
    fizzbuzz(limit);
    return 0;
  } else {
    fprintf(stderr, INVALID_LIMIT_MESSAGE);
    return 1;
  }
}

void cliLoop () {
  char rawLimit[INPUT_BUFFER_SIZE];
  int limit;

  while (true) {
    printf(PROMPT_MESSAGE);

    if (fgets(rawLimit, INPUT_BUFFER_SIZE, stdin) == NULL) {
      continue;
    }

    if (parseLimit(rawLimit, &limit)) {
      printf("\n");
      fizzbuzz(limit);
    } else {
      printf(INVALID_LIMIT_MESSAGE);
    }

    printf("\n\n");
  }
}

int main (int argc, char **argv) {
  if (argc == 2) {
    return cliInput(argv[1]);
  } else if (argc > 2) {
    fprintf(stderr, TOO_MANY_ARGUMENTS_MESSAGE);
    return 1;
  } else {
    cliLoop();
    return 0;
  }
}
