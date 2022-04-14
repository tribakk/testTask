// Реализовать класс, который обрабатывает поток символов и выдаёт первый символ (в порядке появления символа в потоке),
// который повторялся не больше N раз, а если такого символа нет - выдаёт std::nullopt.
//
// Например:
//
// N=1
// вход  выход
// a   ->   a
// b   ->   a
// b   ->   a
// c   ->   a
// a   ->   c
// c   ->   nullopt
// f   ->   f
// g   ->   f
//
//
// N=2
// вход     выход
// b   ->   b
// c   ->   b
// f   ->   b
// b   ->   b
// f   ->   b
// c   ->   b
// b   ->   c
// c   ->   f
// c   ->   f
// f   ->   nullopt
// c   ->   nullopt
// c   ->   nullopt
// b   ->   nullopt
// b   ->   nullopt
//
// На вход алгоритм должен уметь принимать любой char.
// Оценивается корректность, читаемость и эффективность (по быстродействию) реализации.
// Решение должно быть подано в виде одного .h файла с реализацией класса FirstNRepeatingStream,
// который должен иметь интерфейс, описанный ниже:

#include <optional>
#include <unordered_map>
#include <list>

class FirstNRepeatingStream
{
    std::list<char> _charList;
    std::unordered_map<char, int> _charUseCount;
    int _maxRepeat;
public:
    FirstNRepeatingStream(int N)
        : _maxRepeat(N)
    {
    }
private:
    void checkList(char c)
    {
        
    }
public:
    std::optional<char> next(char c)
    {
        /* возможны 3 варианта
        * 1 вариант, данный символ еще не встречался, и его надо поместить в мапу
        * 2 вариант, данный символ уже встречался, и надо его счетчик увеличить
        * 3 вариант, данный символ встретился слишком много раз и надо удалить информацию о нем
        *
        * информацию в список символов надо добавлять только в случае 1 и 2
        */
        auto charCountIter = _charUseCount.find(c);
        bool bNeedPushToList = true;
        if (charCountIter != _charUseCount.end())
        {
            if (_charUseCount[c] > 0)
            {
                _charUseCount[c]++;
            }
            else
            {
                bNeedPushToList = false;
            }

            if (_charUseCount[c] > _maxRepeat)
            {
                bNeedPushToList = false;
                _charList.remove(c);
                _charUseCount[c] = -1;
            }
        }
        else
        {
            _charUseCount[c] = 1;
        }

        if (bNeedPushToList)
            _charList.push_back(c);
            
        if (_charList.size() > 0)
            return _charList.front();
        return std::nullopt;
    }
};
// можно использовать любые заголовки из стандарта С++, код будет проверяться на C++17
