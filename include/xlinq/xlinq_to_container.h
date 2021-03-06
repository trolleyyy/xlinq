/*
MIT License

Copyright (c) 2017 TrolleY

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
/**
*	@file xlinq_to_container.h
*	Converting IEnumerable to STL container.
*	@author TrolleY
*/
#ifndef XLINQ_TO_CONTAINER_H_
#define XLINQ_TO_CONTAINER_H_

#include "xlinq_base.h"
#include "xlinq_stl.h"
#include "xlinq_select.h"
#include <utility>
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

namespace xlinq
{
	/*@cond XLINQ_INTERNAL*/
	namespace internal
	{
		class _ToVectorBuilder
		{
		public:
			template<typename TElem>
			std::vector<TElem> build(std::shared_ptr<IEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::vector<TElem>(container.begin(), container.end());
			}

			template<typename TElem>
			std::vector<TElem> build(std::shared_ptr<IBidirectionalEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::vector<TElem>(container.begin(), container.end());
			}

			template<typename TElem>
			std::vector<TElem> build(std::shared_ptr<IRandomAccessEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::vector<TElem>(container.begin(), container.end());
			}
		};

		class _ToListBuilder
		{
		public:
			template<typename TElem>
			std::list<TElem> build(std::shared_ptr<IEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::list<TElem>(container.begin(), container.end());
			}

			template<typename TElem>
			std::list<TElem> build(std::shared_ptr<IBidirectionalEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::list<TElem>(container.begin(), container.end());
			}

			template<typename TElem>
			std::list<TElem> build(std::shared_ptr<IRandomAccessEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::list<TElem>(container.begin(), container.end());
			}
		};

		class _ToForwardListBuilder
		{
		public:
			template<typename TElem>
			std::forward_list<TElem> build(std::shared_ptr<IEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::forward_list<TElem>(container.begin(), container.end());
			}

			template<typename TElem>
			std::forward_list<TElem> build(std::shared_ptr<IBidirectionalEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::forward_list<TElem>(container.begin(), container.end());
			}

			template<typename TElem>
			std::forward_list<TElem> build(std::shared_ptr<IRandomAccessEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::forward_list<TElem>(container.begin(), container.end());
			}
		};

		class _ToSetBuilder
		{
		public:
			template<typename TElem>
			std::set<TElem> build(std::shared_ptr<IEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::set<TElem>(container.begin(), container.end());
			}

			template<typename TElem>
			std::set<TElem> build(std::shared_ptr<IBidirectionalEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::set<TElem>(container.begin(), container.end());
			}

			template<typename TElem>
			std::set<TElem> build(std::shared_ptr<IRandomAccessEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::set<TElem>(container.begin(), container.end());
			}
		};

		template<typename TLess>
		class _ToSetWithLessBuilder
		{
		private:
			TLess _less;
		public:
			_ToSetWithLessBuilder(TLess less) : _less(less) {}

			template<typename TElem>
			std::set<TElem, TLess> build(std::shared_ptr<IEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::set<TElem, TLess>(container.begin(), container.end(), _less);
			}

			template<typename TElem>
			std::set<TElem, TLess> build(std::shared_ptr<IBidirectionalEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::set<TElem, TLess>(container.begin(), container.end(), _less);
			}

			template<typename TElem>
			std::set<TElem, TLess> build(std::shared_ptr<IRandomAccessEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::set<TElem, TLess>(container.begin(), container.end(), _less);
			}
		};

		class _ToMultiSetBuilder
		{
		public:
			template<typename TElem>
			std::multiset<TElem> build(std::shared_ptr<IEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::multiset<TElem>(container.begin(), container.end());
			}

			template<typename TElem>
			std::multiset<TElem> build(std::shared_ptr<IBidirectionalEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::multiset<TElem>(container.begin(), container.end());
			}

			template<typename TElem>
			std::multiset<TElem> build(std::shared_ptr<IRandomAccessEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::multiset<TElem>(container.begin(), container.end());
			}
		};

		template<typename TLess>
		class _ToMultiSetWithLessBuilder
		{
		private:
			TLess _less;
		public:
			_ToMultiSetWithLessBuilder(TLess less) : _less(less) {}

			template<typename TElem>
			std::multiset<TElem, TLess> build(std::shared_ptr<IEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::multiset<TElem, TLess>(container.begin(), container.end(), _less);
			}

