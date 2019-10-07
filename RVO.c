#include <iostream>

class Printer {
    public:
       Printer(std::string string){std::cout << "Edit " << string << '\n';}
       Printer(const Printer&){std::cout << "Copy " << '\n';}
       ~Printer(){std::cout << "Undo " << '\n';}
};
Printer foo_noRVO( bool x ) {
//У компилятора нет шансов решить, что нужна RVO, вернуть только a / b в зависимости от x
// Т.к. Есть конструкторы, в которых есть побочные эффекты - а значит,
// невозможно свести граф выполнения к дереву решений.
   Printer a("a"), b("b");
   if ( x ) return a;
   else return b;
}
Printer foo_mbRVO( bool x ) {
//У компилятора есть шанс (маленький) решить, что нужна RVO, и вставить на место выполнения ветвление
       if ( x ) {
          Printer a("a");
          return a;
       } else {
          Printer b("b");
          return b;
       }
    }
Printer foo_RVO( bool x ) {
//Компилятору прямо сказано - вставь ветку. Если x, то печатай одно, иначе другое.
       return x ? Printer("a") : Printer("b");
    }
int main()
{
    foo_noRVO(1);
    foo_mbRVO(1);
    foo_RVO(1);
    std::cout << "Hello World!\n";
    C obj = F();
    return 0;
}
