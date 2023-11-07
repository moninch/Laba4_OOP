#include <iostream>
#include <vld.h>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>



class Vector;
class Map;
class ZodiacSigns;



std::string value;

class ZodiacSigns
{
    friend Vector;
    friend Map;
public:
    ZodiacSigns() { }
    bool operator <(const ZodiacSigns& zs)
    {
        std::string a, b;
        a = this->birthday;
        b = zs.birthday;
        a[2] = ' ';
        a[5] = ' ';
        b[2] = ' ';
        b[5] = ' ';
        int day1, month1, year1, day2, month2, year2;
        std::istringstream astr(a);
        astr >> day1 >> month1 >> year1;
        std::istringstream bstr(b);
        bstr >> day2 >> month2 >> year2;
        if (year1 < year2)
        {
            return 1;
        }
        else if (year1 == year1 && month1 < month2)
        {
            return 1;
        }
        else if (year1 == year2 && month1 == month2 && day1 < day2)
        {
            return 1;
        }
        return 0;
    }
    std::string getBirhday()
    {
        return this->birthday;
    }
    
    
private:
    std::string fName = "";
    std::string sName = "";
    std::string tName = "";
    std::string zodiacSigns = "";
    std::string birthday = "";
    std::string telNumber = "";
    std::string shortInfo = "";
};

class foName
{
public:
    bool operator () (ZodiacSigns a)
    {
        return a.getBirhday() == value;
    }
};

class Container
{
public:
    virtual ~Container() { }
    virtual void print() = 0;
    virtual void sortCont() = 0;
    virtual void find() = 0;
private:

};
class Vector : public Container
{
public:
    Vector() { }
    ~Vector() override { }
    Vector(std::ifstream& fin)
    {
        while (!fin.eof())
        {
            ZodiacSigns zs;
            fin >> zs.sName >> zs.fName >> zs.tName >> zs.zodiacSigns >> zs.birthday >> zs.telNumber >> zs.shortInfo;
            this->vecSigns.push_back(zs);
        }
    }
    void print() override
    {
        for (int i = 0; i < vecSigns.size(); i++)
        {
            std::cout << vecSigns[i].sName << ' ' << vecSigns[i].fName << ' ' << vecSigns[i].tName << '\n' << vecSigns[i].zodiacSigns << '\n' << vecSigns[i].birthday << '\n' << vecSigns[i].telNumber << '\n' << vecSigns[i].shortInfo << '\n';
        }
    }
    void sortCont() override
    {
        std::sort(vecSigns.begin(), vecSigns.end());
    }
    void find() override
    {
        bool flag = 0;
        auto it = vecSigns.begin();
        while (it != vecSigns.end())
        {
            it = std::find_if(it, vecSigns.end(), foName());
            if (it != vecSigns.end())
            {
                flag = 1;
                std::cout << it->telNumber << '\n' << it->zodiacSigns << '\n' << it->shortInfo << '\n';
                it++;
            }
            else
            {
                break;
            }
        }
        if (flag == 0)
        {
            std::cout << "Не найдено\n";
        }
    }
private:
    std::vector <ZodiacSigns> vecSigns;
};

class Map : public Container
{
public:
    Map() { }
    ~Map() override { }
    Map(std::ifstream& fin)
    {
        
        std::string date = "";
        while (!fin.eof())
        {
            ZodiacSigns zs;
            fin >> zs.sName >> zs.fName >> zs.tName >> zs.zodiacSigns >> date >> zs.telNumber >> zs.shortInfo;
            std::pair <std::string, ZodiacSigns> myP(date,zs);
            mMap.insert(myP);
            
        }
    }
    void print() override
    {
        for (auto it : mMap)
        {
            std::cout << it.second.sName << ' ' << it.second.fName << ' ' << it.second.tName << '\n' << it.second.zodiacSigns << '\n' << it.first << '\n' << it.second.telNumber << '\n' << it.second.shortInfo << '\n';
        }
    }
    void sortCont() override
    {
        std::cout << '\n';
    }
    void find() override
    {
        std::pair <std::multimap <std::string, ZodiacSigns> ::iterator, std::multimap <std::string, ZodiacSigns> ::iterator> pit;
        pit = mMap.equal_range(value);
        
        while (pit.first != pit.second)
        {
            std::cout << pit.first->second.telNumber << '\n' << pit.first->second.zodiacSigns << '\n' << pit.first->second.shortInfo << '\n';
            pit.first++;
        }
        if (pit.first == pit.second && pit.first == mMap.begin())
        {
            std::cout << "Не найдено\n";
        }
    }
private:
    std::multimap <std::string, ZodiacSigns> mMap;
};

class Interface
{
public:
    static Container* selectContainer(char type, std::ifstream& fin)
    {
        switch (type)
        {
        case 'V':
            return new Vector(fin);
        case 'M':
            return new Map(fin);
        default:
            break;
        }
    }
private:

};

int main()
{
    setlocale(LC_ALL, "Ru");
    std::string FilePath = "input.txt";
    std::ifstream fin;
    fin.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    try
    {
        fin.open(FilePath);
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << '\n';
        return 1;
    }
    std::cout << "Файл успешно открыт\nВыбирите контейнер для работы с файлом V - vector, M - map:";
    char type;
    std::cin >> type;
    Container* ptr = Interface::selectContainer(type, fin);
    if (type == 'V')
    {
        ptr->sortCont();
    }
    std::cout << "Введите параметр поиска в формате дд.мм.гггг :\n";
    std::cin >> value;
    ptr->find();
    



    delete[] ptr;
    fin.close();

    

    return 0;
}

