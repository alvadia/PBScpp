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

#include <algorithm>
auto MakePredicate(Items& vector) {
  return [&vector](int input) {
    return (vector.end()->value == input) ||
           (input == (std::find_if(
              vector.begin(),
              vector.end(),
              [input](TItem item) {return item.value == input;}
              )
           )->value);
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
