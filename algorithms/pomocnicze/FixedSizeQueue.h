#include <iostream>
#include <deque>
#include <algorithm> // dla std::find

template <typename T>
class FixedSizeQueue {
private:
    std::deque<T> queue;
    size_t maxSize;

public:
    // Konstruktor z ustalonym rozmiarem maksymalnym
    explicit FixedSizeQueue(size_t size) : maxSize(size) {}

    // Dodaj element do kolejki
    void push(const T& value) {
        if (queue.size() == maxSize) {
            queue.pop_front(); // Usuń najstarszy element
        }
        queue.push_back(value); // Dodaj nowy element
    }

    // Sprawdź, czy kolejka jest pusta
    bool empty() const {
        return queue.empty();
    }

    // Pobierz najstarszy element (bez usuwania)
    const T& front() const {
        return queue.front();
    }

    // Pobierz najnowszy element (bez usuwania)
    const T& back() const {
        return queue.back();
    }

    // Usuń najstarszy element
    void pop() {
        if (!queue.empty()) {
            queue.pop_front();
        }
    }

    // Zwróć rozmiar kolejki
    size_t size() const {
        return queue.size();
    }

    // Zwróć maksymalny rozmiar kolejki
    size_t capacity() const {
        return maxSize;
    }

    // Sprawdź, czy element znajduje się w kolejce
    bool contains(const T& value) const {
        return std::find(queue.begin(), queue.end(), value) != queue.end();
    }
};