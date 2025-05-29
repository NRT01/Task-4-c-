#pragma once

#include <string>
#include "SynonymDictionary.h"

class TextProcessor
{
public:
    explicit TextProcessor(const SynonymDictionary& dictionary);
    ~TextProcessor() = default;

    // ������������ ������� ���� � ���������� ��������� � ��������
    // ���������� true ��� �������� ���������
    bool ProcessFile(const std::wstring& inputFile, const std::wstring& outputFile);

private:
    const SynonymDictionary& m_dictionary;

    // ��������������� ������� ��� ������ ���� � ������
    std::wstring ReplaceWordsInLine(const std::wstring& line) const;

    // ��������������� ������� ��� ��������� ���� �� ������, � ����������� ������������
    void TokenizeLine(const std::wstring& line,
        std::vector<std::wstring>& tokens,
        std::vector<bool>& isWordToken) const;

    // ���������, �������� �� ������ ������ �����
    bool IsWordChar(wchar_t ch) const;
};
