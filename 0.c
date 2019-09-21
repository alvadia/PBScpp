class ComplexNumber {
 private:
  int re, im;

 public:
  constexpr ComplexNumber(const int a, const int b) : re(a), im(b) {}
  constexpr ComplexNumber() : re(0), im(0) {}
  constexpr int GetRe() const { return re; }
  constexpr int GetIm() const { return im; }
  constexpr int SetRe(int arg) { return re = arg; }
  constexpr int SetIm(int arg) { return im = arg; }
  constexpr bool operator==(const ComplexNumber& x) const {
    return (re == x.re) && (im == x.im);
  }
  constexpr ComplexNumber Conjugate(const ComplexNumber&);
  ~ComplexNumber() = default;
};
constexpr ComplexNumber Conjugate(const ComplexNumber& x) {
  ComplexNumber res;
  res.SetRe(x.GetRe());
  res.SetIm(-x.GetIm());
  return res;
}
int main() {
  constexpr ComplexNumber a(1, 2);
  constexpr ComplexNumber b(1, -2);
  constexpr auto c = Conjugate(a);
  static_assert(b == c, "failed");
}
