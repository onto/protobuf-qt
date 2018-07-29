#ifndef REPEATED_FIELD_ADAPTOR_H
#define REPEATED_FIELD_ADAPTOR_H

#include <utility>
#include <functional>

template<class Object, typename CountFunction, typename GetFunction>
class repeated_adaptor_impl
{
    class iterator
    {
    public:
        iterator(const Object &object, GetFunction get_func, int index)
            : _object(object)
            , _get_func(get_func)
            , _index(index)
        {
        }

        iterator &operator++()
        {
            ++_index;
            return *this;
        }

        bool operator!=(const iterator &other)
        {
            return _index != other._index;
        }

        const auto &operator*()
        {
            return *(std::invoke(_get_func, std::ref(_object), _index));
        }

    private:
        const Object &_object;
        GetFunction _get_func;
        int _index;
    };

public:
    repeated_adaptor_impl(const Object &object, CountFunction count_func, GetFunction get_func)
        : _object(object)
        , _count_func(count_func)
        , _get_func(get_func)
    {
    }

    auto begin() const
    {
        return iterator(_object, _get_func, 0);
    }

    auto begin()
    {
        return iterator(_object, _get_func, 0);
    }

    auto end() const
    {
        return iterator(_object, _get_func, std::invoke(_count_func, std::ref(_object)));
    }

    auto end()
    {
        return iterator(_object, _get_func, std::invoke(_count_func, std::ref(_object)));
    }

private:
    const Object &_object;
    CountFunction _count_func;
    GetFunction _get_func;
};

template<class Object,
         class Result,
         typename CountFunction = int (Object::*)() const,
         typename GetFunction = const Result *(Object::*)(int) const>
repeated_adaptor_impl<Object, CountFunction, GetFunction> repeated_adaptor(const Object &object,
        int (Object::* count_func)() const, const Result * (Object::* get_func)(int) const)
{
    return repeated_adaptor_impl<Object, CountFunction, GetFunction>(object, count_func, get_func);
}

#endif // REPEATED_FIELD_ADAPTOR_H
