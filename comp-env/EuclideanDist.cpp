
template<typename T>
long double edist(pair<T, T>& p1, pair<T, T>& p2) {
    return sqrt(pow((p1.first - p2.first), 2) + pow((p1.second - p2.second), 2));
}
