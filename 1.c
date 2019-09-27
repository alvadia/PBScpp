#include <ctime>
#include <vector>
struct TItem {
  int value;
  time_t timestamp;
  TItem(int v) : value(v), timestamp(std::time(0)) {}
  // ...
};
using Items = std::vector<TItem>;

#include <initializer_list>
template <int... tail>
Items MakeItemsSimple() {
  Items inputs{tail...};
  return inputs;
}

auto MakePredicate(Items& vector) {
  return [&vector](int input) {
    auto step = vector.begin();
    auto rec = [&step, &vector](int input, auto& ref) mutable -> bool{
        if (step==vector.end()) return false;
        if (step->value==input) return true;
        ++step;
        return ref(input, ref);
    };
    return vector.end()->value == input ? true : rec(input, rec);
    };
}

#include <assert.h>
int main() {
  Items items = MakeItemsSimple<0, 1, 4, 5, 6>();
  Items newItems = MakeItemsSimple<7, 15, 1>();

  auto isFound = MakePredicate(items);
  auto isFoundNew = MakePredicate(newItems);

  assert(isFound(0) == true);
  assert(isFound(7) == false);
  assert(isFoundNew(7) == true);
  assert(isFoundNew(6) == false);
}
