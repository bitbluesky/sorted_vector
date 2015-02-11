#ifndef __UNIQUE_ALGo_SET_H
#define __UNIQUE_ALGo_SET_H

// 判断[first1, last1)是否包含[first2, last2),  
// 注意: 两个区间要保证有序,默认排序方式是operator<
template <class _InputIter1, class _InputIter2>
bool unique_includes(_InputIter1 __first1, _InputIter1 __last1,
        _InputIter2 __first2, _InputIter2 __last2) {
  while (__first1 != __last1 && __first2 != __last2)//遍历两个区间
    if (*__first2 < *__first1)//first2小于first1表示不包含
      return false;//返回FALSE
    else if(*__first1 < *__first2)//若first1小于first2 
      ++__first1;//寻找第一个区间下一个位置
    else
      ++__first1, ++__first2;//若first2等于first1,遍历两区间的下一位置

  return __first2 == __last2;//若第二个区间先到达尾端，则返回TRUE
}
//版本二：用户通过comp自行指定排序方式
template <class _InputIter1, class _InputIter2, class _Compare>
bool unique_includes(_InputIter1 __first1, _InputIter1 __last1,
              _InputIter2 __first2, _InputIter2 __last2, _Compare __comp) {
  while (__first1 != __last1 && __first2 != __last2)
    if (__comp(*__first2, *__first1))
      return false;
    else if(__comp(*__first1, *__first2)) 
      ++__first1;
    else
      ++__first1, ++__first2;

  return __first2 == __last2;
}


//版本一：默认是operator<操作的排序方式
template <class _InputIter1, class _InputIter2, class _OutputIter>
_OutputIter unique_set_union(_InputIter1 __first1, _InputIter1 __last1,
        _InputIter2 __first2, _InputIter2 __last2,
        _OutputIter __result) {
  //两个区间都尚未到达区间尾端，执行以下操作
  while (__first1 != __last1 && __first2 != __last2) {
	  /*
	  在两区间内分别移动迭代器，首先将元素较小者(假设为A区)记录在目标区result
	  移动A区迭代器使其前进；同时另一个区的迭代器不变。然后进行一次新的比较，
	  记录较小值，移动迭代器...直到两区间中有一个到达尾端。若两区间存在元素相等，
	  默认记录第一区间的元素到目标区result.
	  */
    if (*__first1 < *__first2) {//first1小于first2
      *__result = *__first1;//则result初始值为first1
      ++__first1;//继续第一个区间的下一个元素位置
    }
    else if (*__first2 < *__first1) {//first2小于first1
      *__result = *__first2;//第二区间元素值记录到目标区
      ++__first2;//移动第二区间的迭代器
    }
    else {//若两区间存在相等的元素，把第一区间元素记录到目标区
		//同时移动两个区间的迭代器
      *__result = *__first1;
      ++__first1;
      ++__first2;
    }
    ++__result;//更新目标区位置，以备进入下一次记录操作操作
  }
  /*
  只要两区间之中有一个区间到达尾端，就结束上面的while循环
  以下将尚未到达尾端的区间剩余的元素拷贝到目标区
  此刻，[first1, last1)和[first2, last2)至少有一个是空区间
  */
  return copy(__first2, __last2, copy(__first1, __last1, __result));
}
//版本二：用户根据仿函数comp指定排序规则
template <class _InputIter1, class _InputIter2, class _OutputIter,
          class _Compare>
_OutputIter unique_set_union(_InputIter1 __first1, _InputIter1 __last1,
                      _InputIter2 __first2, _InputIter2 __last2,
                      _OutputIter __result, _Compare __comp) {
  while (__first1 != __last1 && __first2 != __last2) {
    if (__comp(*__first1, *__first2)) {
      *__result = *__first1;
      ++__first1;
    }
    else if (__comp(*__first2, *__first1)) {
      *__result = *__first2;
      ++__first2;
    }
    else {
      *__result = *__first1;
      ++__first1;
      ++__first2;
    }
    ++__result;
  }
  return copy(__first2, __last2, copy(__first1, __last1, __result));
}



template <class _InputIter1, class _InputIter2, class _OutputIter>
_OutputIter unique_set_intersection(_InputIter1 __first1, _InputIter1 __last1,
        _InputIter2 __first2, _InputIter2 __last2,
        _OutputIter __result) {
  //若两个区间都尚未到达尾端，则执行以下操作
  while (__first1 != __last1 && __first2 != __last2) 
	//在两个区间分别移动迭代器，直到遇到相等元素，记录到目标区
	//继续移动迭代器...直到两区间之中有到达尾端
    if (*__first1 < *__first2) //第一个区间元素小于第二区间元素
      ++__first1;//移动第一区间的迭代器，此时第二区间的迭代器不变
    else if (*__first2 < *__first1) //第二区间的元素小于第一区间元素
      ++__first2;//移动第二区间元素，此时第一区间的迭代器不变
    else {//若第一区间元素等于第二区间元素
      *__result = *__first1;//按第一区间的相对排序记录到目标区
	  //分别移动两区间的迭代器
      ++__first1;
      ++__first2;
	  //更新目标区迭代器，以便继续记录元素
      ++__result;
    }
	//若有区间到达尾部，则停止while循环
	//此时，返回目标区
  return __result;
}
//版本二：用户根据仿函数comp指定排序规则
template <class _InputIter1, class _InputIter2, class _OutputIter,
          class _Compare>
