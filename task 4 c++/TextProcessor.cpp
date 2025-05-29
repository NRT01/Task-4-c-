#include "TextProcessor.h"
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>
#include <vector>
#include <cwctype> // для iswalpha, iswdigit

TextProcessor::TextProcessor(const SynonymDictionary& dictionary)
    : m_dictionary(dictionary)
{
}

bool TextProcessor::ProcessFile(const std::wstring& inputFile, const std::wstring& outputFile)
{
    std::wifstream inFile(inputFile);
    if (!inFile.is_open())
        return false;

    std::wofstream outFile(outputFile);
    if (!outFile.is_open())
        return false;

    // Настроим локаль для поддержки UTF-8
    inFile.imbue(std::locale(inFile.getloc(),
        new std::codecvt_utf8_utf16<wchar_t, 0x10ffff, std::consume_header>));

    outFile.imbue(std::locale(outFile.getloc(),
        new std::codecvt_utf8_utf16<wchar_t, 0x10ffff, std::generate_header>));

    std::wstring line;
    while (std::getline(inFile, line))
    {
        std::wstring replacedLine = ReplaceWordsInLine(line);
        outFile << replacedLine << L'\n';
    }

    return true;
}

std::wstring TextProcessor::ReplaceWordsInLine(const std::wstring& line) const
{
    std::vector<std::wstring> tokens;
    std::vector<bool> isWordToken;

    TokenizeLine(line, tokens, isWordToken);

    for (size_t i = 0; i < tokens.size(); ++i)
    {
        if (isWordToken[i])
        {
            // Заменяем слово на случайный синоним
            tokens[i] = m_dictionary.GetRandomSynonym(tokens[i]);
        }
    }

    // Объединяем обратно
    std::wstring result;
    for (const auto& token : tokens)
    {
        result += token;
    }

    return result;
}

void TextProcessor::TokenizeLine(const std::wstring& line,
    std::vector<std::wstring>& tokens,
    std::vector<bool>& isWordToken) const
{
    tokens.clear();
    isWordToken.clear();

    size_t start = 0;
    size_t length = line.length();

    while (start < length)
    {
        if (IsWordChar(line[start]))
        {
            // Считаем слово
            size_t end = start + 1;
            while (end < length && IsWordChar(line[end]))
                ++end;

            tokens.push_back(line.substr(start, end - start));
            isWordToken.push_back(true);

            start = end;
        }
        else
        {
            // Считаем не-слово (пробелы, знаки препинания и т.п.)
            size_t end = start + 1;
            while (end < length && !IsWordChar(line[end]))
                ++end;

            tokens.push_back(line.substr(start, end - start));
            isWordToken.push_back(false);

            start = end;
        }
    }
}

bool TextProcessor::IsWordChar(wchar_t ch) const
{
    // Считаем слово — буквы и цифры (можно расширить под нужды)
    return std::iswalpha(ch) || std::iswdigit(ch) || ch == L'-' || ch == L'\'';
}
