#ifndef ELEVEN_H
#define ELEVEN_H

#include <initializer_list>
#include <string>
#include <stdexcept>

class Eleven
{

private:
    int const base{11};
    size_t _size;
    unsigned char *_body;

public:
    Eleven();
    Eleven(size_t size, unsigned char digit_val = 0);
    Eleven(const std::initializer_list<unsigned char>& digit_vals);
    Eleven(const std::string& number);
    Eleven(const Eleven& other);
    Eleven(Eleven&& other) noexcept;
    virtual ~Eleven() noexcept;

public:
    bool less(const Eleven& other) const noexcept;
    bool greater(const Eleven& other) const noexcept;
    bool equal(const Eleven& other) const noexcept;
    bool notEqual(const Eleven& other) const noexcept;

public:
    Eleven add(const Eleven& other) const;
    Eleven substract(const Eleven& other) const;
    Eleven copy() const;
    Eleven addEq(const Eleven& other) const;
    Eleven substractEq(const Eleven& other) const;

public:
    std::string getStr() const;

private:
    bool isDigitValueValid(unsigned char digit_val) const noexcept;
    bool isDigitValid(unsigned char digit) const noexcept;
    unsigned char getDigitValue(unsigned char digit) const noexcept;
    unsigned char getDigit(unsigned char digit_val) const noexcept;

};

#endif