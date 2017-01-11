# Interpolated-ostream-output-in-C-

Developed a function template, i. e. idiomatic like C++ <iostream> and easy to read and write like C’s printf(), but is type-safe and extensible.

Designed to use variadic template to overload << operator to std::ostream rather than creating string. Each argument is printed only when its corresponding "%" sign is encountered in format string.

A \% sequence should output a percent sign.

SomeArbitraryClass obj;
int i = 1234;
double x = 3.14;
std::string str("foo");
std::cout << Interpolate(R"(i=%, x1=%, x2=%\%, str1=%, str2=%, obj=%)", i, x, 1.001, str, "hello", obj) << std::endl;
If there is a mismatch between the number of percent signs and the number of arguments to output, throw an exception of type cs540::WrongNumberOfArgs
