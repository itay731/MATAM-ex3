#ifndef HEALTHPOINTS_H
#define HEALTHPOINTS_H

#include <iostream>
#include <new>



class HealthPoints
{
    int m_maxHp;
    int m_currentHP;
    int getMaxHealthPoints() const;//return value of max healthPoints 
    int getCurrentHealthPoints() const;//return value of current healthPoints 

public:
    class InvalidArgument{};
    HealthPoints();
    HealthPoints(int maxHP);
    HealthPoints(const HealthPoints& newHealth) = default;
    ~HealthPoints()=default;
    bool operator==(const HealthPoints& otherHealth) const;
    bool operator==(int value) const;
    HealthPoints& operator=(const HealthPoints& newHealth);
    HealthPoints& operator=(const int &number);
    HealthPoints operator+(int addHP) const;
    HealthPoints operator-(int reduceHP) const;
    HealthPoints& operator+=(const HealthPoints& newHealth);
    HealthPoints& operator+=(int addHP);
    HealthPoints& operator-=(const HealthPoints& newHealth);
    HealthPoints& operator-=(int reduceHP);
    bool operator!=(const HealthPoints& otherHealth) const;
    bool operator!=(int value) const;
    bool operator<(const HealthPoints& otherHealth) const;
    bool operator<(int value) const;
    bool operator<=(int value) const;
    bool operator<=(const HealthPoints& otherHealth) const;
    bool operator>(int value) const;
    bool operator>(const HealthPoints& otherHealth) const;
    bool operator>=(int value) const;
    bool operator>=(const HealthPoints& otherHealth) const;
    friend bool operator==(int value, const HealthPoints& health);
    friend std::ostream& operator<<(std::ostream& os, const HealthPoints& health);
};

//making operators for cases of int and than appearance of object
HealthPoints operator+(int addHP,const HealthPoints& current);
HealthPoints operator-(int reduceHP,const HealthPoints& current2);
bool operator!=(int value, const HealthPoints& health);
bool operator<(int value, const HealthPoints& current);
bool operator<=(int value, const HealthPoints& current);
bool operator>(int value, const HealthPoints& current);
bool operator>=(int value, const HealthPoints& current);

#endif