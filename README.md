# CPPQuiz
> Quiz yourself on ANY topic, from the command line.

I wanted to prove myself (and to the _WORLD_) that I could learn C++ after
avoiding it for almost 20 years. The thought process went something like this:

1. I should make a little C++ app to quiz me on C++
2. Hey, ChatGPT could generate quiz questions
3. Wait.. ChatGPT could generate quiz about **anything**.

Thus, the project was born and it goes something like this:

[ Insert GIF here ]

## Installation

**Pre-requisites: libcurl.4, soon to be libxml2**

This app uses CMake, mainly because of its GoogleTest integration.

```bash
$ git clone https://github.com/aphelionz/cppquiz && cd cppquiz
$ cmake -S . -B build
$ cmake --build build
```

## Usage

After following the steps above, simply:
```bash
$ ./build/cppquiz
```

Then, see the GIF above.

### Testing

Tests are build with GoogleTest and run via `ctest`.

## Contributing

Sure, why not!

## License

This code is licensed under the extremely permissive MIT license. Do what you want :)
