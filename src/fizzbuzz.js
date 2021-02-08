'use strict'

const readline = require('readline')

const DIVISORS = new Map([
  [3, 'fizz'],
  [5, 'buzz']
])

const PROMPT_MESSAGE = 'Enter a limit: '
const INVALID_LIMIT_MESSAGE = 'You must provide a positive integer.'
const TOO_MANY_ARGUMENTS_MESSAGE = 'Too many arguments.'

const capitalize = string => string[0].toUpperCase() + string.slice(1)
const prompt = async (cli, text = '') => await new Promise(resolve => cli.question(text, resolve))

const parseLimit = rawLimit => {
  const limit = Number(rawLimit)
  if (Number.isNaN(limit) || limit < 1) return null
  return limit
}

const fizzbuzz = limit => {
  for (let number = 1; number <= limit; number++) {
    let string = ''

    for (const [divisor, divisorString] of DIVISORS) {
      if (number % divisor === 0) string += divisorString
    }

    if (string.length > 0) {
      process.stdout.write(capitalize(string))
    } else {
      process.stdout.write(number.toString())
    }

    if (number < limit) process.stdout.write('\n')
  }
}

const cliInput = () => {
  const limit = parseLimit(process.argv[2])

  if (limit === null) {
    process.stderr.write(INVALID_LIMIT_MESSAGE)
    process.exit(1)
  }

  fizzbuzz(limit)
}

const cliLoop = async () => {
  const cli = readline.createInterface({ input: process.stdin, output: process.stdout })

  while (true) {
    const limit = parseLimit(await prompt(cli, PROMPT_MESSAGE))

    if (limit === null) {
      process.stdout.write(INVALID_LIMIT_MESSAGE)
    } else {
      process.stdout.write('\n')
      fizzbuzz(limit)
    }

    process.stdout.write('\n\n')
  }
}

if (process.argv.length === 3) {
  cliInput()
} else if (process.argv.length > 3) {
  process.stderr.write(TOO_MANY_ARGUMENTS_MESSAGE)
} else {
  cliLoop()
}
