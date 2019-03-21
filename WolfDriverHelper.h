// WolfDriverHelper.h
// version 1.1
// Risger 2018/2/12

///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <minwindef.h>
#include <initializer_list>
namespace WolfDH
{
	template<typename _type>
	bool SetInBetween(_type& target, const _type _min, const _type _max)
	{
		_type old = target;
		max(target, _min);
		min(target, _max);
		return target != old;
	}

	template<class T>
	class WFvector
	{
	public:
		WFvector(size_t capacity = 0)
			:m_array(), m_Size(), m_Capacity()
		{
			if (capacity == 0)
				capacity = 4;
			Reserve(capacity);
		}

		WFvector(std::initializer_list<T> _Ilist)
			:m_array(), m_Size(), m_Capacity()
		{
			*this = _Ilist;
		}
		WFvector& operator=(const std::initializer_list<T> _Ilist)
		{
			clear();
			Reserve(_Ilist.size());
			for (const T& ele : _Ilist)
				Add(ele);
			if(!m_Capacity)
				Reserve(4);
			return *this;
		}

		WFvector(const WFvector& wfv)
			:m_array(), m_Size(), m_Capacity()
		{
			*this = wfv;
		}
		WFvector<T>& operator=(const WFvector<T>& wfv)
		{
			clear();
			Reserve(wfv.size());
			for (size_t i = 0; i < wfv.size(); i++)
				Add(wfv[i]);
			return *this;
		}

		~WFvector()
		{
			clear();
		}

		size_t size() const
		{
			return m_Size;
		}

		size_t capacity() const
		{
			return m_Capacity;
		}

		size_t Add(const T&& value)
		{
			//NT_ASSERT(m_Size <= m_Capacity);
			if (m_Size == m_Capacity || !m_Capacity)
				Reserve(m_Capacity * 2 + 4);
			m_array[m_Size] = value;
			return m_Size++;
		}

		size_t Add(const T& value)
		{
			//NT_ASSERT(m_Size <= m_Capacity);
			if (m_Size >= m_Capacity || !m_Capacity)
				Reserve(m_Capacity * 2 + 4);
			m_array[m_Size] = value;
			return m_Size++;
		}

		T* begin()
		{
			return m_array;
		}

		const T* begin() const
		{
			return m_array;
		}

		T* end()
		{
			return m_array + m_Size;
		}

		const T* end() const
		{
			return m_array + m_Size;
		}
		void Resize(size_t sz)
		{
			if (sz > m_Capacity)
				Reserve(sz);
			m_Size = sz;
		}
		void Reserve(size_t capacity)
		{
			if (m_Capacity < capacity)
			{
				auto* p = Allocate(capacity);
				if (m_array)
				{
					for (size_t i = 0; i < m_Size; i++)
						p[i] = m_array[i];
					delete[] m_array;
				}
				m_array = p;
				m_Capacity = capacity;
			}
		}
		T& at(size_t pos)
		{
			return m_array[pos];
		}
		const T& at(size_t pos) const
		{
			return m_array[pos];
		}
		T& operator[](size_t pos)
		{
			return at(pos);
		}
		const T& operator[](size_t pos) const
		{
			return at(pos);
		}
		void clear()
		{
			if (m_array)
				delete[] m_array;
			m_array = nullptr;
			m_Size = 0;
			m_Capacity = 0;
		}
		T* data()
		{
			return m_array;
		}
	private:
		T * Allocate(size_t capacity) const
		{
			auto* array = new T[capacity];
			return array;
		}

		T* m_array;
		size_t m_Size;
		size_t m_Capacity;
	};

	template<typename _Key, typename _Data>
	struct _keyvalue
	{
		_Key key;
		_Data data;
	};

	template<class _Key, class _Data>
	class WFSimpleMap
	{
		WFvector<_keyvalue<_Key, _Data>> m_vec;
	public:
		WFSimpleMap() {};
		WFSimpleMap(std::initializer_list<_keyvalue<_Key, _Data>> _Ilist)
		{
			clear();
			for (auto& ele : _Ilist)
				(*this)[ele.key] = ele.data;
		}
		_Data& atpos(size_t pos)
		{
			static _Data dummy{};
			if (size() > pos)
				return m_vec[pos].data;
			return dummy;
		}

		_Data& operator[](_Key key)
		{
			for (size_t i = 0; i < m_vec.size(); i++)
			{
				if (m_vec[i].key == key)
					return m_vec[i].data;
			}
			_keyvalue<_Key, _Data> map{};
			map.key = key;
			auto pos = m_vec.Add(map);
			return m_vec[pos].data;
		}

