#include "SynonymDictionary.h"
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>
#include <algorithm>
#include <random>
#include <chrono>

SynonymDictionary::SynonymDictionary()
{
    // Инициализация генератора случайных чисел текущим временем
    auto seed = static_cast<unsigned int>(
        std::chrono::system_clock::now().time_since_epoch().count() & 0xFFFFFFFF
    );
    m_rng.seed(seed);
}

bool SynonymDictionary::LoadFromFile(const std::wstring& filename)
{
    m_dictionary.clear();

    std::wifstream file(filename);
    if (!file.is_open())
        return false;

    file.imbue(std::locale(file.getloc(),
        new std::codecvt_utf8_utf16<wchar_t, 0x10ffff, std::consume_header>)); // UTF-8 � BOM

    std::wstring line;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        // ������: �����: �������1, �������2, ...
        size_t colonPos = line.find(L':');
        if (colonPos == std::wstring::npos)
            continue; // ���������� ������ ��� ":"

        std::wstring key = line.substr(0, colonPos);
        std::wstring synonymsStr = line.substr(colonPos + 1);

        // ������� ������� � ������ � ����� key
        key.erase(key.begin(), std::find_if(key.begin(), key.end(), [](wchar_t ch) { return !iswspace(ch); }));
        key.erase(std::find_if(key.rbegin(), key.rend(), [](wchar_t ch) { return !iswspace(ch); }).base(), key.end());

        // ������ ��������, ���������� ��������
        std::vector<std::wstring> synonyms;
        std::wistringstream ss(synonymsStr);
        std::wstring item;

        while (std::getline(ss, item, L','))
        {
            // ������� �������
            item.erase(item.begin(), std::find_if(item.begin(), item.end(), [](wchar_t ch) { return !iswspace(ch); }));
            item.erase(std::find_if(item.rbegin(), item.rend(), [](wchar_t ch) { return !iswspace(ch); }).base(), item.end());

            if (!item.empty())
                synonyms.push_back(item);
        }

        if (!key.empty() && !synonyms.empty())
            m_dictionary[key] = std::move(synonyms);
    }

    return true;
}

std::wstring SynonymDictionary::GetRandomSynonym(const std::wstring& word) const
{
    auto it = m_dictionary.find(word);
    if (it == m_dictionary.end() || it->second.empty())
    {
        // ��� ��������� � ���������� �������� �����
        return word;
    }

    const std::vector<std::wstring>& synonyms = it->second;
    std::uniform_int_distribution<size_t> dist(0, synonyms.size() - 1);
    size_t index = dist(m_rng);

    return synonyms[index];
}
