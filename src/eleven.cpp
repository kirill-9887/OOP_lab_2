#include "../include/eleven.h"

Eleven::Eleven() {
    _size = 1;
    _body = new unsigned char[_size]{};
}

Eleven::Eleven(size_t size, unsigned char digit_val) {
    if (size == 0) {
        throw std::invalid_argument("Size should be larger then 0");
    }
    if (digit_val > base - 1) {
        throw std::invalid_argument("Digit should be from 0 to" + std::to_string(base - 1));
    }
    _size = size;
    _body = new unsigned char[_size];
    for (size_t i{0}; i < _size; ++i) {
        _body[i] = digit_val;
    }
}

Eleven::Eleven(const std::initializer_list<unsigned char>& digit_vals) {
    if (digit_vals.size() == 0) {
        throw std::invalid_argument("Initializer list should not be empty");
    }
    _size = digit_vals.size();
    _body = new unsigned char[_size];
    size_t i{_size - 1};
    for (auto digit_val : digit_vals) {
        if (!isDigitValueValid(digit_val)) {
            delete[] _body;
            throw std::invalid_argument("Digit should be from 0 to" + std::to_string(base - 1));
        }
        _body[i--] = digit_val;
    }
}

Eleven::Eleven(const std::string& number) {
    if (number.size() == 0) {
        throw std::invalid_argument("Cannot create number from passed empty string");
    }
    _size = number.size();
    _body = new unsigned char[_size];
    size_t i{_size - 1};
    for (auto digit : number) {
        if (!isDigitValid(digit)) {
            delete[] _body;
            throw std::invalid_argument("Digit should be in '0123456789aA'");
        }
        _body[i--] = getDigitValue(digit);
    }
}

Eleven::Eleven(const Eleven& other) {
    _size = other._size;
    _body = new unsigned char[_size];
    for (size_t i{0}; i < _size; ++i) {
        _body[i] = other._body[i];
    }
}

Eleven::Eleven(Eleven&& other) noexcept {
    _size = other._size;
    _body = other._body;
    other._size = 0;
    other._body = nullptr;
}

Eleven::~Eleven() noexcept {
    delete[] _body;
}

bool Eleven::less(const Eleven& other) const noexcept {
    if (_size == 0 && other._size == 0) {
        return false;
    }
    if (_size == 0 || other._size == 0) {
        //*const_cast<Eleven *>(this) = std::move(Eleven("0"));
        const Eleven &size_obj = _size ? *this : other;
        size_t size = _size + other._size;
        for (size_t i = 0; i < size; ++i) {
            if (size_obj._body[i]) {
                return _size == 0;
            }
        }
        return false;
    }
    size_t i{_size - 1};
    size_t other_i{other._size - 1};
    while (!_body[i] && i > 0) {
        --i;
    }
    while (!other._body[other_i] && other_i > 0) {
        --other_i;
    }
    if (i != other_i) {
        return i < other_i;
    }
    while (_body[i] == other._body[i] && i > 0) {
        --i;
    }
    return _body[i] < other._body[i];
}

bool Eleven::greater(const Eleven& other) const noexcept {
    return other.less(*this);
}

bool Eleven::equal(const Eleven& other) const noexcept {
    return !this->less(other) && !other.less(*this);
}

Eleven Eleven::add(const Eleven& other) const {
    size_t res_size{std::max(_size, other._size) + 1};
    Eleven res(res_size);
    unsigned char memory{0};
    for (size_t i{0}; i < res_size - 1; ++i) {
        unsigned char digit_val{i < _size ? _body[i] : 0};
        unsigned char other_digit_val{i < other._size ? other._body[i] : 0};
        res._body[i] = (digit_val + other_digit_val + memory) % base;
        memory = (digit_val + other_digit_val + memory) / base;
    }
    res._body[res_size - 1] = memory;
    return res;
}

Eleven Eleven::substract(const Eleven& other) const {
    size_t res_size;
    if (_size == 0 && other._size == 0) {
        res_size = 1;
    } else {
        res_size = std::max(_size, other._size);
    }
    Eleven res(res_size);
    bool take_up{false};
    for (size_t i{0}; i < res_size; ++i) {
        unsigned char digit_val{i < _size ? _body[i] : 0};
        unsigned char other_digit_val{i < other._size ? other._body[i] : 0};
        if (take_up) {
            if (digit_val > 0) {
                other_digit_val++;
                take_up = false;
            } else {
                digit_val = base - 1;
            }
        }
        if (digit_val < other_digit_val) {
            digit_val += base;
            take_up = true;
        }
        res._body[i] = digit_val - other_digit_val;
    }
    if (take_up) {
        throw std::underflow_error("Subtracting a larger number from a smaller unsigned number");
    }
    return res;
}

Eleven Eleven::copy() const {
    return *this;
}

Eleven Eleven::addWithAssign(const Eleven& other) const {
    return this->add(other);
}

Eleven Eleven::substractWithAssign(const Eleven& other) const {
    return this->substract(other);
}

std::string Eleven::getStr() const {
    if (_size == 0) {
        return "0";
    }
    size_t i{_size - 1};
    while (!_body[i] && i > 0) {
        i--;
    }
    std::string str;
    str.resize(i + 1);
    for (size_t j = 0; j < str.size(); ++j, --i) {
        str[j] = getDigit(_body[i]);
    }
    return str;
}

bool Eleven::isDigitValueValid(unsigned char digit_val) const noexcept {
    return digit_val < base;
}

bool Eleven::isDigitValid(unsigned char digit) const noexcept {
    return ('0' <= digit && digit <= '9') || digit == 'a' || digit == 'A';
}

unsigned char Eleven::getDigitValue(unsigned char digit) const noexcept {
    if ('0' <= digit && digit <= '9') {
        return digit - '0';
    }
    if ('a' <= digit && digit <= 'z') {
        return digit - 'a' + 10;
    }
    return digit - 'A' + 10;
}

unsigned char Eleven::getDigit(unsigned char digit_val) const noexcept {
    if (digit_val < 10) {
        return '0' + digit_val;
    }
    return 'a' + (digit_val - 10);
}