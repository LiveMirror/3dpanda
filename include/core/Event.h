////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// Author:  htz
// Created: 2010-11-8 2:30:08
// Describe:ÊÂ¼þ
////////////////////////////////////////////////////////

#ifndef	_Tian_201011823008_H_
#define	_Tian_201011823008_H_

#include <list>

namespace panda
{
	class BaseNoUse
	{
	public:
		virtual ~BaseNoUse(){}
	};

	template<typename T, typename F>
	class Delegate;

	template<typename T>
	class Delegate<T, void()>
	{
		typedef void(T::*Fun)();
	public:
		Delegate(T* pRecver, Fun pFun)
		{
			_this = pRecver;
			_fun = pFun;
		}

		virtual void	CallFun()
		{
			(_this->*_fun)();
		}
	public:
		T*	_this;
		union
		{
			Fun		_fun;
			void*	_p;
		};
	};
	template<typename T>
	class Delegate<T, bool()>
	{
		typedef bool(T::*Fun)();
	public:
		Delegate(T* pRecver, Fun pFun)
		{
			_this = pRecver;
			_fun = pFun;
		}

		virtual bool	CallFun()
		{
			return (_this->*_fun)();
		}
	public:
		T*	_this;
		union
		{
			Fun		_fun;
			void*	_p;
		};
	};	

	template<typename T, typename P1>
	class Delegate<T, void(P1)>
	{
		typedef void(T::*Fun)(P1);
	public:
		Delegate(T* pRecver, Fun pFun)
		{
			_this = pRecver;
			_fun = pFun;
		}

		virtual void	CallFun(P1 p1)
		{
			(_this->*_fun)(p1);
		}
	public:
		T*	_this;
		union
		{
			Fun		_fun;
			void*	_p;
		};
	};
	template<typename T, typename P1>
	class Delegate<T, bool(P1)>
	{
		typedef bool(T::*Fun)(P1);
	public:
		Delegate(T* pRecver, Fun pFun)
		{
			_this = pRecver;
			_fun = pFun;
		}

		virtual bool	CallFun(P1 p1)
		{
			return (_this->*_fun)(p1);
		}
	public:
		T*	_this;
		union
		{
			Fun		_fun;
			void*	_p;
		};
	};

	template<typename T, typename P1, typename P2>
	class Delegate<T, void(P1, P2)>
	{
		typedef void(T::*Fun)(P1, P2);
	public:
		Delegate(T* pRecver, Fun pFun)
		{
			_this = pRecver;
			_fun = pFun;
		}

		virtual void	CallFun(P1 p1, P2 p2)
		{
			(_this->*_fun)(p1, p2);
		}
	public:
		T*	_this;
		union
		{
			Fun		_fun;
			void*	_p;
		};
	};

	template<typename T, typename P1, typename P2>
	class Delegate<T, bool(P1, P2)>
	{
		typedef bool(T::*Fun)(P1, P2);
	public:
		Delegate(T* pRecver, Fun pFun)
		{
			_this = pRecver;
			_fun = pFun;
		}

		virtual bool	CallFun(P1 p1, P2 p2)
		{
			return (_this->*_fun)(p1, p2);
		}
	public:
		T*	_this;
		union
		{
			Fun		_fun;
			void*	_p;
		};
	};

	template<typename T, typename P1, typename P2, typename P3>
	class Delegate<T, void(P1, P2, P3)>
	{
		typedef void(T::*Fun)(P1, P2, P3);
	public:
		Delegate(T* pRecver, Fun pFun)
		{
			_this = pRecver;
			_fun = pFun;
		}

		virtual void	CallFun(P1 p1, P2 p2, P3 p3)
		{
			(_this->*_fun)(p1, p2, p3);
		}
	public:
		T*	_this;
		union
		{
			Fun		_fun;
			void*	_p;
		};
	};

    template<typename T, typename P1, typename P2, typename P3>
    class Delegate<T, bool(P1, P2, P3)>
    {
        typedef bool(T::*Fun)(P1, P2, P3);
    public:
        Delegate(T* pRecver, Fun pFun)
        {
            _this = pRecver;
            _fun = pFun;
        }

        virtual bool	CallFun(P1 p1, P2 p2, P3 p3)
        {
            return (_this->*_fun)(p1, p2, p3);
        }
    public:
        T*	_this;
        union
        {
            Fun		_fun;
            void*	_p;
        };
    };


