VLOG -- проект по логгированию действий в программах.
Для начала логгирования необходимо включить
#define "vlog.h"

Логгирование производится через макросы:
VTRACE
VDEBUG
VRUNLOG
VWARNING
VFATAL

Действуют интерфейсы потоков, а также перегружен оператор () с произвольным 
количеством аргументов. 

Т.е. разрешены такие конструкции как:
int ii; 
double dd; 
string ss; 
float ff;
chrono::milliseconds ms;

VTRACE( "text", ii, dd, ss, ms );
VDEBUG ("text")(ii)(dd, ss)(ms);
VRUNLOG << "text" << ii << dd << ss << ms;


Действуют все стандартные модификаторы, часть из них вынесена в отдельные методы:
VWARNING.max_presicion()(dd).presicion(4)(ff).hex()(ii)(std::oct, ii)

Действует модификатор vcat::space, vcat::nospace, включающий пробелы между аргументами.
Питом он ВКЛЮЧЕН ПО УМОЛЧАНИЮ. Также есть соответствующие методы:
VFATAL.nospace()("Filename '", fname, "' does not exists!"); 
В примере выше, если не выключить пробелы, имя файла окажется не в кавычках, 
будут пробелы между ними.



Для любителей есть файл включения "vlog_pretty.h", повторяющий те же макросы 
в нижнем регистре. Также в нем содержится класс VLogError : public std::exception, 
который можно использовать для бросания исключений:

if ( some_error )
    throw VLogError( vfatal << "Some problem" );
    
Метод what(), кроме сообщения, будет содержать точку, где было брошено исключение в виде:
[source.cpp:42] >> "Some problem";


