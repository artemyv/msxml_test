// msxml_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <format>
#include <source_location>
#include <string_view>

#define LOG(...) logline(std::source_location::current(), __VA_ARGS__)

template<class... Args>
void logline(const std::source_location location, const std::string_view fmt, const Args&... args)
{
    std::cout << std::format("{}:{} - ", location.file_name(), location.line()) << std::format(fmt, args...) << '\n';
}
template<class... Args>
void logline(const std::source_location location, const std::wstring_view fmt, const Args&... args)
{
    std::format_to(std::ostream_iterator<char>(std::cout), "{}:{} - ", location.file_name(), location.line());
    std::format_to(std::ostream_iterator<wchar_t>(std::wcout), fmt, args...);
    std::cout << '\n';
}
int main()
{
    LOG("Hello world");
}