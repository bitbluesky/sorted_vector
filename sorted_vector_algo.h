#ifndef _my_STL_ALGO_H
#define _my_STL_ALGO_H
/*
* 摘自stl_algo.h, sorted vector相关算法
*/
#include "concept_checks.h"

namespace sorted_vector_algo
{
  /**
   *  @brief Finds the first position in which @a val could be inserted
   *         without changing the ordering.
   *  @param  first   An iterator.
   *  @param  last    Another iterator.
   *  @param  val     The search term.
   *  @return         An iterator pointing to the first element <em>not less
   *                  than</em> @a val, or end() if every element is less than 
   *                  @a val.
   *  @ingroup binary_search_algorithms
   Performs approximately log2(N)+1 element comparisons (where N is this distance).
   On non-random-access iterators, the iterator advances produce themselves an additional linear complexity in N on average.
  */
  template<typename _ForwardIterator, typename _Tp>
    _ForwardIterator
    lower_bound(_ForwardIterator __first, _ForwardIterator __last,
		const _Tp& __val)
    {
      typedef typename std::iterator_traits<_ForwardIterator>::value_type
	_ValueType;
      typedef typename std::iterator_traits<_ForwardIterator>::difference_type
	_DistanceType;

      // concept requirements
      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
      __glibcxx_function_requires(_LessThanOpConcept<_ValueType, _Tp>)
      __glibcxx_requires_partitioned_lower(__first, __last, __val);

      _DistanceType __len = std::distance(__first, __last);

      while (__len > 0)
	{
	  _DistanceType __half = __len >> 1;
	  _ForwardIterator __middle = __first;
	  /*
	  Advances the iterator it by n element positions.
	     If it is a random-access iterator, the function uses just once operator+ or operator-. 
	     Otherwise, the function uses repeatedly the increase or decrease operator (operator++ or operator--) 
	     until n elements have been advanced.
	  */
	  std::advance(__middle, __half);
	  if (*__middle < __val)
	    {
	      __first = __middle;
	      ++__first;
	      __len = __len - __half - 1;
	    }
	  else
	    __len = __half;
	}
      return __first;
    }

  /**
   *  @brief Finds the first position in which @a val could be inserted
   *         without changing the ordering.
   *  @ingroup binary_search_algorithms
   *  @param  first   An iterator.
   *  @param  last    Another iterator.
   *  @param  val     The search term.
   *  @param  comp    A functor to use for comparisons.
   *  @return An iterator pointing to the first element <em>not less
   *           than</em> @a val, or end() if every element is less
   *           than @a val.
   *  @ingroup binary_search_algorithms
   *
   *  The comparison function should have the same effects on ordering as
   *  the function used for the initial sort.
  */
  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    _ForwardIterator
    lower_bound(_ForwardIterator __first, _ForwardIterator __last,
		const _Tp& __val, _Compare __comp)
    {
      typedef typename std::iterator_traits<_ForwardIterator>::value_type
	_ValueType;
      typedef typename std::iterator_traits<_ForwardIterator>::difference_type
	_DistanceType;

      // concept requirements
      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
				  _ValueType, _Tp>)
      __glibcxx_requires_partitioned_lower_pred(__first, __last,
						__val, __comp);

      _DistanceType __len = std::distance(__first, __last);

