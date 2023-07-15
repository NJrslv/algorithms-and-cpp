// Реалиация без аллокатора с exception safety
template<typename T>
class vector {
public:
    void push_back(const T& value) {
        push_back_private(value);
    }

    void push_back(T&& value) {
        push_back_private(std::move(value));
    }
private:
    T* arr
    size_t sz;
    size_t cap;
    
    //В современном C++, мы могли написать:
    //void push_back(T value);
    //чтобы избавиться от копипасты, но это работает только если T - тип,
    //который поддерживает move-семантику, тогда мы бы мували rvalue ref
    //и копировали lvalue ref, но мы не можем гарантировать, что T - тип,
    //поддерживающий move семантику, поэтому приходится писать 2 реализации.

    template<typename U>
    void push_back_private(U&& value) {
        if(cap == sz) {
            size_t newcap = std::max(2 * cap, (size_t)1);
            // Выделяем сырые байты без конструирования самих объектов.
            T* newarr = reinterpret_cast<T*>(new int8_t[newcap * sizeof(T)]);
            
            size_t i = 0;
            try {
                for(; i < sz; ++i) {
                    // move конструктор может кинуть исключение => может быть 2 исключения.
                    // поэтому move конструктор noexcept(false),
                    // то мы будет просто копировать объект,
                    // для сохранения exception safety => move_if_noexcept
                    new(newarr + i)T(std::move_if_noexcept(arr[i]);
                }

                //Из-за этого места мы не можем выразить push_back через reserve,
                //так так тут может вылететь исключение
                new(newarr + sz)T(std::forward<U>(value));
            } catch(...) {
                //Если кинули исключение, то возвращаем все обратно
                for(size_t j = 0; j < i; ++j) {
                    (newarr + j)->~T();
                }
                //Так как мы вызвали деструкторы, то у нас там не лежам объекты T => cast
                delete reinterpret_cast<int8_t*>(newarr);
                throw;
            }

            //Чистим arr
            for(size_t i = 0; i < sz; ++i) {
                (arr + i)->~T();
            } 
            delete reinterpret_cast<int8_t*>(arr);

            cap = newcap;
            arr = newarr;
        } else {
            new(newarr + sz)T(std::forward<U>(value));
        }
        sz++
    }
}
