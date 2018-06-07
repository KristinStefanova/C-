#ifndef PAIR_H_INCLUDED
#define PAIR_H_INCLUDED

template <typename Key, typename Value>
struct Pair{

    Key first;
    Value second;

    Pair(){}
    Pair(Key const& fst, Value const& snd);
    Pair(Pair<Key,Value>const&);
    Pair& operator=(Pair<Key, Value> const&);

    bool operator==(Pair<Key, Value> const&);
    bool operator!=(Pair<Key, Value> const&);
};

template <typename Key, typename Value>
Pair<Key, Value>::Pair(Key const& fst, Value const& snd)
{
    first = fst;
    second = snd;
}

template <typename Key, typename Value>
Pair<Key, Value>::Pair(Pair<Key,Value>const& other)
{
    first = other.first;
    second = other.second;
}

template <typename Key, typename Value>
Pair<Key, Value>& Pair<Key, Value>::operator=(Pair<Key, Value> const& other)
{
    if(this != &other)
    {
        this->first = other.first;
        this->second = other.second;
    }
    return *this;
}

template <typename Key, typename Value>
bool Pair<Key, Value>::operator==(Pair<Key, Value> const& r)
{
    return first == r.first && second == r.second;
}

template <typename Key, typename Value>
bool Pair<Key, Value>::operator!= (Pair<Key, Value> const& r)
{
    return first != r.first && second != r.second;
}
#endif // PAIR_H_INCLUDED
