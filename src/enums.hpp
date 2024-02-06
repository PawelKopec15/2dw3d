#pragma once
#include <vector>
#include <string>

//enums databases schould be loaded from list of files

template <typename V>
class EnumDatabase
{
    std::vector<std::string> key;
    std::vector<V> value;

public:
    V GetEnumValue(std::string label)
    {
        for (int i = 0; i < key.size(); ++i)
        {
            if (!label.compare(key[i]))
            {
                return value[i];
            }
        }

        throw 0;
    }

    V GetEnumValue(int index)
    {
        if (index >= value.size())
        {
            throw 0;
        }
        
        return value[index];
    }

    std::string GetEnumLabel(int index)
    {
        if (index >= value.size())
        {
            throw 0;
        }

        return key[index];
    }
};

template <typename V>
class Enum
{
public:
    EnumDatabase<V> database;
private:
    std::string label;
    V value;

public:
    void SetEnum(std::string newLabel)
    {
        label = newLabel;
        value = database.GetEnumValue(newLabel);
    }

    void SetEnum(int index)
    {
        label = database.GetEnumLabel(index);
        value = database.GetEnumValue(index);
    }

    V Value()
    {
        return value;
    }

    std::string Label()
    {
        return label;
    }
};