_OutputIter unique_set_intersection(_InputIter1 __first1, _InputIter1 __last1,
                             _InputIter2 __first2, _InputIter2 __last2,
                             _OutputIter __result, _Compare __comp) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  __STL_REQUIRES(_OutputIter, _OutputIterator);
  __STL_REQUIRES_SAME_TYPE(
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);
  __STL_BINARY_FUNCTION_CHECK(_Compare, bool,
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);

  while (__first1 != __last1 && __first2 != __last2)
    if (__comp(*__first1, *__first2))
      ++__first1;
    else if (__comp(*__first2, *__first1))
      ++__first2;
    else {
      *__result = *__first1;
      ++__first1;
      ++__first2;
      ++__result;
    }
  return __result;
}

template <class _InputIter1, class _InputIter2, class _OutputIter>
_OutputIter unique_set_difference(_InputIter1 __first1, _InputIter1 __last1,
        _InputIter2 __first2, _InputIter2 __last2,
        _OutputIter __result) {
  //若两个区间都尚未到达尾端，则执行以下操作
  while (__first1 != __last1 && __first2 != __last2)
	 /*
	 在两个区间分别移动迭代器，当第一区间元素等于第二区间元素时，表示两区间共同存在该元素
	 则同时移动迭代器；
	 当第一区间元素大于第二区间元素时，就让第二区间迭代器前进；
	 第一区间元素小于第二区间元素时，把第一区间元素记录到目标区
	继续移动迭代器...直到两区间之中有到达尾端
	*/
    if (*__first1 < *__first2) {//第一区间元素小于第二区间元素
      *__result = *__first1;//把第一区间元素记录到目标区
      ++__first1;//移动第一区间迭代器
      ++__result;//跟新目标区，以便继续记录数据
    }
    else if (*__first2 < *__first1)//当第一区间的元素大于第二区间的元素
      ++__first2;//移动第二区间迭代器,注意：这里不记录任何元素
    else {//若两区间的元素相等时,同时移动两区间的迭代器
      ++__first1;
      ++__first2;
    }
	//若第二区间先到达尾端，则把第一区间剩余的元素复制到目标区
  return copy(__first1, __last1, __result);
}
//版本二：用户根据仿函数comp指定排序规则
template <class _InputIter1, class _InputIter2, class _OutputIter, 
          class _Compare>
_OutputIter unique_set_difference(_InputIter1 __first1, _InputIter1 __last1,
                           _InputIter2 __first2, _InputIter2 __last2, 
                           _OutputIter __result, _Compare __comp) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  __STL_REQUIRES(_OutputIter, _OutputIterator);
  __STL_REQUIRES_SAME_TYPE(
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);
  __STL_BINARY_FUNCTION_CHECK(_Compare, bool,
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);

  while (__first1 != __last1 && __first2 != __last2)
    if (__comp(*__first1, *__first2)) {
      *__result = *__first1;
      ++__first1;
      ++__result;
    }
    else if (__comp(*__first2, *__first1))
      ++__first2;
    else {
      ++__first1;
      ++__first2;
    }
  return copy(__first1, __last1, __result);
}


template <class _InputIter1, class _InputIter2, class _OutputIter>
_OutputIter 
unique_set_symmetric_difference(_InputIter1 __first1, _InputIter1 __last1,
        _InputIter2 __first2, _InputIter2 __last2,
        _OutputIter __result) {
  //若两个区间都尚未到达尾端，则执行下面的操作
  while (__first1 != __last1 && __first2 != __last2)
	  /*
	  情况1：若两区间元素相等，则同时移动两区间的迭代器.
	  情况2：若第一区间的元素小于第二区间元素，则把第一区间元素记录到目标区，且移动第一区间迭代器.
	  情况3：若第一区间的元素大于第二区间元素，则把第二区间元素记录到目标区，且移动第二区间迭代器.
	  */
    if (*__first1 < *__first2) {//属于情况2
      *__result = *__first1;//把第一区间元素记录到目标区
      ++__first1;//移动第一区间迭代器.此时第二区间迭代器不变
      ++__result;
    }
    else if (*__first2 < *__first1) {//属于情况3
      *__result = *__first2;//把第二区间元素记录到目标区
      ++__first2;//移动第二区间迭代器.此时第一区间迭代器不变
      ++__result;
    }
    else {//属于情况1
		//同时移动两区间的迭代器
      ++__first1;
      ++__first2;
    }
	 /*
  只要两区间之中有一个区间到达尾端，就结束上面的while循环
  以下将尚未到达尾端的区间剩余的元素拷贝到目标区
  此刻，[first1, last1)和[first2, last2)至少有一个是空区间
  */
  return copy(__first2, __last2, copy(__first1, __last1, __result));
}
//版本二：用户根据仿函数comp指定排序规则
template <class _InputIter1, class _InputIter2, class _OutputIter,
          class _Compare>
_OutputIter 
unique_set_symmetric_difference(_InputIter1 __first1, _InputIter1 __last1,
                         _InputIter2 __first2, _InputIter2 __last2,
                         _OutputIter __result,
                         _Compare __comp) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  __STL_REQUIRES(_OutputIter, _OutputIterator);
  __STL_REQUIRES_SAME_TYPE(
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);
  __STL_BINARY_FUNCTION_CHECK(_Compare, bool,
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);
  while (__first1 != __last1 && __first2 != __last2)
    if (__comp(*__first1, *__first2)) {
      *__result = *__first1;
      ++__first1;
      ++__result;
    }
    else if (__comp(*__first2, *__first1)) {
      *__result = *__first2;
      ++__first2;
      ++__result;
    }
    else {
      ++__first1;
      ++__first2;
    }
  return copy(__first2, __last2, copy(__first1, __last1, __result));
}

#endif

