#include "stl_test.h"

// ������ֹ�ݹ�, ����ӡ���һ��Ԫ��
// �����ڿɱ�����汾֮ǰ����
// ����֮������, ���޷�ͨ������, 
// note:   candidate expects at least 2 arguments, 1 provided
template<typename T>
ostream &print(ostream& os, const T &t)
{
    return os << t << std::endl;
}
// �ɱ��������ͨ���ǵݹ��,ÿһ��������ǰ���һ��ʵ��, Ȼ����ʣ�������������.
// �������һ��Ԫ��֮�������Ԫ�ض����������汾��print
template <typename T, typename ... Args>
ostream &print(ostream& os, const T& t, const Args&... rest)
// const Args&.. rest
// ��ʾ��const Args& Ӧ�õ����е�ÿһ��Ԫ��, ����չ���Ϊһ�����ŷָ�������������͵��б�
// ÿ�����Ͷ�����const type&
// print(std::cout, 12, 13.3, "asfdae");
// ʵ����Ϊ print(ostream&, const int&, const double&, const string&)
{
    os << t << ", ";
    return print(os, rest...);
    // ģʽ�Ǻ��������������� rest.
    // ��չΪһ�����ɰ���Ԫ����ɵġ����ŷָ����б�.
    // print(os, 13.3, "asfdae");
}

void printT1() {}

template <typename T, typename... Types>
void printT1(const T& firstArg, const Types&... args) {
    cout << firstArg << ": " << sizeof...(args)<< endl;
    printT1(args...);
}

template <typename... Types>
void printT1(const Types&... args) {
    cout << "???" << endl;
}

int maximum(int n) {
    return n;
}

template <typename ... Args> 
int maximum(int n, Args... args) {
    return std::max(n, maximum(args...));
};



template <int IDX, int MAX, typename... Args>
struct PRINT_TUPLE {
    static void print(ostream& os, const tuple<Args...>& t) {
        os << get<IDX>(t) << (IDX + 1 == MAX ? "" : ",");
        PRINT_TUPLE<IDX + 1, MAX, Args...>::print(os, t);
    }
};

template <int MAX, typename... Args>
struct PRINT_TUPLE<MAX, MAX, Args...> {
    static void print(std::ostream& os, const tuple<Args...>& t) {

    }
};

template <typename ...Args>
ostream& operator<<(ostream& os, const tuple<Args...>& t) {
    os << "[";
    PRINT_TUPLE<0, sizeof...(Args), Args...>::print(os, t);
    return os << "]";
}



int variadic_template_test(int argc, char *argv[])
{
    printT1(7.5, "hello", bitset<16>(377), 42);
    print(std::cout, 12, 13.3, "asfdae"); // ���ÿɱ�ΰ汾
    print(std::cout, 13.3, "asfdae"); // ���ÿɱ�ΰ汾
    print(std::cout, "asfdae"); // ����print�汾�Ĳ�������ƥ��ģ����Ƿǿɱ����ģ��ȿɱ����
                                // ģ���������, ��˱�����ѡ��ǿɱ�����汾
    std::cout << "max: " << maximum(1, 2, 3, 4, 5, 6) << endl;
    cout << make_tuple(7.5, string("hello"), bitset<16>(377), 42);
    return 0;
}