      while (__len > 0)
	{
	  _DistanceType __half = __len >> 1;
	  _ForwardIterator __middle = __first;
	  std::advance(__middle, __half);
	  if (__comp(*__middle, __val))
	    {
	      __first = __middle;
	      ++__first;
	      __len = __len - __half - 1;
	    }
	  else
	    __len = __half;
	}
      return __first;
    }

  /**
   *  @brief Finds the last position in which @a val could be inserted
   *         without changing the ordering.
   *  @ingroup binary_search_algorithms
   *  @param  first   An iterator.
   *  @param  last    Another iterator.
   *  @param  val     The search term.
   *  @return  An iterator pointing to the first element greater than @a val,
   *           or end() if no elements are greater than @a val.
   *  @ingroup binary_search_algorithms
  */
  template<typename _ForwardIterator, typename _Tp>
    _ForwardIterator
    upper_bound(_ForwardIterator __first, _ForwardIterator __last,
		const _Tp& __val)
    {
      typedef typename std::iterator_traits<_ForwardIterator>::value_type
	_ValueType;
      typedef typename std::iterator_traits<_ForwardIterator>::difference_type
	_DistanceType;

      // concept requirements
      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
      __glibcxx_function_requires(_LessThanOpConcept<_Tp, _ValueType>)
      __glibcxx_requires_partitioned_upper(__first, __last, __val);

      _DistanceType __len = std::distance(__first, __last);

      while (__len > 0)
	{
	  _DistanceType __half = __len >> 1;
	  _ForwardIterator __middle = __first;
	  std::advance(__middle, __half);
	  if (__val < *__middle)
	    __len = __half;
	  else
	    {
	      __first = __middle;
	      ++__first;
	      __len = __len - __half - 1;
	    }
	}
      return __first;
    }

  /**
   *  @brief Finds the last position in which @a val could be inserted
   *         without changing the ordering.
   *  @ingroup binary_search_algorithms
   *  @param  first   An iterator.
   *  @param  last    Another iterator.
   *  @param  val     The search term.
   *  @param  comp    A functor to use for comparisons.
   *  @return  An iterator pointing to the first element greater than @a val,
   *           or end() if no elements are greater than @a val.
   *  @ingroup binary_search_algorithms
   *
   *  The comparison function should have the same effects on ordering as
   *  the function used for the initial sort.
  */
  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    _ForwardIterator
    upper_bound(_ForwardIterator __first, _ForwardIterator __last,
		const _Tp& __val, _Compare __comp)
    {
      typedef typename std::iterator_traits<_ForwardIterator>::value_type
	_ValueType;
      typedef typename std::iterator_traits<_ForwardIterator>::difference_type
	_DistanceType;

      // concept requirements
      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
				  _Tp, _ValueType>)
      __glibcxx_requires_partitioned_upper_pred(__first, __last,
						__val, __comp);

      _DistanceType __len = std::distance(__first, __last);

      while (__len > 0)
	{
	  _DistanceType __half = __len >> 1;
	  _ForwardIterator __middle = __first;
	  std::advance(__middle, __half);
	  if (__comp(__val, *__middle))
	    __len = __half;
	  else
	    {
	      __first = __middle;
	      ++__first;
	      __len = __len - __half - 1;
	    }
	}
      return __first;
    }

  /**
   *  @brief Finds the largest subrange in which @a val could be inserted
   *         at any place in it without changing the ordering.
   *  @ingroup binary_search_algorithms
   *  @param  first   An iterator.
   *  @param  last    Another iterator.
   *  @param  val     The search term.
   *  @return  An pair of iterators defining the subrange.
   *  @ingroup binary_search_algorithms
   *
   *  This is equivalent to
   *  @code
   *    std::make_pair(lower_bound(first, last, val),
   *                   upper_bound(first, last, val))
   *  @endcode
   *  but does not actually call those functions.
  */
  template<typename _ForwardIterator, typename _Tp>
    std::pair<_ForwardIterator, _ForwardIterator>
    equal_range(_ForwardIterator __first, _ForwardIterator __last,
		const _Tp& __val)
    {
      typedef typename std::iterator_traits<_ForwardIterator>::value_type
	_ValueType;
      typedef typename std::iterator_traits<_ForwardIterator>::difference_type
	_DistanceType;

      // concept requirements
      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
      __glibcxx_function_requires(_LessThanOpConcept<_ValueType, _Tp>)
      __glibcxx_function_requires(_LessThanOpConcept<_Tp, _ValueType>)	
      __glibcxx_requires_partitioned_lower(__first, __last, __val);
      __glibcxx_requires_partitioned_upper(__first, __last, __val);      

      _DistanceType __len = std::distance(__first, __last);
 
      while (__len > 0)
	{
	  _DistanceType __half = __len >> 1;
	  _ForwardIterator __middle = __first;
	  std::advance(__middle, __half);
	  if (*__middle < __val)
	    {
	      __first = __middle;
	      ++__first;
	      __len = __len - __half - 1;
	    }
	  else if (__val < *__middle)
	    __len = __half;
	  else
	    {
	      _ForwardIterator __left = std::lower_bound(__first, __middle,
							 __val);
	      std::advance(__first, __len);
	      _ForwardIterator __right = std::upper_bound(++__middle, __first,
							  __val);
	      return std::pair<_ForwardIterator, _ForwardIterator>(__left, __right);
	    }
	}
      return std::pair<_ForwardIterator, _ForwardIterator>(__first, __first);
    }

  /**
   *  @brief Finds the largest subrange in which @a val could be inserted
   *         at any place in it without changing the ordering.
   *  @param  first   An iterator.
   *  @param  last    Another iterator.
   *  @param  val     The search term.
   *  @param  comp    A functor to use for comparisons.
   *  @return  An pair of iterators defining the subrange.
   *  @ingroup binary_search_algorithms
   *
   *  This is equivalent to
   *  @code
   *    std::make_pair(lower_bound(first, last, val, comp),
   *                   upper_bound(first, last, val, comp))
   *  @endcode
   *  but does not actually call those functions.
  */
  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    std::pair<_ForwardIterator, _ForwardIterator>
    equal_range(_ForwardIterator __first, _ForwardIterator __last,
		const _Tp& __val, _Compare __comp)
    {
      typedef typename std::iterator_traits<_ForwardIterator>::value_type
	_ValueType;
      typedef typename std::iterator_traits<_ForwardIterator>::difference_type
	_DistanceType;

      // concept requirements
      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
				  _ValueType, _Tp>)
      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
				  _Tp, _ValueType>)
      __glibcxx_requires_partitioned_lower_pred(__first, __last,
						__val, __comp);
      __glibcxx_requires_partitioned_upper_pred(__first, __last,
						__val, __comp);

      _DistanceType __len = std::distance(__first, __last);

      while (__len > 0)
	{
	  _DistanceType __half = __len >> 1;
	  _ForwardIterator __middle = __first;
	  std::advance(__middle, __half);
	  if (__comp(*__middle, __val))
	    {
	      __first = __middle;
	      ++__first;
	      __len = __len - __half - 1;
	    }
	  else if (__comp(__val, *__middle))
	    __len = __half;
	  else
	    {
	      _ForwardIterator __left = std::lower_bound(__first, __middle,
							 __val, __comp);
	      std::advance(__first, __len);
	      _ForwardIterator __right = std::upper_bound(++__middle, __first,
							  __val, __comp);
	      return std::pair<_ForwardIterator, _ForwardIterator>(__left, __right);
	    }
	}
      return std::pair<_ForwardIterator, _ForwardIterator>(__first, __first);
    }

  /**
   *  @brief Determines whether an element exists in a range.
   *  @ingroup binary_search_algorithms
   *  @param  first   An iterator.
   *  @param  last    Another iterator.
   *  @param  val     The search term.
   *  @return  True if @a val (or its equivalent) is in [@a first,@a last ].
   *
   *  Note that this does not actually return an iterator to @a val.  For
   *  that, use std::find or a container's specialized find member functions.
  */
  template<typename _ForwardIterator, typename _Tp>
    bool
    binary_search(_ForwardIterator __first, _ForwardIterator __last,
                  const _Tp& __val)
    {
      typedef typename std::iterator_traits<_ForwardIterator>::value_type
	_ValueType;

      // concept requirements
      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
      __glibcxx_function_requires(_LessThanOpConcept<_Tp, _ValueType>)
      __glibcxx_requires_partitioned_lower(__first, __last, __val);
      __glibcxx_requires_partitioned_upper(__first, __last, __val);

      _ForwardIterator __i = std::lower_bound(__first, __last, __val);
      return __i != __last && !(__val < *__i);
    }

  /**
   *  @brief Determines whether an element exists in a range.
   *  @ingroup binary_search_algorithms
   *  @param  first   An iterator.
   *  @param  last    Another iterator.
   *  @param  val     The search term.
   *  @param  comp    A functor to use for comparisons.
   *  @return  True if @a val (or its equivalent) is in [@a first,@a last ].
   *
   *  Note that this does not actually return an iterator to @a val.  For
   *  that, use std::find or a container's specialized find member functions.
   *
   *  The comparison function should have the same effects on ordering as
   *  the function used for the initial sort.
  */
  template<typename _ForwardIterator, typename _Tp, typename _Compare>
    bool
    binary_search(_ForwardIterator __first, _ForwardIterator __last,
                  const _Tp& __val, _Compare __comp)
    {
      typedef typename std::iterator_traits<_ForwardIterator>::value_type
	_ValueType;

      // concept requirements
      __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator>)
      __glibcxx_function_requires(_BinaryPredicateConcept<_Compare,
				  _Tp, _ValueType>)
      __glibcxx_requires_partitioned_lower_pred(__first, __last,
						__val, __comp);
      __glibcxx_requires_partitioned_upper_pred(__first, __last,
						__val, __comp);

      _ForwardIterator __i = std::lower_bound(__first, __last, __val, __comp);
      return __i != __last && !bool(__comp(__val, *__i));
    }
    
}// namespace sorted_vector_algo

#endif