	template<typename F>
	class Event;

	template<>
	class Event<void()>
	{
	public:
		typedef Delegate<BaseNoUse, void()> BaseDelegate;

        ~Event()
        {
            std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
            std::list<BaseDelegate*>::iterator itEnd = m_delegatList.end();
            while (it != itEnd)
            {
                delete (*it);
                it++;
            }
        }

		template<typename T>
		void Add(T* pRecever, void(T::*Fun)())
		{
			BaseDelegate* pD = (BaseDelegate*)(new Delegate<T, void()>(pRecever, Fun));
			m_delegatList.push_back(pD);
		}

		template<typename T>
		void Remove(T* pRecever, void(T::*Fun)())
		{
			std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
			for (; it != m_delegatList.end(); it++)
			{
				if ((T*)(*it)->_this == pRecever )
				{
					typedef void(T::*pFun)();
					union
					{
						pFun  _pFun;
						void* _pVoid;
					} temp;
					temp._pFun = Fun;

					if ((*it)->_p == temp._pVoid)
					{
						delete (*it);
						m_delegatList.erase(it);
						return;
					}
				}
			}
		}

		void operator ()()
		{
			std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
			for (;it != m_delegatList.end(); it++)
			{
				BaseDelegate* pDelegate = (*it);
				pDelegate->CallFun();
			}
		}

	public:
		std::list<BaseDelegate*>	m_delegatList;
	};

	template<>
	class Event<bool()>
	{
	public:
		typedef Delegate<BaseNoUse, bool()> BaseDelegate;

        ~Event()
        {
            std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
            std::list<BaseDelegate*>::iterator itEnd = m_delegatList.end();
            while (it != itEnd)
            {
                delete (*it);
                it++;
            }
        }

		template<typename T>
		void Add(T* pRecever, bool(T::*Fun)())
		{
			BaseDelegate* pD = (BaseDelegate*)(new Delegate<T, bool()>(pRecever, Fun));
			m_delegatList.push_back(pD);
		}

		template<typename T>
		void Remove(T* pRecever, bool(T::*Fun)())
		{
			std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
			for (; it != m_delegatList.end(); it++)
			{
				if ((T*)(*it)->_this == pRecever )
				{
					typedef bool(T::*pFun)();
					union
					{
						pFun  _pFun;
						void* _pVoid;
					} temp;
					temp._pFun = Fun;

					if ((*it)->_p == temp._pVoid)
					{
						delete (*it);
						m_delegatList.erase(it);
						return;
					}
				}
			}
		}

		void operator ()()
		{
			std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
			for (;it != m_delegatList.end(); it++)
			{
				BaseDelegate* pDelegate = (*it);
				if(!pDelegate->CallFun())
				{
					break;
				}
			}
		}

	public:
		std::list<BaseDelegate*>	m_delegatList;
	};
   
	template<typename P1>
	class Event<void(P1)>
	{
	public:
		typedef Delegate<BaseNoUse, void(P1)> BaseDelegate;

        ~Event()
        {
            std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
            std::list<BaseDelegate*>::iterator itEnd = m_delegatList.end();
            while (it != itEnd)
            {
                delete (*it);
                it++;
            }
        }


		template<typename T>
		void Add(T* pRecever, void(T::*Fun)(P1))
		{
			BaseDelegate* pD = (BaseDelegate*)(new Delegate<T, void(P1)>(pRecever, Fun));
			m_delegatList.push_back(pD);
		}

		template<typename T>
		void Remove(T* pRecever, void(T::*Fun)(P1))
		{
			std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
			for (; it != m_delegatList.end(); it++)
			{
				if ((T*)(*it)->_this == pRecever )
				{
					typedef void(T::*pFun)(P1);
					union
					{
						pFun  _pFun;
						void* _pVoid;
					} temp;
					temp._pFun = Fun;

					if ((*it)->_p == temp._pVoid)
					{
						delete (*it);
						m_delegatList.erase(it);
						return;
					}
				}
			}
		}

		void RemoveAll()
		{
			std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
			for (; it != m_delegatList.end(); it++)
			{
				delete (*it);
			}
			m_delegatList.clear();
		}

		void operator ()(P1 p1)
		{
			std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
			for (;it != m_delegatList.end(); it++)
			{
				BaseDelegate* pDelegate = (*it);
				pDelegate->CallFun(p1);
			}
		}

