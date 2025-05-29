#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <random>

class SynonymDictionary
{
public:
    SynonymDictionary();
    ~SynonymDictionary() = default;

    // Загрузить словарь синонимов из файла
    // Формат файла: слово: синоним1, синоним2, ...
    bool LoadFromFile(const std::wstring& filename);

    // Получить случайный синоним для слова
    // Если синонимов нет, вернуть исходное слово
    std::wstring GetRandomSynonym(const std::wstring& word) const;

    // Очистить словарь
    void Clear() { m_dictionary.clear(); }

private:
    std::unordered_map<std::wstring, std::vector<std::wstring>> m_dictionary;

    mutable std::mt19937 m_rng; // Генератор случайных чисел
};
