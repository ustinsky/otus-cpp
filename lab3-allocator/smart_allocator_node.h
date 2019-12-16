#include <iostream>
#include <vector>

template<typename M, size_t m_capacity = 1000000>
class MChunk {
    using pointer = M*;
public:
    MChunk(pointer _m_pool = nullptr): m_pool(_m_pool), m_size(0) {
       reserve();
    } 

    // выделение памяти
    void reserve() {

        // выделяем память размером в m_capacity
        if (m_pool == nullptr) {
            auto p = std::malloc(m_capacity * sizeof(M));
            if (p == nullptr) 
                throw std::bad_alloc();
            else {
                m_pool = reinterpret_cast<pointer>(p);
            }
        }
        
        // Обнуляем значения матрицы
        for (size_t i = 0; i < m_capacity; ++i) {
            m_matrix[i] = false;
        }

        // std::cout << "Выделяем память" << m_pool << std::endl;
    }

    // Эта моя реализация - я не профессиональный программист на C++, я системный администратор(эникейщик)
    // Поэтому прошу сильно не ругаться за кривизну решения 
    // Логика выделения сводиться к следующему:
    // Проходимся по матрице m_matrix и ищем n свободных элементов 
    // Если не находим возвращаем nullptr
    pointer alloc(size_t n = 1) {
        // Если запрашиваемый размер больше чем размер емкости то мы возвращаем ошибку
        if (n > m_capacity) {
            return nullptr;
        }

        if (m_pool == nullptr) {
            reserve();
        }

        pointer p; 
        size_t tmp_size = 0;

        // Мы проходимся в худшем случае  - 2 раза
        // Почему - чтобы решить 2 проблемы
        // 1. Если мы проходимся последовательно - то для последних элементов выделение памяти 
        //    будет дольше. При больших размерах chunk-а - длительность будет очень долгая. 
        //    Для минимизации этой проблемы введена всмопогательная переменная - pos_free. 
        // 2. В процессе работы могут образовываться пустоты в памяти. В пустоты возможно 
        //    мы можем поместить данные. Поэтому если пройдясь 1 раз не нашли где разместить 
        //    объект, мы проходимся еще раз начиная с начала - возможно его можно разместить 
        //    в освободившемся промежутке памяти.
        for (int step = 0; step < 2; ++step) {
            size_t i;
            if (step == 0) {
                i = pos_free;
            } else {
                i = 0;
            }
            // for( auto i = 0; i<m_capacity; ++i) {
            for(; i<m_capacity; ++i) {
                // print_mat();

                // Если память свободна
                if (m_matrix[i] == false) {
                    
                    // Если первый раз - сохраняем текущее значение указателя
                    if (tmp_size == 0) {
                        p = m_pool + i;
                        // std::cout << "cur: " << p << std::endl;
                    }
                        
                    // Увеличиваем на единицу
                    tmp_size++;
                    

                    // Нам нужен запрашиваемый размер расположенный подряд.
                    // Поэтому ищем последовательные элементы
                    if (tmp_size == n) {
                        // Если размер подходит
                        pos_free = i;

                        // Помечаем ячейки как занятые
                        for(auto j = i - n + 1; j <= i; ++j) {
                            m_matrix[j] = true;
                        }

                        // увеличиваем занятый размер
                        m_size += n;

                        // обнуляем tmp_size
                        tmp_size = 0;

                        // Выдаем память
                        return p;
                    }
                } else {
                    tmp_size = 0;
                }
            }
        }
        // std::cout << "Exit" << std::endl;
        return nullptr;
    }

    // Освобождаем память
    bool dealloc(pointer p, size_t n = 1) {
        if ((p == nullptr) || (n > m_capacity)) {
            return false;
        }

        // Если память находится в диапазоне от m_pool до m_pool+m_capacity 
        // то эта память может быть освобождена в этом Chunk-е 
        if ( ((p - m_pool) >= 0) && ((p - m_pool) < (long int)m_capacity)) {
            for (auto i = p - m_pool; (i < (p - m_pool) + (long int)n) && (i < (long int)m_capacity) ; ++i) {
                m_matrix[i] = false;
            }
            m_size -= n;

            // Если размер стал равен 0. То имеет смысл освободить память
            // if (m_size == 0) {
            //     if (m_pool != nullptr) {
            //         free(m_pool);
            //         m_pool = nullptr;

            //         return true;
            //     }
            // }
            return true;
        } else {
            return false;
        }
    }

    virtual ~MChunk() {
        if (m_pool != nullptr) {
            std::cout << "Очистка памяти по адресу: " << m_pool << std::endl;
            free(m_pool);
            m_pool = nullptr;
        }
            
    }

    void print_mat() {
        for (auto bol : m_matrix) {
            std::cout << bol;
        }
        std::cout << std::endl;
    }

    pointer m_pool;
    size_t  m_size;
    int     pos_free;
    bool m_matrix[m_capacity];
};

template<typename T, size_t M_Capacity = 1000000>
class smart_alloc_logic {
    using type    = T;
    using pointer = T*;

public:
    smart_alloc_logic() {}

    virtual ~smart_alloc_logic() {
        for (auto cur : m_list) {
            // cur->~MChunk<type, M_Capacity>();
            delete cur;
        }
    }

    pointer alloc(size_t n = 1) {
        // если список пуст - то создаем элемент
        if (m_list.empty()) {
            m_cur_chunk = new MChunk<type, M_Capacity>();
            m_list.emplace_back(m_cur_chunk); 
        }

        // Проверяем размер необходимого выделения памяти
        // Если он больше чем емкость , то возвращаем ошибку
        if (n > M_Capacity) {
            return nullptr;
        } 

        // Выделение памяти
        // Проходимся по списку ищем подходящее место для вставки элемента
        auto p = m_cur_chunk->alloc(n);
        if (p == nullptr) {
            for(auto cur: m_list) {
               auto p = cur->alloc(n);
                if (p != nullptr) {
                    return p;
                }
            }
        } else {
            return p;
        }
        

        // Если не находим создаем новый
        m_cur_chunk = new MChunk<type, M_Capacity>();
        m_list.emplace_back(m_cur_chunk);
        return m_cur_chunk->alloc(n);
    }

    bool dealloc(pointer p, size_t n = 1) {
        // Нам надо найти в каком из элементов списка нужно осуществить удаление
        for(auto cur: m_list) {
            auto res = cur->dealloc(p, n);
            if (res == true) {
                return true;
            } 
        }

        // Если не нашли адрес, и не смогли освободить ресурсы
        return false;
    }

    void print() {
        for (auto cur : m_list) {
            std::cout << "Element: " << cur << std::endl;
            cur->print_mat();
            std::cout << "================" << std::endl;
        }
    }

    std::vector<MChunk<type, M_Capacity>*>  m_list;
    MChunk<type, M_Capacity>*               m_cur_chunk;
};
