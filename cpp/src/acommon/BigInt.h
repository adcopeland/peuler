#pragma once

#include <algorithm>
#include <cstdint>
#include <ctype.h>
#include <stdexcept>
#include <string>
#include <tuple>
#include <iostream>

// Enough of a BigInt to work for problem 13 (add only)
// Definitely not for general use, but in here because it was useful for problem 16 too
// ...and then added multiplication for problem 20
class BigInt
{
  public:
    // Build a BigInt
    explicit BigInt(const std::string& s);

    // Add other to this BigInt
    void Add(const BigInt& other);

    // Multiply other to this BigInt
    void Mul(const BigInt& other);

    // Get the string form of this BigInt
    std::string String() const
      { return reverse(m_self); }

    // returns true if other is less than this
    bool operator<(const BigInt& other) const;

  private:
    // reverse the in string and return it
    std::string reverse(const std::string& in) const;

    friend std::ostream& operator<<(std::ostream& os, const BigInt& bi);
    std::string m_self; // number stored in reverse (so rollover is added to the end)
};

inline BigInt::BigInt(const std::string& s)
  : m_self(reverse(s))
{
  for (const auto c : m_self) {
    if (!isdigit(c)) {
      throw std::runtime_error("Invalid string passed to BigInt");
    }
  }
}

inline void BigInt::Add(const BigInt& other)
{
  bool rollover = false;
  const size_t largestSize = (m_self.size() > other.m_self.size() ? m_self.size() : other.m_self.size());
  for (size_t i = 0; i < largestSize; ++i) {
    const int c1 = (i < m_self.size())       ? m_self[i] - '0'       : 0;
    const int c2 = (i < other.m_self.size()) ? other.m_self[i] - '0' : 0;
    int c3 = c1 + c2 + (rollover ? 1 : 0);
    rollover = (c3 >= 10);
    if (rollover) {
      c3 -= 10;
    }
    if (m_self.size() <= i) {
      m_self.resize(i+1);
    }
    m_self[i] = '0' + c3;
  }

  if (rollover) {
    m_self.push_back('1');
  }
}

inline void BigInt::Mul(const BigInt& other)
{
  // For now since this is just for problem 20 and I happen to know "other" is a small value, just add
  // this value to itself that many times. Need a copy though since Add is destructive.
  const BigInt self = *this;
  const BigInt increment("1");

  // Start current at 1 because self already has itself so adding once would double it.
  for (BigInt current("1"); current < other; current.Add(increment)) {
    this->Add(self);
  }
}


inline bool BigInt::operator<(const BigInt& other) const
{
  // Different number of digits implies one is less than the other
  if (m_self.size() != other.m_self.size()) {
    return m_self.size() < other.m_self.size();
  }

  // Otherwise they're the same size, compare them in reverse since the
  // string is stored in reverse.
  return std::lexicographical_compare(m_self.rbegin(),       m_self.rend(),
                                      other.m_self.rbegin(), other.m_self.rend());
}

inline std::string BigInt::reverse(const std::string& in) const
{
  std::string result(in.size(), '0');
  for (size_t i = 0; i < in.size(); ++i) {
    result[i] = in[in.size()-1-i];
  }
  return result;
}

std::ostream& operator<<(std::ostream& os, const BigInt& bi)
{
  return os << bi.reverse(bi.m_self);
}
