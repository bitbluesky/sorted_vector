#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <string.h>

#include "sorted_vector/sorted_vector.h"
//#include "sorted_vector.h"
#include "stl_algo_set.h"  //使用有序区间起始位置的迭代器作为集合运算的参数，较通用
#include "unique_algo_set.h"

using namespace std;
using namespace codeproject;

/* an employee record holds its ID, name and age */
class employee
{
public:
  int         id;
  std::string name;
  int         age;
public:
  employee():id(0){}
  employee(int id_,std::string name_,int age_):id(id_),name(name_),age(age_){}
  employee(const employee& e2)
  {
      *this = e2;
  }

  friend std::ostream& operator<<(std::ostream& os,const employee& e)
  {
    os<<e.id<<" "<<e.name<<" "<<e.age<<std::endl;
    return os;
  }
  bool operator<(const employee& e2) const
  {
      return this->id < e2.id;
  }

  employee& operator=(const employee& e2)
  {
      id = e2.id;
      name = e2.name;
      age = e2.age;
      return *this;
  }

};

typedef sorted_vector<employee> employee_set;
class index_age
{
public:
    int age;
    employee_set::iterator e;

    index_age():age(-1),e(NULL) {}
    index_age(int age_, const employee_set::iterator &e_):age(age_),e(e_){}
    index_age(const employee_set::iterator &e_):age(e_->age),e(e_){}
    bool operator<(const index_age& e2) const
    {
        if(this->age == e2.age)
            return this->e->id < e2.e->id;
        return this->age < e2.age;
    }
    friend std::ostream& operator<<(std::ostream& os,const index_age& e_age)
    {
        os<<e_age.e->id<<" "<<e_age.e->name<<" "<<e_age.age<<std::endl;
        return os;
    }

};

//测试age索引上的查找，根据age查找
struct comp_age
{
    // compare an ID and an index_age对象
    bool operator()(int x,const index_age& e2)const{return x<e2.age;}

    // compare an index_age对象 and an ID
    bool operator()(const index_age& e1,int x)const{return e1.age<x;}
};

class ID_COMP{
public:
    bool operator() (const employee& e1, const employee& e2){
        return e1.id < e2.id;
    }
};
class employee_equal{
public:
    bool operator() (const employee& e1, const employee& e2){
        return e1.id == e2.id && e1.age == e2.age;
    }
};

//问题：
//1、使用age索引进行的交并集操作，只比较age时得出的结果会出错，因为只有age相等不能说明两个对象相等
//2、如果id是主键且唯一，在两个集合中相同的id能够说明对应的对象相等，則使用目前的交并集函数可以得到正确结果
//3、针对非唯一索引，需要重写交并集函数
//多维索引如何实现？ 使用（指针+该维属性）封装新的类，插入删除操作的同步较复杂；修改rd-tree类，构建多套树索引指针
/* Define a multi_index_container of employees with following indices:
 *   - a unique index sorted by employee::int,
 *   - a non-unique index sorted by employee::name,
 *   - a non-unique index sorted by employee::age.
 */
/*
typedef multi_index_container<
  employee,
  indexed_by<
    ordered_unique<identity<employee> >,
    ordered_unique<
      tag<id>,  BOOST_MULTI_INDEX_MEMBER(employee,int,id)>,
    ordered_non_unique<
      tag<name>,BOOST_MULTI_INDEX_MEMBER(employee,std::string,name)>,
    ordered_non_unique<
      tag<age>, BOOST_MULTI_INDEX_MEMBER(employee,int,age)> >
> employee_set;
*/
//template<typename Tag,typename MultiIndexContainer>
//void print_out_by(const MultiIndexContainer& s)
//{
//  /* obtain a reference to the index tagged by Tag */
//
//  const typename boost::multi_index::index<MultiIndexContainer,Tag>::type& i=
//    get<Tag>(s);
//
//  typedef typename MultiIndexContainer::value_type value_type;
//
//  /* dump the elements of the index to cout */
//
//  std::copy(i.begin(),i.end(),std::ostream_iterator<value_type>(std::cout));
//}

struct ltstr
{
  bool operator()(const char* s1, const char* s2) const
  {
     return strcmp(s1, s2) < 0;
  }
};