	public:
		std::list<BaseDelegate*>	m_delegatList;
	};

	template<typename P1>
	class Event<bool(P1)>
	{
	public:
		typedef Delegate<BaseNoUse, bool(P1)> BaseDelegate;
        
        ~Event()
        {
            std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
            std::list<BaseDelegate*>::iterator itEnd = m_delegatList.end();
            while (it != itEnd)
            {
                delete (*it);
                it++;
            }
        }


		template<typename T>
		void Add(T* pRecever, bool(T::*Fun)(P1))
		{
			BaseDelegate* pD = (BaseDelegate*)(new Delegate<T, bool(P1)>(pRecever, Fun));
			m_delegatList.push_back(pD);
		}

		template<typename T>
		void Remove(T* pRecever, bool(T::*Fun)(P1))
		{
			std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
			for (; it != m_delegatList.end(); it++)
			{
				if ((T*)(*it)->_this == pRecever )
				{
					typedef bool(T::*pFun)(P1);
					union
					{
						pFun  _pFun;
						void* _pVoid;
					} temp;
					temp._pFun = Fun;

					if ((*it)->_p == temp._pVoid)
					{
						delete (*it);
						m_delegatList.erase(it);
						return;
					}
				}
			}
        }

        void RemoveAll()
        {
            std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
            for (; it != m_delegatList.end(); it++)
            {
                delete (*it);
            }
            m_delegatList.clear();
        }

		void operator ()(P1 p1)
		{
			std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
			for (;it != m_delegatList.end(); it++)
			{
				BaseDelegate* pDelegate = (*it);
				if(!pDelegate->CallFun(p1))
				{
					break;
				}
			}
		}

	public:
		std::list<BaseDelegate*>	m_delegatList;
	};

	template<typename P1, typename P2>
	class Event<void(P1, P2)>
	{
	public:
		typedef Delegate<BaseNoUse, void(P1, P2)> BaseDelegate;

        ~Event()
        {
            std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
            std::list<BaseDelegate*>::iterator itEnd = m_delegatList.end();
            while (it != itEnd)
            {
                delete (*it);
                it++;
            }
        }


		template<typename T>
		void Add(T* pRecever, void(T::*Fun)(P1, P2))
		{
			BaseDelegate* pD = (BaseDelegate*)(new Delegate<T, void(P1, P2)>(pRecever, Fun));
			m_delegatList.push_back(pD);
		}

		template<typename T>
		void Remove(T* pRecever, void(T::*Fun)(P1, P2))
		{
			std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
			for (; it != m_delegatList.end(); it++)
			{
				if ((T*)(*it)->_this == pRecever )
				{
					typedef void(T::*pFun)(P1, P2);
					union
					{
						pFun  _pFun;
						void* _pVoid;
					} temp;
					temp._pFun = Fun;

					if ((*it)->_p == temp._pVoid)
					{
						delete (*it);
						m_delegatList.erase(it);
						return;
					}
				}
			}
		}

		void operator ()(P1 p1, P2 p2)
		{
			std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
			for (;it != m_delegatList.end(); it++)
			{
				BaseDelegate* pDelegate = (*it);
				pDelegate->CallFun(p1, p2);
			}
		}

	public:
		std::list<BaseDelegate*>	m_delegatList;
	};

	template<typename P1, typename P2>
	class Event<bool(P1, P2)>
	{
	public:
		typedef Delegate<BaseNoUse, bool(P1, P2)> BaseDelegate;

        ~Event()
        {
            std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
            std::list<BaseDelegate*>::iterator itEnd = m_delegatList.end();
            while (it != itEnd)
            {
                delete (*it);
                it++;
            }
        }


		template<typename T>
		void Add(T* pRecever, bool(T::*Fun)(P1, P2))
		{
			BaseDelegate* pD = (BaseDelegate*)(new Delegate<T, bool(P1, P2)>(pRecever, Fun));
			m_delegatList.push_back(pD);
		}

		template<typename T>
		void Remove(T* pRecever, bool(T::*Fun)(P1, P2))
		{
			std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
			for (; it != m_delegatList.end(); it++)
			{
				if ((T*)(*it)->_this == pRecever )
				{
					typedef bool(T::*pFun)(P1, P2);
					union
					{
						pFun  _pFun;
						void* _pVoid;
					} temp;
					temp._pFun = Fun;

					if ((*it)->_p == temp._pVoid)
					{
						delete (*it);
						m_delegatList.erase(it);
						return;
					}
				}
			}
		}

