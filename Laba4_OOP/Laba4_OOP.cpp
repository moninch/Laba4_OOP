#include <iostream>
#include <vld.h>
#include <vector>
#include <map>
#include <fstream>

class Vector;
class Map;

class ZodiacSigns
{
    friend Vector;
    friend Map;
public:
    ZodiacSigns() { }
    ZodiacSigns(std::string fName, std::string sName, std::string tName, std::string zodiacSigns, std::string birthday, std::string telNumber, std::string shortInfo)
    {
        this->fName = fName;
        this->sName = sName;
        this->tName = tName;
        this->zodiacSigns = zodiacSigns;
        this->birthday = birthday;
        this->telNumber = telNumber;
        this->shortInfo = shortInfo;
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

class Container
{
public:
    virtual void print() = 0;
private:

};
class Vector : public Container
{
public:
    Vector() { }
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

private:
    std::vector <ZodiacSigns> vecSigns;
};

class Map : public Container
{
public:
    Map() { }
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
    ptr->print();



    

    

    return 0;
}