		const _Data& operator[](_Key key) const
		{
			for (size_t i = 0; i < m_vec.size(); i++)
			{
				if (m_vec[i].key == key)
					return m_vec[i].data;
			}
			_keyvalue<_Key, _Data> map{};
			map.key = key;
			auto pos = m_vec.Add(map);
			return m_vec[pos].data;
		}
		auto size()
		{
			return m_vec.size();
		}
		_keyvalue<_Key, _Data>* begin()
		{
			return m_vec.begin();
		}
		_keyvalue<_Key, _Data>* end()
		{
			return m_vec.end();
		}
		void clear()
		{
			m_vec.clear();
		}
	};

	class WFstring
	{
	public:
		WFstring(const wchar_t* str = nullptr) :m_str()
		{
			*this = str;
		}
		WFstring(const WFstring& other) :m_str()
		{
			*this = other;
		}
		WFstring(WFstring&& other) :m_str()
		{
			*this = (WFstring&&)other;
		}
		WFstring& operator= (const wchar_t* str)
		{
			clear();
			m_str = Allocate(str);
			return *this;
		}
		WFstring& operator= (const WFstring& other)
		{
			clear();
			m_str = Allocate(other.m_str);
			return *this;
		}
		WFstring& operator=(WFstring&& other)
		{
			if (m_str == other.m_str)
				return *this;	//same pointer
			clear();
			m_str = other.m_str;
			other.m_str = nullptr;

			return *this;
		}
		bool operator==(const WFstring& other) const
		{
			return wcscmp(m_str, other.m_str) == 0;
		}
		bool operator==(const wchar_t* other) const
		{
			return wcscmp(m_str, other) == 0;
		}
		operator const wchar_t*() const
		{
			return m_str;
		}
		WFstring& operator+=(const WFstring& str)
		{
			auto szR = wcslen(str.m_str);
			auto szL = size();
			auto szT = szR + szL;
			auto strA = new wchar_t[szT + 1];
			if (m_str)
				wcscpy_s(strA, szT + 1, m_str);
			wcscat_s(strA, szT + 1, str.m_str);
			clear();
			m_str = strA;
			return *this;
		}
		friend WFstring operator+(const WFstring& wfl, const WFstring& wfr)
		{
			auto szL = wcslen(wfl.m_str);
			auto szR = wcslen(wfr.m_str);
			auto szT = szR + szL;
			auto strA = new wchar_t[szT + 1];
			if (wfl.m_str)
				wcscpy_s(strA, szT + 1, wfl.m_str);
			if (wfr.m_str)
				wcscat_s(strA, szT + 1, wfr.m_str);
			WFstring res(strA);
			delete[] strA;
			return res;
		}
		~WFstring()
		{
			clear();
		}
		//UNICODE_STRING* GetUnicodeString(PUNICODE_STRING pUnicodeWFstring);

		size_t size() const
		{
			if (!m_str)
				return 0;
			return wcslen(m_str);
		}
		void clear()
		{
			if (m_str)
				delete[] m_str;
			m_str = nullptr;
		}
		bool IsValid() const
		{
			return bool(m_str);
		}
		WFvector<char> toMultiByte(int cp)
		{
			auto sz = size();
			if (!sz)
				return WFvector<char>();
			WFvector<char> vC(sz * 2 + 2);
			WideCharToMultiByte(cp, 0, m_str, -1, vC.data(), int(sz * 2 + 2), NULL, NULL); // 950 for big5
			vC.Resize(strlen(vC.data()));
			return vC;
		}
		const wchar_t* c_str()
		{
			return m_str;
		}
		WFstring substr(size_t left, size_t right = 0)
		{
			if(!right && left < size())
				return &m_str[left];
			if (left <= right && right < size())
			{
				WFstring result = &m_str[left];
				result.m_str[right - left + 1] = NULL;
				return result;
			}
			return WFstring();
		}
		int find(size_t start, wchar_t* str)
		{
			if (start > size())
				return -1;
			auto p = wcsstr(&m_str[start], str);
			if (p)
				return int(p - m_str);
			else
				return -1;
		}
		WFvector<WFstring> Tokenize(wchar_t* sp)
		{
			WFvector<WFstring> result;
			if (!m_str)
				return result;
			int iStart = 0;
			int schlen = int(wcslen(sp));
			int iNext = find(iStart, sp);
			if (iNext < 0)
			{
				result.Add(*this);
				return result;
			}
			result.Add(substr(iStart, iNext - 1));
			iStart = iNext + schlen;
			do
			{
				iNext = find(iStart, sp);
				if (iNext >= 0)
				{
					result.Add(substr(iStart, iNext - 1));
					iStart = iNext + schlen;
				}
				else
					result.Add(substr(iStart));
			} while (iNext >= 0);
			return result;
		}
		const wchar_t* data()
		{
			return m_str;
		}
	private:
		static wchar_t* Allocate(const wchar_t* src)
		{
			if (!src)
				return nullptr;
			auto size = wcslen(src);
			auto str = new wchar_t[size + 1];
			if (!str)
				return nullptr;
			if (src)
				memcpy(str, src, 2 * size);
			str[size] = 0;
			return str;
		}

