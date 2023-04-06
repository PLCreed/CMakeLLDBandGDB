#include <iostream>
#include <memory>
#include <type_traits>

const char *p = "12345678";
const char *q = "12345678";
const char *const s = "12345678";
const char arr[] = "12345678";
const char *const t = "12345678";

void constCharTest()
{
    const char arr2[] = "12345678"; // 定义在栈上
    std::cout << (void *)&p << " " << (void *)&(*p) << std::endl;
    std::cout << (void *)&q << " " << (void *)&(*q) << std::endl;
    std::cout << (void *)&s << " " << (void *)&(*s) << std::endl;
    std::cout << (void *)arr << " " << (void *)&(*arr) << std::endl;
    std::cout << (void *)&arr << " " << (void *)&(*arr) << std::endl;
    std::cout << (void *)&arr2 << " " << (void *)&(*arr2) << std::endl;
    p = t;
}

int main()
{
    constCharTest();

    int a = 0;
    std::shared_ptr<int> b(new int(1));

    std::cout << "Hello Code Sever!" << std::endl;
    return 0;
}

/*
阅读gtest.cc 代码发现 字符串常量都定义成数组的形式，为什么不定义成指针呢？

// A test filter that matches everything.
static const char kUniversalFilter[] = "*";
// The default output file for XML output.
static const char kDefaultOutputFile[] = "test_detail.xml";
//为什么不定义成更简单的指针形式呢？
static const char *kUniversalFilter2 = "*";

定义成数组形式，数组变量地址和字符串首地址地址一样的。

定义成指针，指针变量本身额外占8个字节（64bit），访问字符串需要先读取指针的值，性能比数组形式稍差，指针的值等于字符串的首地址。

为什么编译器不优化指针的地址和字符串一样？ 因为指针的值可以变，编译器不敢优化。
测试发现即使定义成 const char * const 的形式，编译器也没有把指针地址优化成字符串。
因此字符串常量建议都定义成数组形式。

测试结果：
00007FF7DA08D020 00007FF7DA071270
00007FF7DA08D028 00007FF7DA071270
00007FF7DA071280 00007FF7DA071270
00007FF7DA071288 00007FF7DA071288
00007FF7DA071288 00007FF7DA071288
0000002A614FF7C0 0000002A614FF7C0
*/