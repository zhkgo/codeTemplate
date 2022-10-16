//找到第一个是的comp(it,value)为True的位置
template<class M, class T, class Compare>
M mbsearch(M first, M last, const T& value, Compare comp)
{
    M count = last-first;
    M step, it;
    while (count > 0) {
        step = count/2;
        it = first + step;
        if (!comp(it, value)) {
            first = ++it;
            count -= step + 1;
        }
        else
            count = step;
    }
    return first;
}
