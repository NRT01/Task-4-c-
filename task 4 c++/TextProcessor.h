#pragma once

#include <string>
#include "SynonymDictionary.h"

class TextProcessor
{
public:
    explicit TextProcessor(const SynonymDictionary& dictionary);
    ~TextProcessor() = default;

    // Обрабатывает входной файл и записывает результат в выходной
    // Возвращает true при успешной обработке
    bool ProcessFile(const std::wstring& inputFile, const std::wstring& outputFile);

private:
    const SynonymDictionary& m_dictionary;

    // Вспомогательная функция для замены слов в строке
    std::wstring ReplaceWordsInLine(const std::wstring& line) const;

    // Вспомогательная функция для выделения слов из строки, с сохранением разделителей
    void TokenizeLine(const std::wstring& line,
        std::vector<std::wstring>& tokens,
        std::vector<bool>& isWordToken) const;

    // Проверяет, является ли символ частью слова
    bool IsWordChar(wchar_t ch) const;
};