			template<typename TElem>
			std::multiset<TElem, TLess> build(std::shared_ptr<IBidirectionalEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::multiset<TElem, TLess>(container.begin(), container.end(), _less);
			}

			template<typename TElem>
			std::multiset<TElem, TLess> build(std::shared_ptr<IRandomAccessEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::multiset<TElem, TLess>(container.begin(), container.end(), _less);
			}
		};

		template<typename TKeySelector, typename TValueSelector>
		class _ToMapBuilder
		{
		private:
			TKeySelector _keySelector;
			TValueSelector _valueSelector;
		public:
			_ToMapBuilder(TKeySelector keySelector, TValueSelector valueSelector) : _keySelector(keySelector), _valueSelector(valueSelector) {}

			template<typename TElem>
			auto build(std::shared_ptr<IEnumerable<TElem>> enumerable) -> std::map<typename unaryreturntype<TKeySelector, TElem>::type, typename unaryreturntype<TValueSelector, TElem>::type>
			{
				typedef typename unaryreturntype<TKeySelector, TElem>::type TKey;
				typedef typename unaryreturntype<TValueSelector, TElem>::type TValue;
				auto container = enumerable >> select([this](TElem val) { return std::pair<TKey, TValue>(this->_keySelector(val), this->_valueSelector(val)); }) >> stl();
				return std::map<TKey, TValue>(container.begin(), container.end());
			}

			template<typename TElem>
			auto build(std::shared_ptr<IBidirectionalEnumerable<TElem>> enumerable) -> std::map<typename unaryreturntype<TKeySelector, TElem>::type, typename unaryreturntype<TValueSelector, TElem>::type>
			{
				typedef typename unaryreturntype<TKeySelector, TElem>::type TKey;
				typedef typename unaryreturntype<TValueSelector, TElem>::type TValue;
				auto container = enumerable >> select([this](TElem val) { return std::pair<TKey, TValue>(this->_keySelector(val), this->_valueSelector(val)); }) >> stl();
				return std::map<TKey, TValue>(container.begin(), container.end());
			}

			template<typename TElem>
			auto build(std::shared_ptr<IRandomAccessEnumerable<TElem>> enumerable) -> std::map<typename unaryreturntype<TKeySelector, TElem>::type, typename unaryreturntype<TValueSelector, TElem>::type>
			{
				typedef typename unaryreturntype<TKeySelector, TElem>::type TKey;
				typedef typename unaryreturntype<TValueSelector, TElem>::type TValue;
				auto container = enumerable >> select([this](TElem val) { return std::pair<TKey, TValue>(this->_keySelector(val), this->_valueSelector(val)); }) >> stl();
				return std::map<TKey, TValue>(container.begin(), container.end());
			}
		};

		template<typename TKeySelector, typename TValueSelector, typename TLess>
		class _ToMapWithLessBuilder
		{
		private:
			TKeySelector _keySelector;
			TValueSelector _valueSelector;
			TLess _less;
		public:
			_ToMapWithLessBuilder(TKeySelector keySelector, TValueSelector valueSelector, TLess less) : _keySelector(keySelector), _valueSelector(valueSelector), _less(less) {}

			template<typename TElem>
			auto build(std::shared_ptr<IEnumerable<TElem>> enumerable) -> std::map<typename unaryreturntype<TKeySelector, TElem>::type, typename unaryreturntype<TValueSelector, TElem>::type, TLess>
			{
				typedef typename unaryreturntype<TKeySelector, TElem>::type TKey;
				typedef typename unaryreturntype<TValueSelector, TElem>::type TValue;
				auto container = enumerable >> select([this](TElem val) { return std::pair<TKey, TValue>(this->_keySelector(val), this->_valueSelector(val)); }) >> stl();
				return std::map<TKey, TValue, TLess>(container.begin(), container.end(), _less);
			}

			template<typename TElem>
			auto build(std::shared_ptr<IBidirectionalEnumerable<TElem>> enumerable) -> std::map<typename unaryreturntype<TKeySelector, TElem>::type, typename unaryreturntype<TValueSelector, TElem>::type, TLess>
			{
				typedef typename unaryreturntype<TKeySelector, TElem>::type TKey;
				typedef typename unaryreturntype<TValueSelector, TElem>::type TValue;
				auto container = enumerable >> select([this](TElem val) { return std::pair<TKey, TValue>(this->_keySelector(val), this->_valueSelector(val)); }) >> stl();
				return std::map<TKey, TValue, TLess>(container.begin(), container.end(), _less);
			}