		wchar_t* m_str;
	public:
		static WFstring to_string(int i)
		{
			wchar_t buf[32];
			_itot_s(i, buf, 10);
			return WFstring(buf);
		}
	};

	class WFcstring
	{
	public:
		WFcstring(const char* str = nullptr) :m_str()
		{
			*this = str;
		}
		WFcstring(const WFcstring& other) :m_str()
		{
			*this = other;
		}
		WFcstring(WFcstring&& other) :m_str()
		{
			*this = (WFcstring&&)other;
		}
		WFcstring& operator= (const char* str)
		{
			clear();
			m_str = Allocate(str);
			return *this;
		}
		WFcstring& operator= (const WFcstring& other)
		{
			clear();
			m_str = Allocate(other.m_str);
			return *this;
		}
		WFcstring& operator=(WFcstring&& other)
		{
			if (m_str == other.m_str)
				return *this;	//same pointer
			clear();
			m_str = other.m_str;
			other.m_str = nullptr;

			return *this;
		}
		bool operator==(const WFcstring& other) const
		{
			return strcmp(m_str, other.m_str) == 0;
		}
		bool operator==(const char* other) const
		{
			return strcmp(m_str, other) == 0;
		}
		operator const char*() const
		{
			return m_str;
		}
		WFcstring& operator+=(const WFcstring& str)
		{
			auto szR = strlen(str.m_str);
			auto szL = size();
			auto szT = szR + szL;
			auto strA = new char[szT + 1];
			if (m_str)
				strcpy_s(strA, szT + 1, m_str);
			strcat_s(strA, szT + 1, str.m_str);
			clear();
			m_str = strA;
			return *this;
		}
		friend WFcstring operator+(const WFcstring& wfl, const WFcstring& wfr)
		{
			auto szL = strlen(wfl.m_str);
			auto szR = strlen(wfr.m_str);
			auto szT = szR + szL;
			auto strA = new char[szT + 1];
			if (wfl.m_str)
				strcpy_s(strA, szT + 1, wfl.m_str);
			if (wfr.m_str)
				strcat_s(strA, szT + 1, wfr.m_str);
			WFcstring res(strA);
			delete[] strA;
			return res;
		}
		~WFcstring()
		{
			clear();
		}
		//UNICODE_STRING* GetUnicodeString(PUNICODE_STRING pUnicodeWFcstring);

		size_t size() const
		{
			if (!m_str)
				return 0;
			return strlen(m_str);
		}
		void clear()
		{
			if (m_str)
				delete[] m_str;
			m_str = nullptr;
		}
		bool IsValid() const
		{
			return bool(m_str);
		}

		const char* c_str()
		{
			return m_str;
		}
		WFcstring substr(size_t left, size_t right = 0)
		{
			if (!right && left < size())
				return &m_str[left];
			if (left <= right && right < size())
			{
				WFcstring result = &m_str[left];
				result.m_str[right - left + 1] = NULL;
				return result;
			}
			return WFcstring();
		}
		int find(size_t start, char* str)
		{
			if (start > size())
				return -1;
			auto p = strstr(&m_str[start], str);
			if (p)
				return int(p - m_str);
			else
				return -1;
		}
		WFvector<WFcstring> Tokenize(char* sp)
		{
			WFvector<WFcstring> result;
			if (!m_str)
				return result;
			int iStart = 0;
			int schlen = int(strlen(sp));
			int iNext = find(iStart, sp);
			if (iNext < 0)
			{
				result.Add(*this);
				return result;
			}
			result.Add(substr(iStart, iNext - 1));
			iStart = iNext + schlen;
			do
			{
				iNext = find(iStart, sp);
				if (iNext >= 0)
				{
					result.Add(substr(iStart, iNext - 1));
					iStart = iNext + schlen;
				}
				else
					result.Add(substr(iStart));
			} while (iNext >= 0);
			return result;
		}
		const char* data()
		{
			return m_str;
		}
	private:
		char* Allocate(const char* src)
		{
			if (!src)
				return nullptr;
			auto size = strlen(src);
			auto str = new char[size + 1];
			if (!str)
				return nullptr;
			if (src)
				memcpy(str, src, size);
			str[size] = 0;
			return str;
		}

		char* m_str;
	public:
		static WFcstring to_string(int i)
		{
			char buf[32];
			_itoa_s(i, buf, 10);
			return WFcstring(buf);
		}
	};
}