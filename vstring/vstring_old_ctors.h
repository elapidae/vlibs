//  Этот файл введен не от хорошей жизни, старые компиляторы не понимают применение
//  using std::string::string.
//  Поэтому, следует просто проксировать все нужные вызовы конструкторов базовому классу.

// Специально писать их не буду, давайте заявки.

// Ниже приведен список конструкторов для возможной перегрузки.
// http://www.cplusplus.com/reference/string/string/string/

// Реализован в основном.
//default (1)
//string();

// Реализован в основном.
//copy (2)
//string (const string& str);

//substring (3)
//string (const string& str, size_t pos, size_t len = npos);

//from c-string (4)
//string (const char* s);

//from buffer (5)
//string (const char* s, size_t n);

//fill (6)
//string (size_t n, char c);

//range (7)
//template <class InputIterator>
//  string  (InputIterator first, InputIterator last);

//initializer list (8)
//string (initializer_list<char> il);

// Реализован в основном.
//move (9)
//string (string&& str) noexcept;