			template<typename TElem>
			auto build(std::shared_ptr<IRandomAccessEnumerable<TElem>> enumerable) -> std::map<typename unaryreturntype<TKeySelector, TElem>::type, typename unaryreturntype<TValueSelector, TElem>::type, TLess>
			{
				typedef typename unaryreturntype<TKeySelector, TElem>::type TKey;
				typedef typename unaryreturntype<TValueSelector, TElem>::type TValue;
				auto container = enumerable >> select([this](TElem val) { return std::pair<TKey, TValue>(this->_keySelector(val), this->_valueSelector(val)); }) >> stl();
				return std::map<TKey, TValue, TLess>(container.begin(), container.end(), _less);
			}
		};

		class _ToUnorderedSetBuilder
		{
		public:
			template<typename TElem>
			std::unordered_set<TElem> build(std::shared_ptr<IEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::unordered_set<TElem>(container.begin(), container.end());
			}

			template<typename TElem>
			std::unordered_set<TElem> build(std::shared_ptr<IBidirectionalEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::unordered_set<TElem>(container.begin(), container.end());
			}

			template<typename TElem>
			std::unordered_set<TElem> build(std::shared_ptr<IRandomAccessEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::unordered_set<TElem>(container.begin(), container.end());
			}
		};

		template<typename THasher, typename TEqComp>
		class _ToUnorderedSetFullBuilder
		{
		private:
			const int default_buckets = 8;
			THasher _hasher;
			TEqComp _eqComp;

		public:
			_ToUnorderedSetFullBuilder(THasher hasher, TEqComp eqComp) : _hasher(hasher), _eqComp(eqComp) {}

			template<typename TElem>
			std::unordered_set<TElem, THasher, TEqComp> build(std::shared_ptr<IEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::unordered_set<TElem, THasher, TEqComp>(container.begin(), container.end(), default_buckets, _hasher, _eqComp);
			}

			template<typename TElem>
			std::unordered_set<TElem, THasher, TEqComp> build(std::shared_ptr<IBidirectionalEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::unordered_set<TElem, THasher, TEqComp>(container.begin(), container.end(), default_buckets, _hasher, _eqComp);
			}

			template<typename TElem>
			std::unordered_set<TElem, THasher, TEqComp> build(std::shared_ptr<IRandomAccessEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::unordered_set<TElem, THasher, TEqComp>(container.begin(), container.end(), default_buckets, _hasher, _eqComp);
			}
		};

		class _ToUnorderedMultiSetBuilder
		{
		public:
			template<typename TElem>
			std::unordered_multiset<TElem> build(std::shared_ptr<IEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::unordered_multiset<TElem>(container.begin(), container.end());
			}

			template<typename TElem>
			std::unordered_multiset<TElem> build(std::shared_ptr<IBidirectionalEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::unordered_multiset<TElem>(container.begin(), container.end());
			}

			template<typename TElem>
			std::unordered_multiset<TElem> build(std::shared_ptr<IRandomAccessEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::unordered_multiset<TElem>(container.begin(), container.end());
			}
		};

		template<typename THasher, typename TEqComp>
		class _ToUnorderedMultiSetFullBuilder
		{
		private:
			const int default_buckets = 8;
			THasher _hasher;
			TEqComp _eqComp;

		public:
			_ToUnorderedMultiSetFullBuilder(THasher hasher, TEqComp eqComp) : _hasher(hasher), _eqComp(eqComp) {}

			template<typename TElem>
			std::unordered_multiset<TElem, THasher, TEqComp> build(std::shared_ptr<IEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::unordered_multiset<TElem, THasher, TEqComp>(container.begin(), container.end(), default_buckets, _hasher, _eqComp);
			}

			template<typename TElem>
			std::unordered_multiset<TElem, THasher, TEqComp> build(std::shared_ptr<IBidirectionalEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::unordered_multiset<TElem, THasher, TEqComp>(container.begin(), container.end(), default_buckets, _hasher, _eqComp);
			}

