Úkolem je vytvořit šablonu třídy, který bude implementovat generický index.

Implementovaná třída CIndex dostane při vytváření parametrem kolekci s posloupností prvků. Tuto posloupnost prvků bude indexovat. Posloupnost může být:

string - řetězec znaků (C++ string prvků typu char),
vector<T> - vektorem hodnot (nějakého typu T),
list<T> - seznamem hodnot (nějakého typu T).
Nad takto zaindexovanou posloupností chceme vyhledávat. Tedy zadáme nějakou posloupnost prvků (stejného typu) a chceme zjistit, zda ji indexovaná posloupnost někde obsahuje. Výsledkem bude množina pozic, kde je hledaná posloupnost nalezena.

Aby byla indexovací třída obecnější, je vylepšena ještě možností zadat vlastní porovnávač (nepovinný druhý generický parametr). Vyhledávání tedy nemusí probíhat na přesnou shodu, pomocí vlastního porovnávače můžeme zadat, že při porovnávání např. nerozlišujeme malá a velká písmena. Porovnávač bude mít podobu jakou mají porovnávače v STL: bude se jednat o funkci, funktor nebo C++11 lambda výraz, který pro dvojici prvků typu T v posloupnosti rozhodne, který je v požadovaném porovnání menší. Pokud porovnávač není zadán, použije pro porovnávání prvků operátor < platný pro ukládané hodnoty prvků.

Vlastní prvky v posloupnostech (prvky typu T) mohou být libovolné. Příkladem je znak (char), celé číslo (int) nebo řetězec (string). Obecně víte, že pro typ T jsou definované následující operace:

kopírování (operátorem = a kopírujícím konstruktorem),
porovnávání "menší než" operátorem < nebo dodaným komparátorem,
uvolňování (destruktor),
další operace mohou, ale nemusí být s typem T dostupné, tedy Vaše implementace se na ně obecně nemůže spolehnout. Pozor, nemusí být k dispozici implicitní konstruktor, operátor ==, operátor !=, ...
