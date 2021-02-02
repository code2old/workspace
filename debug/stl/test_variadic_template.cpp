#include "stl_test.h"

// 用于终止递归, 并打印最后一个元素
// 必须在可变参数版本之前声明
// 若在之后声明, 则无法通过编译, 
// note:   candidate expects at least 2 arguments, 1 provided
template<typename T>
ostream &print(ostream& os, const T &t)
{
    return os << t << std::endl;
}
// 可变参数函数通常是递归的,每一步处理最前面的一个实参, 然后用剩余参数调用自身.
// 除了最后一个元素之外的其他元素都会调用这个版本的print
template <typename T, typename ... Args>
ostream &print(ostream& os, const T& t, const Args&... rest)
// const Args&.. rest
// 表示将const Args& 应用到包中的每一个元素, 其扩展结果为一个逗号分隔的零个或多个类型的列表，
// 每个类型都形如const type&
// print(std::cout, 12, 13.3, "asfdae");
// 实例化为 print(ostream&, const int&, const double&, const string&)
{
    os << t << ", ";
    return print(os, rest...);
    // 模式是函数参数包的名字 rest.
    // 扩展为一个由由包中元素组成的、逗号分隔的列表.
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
    print(std::cout, 12, 13.3, "asfdae"); // 调用可变参版本
    print(std::cout, 13.3, "asfdae"); // 调用可变参版本
    print(std::cout, "asfdae"); // 两个print版本的参数都是匹配的，但是非可变参数模板比可变参数
                                // 模板更特例化, 因此编译器选择非可变参数版本
    std::cout << "max: " << maximum(1, 2, 3, 4, 5, 6) << endl;
    cout << make_tuple(7.5, string("hello"), bitset<16>(377), 42);
    return 0;
}