			template<typename TElem>
			std::unordered_multiset<TElem, THasher, TEqComp> build(std::shared_ptr<IRandomAccessEnumerable<TElem>> enumerable)
			{
				auto container = enumerable >> stl();
				return std::unordered_multiset<TElem, THasher, TEqComp>(container.begin(), container.end(), default_buckets, _hasher, _eqComp);
			}
		};

		template<typename TKeySelector, typename TValueSelector>
		class _ToUnorderedMapBuilder
		{
		private:
			TKeySelector _keySelector;
			TValueSelector _valueSelector;
		public:
			_ToUnorderedMapBuilder(TKeySelector keySelector, TValueSelector valueSelector) : _keySelector(keySelector), _valueSelector(valueSelector) {}

			template<typename TElem>
			auto build(std::shared_ptr<IEnumerable<TElem>> enumerable) -> std::unordered_map<typename unaryreturntype<TKeySelector, TElem>::type, typename unaryreturntype<TValueSelector, TElem>::type>
			{
				typedef typename unaryreturntype<TKeySelector, TElem>::type TKey;
				typedef typename unaryreturntype<TValueSelector, TElem>::type TValue;
				auto container = enumerable >> select([this](TElem val) { return std::pair<TKey, TValue>(this->_keySelector(val), this->_valueSelector(val)); }) >> stl();
				return std::unordered_map<TKey, TValue>(container.begin(), container.end());
			}

			template<typename TElem>
			auto build(std::shared_ptr<IBidirectionalEnumerable<TElem>> enumerable) -> std::unordered_map<typename unaryreturntype<TKeySelector, TElem>::type, typename unaryreturntype<TValueSelector, TElem>::type>
			{
				typedef typename unaryreturntype<TKeySelector, TElem>::type TKey;
				typedef typename unaryreturntype<TValueSelector, TElem>::type TValue;
				auto container = enumerable >> select([this](TElem val) { return std::pair<TKey, TValue>(this->_keySelector(val), this->_valueSelector(val)); }) >> stl();
				return std::unordered_map<TKey, TValue>(container.begin(), container.end());
			}

			template<typename TElem>
			auto build(std::shared_ptr<IRandomAccessEnumerable<TElem>> enumerable) -> std::unordered_map<typename unaryreturntype<TKeySelector, TElem>::type, typename unaryreturntype<TValueSelector, TElem>::type>
			{
				typedef typename unaryreturntype<TKeySelector, TElem>::type TKey;
				typedef typename unaryreturntype<TValueSelector, TElem>::type TValue;
				auto container = enumerable >> select([this](TElem val) { return std::pair<TKey, TValue>(this->_keySelector(val), this->_valueSelector(val)); }) >> stl();
				return std::unordered_map<TKey, TValue>(container.begin(), container.end());
			}
		};

		template<typename TKeySelector, typename TValueSelector, typename THasher, typename TEqComp>
		class _ToUnorderedMapFullBuilder
		{
		private:
			const int default_buckets = 8;
			TKeySelector _keySelector;
			TValueSelector _valueSelector;
			THasher _hasher;
			TEqComp _eqComp;
		public:
			_ToUnorderedMapFullBuilder(TKeySelector keySelector, TValueSelector valueSelector, THasher hasher, TEqComp eqComp) : _keySelector(keySelector), _valueSelector(valueSelector), _hasher(hasher), _eqComp(eqComp) {}

			template<typename TElem>
			auto build(std::shared_ptr<IEnumerable<TElem>> enumerable) -> std::unordered_map<typename unaryreturntype<TKeySelector, TElem>::type, typename unaryreturntype<TValueSelector, TElem>::type, THasher, TEqComp>
			{
				typedef typename unaryreturntype<TKeySelector, TElem>::type TKey;
				typedef typename unaryreturntype<TValueSelector, TElem>::type TValue;
				auto container = enumerable >> select([this](TElem val) { return std::pair<TKey, TValue>(this->_keySelector(val), this->_valueSelector(val)); }) >> stl();
				return std::unordered_map<TKey, TValue, THasher, TEqComp>(container.begin(), container.end(), default_buckets, _hasher, _eqComp);
			}

