template <class T>
struct CLess{
	inline bool operator()(T a, T b){return a<b;};
};
template <class T>
struct CGreater{
	inline bool operator()(T a, T b){return a>b;};
};
// +++++++++  CLASS NODE ++++++++++++++++++
template <class T>
struct CNode{
		CNode(T x){ m_Data = x; m_Next=m_Prev=this;};
		~CNode(){};
		T m_Data;
		CNode<T> *m_Next;
		CNode<T> *m_Prev;
};
// +++++++++  CLASS LINKED LIST ++++++++++++++++++
template <class T, class C>
class CLinkedList{
public:
	CLinkedList();
	~CLinkedList();
	bool find(T x, CNode<T> **&p);
	bool insert(T x);
	bool remove(T x);
	bool is_empty();
	void print();
	void print_reversed();

	CNode<T> *m_Head;
	C m_cmp;
};

template <class T, class C>
CLinkedList<T, C>::CLinkedList(){
	m_Head = 0;
};
template <class T, class C>
CLinkedList<T, C>::~CLinkedList(){
	while(m_Head)
		remove(m_Head->m_Data);
};
template <class T, class C>
bool CLinkedList<T, C>::is_empty(){
	return !m_Head ? 1: 0;
};

template <class T, class C>
bool CLinkedList<T, C>::find(T x, CNode<T> **&p){
	for(p=&m_Head; (*p)->m_Next != m_Head && m_cmp((*p)->m_Data, x); p=&(*p)->m_Next);
	if((*p)->m_Next == m_Head && m_cmp((*p)->m_Data, x))
		p=&(*p)->m_Next;
	return (*p)->m_Data == x;
};

template <class T, class C>
bool CLinkedList<T, C>::insert(T x){
	if(!m_Head){
		m_Head = new CNode<T>(x);
		return 1;
	}
	CNode<T> **p, *q;
	if(find(x, p))
		return 0;
	q = new CNode<T>(x);
	q->m_Prev = (*p)->m_Prev;
	q->m_Next = *p;
	if(p == &m_Head)
		(*p)->m_Prev->m_Next = q;
	(*p)->m_Prev = q;
	*p = q;
	return 1;
};

template <class T, class C>
bool CLinkedList<T, C>::remove(T x){
	CNode<T> **p, *q;
	if(m_Head && find(x, p)){
		q = *p;
		if(m_Head->m_Next == m_Head){
			m_Head = 0;
			delete q;
			return 1;
		}
		(*p)->m_Next->m_Prev = (*p)->m_Prev;
		(*p)->m_Prev->m_Next = (*p)->m_Next;
		if(p == &m_Head)
			*p = (*p)->m_Next;
			//*p == (*p)->m_Next;
		q = 0;
		delete q;
		return 1;
	}
	return 0;
};

template <class T, class C>
void CLinkedList<T, C>::print(){
	CNode<T> *p;
	if (!m_Head){
		cout << "empty list." << endl;
		return;
	}
	int i=0;
	for(p=m_Head ; p->m_Next != m_Head; p=(p->m_Next), i++)
		cout << i+1 <<" th: " << p << " dir :: " <<  p->m_Data << endl;
	cout << i+1 <<" th: " << p << " dir :: " <<  p->m_Data << endl;
	return;
};
template <class T, class C>
void CLinkedList<T, C>::print_reversed(){
	CNode<T> *p;
	if (!m_Head){
		cout << "empty list." << endl;
		return;
	}
	int i=0;
	for(p=m_Head->m_Prev; p->m_Prev != m_Head->m_Prev; p=(p->m_Prev), i++)
		cout << i+1 <<" th: " << p << " dir :: " <<  p->m_Data << endl;
	cout << i+1 <<" th: " << p << " dir :: " <<  p->m_Data << endl;
	return;
};