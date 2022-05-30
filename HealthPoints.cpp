

#include "HealthPoints.h"
#include <iostream>

static const int LOWEST_HP=0;
static const int DEFAULT_HP=100;

HealthPoints::HealthPoints()
{
    m_maxHp=DEFAULT_HP;
    m_currentHP=DEFAULT_HP;
}

HealthPoints::HealthPoints(const int maxHP)
{
    if(maxHP<=LOWEST_HP){
        throw InvalidArgument();
    }
    m_maxHp=maxHP;
    m_currentHP=maxHP;
}

int HealthPoints::getMaxHealthPoints() const
{
    return this->m_maxHp;
}

int HealthPoints::getCurrentHealthPoints() const
{
    return this->m_currentHP;
}

bool HealthPoints::operator==(const HealthPoints& otherHealth) const
{
    if(this->m_currentHP==otherHealth.getCurrentHealthPoints()){
        return true;
    }
    return false;
}

bool HealthPoints::operator==(const int value) const
{
    if(m_currentHP==value){
        return true;
    }
    return false;
}

HealthPoints& HealthPoints::operator=(const HealthPoints& newHealth)
{
    if(this==&newHealth){
        return *this;
    }
    m_currentHP=newHealth.getCurrentHealthPoints();
    m_maxHp=newHealth.getMaxHealthPoints();
    return *this;

}

HealthPoints& HealthPoints::operator=(const int &number)
{
    if(number<LOWEST_HP){
        throw InvalidArgument();
    }
    m_currentHP=number;
    m_maxHp = number;
    return *this;
}

HealthPoints HealthPoints::operator+(int addHP) const
{
    HealthPoints toSend=*this;
    toSend += addHP;
    return toSend;
}

HealthPoints HealthPoints::operator-(int reduction) const
{
    HealthPoints toSend=*this;
    toSend-=reduction;
    return toSend;
}


HealthPoints& HealthPoints::operator+=(const HealthPoints& newHealth)
{
    if(this->m_currentHP+newHealth.getCurrentHealthPoints()>=this->m_maxHp){
        this->m_currentHP=this->m_maxHp;
    }
    else{
        this->m_currentHP+=newHealth.getCurrentHealthPoints();
    }
    return *this;
}


HealthPoints& HealthPoints::operator+=(int addHP)
{
    if(m_currentHP+addHP>=m_maxHp){
        m_currentHP=m_maxHp;
    }
    else if(m_currentHP+addHP<= LOWEST_HP){
        m_currentHP = LOWEST_HP;
    }
    else{
        m_currentHP+=addHP;
    }
    return *this;
}

HealthPoints& HealthPoints::operator-=(const HealthPoints& newHealth)
{
    if(this->m_currentHP-newHealth.getCurrentHealthPoints()<=LOWEST_HP){
        this->m_currentHP=LOWEST_HP;
    }
    else{
        this->m_currentHP-=newHealth.getCurrentHealthPoints();
    }
    return *this;
}

HealthPoints& HealthPoints::operator-=(int reduction)
{
    if(m_currentHP-reduction<=LOWEST_HP){
        m_currentHP=LOWEST_HP;
    }
    else if(m_currentHP-reduction>=m_maxHp){
        m_currentHP=m_maxHp;
    }
    else{
        m_currentHP-=reduction;
    }
    return *this;
}

bool HealthPoints::operator!=(const HealthPoints& otherHealth) const
{
    return !(*this==otherHealth);
}

bool HealthPoints::operator!=(const int value) const
{
    return !(*this==value);
}

bool HealthPoints::operator<(const HealthPoints& otherHealth) const
{
    if(this->m_currentHP<otherHealth.getCurrentHealthPoints()){
        return true;
    }
    return false;
}

bool HealthPoints::operator<( int value) const
{
    return (m_currentHP<value);
}

bool HealthPoints::operator<=(const HealthPoints& otherHealth) const
{
    if(!(otherHealth<*this)){
        return true;
    }
    return false;
}

bool HealthPoints::operator<=( int value) const
{
    return(m_currentHP<=value);
}

bool HealthPoints::operator>(const HealthPoints& otherHealth) const
{
    if(!(*this<=otherHealth)){
        return true;
    }
    return false;
}


bool HealthPoints::operator>( int value) const
{
    return m_currentHP > value;
}


bool HealthPoints::operator>=(const HealthPoints& otherHealth) const
{
    if(!(*this<otherHealth)){
        return true;
    }
    return false;
}


bool HealthPoints::operator>=( int value) const
{
    return m_currentHP >= value;
}


HealthPoints operator+(int addHP, const HealthPoints& current)
{
    HealthPoints toSend=current;
    toSend+=addHP;
    return toSend;
}

HealthPoints operator-(int reduction, const HealthPoints& current)
{
    HealthPoints toSend=current;
    toSend-=reduction;
    return toSend;
}

bool operator==(const int value, const HealthPoints& health)
{
    if(health.getCurrentHealthPoints()==value){
        return true;
    }
    return false;
}

bool operator!=(const int value, const HealthPoints& health)
{
    return !(health==value);
}

std::ostream& operator<<(std::ostream& os, const HealthPoints& health)
{
    return os<<health.getCurrentHealthPoints()<<'('<<health.getMaxHealthPoints()<<')';
}

bool operator<(int value, const HealthPoints& current)
{
    return (current>value);
}

bool operator<=(int value, const HealthPoints& current)
{
    return (current>=value);
}

bool operator>(int value, const HealthPoints& current)
{
    return (current<value);
}

bool operator>=(int value, const HealthPoints& current)
{
    return (current<=value);
}