			template<typename TElem>
			auto build(std::shared_ptr<IBidirectionalEnumerable<TElem>> enumerable) -> std::unordered_map<typename unaryreturntype<TKeySelector, TElem>::type, typename unaryreturntype<TValueSelector, TElem>::type, THasher, TEqComp>
			{
				typedef typename unaryreturntype<TKeySelector, TElem>::type TKey;
				typedef typename unaryreturntype<TValueSelector, TElem>::type TValue;
				auto container = enumerable >> select([this](TElem val) { return std::pair<TKey, TValue>(this->_keySelector(val), this->_valueSelector(val)); }) >> stl();
				return std::unordered_map<TKey, TValue, THasher, TEqComp>(container.begin(), container.end(), default_buckets, _hasher, _eqComp);
			}

			template<typename TElem>
			auto build(std::shared_ptr<IRandomAccessEnumerable<TElem>> enumerable) -> std::unordered_map<typename unaryreturntype<TKeySelector, TElem>::type, typename unaryreturntype<TValueSelector, TElem>::type, THasher, TEqComp>
			{
				typedef typename unaryreturntype<TKeySelector, TElem>::type TKey;
				typedef typename unaryreturntype<TValueSelector, TElem>::type TValue;
				auto container = enumerable >> select([this](TElem val) { return std::pair<TKey, TValue>(this->_keySelector(val), this->_valueSelector(val)); }) >> stl();
				return std::unordered_map<TKey, TValue, THasher, TEqComp>(container.begin(), container.end(), default_buckets, _hasher, _eqComp);
			}
		};
	}
	/*@endcond*/

	/**
	*	Converts IEnumerable to STL vector.
	*	This function allows to gather all enumerable elements to STL vector.
	*	@return to_vector expression builder
	*/
	XLINQ_INLINE internal::_ToVectorBuilder to_vector()
	{
		return internal::_ToVectorBuilder();
	}

	/**
	*	Converts IEnumerable to STL list.
	*	This function allows to gather all enumerable elements to STL list.
	*	@return to_list expression builder
	*/
	XLINQ_INLINE internal::_ToListBuilder to_list()
	{
		return internal::_ToListBuilder();
	}

	/**
	*	Converts IEnumerable to STL forward list.
	*	This function allows to gather all enumerable elements to STL forward list.
	*	@return to_forward_list expression builder
	*/
	XLINQ_INLINE internal::_ToForwardListBuilder to_forward_list()
	{
		return internal::_ToForwardListBuilder();
	}

	/**
	*	Converts IEnumerable to STL set.
	*	This function allows to gather all enumerable elements to STL set.
	*	@return to_set expression builder
	*/
	XLINQ_INLINE internal::_ToSetBuilder to_set()
	{
		return internal::_ToSetBuilder();
	}

	/**
	*	Converts IEnumerable to STL set with specified comparer.
	*	This function allows to gather all enumerable elements to STL set.
	*	@param less Less than comparer.
	*	@return to_set expression builder
	*/
	template<typename TLess>
	XLINQ_INLINE internal::_ToSetWithLessBuilder<TLess> to_set(TLess less)
	{
		return internal::_ToSetWithLessBuilder<TLess>(less);
	}

	/**
	*	Converts IEnumerable to STL multiset.
	*	This function allows to gather all enumerable elements to STL multiset.
	*	@return to_multiset expression builder
	*/
	XLINQ_INLINE internal::_ToMultiSetBuilder to_multiset()
	{
		return internal::_ToMultiSetBuilder();
	}

	/**
	*	Converts IEnumerable to STL multiset with specified comparer.
	*	This function allows to gather all enumerable elements to STL multiset.
	*	@param less Less than comparer.
	*	@return to_multiset expression builder
	*/
	template<typename TLess>
	XLINQ_INLINE internal::_ToMultiSetWithLessBuilder<TLess> to_multiset(TLess less)
	{
		return internal::_ToMultiSetWithLessBuilder<TLess>(less);
	}

	/**
	*	Converts IEnumerable to STL map.
	*	This function allows to gather all enumerable elements to STL map.
	*	@param keySelector selector of key from element
	*	@param valueSelector selector of value from element
	*	@return to_map expression builder
	*/
	template<typename TKeySelector, typename TValueSelector>
	XLINQ_INLINE internal::_ToMapBuilder<TKeySelector, TValueSelector> to_map(TKeySelector keySelector, TValueSelector valueSelector)
	{
		return internal::_ToMapBuilder<TKeySelector, TValueSelector>(keySelector, valueSelector);
	}

