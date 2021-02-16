# Airport counter
You need to develop a basic departure statistics collection system for small airlines. The high-level requirements are as follows:

1. The statistics collection system must be an AirportCounter class capable of returning the current number of departures from it at an arbitrary time for a given airport.
2. The set of possible airports is fixed in the form of an enum and therefore cannot be changed within one session of the statistics system, that is, within one instance of AirportCounter. Thus, the AirportCounter class must be templated with the type of this enum: if you call such an enum TAirport, we get the template class AirportCounter <TAirport>.
3. It is guaranteed (at least promised by the customer) that it will be possible to easily determine the number of elements in it using the airport enum, as well as iterate over the elements themselves. Namely, any enum used will have the form enum class SomeCityAirport {Airport1, Airport2, ..., AirportN, Last_};, that is, it will contain a number of airport elements and the Last_ element as the last. Since this enum will not provide numeric values ​​for the elements, you can rely on the fact that they will be numbered in a row from 0 to N-1, and the expression static_cast <uint32_t> (SomeCityAirport :: Last_) will contain the number of airports (N).
4. The class should be able to construct according to the list of departure airports, and also allow updating this list: adding a departure from an airport, deleting one departure (for example, an erroneously added one) or deleting all departures from a certain airport from the history.

## Testing

Before proceeding to a more detailed description of the class interface, let us describe the process of testing the task.

You will be given all the tests against which the template class AirportCounter will be tested. Your task is to achieve not only correct work on these tests, but also meet them in 2 seconds. (Consider that the customer provided you with detailed use cases for your class, which were then converted into specific benchmarks.)

Thus, you must choose the way to implement the class, focusing only on specific benchmarks.

Note that these benchmarks are based on a real example from a high-load service, the slowdown of which even by tens of percent is unacceptable. That is why in this problem it is important not only to design a solution with an acceptable asymptotic complexity, but also to "overclock" it with specific examples.

## Class interface
```cpp
template <typename TAirport>
class AirportCounter {
public:
  // конструктор по умолчанию: список элементов пока пуст
  AirportCounter();

  // конструктор от диапазона элементов типа TAirport
  template <typename TIterator>
  AirportCounter(TIterator begin, TIterator end);

  // получить количество элементов, равных данному
  size_t Get(TAirport airport) const;

  // добавить данный элемент
  void Insert(TAirport airport);

  // удалить одно вхождение данного элемента
  void EraseOne(TAirport airport);

  // удалить все вхождения данного элемента
  void EraseAll(TAirport airport);

  using Item = pair<TAirport, size_t>;

  // получить некоторый объект, по которому можно проитерироваться,
  // получив набор объектов типа Item - пар (аэропорт, количество),
  // упорядоченных по аэропорту
  ??? GetItems() const;

private:
  // ???
};
```
