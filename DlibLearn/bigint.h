#pragma once

#include <dlib/bigint.h>
#include <time.h>

using namespace dlib;
using namespace std;

//explicit�ؼ���ֻ���������ڵĵ��������캯��ǰ�档�����޲����Ĺ��캯���Ͷ�����Ĺ��캯��������ʾ���ã���������ڹ��캯��ǰ��explicit�����塣
//google��c++�淶���ᵽexplicit���ŵ��ǿ��Ա��ⲻ��ʱ�˵����ͱ任��ȱ���ޡ�����googleԼ�����е������Ĺ��캯������������ʾ�ģ�
//ֻ�м���������¿������캯�����Բ�������explicit��������Ϊ�������͸����װ�����ࡣ
//effective c++��˵��������Ϊexplicit�Ĺ��캯��ͨ������non - explicit�ֵܸ��ܻ�ӭ����Ϊ���ǽ�ֹ������ִ�з�Ԥ�ڣ�����Ҳ����������������ת����
//��������һ�������������캯����������ʽ����ת���������һ��������Ϊexplicit�����������ѭ��ͬ�����ߡ�
class test_explict
{
public:
    //test_explict() = delete;
	explicit test_explict(int i) {}
	test_explict(const char* p) {}
	test_explict(int i, char* p) : test_explict(i) {}

private:
	int v;
	char* p;
};

struct data_record
{
    explicit data_record(
        uint32 size_
        ) :
        size(size_),
        number(new uint16[size_]),
        references(1),
        digits_used(1)
    {
        *number = 0;
    }
    /*!
        ensures
            - initializes *this to represent zero
    !*/

    data_record(
        const data_record& item,
        uint32 additional_size
        ) :
        size(item.digits_used + additional_size),
        number(new uint16[size]),
        references(1),
        digits_used(item.digits_used)
    {
        uint16* source = item.number;
        uint16* dest = number;
        uint16* end = source + digits_used;
        while (source != end)
        {
            *dest = *source;
            ++dest;
            ++source;
        }
    }
    /*!
        ensures
            - *this is a copy of item except with
              size == item.digits_used + additional_size
    !*/

    ~data_record(
        )
    {
        delete[] number;
    }


    const uint32 size;
    uint16* number;
    uint32 references;
    uint32 digits_used;

private:
    // no copy constructor
    data_record(data_record&);
};

class friend_test
{
public:
    friend_test(int i) : a(i) {}
    int get() const { return a; }
    // ��ʱӦ�����Ԫ����
    friend const friend_test operator+(int i, const friend_test& ft)
    {
        return friend_test(i + ft.get());
    }
    const friend_test& operator+(const friend_test& ft)
    {
        return friend_test(ft.get());
    }
    // �����
    friend std::ostream& operator<< (std::ostream& out, const friend_test& rhs)
    {
        out << rhs.get();
        return out;
    }
private:
    int a;
};

// this object represents an arbitrary precision unsigned integer.
void bigint_example()
{
    //test_explict t;
	//test_explict te(1);
	//te = 1;		// explicit�ؼ���ȡ������ʽת��
	//te = "fdsa";
    
 /*   data_record dr(100);
    data_record dr1(dr, 20);
    data_record dr2(dr);
    data_record dr3 = dr;*/

    friend_test t1(10);
    friend_test t2(20);
    friend_test t3 = 20 + t2;
    std::cout << t3 << std::endl;

    bigint::kernel_1a bi1(UINT32_MAX);
    bigint::kernel_1a bi2(UINT32_MAX -10000);
    bigint::kernel_1a bi3 = bi1 + bi2;
    bigint::kernel_1a bi4(bi1);
    bi4 += bi3;
    bigint::kernel_1a bi5 = bi1 - bi2;
    std::cout << bi5 << std::endl;
    bigint::kernel_1a bi6 = bi4 * bi1;

    bigint::kernel_1a bi7(5);
    bigint::kernel_1a bi8(7);
    bigint::kernel_1a bi9 = bi7 * bi8;
    bi9++;
    bi9 = 18 + bi7;

    bigint::kernel_1a_c bi10(UINT64_MAX);
    std::cout << bi10 << std::endl;

    timespec ts1, ts2;
    std::timespec_get(&ts1, TIME_UTC);
    bi4 = bi2 * bi2 * bi2 * bi2 * bi2 * bi2 * bi2 * bi2 * bi2 * bi2 * bi2 * bi2 * bi2 * bi2;
    std::timespec_get(&ts2, TIME_UTC);
   
}