	/**
	*	Converts IEnumerable to STL map with specified comparer.
	*	This function allows to gather all enumerable elements to STL map.
	*	@param keySelector selector of key from element
	*	@param valueSelector selector of value from element
	*	@param less Less than comparer.
	*	@return to_map expression builder
	*/
	template<typename TKeySelector, typename TValueSelector, typename TLess>
	XLINQ_INLINE internal::_ToMapWithLessBuilder<TKeySelector, TValueSelector, TLess> to_map(TKeySelector keySelector, TValueSelector valueSelector, TLess less)
	{
		return internal::_ToMapWithLessBuilder<TKeySelector, TValueSelector, TLess>(keySelector, valueSelector, less);
	}

	/**
	*	Converts IEnumerable to STL unordered set.
	*	This function allows to gather all enumerable elements to STL unordered set.
	*	@return to_unordered_set expression builder
	*/
	XLINQ_INLINE internal::_ToUnorderedSetBuilder to_unordered_set()
	{
		return internal::_ToUnorderedSetBuilder();
	}

	/**
	*	Converts IEnumerable to STL unordered set with specified hasher and comparer.
	*	This function allows to gather all enumerable elements to STL unordered set.
	*	@param hasher Hasher of elements.
	*	@param comparer Equality comparer of elements.
	*	@return to_unordered_set expression builder
	*/
	template<typename THasher, typename TEqComp>
	XLINQ_INLINE internal::_ToUnorderedSetFullBuilder<THasher, TEqComp> to_unordered_set(THasher hasher, TEqComp comparer)
	{
		return internal::_ToUnorderedSetFullBuilder<THasher, TEqComp>(hasher, comparer);
	}

	/**
	*	Converts IEnumerable to STL unordered multiset.
	*	This function allows to gather all enumerable elements to STL unordered multiset.
	*	@return to_unordered_multiset expression builder
	*/
	XLINQ_INLINE internal::_ToUnorderedMultiSetBuilder to_unordered_multiset()
	{
		return internal::_ToUnorderedMultiSetBuilder();
	}

	/**
	*	Converts IEnumerable to STL unordered multiset with specified hasher and comparer.
	*	This function allows to gather all enumerable elements to STL unordered multiset.
	*	@param hasher Hasher of elements.
	*	@param comparer Equality comparer of elements.
	*	@return to_unordered_multiset expression builder
	*/
	template<typename THasher, typename TEqComp>
	XLINQ_INLINE internal::_ToUnorderedMultiSetFullBuilder<THasher, TEqComp> to_unordered_multiset(THasher hasher, TEqComp comparer)
	{
		return internal::_ToUnorderedMultiSetFullBuilder<THasher, TEqComp>(hasher, comparer);
	}

	/**
	*	Converts IEnumerable to STL unordered map.
	*	This function allows to gather all enumerable elements to STL unordered map.
	*	@param keySelector selector of key from element
	*	@param valueSelector selector of value from element
	*	@return to_unordered_map expression builder
	*/
	template<typename TKeySelector, typename TValueSelector>
	XLINQ_INLINE internal::_ToUnorderedMapBuilder<TKeySelector, TValueSelector> to_unordered_map(TKeySelector keySelector, TValueSelector valueSelector)
	{
		return internal::_ToUnorderedMapBuilder<TKeySelector, TValueSelector>(keySelector, valueSelector);
	}

	/**
	*	Converts IEnumerable to STL map with specified comparer.
	*	This function allows to gather all enumerable elements to STL map.
	*	@param keySelector selector of key from element
	*	@param valueSelector selector of value from element
	*	@param hasher Hasher of elements.
	*	@param comparer Equality comparer of elements.
	*	@return to_unordered_map expression builder
	*/
	template<typename TKeySelector, typename TValueSelector, typename THasher, typename TEqComp>
	XLINQ_INLINE internal::_ToUnorderedMapFullBuilder<TKeySelector, TValueSelector, THasher, TEqComp> to_unordered_map(TKeySelector keySelector, TValueSelector valueSelector, THasher hasher, TEqComp comparer)
	{
		return internal::_ToUnorderedMapFullBuilder<TKeySelector, TValueSelector, THasher, TEqComp>(keySelector, valueSelector, hasher, comparer);
	}
}

#endif