		void RemoveAll()
		{
			std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
			for (; it != m_delegatList.end(); it++)
			{
				delete (*it);
			}
			m_delegatList.clear();
		}

		void operator ()(P1 p1, P2 p2)
		{
			std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
			for (;it != m_delegatList.end(); it++)
			{
				BaseDelegate* pDelegate = (*it);
				if(!pDelegate->CallFun(p1, p2))
				{
					break;
				}
			}
		}

	public:
		std::list<BaseDelegate*>	m_delegatList;
	};


	template<typename P1, typename P2, typename P3>
	class Event<void(P1, P2, P3)>
	{
	public:
		typedef Delegate<BaseNoUse, void(P1, P2, P3)> BaseDelegate;

        ~Event()
        {
            std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
            std::list<BaseDelegate*>::iterator itEnd = m_delegatList.end();
            while (it != itEnd)
            {
                delete (*it);
                it++;
            }
        }


		template<typename T>
		void Add(T* pRecever, void(T::*Fun)(P1, P2, P3))
		{
			BaseDelegate* pD = (BaseDelegate*)(new Delegate<T, void(P1, P2, P3)>(pRecever, Fun));
			m_delegatList.push_back(pD);
		}

		template<typename T>
		void Remove(T* pRecever, void(T::*Fun)(P1, P2, P3))
		{
			std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
			for (; it != m_delegatList.end(); it++)
			{
				if ((T*)(*it)->_this == pRecever )
				{
					typedef void(T::*pFun)(P1, P2, P3);
					union
					{
						pFun  _pFun;
						void* _pVoid;
					} temp;
					temp._pFun = Fun;

					if ((*it)->_p == temp._pVoid)
					{
						delete (*it);
						m_delegatList.erase(it);
						return;
					}
				}
			}
		}

		void RemoveAll()
		{
			std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
			for (; it != m_delegatList.end(); it++)
			{
				delete (*it);
			}
			m_delegatList.clear();
		}

		void operator ()(P1 p1, P2 p2, P3 p3)
		{
			std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
			for (;it != m_delegatList.end(); it++)
			{
				BaseDelegate* pDelegate = (*it);
				pDelegate->CallFun(p1, p2, p3);
			}
		}

	public:
		std::list<BaseDelegate*>	m_delegatList;
	};

    template<typename P1, typename P2, typename P3>
    class Event<bool(P1, P2, P3)>
    {
    public:
        typedef Delegate<BaseNoUse, bool(P1, P2, P3)> BaseDelegate;

        ~Event()
        {
            std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
            std::list<BaseDelegate*>::iterator itEnd = m_delegatList.end();
            while (it != itEnd)
            {
                delete (*it);
                it++;
            }
        }


        template<typename T>
        void Add(T* pRecever, bool(T::*Fun)(P1, P2, P3))
        {
            BaseDelegate* pD = (BaseDelegate*)(new Delegate<T, bool(P1, P2, P3)>(pRecever, Fun));
            m_delegatList.push_back(pD);
        }

        template<typename T>
        void Remove(T* pRecever, bool(T::*Fun)(P1, P2, P3))
        {
            std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
            for (; it != m_delegatList.end(); it++)
            {
                if ((T*)(*it)->_this == pRecever )
                {
                    typedef bool(T::*pFun)(P1, P2, P3);
                    union
                    {
                        pFun  _pFun;
                        void* _pVoid;
                    } temp;
                    temp._pFun = Fun;

                    if ((*it)->_p == temp._pVoid)
                    {
                        delete (*it);
                        m_delegatList.erase(it);
                        return;
                    }
                }
            }
        }

		void RemoveAll()
		{
			std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
			for (; it != m_delegatList.end(); it++)
			{
				delete (*it);
			}
			m_delegatList.clear();
		}

        void operator ()(P1 p1, P2 p2, P3 p3)
        {
            std::list<BaseDelegate*>::iterator it = m_delegatList.begin();
            for (;it != m_delegatList.end(); it++)
            {
                BaseDelegate* pDelegate = (*it);
                if(!pDelegate->CallFun(p1, p2, p3))
                {
                    break;
                }
            }
        }

    public:
        std::list<BaseDelegate*>	m_delegatList;
    };
	
} // end namespace gui

#endif // end _Tian_201011823008_H_