int main()
{
  const int N = 6;
  //const char* a[N] = {"isomer", "ephemeral", "prosaic",
  //                    "nugatory", "artichoke", "serif"};
  const char* b[N] = {"flat", "this", "artichoke",
                      "frigate", "prosaic", "isomer"};
  sorted_vector<const char *, true, ltstr> B(b, b+N);
  copy(B.begin(), B.end(), ostream_iterator<string>(cout, "  "));

  vector<const char *> B2(b, b+N);
  sorted_vector<const char *, true, ltstr> C; //C=B; 声明中C=B会调用拷贝构造函数，而不是重载的'='运算符
  C = B2;
  copy(C.begin(), C.end(), ostream_iterator<string>(cout, "  "));


  employee_set es;
  ID_COMP id_comp;
  comp_age age_comp;

  employee a(0, "Joe",31);
  es.insert(a);//(employee(0,"Joe",31));
  es.insert(employee(1,"Robert",27));
  es.insert(employee(2,"John",40));

  cout<<"\ntest constructor"<<endl;
  employee tmp(a);
  cout<<tmp;
  tmp = employee(343, "wwww", 23);
  cout<<tmp<<endl;
  /* next insertion will fail, as there is an employee with
   * the same ID
   */

  es.insert(employee(2,"Aristotle",2387));

  es.insert(employee(3,"Albert",20));
  es.insert(employee(4,"John",57));

  copy(es.begin(), es.end(), ostream_iterator<employee>(cout, ""));

  sorted_vector<index_age> es_age;
  employee_set::iterator it;
  for(it = es.begin(); it != es.end(); it++)
      es_age.insert(it);
  cout<<sizeof(it)<<" "<< sizeof(index_age)  <<endl<<"by age:\n";
  copy(es_age.begin(), es_age.end(), ostream_iterator<index_age>(cout, ""));

  for(int i = 0; i<es_age.size(); i++)
  {
      cout << es_age[i];
  }

  sorted_vector<index_age>::const_iterator it_age;
 
  if(es_age.find(index_age()) == es_age.end())
      cout<<"lalala"<<endl;
  else
      cout << *es_age.find(index_age());

  it_age = es_age.find(27, age_comp);
  if(it_age != es_age.end())
      cout << *it_age;
  if(es_age.lower_bound(40, age_comp) != es_age.end())
      cout << *es_age.lower_bound(40, age_comp);
  //es_age.erase()
  cout<<"test age find end\n";
  /* list the employees sorted by ID, name and age */
/*
  std::cout<<"by ID"<<std::endl;
  print_out_by<id>(es);
  std::cout<<std::endl;

  std::cout<<"by name"<<std::endl;
  print_out_by<name>(es);
  std::cout<<std::endl;

  std::cout<<"by age"<<std::endl;
  print_out_by<age>(es);
  std::cout<<std::endl;
*/  
  //-------------------------------------------------
  //test stl_algo on set
  employee_set es2;
  es2.insert(employee(5,"wang",26));
  es2.insert(employee(1,"Robert",27));
  es2.insert(employee(6,"John",40));
  es2.insert(employee(4,"John",57));
  es2.insert(employee(9,"zhang",21));
  es2.insert(employee(8,"lilin",29));
  es2.insert(employee(7,"sun",43));
  es2.insert(employee(14,"jay",51));
  es2.insert(employee(0,"Joe",31));
  cout<<endl;
  copy(es2.begin(), es2.end(), ostream_iterator<employee>(cout, ""));
  cout<<endl;
  //+++++++++++++++++++++++++
  //test multi_index of age
  sorted_vector<index_age> es_age2;
  for(it = es2.begin(); it != es2.end(); it++)
      es_age2.insert(it);
  std::vector<index_age> result_age(20);
  std::vector<index_age>::iterator it_re_age;
  it_re_age = my_set_union(es_age.begin(), es_age.end(), es_age2.begin(), es_age2.end(), result_age.begin());
  result_age.resize(it_re_age - result_age.begin());
  std::cout << "test index_age: the union has " << (result_age.size()) << " elements:\n";
  for (it_re_age = result_age.begin(); it_re_age != result_age.end(); ++it_re_age)
      std::cout << ' ' << *it_re_age;
  std::cout << '\n';

  result_age.resize(20);
  it_re_age = my_set_intersection(es_age.begin(), es_age.end(), es_age2.begin(), es_age2.end(), result_age.begin());
  result_age.resize(it_re_age - result_age.begin());
  std::cout << "test index_age: the intersection has " << (result_age.size()) << " elements:\n";
  for (it_re_age = result_age.begin(); it_re_age != result_age.end(); ++it_re_age)
      std::cout << ' ' << *it_re_age;
  std::cout << '\n';
 
  //+++++++++++++++++++++++ 

  std::vector<employee> result(20);
  std::vector<employee>::iterator it_re;

  it_re = my_set_union (es.begin(), es.end(), es2.begin(), es2.end(), result.begin(), id_comp);
  result.resize(it_re-result.begin());

  std::cout << "algo: The union has " << (result.size()) << " elements:\n";
  for (it_re=result.begin(); it_re!=result.end(); ++it_re)
      std::cout << ' ' << *it_re;
  std::cout << '\n';
  //+++++++++++++++++++++++++++++++++++++++
  result.resize(20);
  it_re = my_set_intersection (es.begin(), es.end(), es2.begin(), es2.end(), result.begin(), id_comp);
  result.resize(it_re-result.begin());                 

  std::cout << "algo: The intersection has " << (result.size()) << " elements:\n";
  for (it_re=result.begin(); it_re!=result.end(); ++it_re)
      std::cout << ' ' << *it_re;
  std::cout << '\n';
  //+++++++++++++++++++++++++++++++++++++++
  result.resize(20);
  it_re=my_set_difference (es.begin(), es.end(), es2.begin(), es2.end(), result.begin(), id_comp);
  result.resize(it_re-result.begin());               

  std::cout << "algo: The difference has " << (result.size()) << " elements:\n";
  for (it_re=result.begin(); it_re!=result.end(); ++it_re)
      std::cout << ' ' << *it_re;
  std::cout << '\n';
  //+++++++++++++++++++++++++++++++++++++++
  result.resize(20);
  it_re = my_set_symmetric_difference (es.begin(), es.end(), es2.begin(), es2.end(), result.begin(), id_comp);
  result.resize(it_re-result.begin());                    

  std::cout << "algo: The symmetric_difference has " << (result.size()) << " elements:\n";
  for (it_re=result.begin(); it_re!=result.end(); ++it_re)
      std::cout << ' ' << *it_re;
  std::cout << '\n';
  //------------------------------------------------------------
  //test unique_algo on set
  //先找出公共区间，再求交、并集
  employee_set::iterator public_begin, public_end, public_begin2, public_end2;
es.insert(employee(15,"Robert",27));
  if(*es.begin() < *es2.begin())
  {
      public_begin2 = es2.begin();
      public_begin = es.lower_bound(*es2.begin()); //复杂度: O(log(n)).
  }
  else
  {
      public_begin2 = es2.lower_bound(*es.begin());
      public_begin = es.begin();
  }
  public_end = es.end();
  public_end2 = es2.end();
  if(*(--public_end) < *(--public_end2))
  {
      public_end2 = es2.upper_bound(*public_end);
      public_end++; //集合运算区间为[a, b),因此较小的end需要 后移
  }else
  {
      public_end = es.upper_bound(*public_end2);
      public_end2++;
  }
cout<< "test  :  "<< *public_begin << *public_end << *public_begin2 << endl;
cout<< "test  :  "<< *es.begin() << *es2.begin() << endl;
  //并集，公共区间更小或更大的元素只会出现在一个集合， 但是离散区间的交集，总是需要进行多次比较
  result.resize(20);
  it_re = result.begin();
  if(es.begin() != public_begin)
      it_re = copy(es.begin(), public_begin, result.begin());
  if(es2.begin() != public_begin2)
      it_re = copy(es2.begin(), public_begin2, result.begin());
cout<<"test: "<< it_re-result.begin()<<endl;  
  it_re = unique_set_union (public_begin, public_end, public_begin2, public_end2, it_re);
cout<<"test: "<< it_re-result.begin() <<endl;  
  if(es.end() != public_end)
      it_re = copy(public_end, es.end(), it_re);
  if(es2.end() != public_end2)
      it_re = copy(public_end2, es2.end(), it_re);
cout<<"test: "<< it_re-result.begin() <<endl;  

  result.resize(it_re-result.begin());
  std::cout << "unique_algo: The union has " << (result.size()) << " elements:\n";
  for (it_re=result.begin(); it_re!=result.end(); ++it_re)
      std::cout << ' ' << *it_re;
  std::cout << '\n';
  //+++++++++++++++++++++++++++++++++++++++
  //交集只需要在公共区间上进行操作即可
  result.resize(20);
  it_re = unique_set_intersection (public_begin, public_end, public_begin2, public_end2, result.begin(), id_comp);
  result.resize(it_re-result.begin());                 

  std::cout << "unique_algo: The intersection has " << (result.size()) << " elements:\n";
  for (it_re=result.begin(); it_re!=result.end(); ++it_re)
      std::cout << ' ' << *it_re;
  std::cout << '\n';
  //+++++++++++++++++++++++++++++++++++++++
  //A-B差集为 A的全集 - AB交集
  result.resize(20);
  //std::iterator _re;
  it_re = result.begin();
  it_re = copy(es.begin(), public_begin, result.begin());
  it_re = unique_set_difference (public_begin, public_end, public_begin2, public_end2, it_re, id_comp);
  it_re = copy(public_end, es.end(), it_re);
  result.resize(it_re-result.begin());               

  std::cout << "unique_algo: The difference has " << (result.size()) << " elements:\n";
  for (it_re=result.begin(); it_re!=result.end(); ++it_re)
      std::cout << ' ' << *it_re;
  std::cout << '\n';
  //+++++++++++++++++++++++++++++++++++++++
  result.resize(20);
  it_re = result.begin();
  if(es.begin() != public_begin)
      it_re = copy(es.begin(), public_begin, result.begin());
  if(es2.begin() != public_begin2)
      it_re = copy(es2.begin(), public_begin2, result.begin());
  it_re = unique_set_symmetric_difference (public_begin, public_end, public_begin2, public_end2, it_re, id_comp);
  if(es.end() != public_end)
      it_re = copy(public_end, es.end(), it_re);
  if(es2.end() != public_end2)
      it_re = copy(public_end2, es2.end(), it_re);
 
  result.resize(it_re-result.begin());                    

  std::cout << "unique_algo: The symmetric_difference has " << (result.size()) << " elements:\n";
  for (it_re = result.begin(); it_re!=result.end(); ++it_re)
      std::cout << ' ' << *it_re;
  std::cout << '\n';
  //------------------------------------------------------------
 
  return 0;
}
